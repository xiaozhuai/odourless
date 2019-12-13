//
// Created by xiaozhuai on 2019/12/11.
//

#ifndef ODOURLESS_ALL_LOG_H
#define ODOURLESS_ALL_LOG_H

#include "tinyformat.h"

#include <string>
#include <iostream>
#include <fstream>


class Log {
public:
    static void init();

    static void init(const std::string &logFile);

    static void destroy();

    static Log *getInstance();

    inline std::ostream &getStdout() { return m_stdout; }

private:
    Log();

    explicit Log(const std::string &logFile);

    static Log *instance;
    std::ostream &m_stdout;
    std::ofstream m_stdoutFStream;

};

#define LOG(fmt, ...)  do { tfm::format(Log::getInstance()->getStdout(), "I: " fmt "\n", ##__VA_ARGS__); Log::getInstance()->getStdout().flush(); } while(0)
#define LOGE(fmt, ...) do { tfm::format(Log::getInstance()->getStdout(), "E: " fmt "\n", ##__VA_ARGS__); Log::getInstance()->getStdout().flush(); } while(0)

#endif //ODOURLESS_ALL_LOG_H
