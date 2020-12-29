#include "Injector.h"
#include "mach_inject.h"
#include "Log.h"

#include <dlfcn.h>
#include <csignal>

Injector::Injector(const std::string &bootstrapLib) {
    module = dlopen(bootstrapLib.c_str(), RTLD_NOW | RTLD_LOCAL);
    LOG("module: %p", module);

    if (!module) {
        LOGE("dlopen error: %s", dlerror());
        return;
    }

    bootstrapFunc = dlsym(module, "bootstrap");
    LOG("bootstrapFunc: %p", bootstrapFunc);

    if (!bootstrapFunc) {
        LOGE("could not locate bootstrapFunc");
        return;
    }
}

Injector::~Injector() {
    if (module) {
        dlclose(module);
        module = nullptr;
    }
}

int Injector::inject(pid_t pid, const std::string &lib) {
    if (!module || !bootstrapFunc) {
        LOGE("inject failed, module: %p, bootstrapFunc: %p", module, bootstrapFunc);
        return 1000;
    }
    return mach_inject((mach_inject_entry) bootstrapFunc, lib.c_str(), lib.size() + 1, pid, 0);
}
