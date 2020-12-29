//
// Created by xiaozhuai on 2019/12/11.
//

#include "Log.h"

#include <fstream>

Log *Log::instance;

void Log::init(const std::string &logFile) {
    instance = new Log(logFile);
}

void Log::init() {
    instance = new Log();
}

void Log::destroy() {
    delete instance;
}

Log *Log::getInstance() {
    if (instance == nullptr) {
        Log::init();
    }
    return instance;
}

Log::Log()
        : m_stdout(std::cout) {}

Log::Log(const std::string &logFile)
        : m_stdoutFStream(logFile, std::ios::out | std::ios::trunc),
          m_stdout(m_stdoutFStream) {}
