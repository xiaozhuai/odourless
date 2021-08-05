//
// Created by xiaozhuai on 2019/12/11.
//

#include "asepsis_strategy.h"
#include "Log.h"
#include "FileSystemHelper.h"
#include "../Hook.h"
#include "../DSStoreHelper.h"

#include <fcntl.h>

typedef int (*open_t)(const char *path, int flags, mode_t mode);

typedef int (*openx_np_t)(const char *path, int flags, filesec_t fsec);

typedef int (*getattrlist_t)(const char *path, void *list, void *buf, size_t bufSize, unsigned int options);

typedef int (*setattrlist_t)(const char *path, void *list, void *buf, size_t bufSize, unsigned int options);


open_t real_open = nullptr;
openx_np_t real_openx_np = nullptr;
getattrlist_t real_getattrlist = nullptr;
setattrlist_t real_setattrlist = nullptr;


static int replacement_open(const char *path, int flags, mode_t mode) {
    std::string fakePath;
    if (DSStoreHelper::isDSStore(path)) {
        fakePath = DSStoreHelper::makeCagePath(path);
        if (FileSystemHelper::ensureDir(FileSystemHelper::getDirectory(fakePath), 0755, true)) {
            if (FileSystemHelper::exists(path) && !FileSystemHelper::exists(fakePath)) {
                FileSystemHelper::rename(path, fakePath);
            }
            LOG("open: %s ---> %s", path, fakePath);
            path = fakePath.c_str();
        }
    }
    return real_open(path, flags, mode);
}

static int replacement_openx_np(const char *path, int flags, filesec_t fsec) {
    std::string fakePath;
    if (DSStoreHelper::isDSStore(path)) {
        fakePath = DSStoreHelper::makeCagePath(path);
        if (FileSystemHelper::ensureDir(FileSystemHelper::getDirectory(fakePath), 0755, true)) {
            if (FileSystemHelper::exists(path) && !FileSystemHelper::exists(fakePath)) {
                FileSystemHelper::rename(path, fakePath);
            }
            LOG("openx_np: %s ---> %s", path, fakePath);
            path = fakePath.c_str();
        }
    }
    return real_openx_np(path, flags, fsec);
}

static int replacement_getattrlist(const char *path, void *list, void *buf, size_t bufSize, unsigned int options) {
    std::string fakePath;
    if (DSStoreHelper::isDSStore(path)) {
        fakePath = DSStoreHelper::makeCagePath(path);
        if (FileSystemHelper::ensureDir(FileSystemHelper::getDirectory(fakePath), 0755, true)) {
            if (FileSystemHelper::exists(path) && !FileSystemHelper::exists(fakePath)) {
                FileSystemHelper::rename(path, fakePath);
            }
            LOG("getattrlist: %s ---> %s", path, fakePath);
            path = fakePath.c_str();
        }
    }
    return real_getattrlist(path, list, buf, bufSize, options);
}

static int replacement_setattrlist(const char *path, void *list, void *buf, size_t bufSize, unsigned int options) {
    std::string fakePath;
    if (DSStoreHelper::isDSStore(path)) {
        fakePath = DSStoreHelper::makeCagePath(path);
        if (FileSystemHelper::ensureDir(FileSystemHelper::getDirectory(fakePath), 0755, true)) {
            if (FileSystemHelper::exists(path) && !FileSystemHelper::exists(fakePath)) {
                FileSystemHelper::rename(path, fakePath);
            }
            LOG("setattrlist: %s ---> %s", path, fakePath);
            path = fakePath.c_str();
        }
    }
    return real_setattrlist(path, list, buf, bufSize, options);
}

bool apply_asepsis_strategy() {
    real_open = Hook::getRealFunc<open_t>("open");
    real_openx_np = Hook::getRealFunc<openx_np_t>("openx_np");
    real_getattrlist = Hook::getRealFunc<getattrlist_t>("getattrlist");
    real_setattrlist = Hook::getRealFunc<setattrlist_t>("setattrlist");

    if (real_open == nullptr
        || real_openx_np == nullptr
        || real_getattrlist == nullptr
        || real_setattrlist == nullptr) {
        real_open = nullptr;
        real_openx_np = nullptr;
        real_getattrlist = nullptr;
        real_setattrlist = nullptr;
        return false;
    }

    bool suc;

    suc = Hook::replaceFunc<open_t>(real_open, replacement_open);
    if (!suc) {
        LOGE("replace \"open\" failed!");
        real_open = nullptr;
        cancel_asepsis_strategy();
        return false;
    }

    suc = Hook::replaceFunc<openx_np_t>(real_openx_np, replacement_openx_np);
    if (!suc) {
        LOGE("replace \"openx_np\" failed!");
        real_openx_np = nullptr;
        cancel_asepsis_strategy();
        return false;
    }

    suc = Hook::replaceFunc<getattrlist_t>(real_getattrlist, replacement_getattrlist);
    if (!suc) {
        LOGE("replace \"getattrlist\" failed!");
        real_getattrlist = nullptr;
        cancel_asepsis_strategy();
        return false;
    }

    suc = Hook::replaceFunc<setattrlist_t>(real_setattrlist, replacement_setattrlist);
    if (!suc) {
        LOGE("replace \"setattrlist\" failed!");
        real_setattrlist = nullptr;
        cancel_asepsis_strategy();
        return false;
    }

    return true;
}

void cancel_asepsis_strategy() {
    if (real_open != nullptr) {
        Hook::revertFunc<open_t>(real_open);
        real_open = nullptr;
    }
    if (real_openx_np != nullptr) {
        Hook::revertFunc<openx_np_t>(real_openx_np);
        real_openx_np = nullptr;
    }
    if (real_getattrlist != nullptr) {
        Hook::revertFunc<getattrlist_t>(real_getattrlist);
        real_getattrlist = nullptr;
    }
    if (real_setattrlist != nullptr) {
        Hook::revertFunc<setattrlist_t>(real_setattrlist);
        real_setattrlist = nullptr;
    }
}
