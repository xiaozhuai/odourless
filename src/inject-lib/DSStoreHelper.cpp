//
// Created by xiaozhuai on 2019/12/11.
//

#include "DSStoreHelper.h"
#include "FileSystemHelper.h"

bool DSStoreHelper::isDSStore(const std::string &path) {
    return FileSystemHelper::getName(path) == ".DS_Store"
           && path.find(CAGE_DIRECTORY_PATH) != 0
           && path.find("/.Trashes/") == std::string::npos
           && path.find("/.Trash/") == std::string::npos;
}

std::string DSStoreHelper::makeCagePath(const std::string &path) {
    return std::string(CAGE_DIRECTORY_PATH) + FileSystemHelper::getDirectory(path) + "/_DS_Store";
}
