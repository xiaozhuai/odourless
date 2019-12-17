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

pid_t finderPid = 0;
bool monitoring = true;

void sigHandler(int sig) {
    if (sig == SIGINT) {
        monitoring = false;
    }
}

int main(int argc, char **argv) {
    Log::init();

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
    const std::string bootstrapLib = executableDirectory + "/../lib/libbootstrap.dylib";
    const std::string injectLib = executableDirectory + "/../lib/libodourless-inject.dylib";

    Injector inj(bootstrapLib);

    signal(SIGINT, sigHandler);

    while (monitoring) {
        pid_t pid = ProcessHelper::getPidByProcessPath(finderProcessPath);
        if (finderPid == 0) {
            if (pid != 0) {
                finderPid = pid;
                LOG("finder pid: %u", finderPid);

                sleep(3);
                inj.inject(finderPid, injectLib);
            } else {
                LOG("finder not running");
            }
        } else {
            if (pid != finderPid) {
                finderPid = pid;
                LOG("finder restarted, pid: %u", finderPid);

                sleep(3);
                inj.inject(finderPid, injectLib);
            }
        }

        sleep(3);
    }

    Log::destroy();
    return 0;
}