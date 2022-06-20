//
// Created by xiaozhuai on 2019/12/11.
//

#include "DSStoreHelper.h"
#include "FileSystemHelper.h"
#include "OdourlessUtils.h"
#include "StringUtils.h"

bool DSStoreHelper::isDSStore(const std::string &path) {
    auto tokens = StringUtils::explode(path, "/");
    bool isDesktop =
            tokens[0].empty()
            && tokens[1] == "Users"
            && tokens[3] == "Desktop"
            && tokens[4] == ".DS_Store";
    return FileSystemHelper::getName(path) == ".DS_Store"
           && !StringUtils::startsWith(path, CAGE_DIRECTORY_PATH)
           && !isDesktop
           && path.find("/.Trashes/") == std::string::npos
           && path.find("/.Trash/") == std::string::npos;
}

std::string DSStoreHelper::makeCagePath(const std::string &path) {
    return std::string(CAGE_DIRECTORY_PATH) + FileSystemHelper::getDirectory(path) + "/_DS_Store";
}
