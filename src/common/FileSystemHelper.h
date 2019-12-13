//
// Created by xiaozhuai on 2019/12/11.
//

#ifndef ODOURLESS_FILESYSTEMHELPER_H
#define ODOURLESS_FILESYSTEMHELPER_H

#include <string>

class FileSystemHelper {
public:
    static std::string realpath(const std::string &path);

    static std::string getDirectory(const std::string &path);

    static std::string getName(const std::string &path);

    static bool ensureDir(const std::string &path, mode_t mode, bool recursive = false);

    static bool exists(const std::string &path);

    static bool rename(const std::string &src, const std::string &dst);

};


#endif //ODOURLESS_FILESYSTEMHELPER_H
