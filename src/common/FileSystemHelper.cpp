//
// Created by xiaozhuai on 2019/12/11.
//

#include "FileSystemHelper.h"

#include <cstdlib>
#include <climits>
#include <sys/stat.h>

std::string FileSystemHelper::realpath(const std::string &path) {
    char rpath[PATH_MAX];
    ::realpath(path.c_str(), rpath);
    return std::string(rpath);
}

std::string FileSystemHelper::getDirectory(const std::string &path) {
    auto pos = path.rfind('/');
    if (pos == std::string::npos) {
        return "";
    }
    auto directory = path.substr(0, pos);
    if (directory.empty()) {
        directory = "/";
    }
    return directory;
}

std::string FileSystemHelper::getName(const std::string &path) {
    auto pos = path.rfind('/');
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}

bool FileSystemHelper::ensureDir(const std::string &path, mode_t mode, bool recursive) {
    if (!recursive) {
        struct stat st{};
        if (::stat(path.c_str(), &st) != 0) {
            return ::mkdir(path.c_str(), mode) == 0;
        } else if (S_ISDIR(st.st_mode)) {
            return true;
        } else {
            return false;
        }
    } else {
        std::string::size_type pos = -1;
        while ((pos = path.find('/', pos + 1)) != std::string::npos) {
            if (pos == 0) continue;
            std::string parent = path.substr(0, pos);
            bool suc = ensureDir(parent, mode, false);
            if (!suc) return false;
        }
        bool suc = ensureDir(path, mode, false);
        return suc;
    }
}

bool FileSystemHelper::exists(const std::string &path) {
    struct stat st{};
    return ::stat(path.c_str(), &st) == 0;
}

bool FileSystemHelper::rename(const std::string &src, const std::string &dst) {
    return ::rename(src.c_str(), dst.c_str()) == 0;
}

bool FileSystemHelper::chmod(const std::string &path, int mode) {
    return ::chmod(path.c_str(), mode) == 0;
}
