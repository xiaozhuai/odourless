//
// Created by xiaozhuai on 2019/12/11.
//

#include "ProcessHelper.h"
#include "FileSystemHelper.h"

#include <array>
#include <unistd.h>
#include <libproc.h>
#include <sys/proc_info.h>
#include <mach-o/dyld.h>

std::vector<ProcessInfo> ProcessHelper::getProcessList() {
    std::vector<ProcessInfo> list;
    const int processCount = proc_listpids(PROC_ALL_PIDS, 0, nullptr, 0);
    pid_t pids[processCount];
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    for (int i = 0; i < processCount; ++i) {
        if (!pids[i]) continue;
        char curPath[PROC_PIDPATHINFO_MAXSIZE] = {0};
        proc_pidpath(pids[i], curPath, sizeof(curPath));
        std::string path = curPath;
        std::string name = FileSystemHelper::getName(path);
        list.emplace_back(ProcessInfo{
                .name =  std::move(name),
                .path =  std::move(path),
                .pid =  pids[i]
        });
    }
    return list;
}

pid_t ProcessHelper::getPidByProcessName(const std::string &name) {
    std::vector<ProcessInfo> list = getProcessList();
    for (auto &processInfo : list) {
        if (name == processInfo.name) {
            return processInfo.pid;
        }
    }
    return -1;
}

pid_t ProcessHelper::getPidByProcessPath(const std::string &path) {
    std::string rpath = FileSystemHelper::realpath(path);
    std::vector<ProcessInfo> list = getProcessList();
    for (auto &processInfo : list) {
        if (rpath == processInfo.path) {
            return processInfo.pid;
        }
    }
    return -1;
}

std::string ProcessHelper::getCurrentWorkspaceDirectory() {
    char directory[PATH_MAX];
    getcwd(directory, PATH_MAX);
    return std::string(directory);
}

std::string ProcessHelper::getCurrentExecutablePath() {
    uint32_t size = PATH_MAX;
    char path[size];
    _NSGetExecutablePath(path, &size);
    return FileSystemHelper::realpath(path);
}

std::string ProcessHelper::getCurrentExecutableDirectory() {
    return FileSystemHelper::getDirectory(getCurrentExecutablePath());
}

std::string ProcessHelper::getCurrentExecutableName() {
    return FileSystemHelper::getName(getCurrentExecutablePath());
}
