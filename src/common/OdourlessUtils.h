//
// Created by xiaozhuai on 2019/12/13.
//

#ifndef ODOURLESS_ODOURLESSUTILS_H
#define ODOURLESS_ODOURLESSUTILS_H

#include <string>

//#define ODOURLESS_INSTALL_PATH  "/Users/xiaozhuai/work/odourless/cmake-build-debug/Odourless.app"
//#define ODOURLESS_INSTALL_PATH  "/Applications/Odourless.app"

typedef struct {
    bool suc;
    int ret;
    std::string output;
} ExecResult;

class OdourlessUtils {

public:
    static bool checkSIPEnabled();

    static bool daemonInstalled();

    static bool daemonRunning();

    static ExecResult installDaemon();

    static ExecResult uninstallDaemon();

    static ExecResult startDaemon();

    static ExecResult stopDaemon();

    static ExecResult restartDaemon();

    static ExecResult shellExec(const std::string &shellPath, bool sudo);
};


#endif //ODOURLESS_ODOURLESSUTILS_H
