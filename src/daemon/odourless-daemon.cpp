//
// Created by xiaozhuai on 2019/12/5.
//

#include "Injector.h"
#include "FileSystemHelper.h"
#include "ProcessHelper.h"
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

    signal(SIGINT, sigHandler);

    const std::string finderProcessPath = "/System/Library/CoreServices/Finder.app/Contents/MacOS/Finder";
    const std::string executableDirectory = ProcessHelper::getCurrentExecutableDirectory();
    const std::string bootstrapLib = executableDirectory + "/../lib/libbootstrap.dylib";
    const std::string injectLib = executableDirectory + "/../lib/libodourless-inject.dylib";

    if (getuid() > 0) {
        LOGE("please run me as root");
        return -1;
    }


    Injector inj(bootstrapLib);

    finderPid = ProcessHelper::getPidByProcessPath(finderProcessPath);
    if (!finderPid) {
        LOGE("process %s not found", finderProcessPath.c_str());
        return 0;
    }
    LOG("finder pid: %u", finderPid);

    // sleep for a while
    sleep(3);
    inj.inject(finderPid, injectLib);

    while (monitoring) {
        sleep(3);
        pid_t pid = ProcessHelper::getPidByProcessPath(finderProcessPath);
        if (pid != finderPid) {
            LOG("finder has restarted, pid: %u", finderPid);
            finderPid = pid;

            // sleep for a while
            sleep(3);
            inj.inject(finderPid, injectLib);
        }
    }

    Log::destroy();
    return 0;
}