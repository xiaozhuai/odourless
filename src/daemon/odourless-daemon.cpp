//
// Created by xiaozhuai on 2019/12/5.
//

#include "Injector.h"
#include "FileSystemHelper.h"
#include "ProcessHelper.h"
#include "OdourlessUtils.h"
#include "Log.h"

#include <csignal>
#include <unistd.h>

pid_t finderPid = -1;
bool monitoring = true;

// TODO 监听文件夹删除,移动,拷贝,并在前缀文件夹中重现

void sigHandler(int sig) {
    if (sig == SIGINT) {
        monitoring = false;
    }
}

int main(int argc, char **argv) {
    Log::init(OdourlessUtils::getDaemonLogPath());

    if (getuid() > 0) {
        LOGE("please run me as root");
        return 1;
    }

    if (!FileSystemHelper::ensureDir(CAGE_DIRECTORY_PATH, 0777, true)) {
        LOGE("ensure cage directory \"%s\" failed!", CAGE_DIRECTORY_PATH);
        return 2;
    }

    if (!FileSystemHelper::chmod(CAGE_DIRECTORY_PATH, 0777)) {
        LOGE("chmod cage directory \"%s\" 0777 failed!", CAGE_DIRECTORY_PATH);
        return 3;
    }

    const std::string finderProcessPath = "/System/Library/CoreServices/Finder.app/Contents/MacOS/Finder";
    const std::string executableDirectory = ProcessHelper::getCurrentExecutableDirectory();
    const std::string bootstrapLib = FileSystemHelper::realpath(executableDirectory + "/../lib/libbootstrap.dylib");
    const std::string injectLib = FileSystemHelper::realpath(executableDirectory + "/../lib/libodourless-inject.dylib");

    Injector inj(bootstrapLib);

    signal(SIGINT, sigHandler);

    while (monitoring) {
        pid_t pid = ProcessHelper::getPidByProcessPath(finderProcessPath);
        if (pid == -1) {
            LOGE("finder not running, retrying...");
            sleep(3);
        } else {
            if (finderPid != pid) {
                if (finderPid == -1) {
                    LOG("finder pid: %u", pid);
                } else {
                    LOG("finder restarted, pid: %u", pid);
                }
                finderPid = pid;
                sleep(3);
                int err;
                if ((err = inj.inject(finderPid, injectLib)) != 0) {
                    LOGE("inject failed, error: %d", err);
                } else {
                    LOG("inject suc");
                }
            } else {
                sleep(3);
                // OK
            }
        }
    }

    Log::destroy();
    return 0;
}