//
// Created by xiaozhuai on 2019/12/11.
//

#ifndef ODOURLESS_PROCESSHELPER_H
#define ODOURLESS_PROCESSHELPER_H

#include <string>
#include <vector>
#include <sys/types.h>

typedef struct {
    std::string name;
    std::string path;
    pid_t pid;
} ProcessInfo;

class ProcessHelper {

public:
    static std::vector<ProcessInfo> getProcessList();

    static pid_t getPidByProcessName(const std::string &name);

    static pid_t getPidByProcessPath(const std::string &path);

    static std::string getCurrentWorkspaceDirectory();

    static std::string getCurrentExecutablePath();

    static std::string getCurrentApplicationPath();

    static std::string getCurrentExecutableDirectory();

    static std::string getCurrentExecutableName();
};


#endif //ODOURLESS_PROCESSHELPER_H
