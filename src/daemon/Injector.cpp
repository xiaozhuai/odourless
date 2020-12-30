#include "Injector.h"
#include "Log.h"
#include <dlfcn.h>
#include <csignal>

Injector::Injector() {
    frida_init();
    m_injector = frida_injector_new_inprocess();
}

Injector::~Injector() {
    frida_injector_close_sync(m_injector, nullptr, nullptr);
    g_object_unref(m_injector);
    frida_deinit();
}

bool Injector::inject(pid_t pid, const std::string &lib) {
    GError *error = nullptr;
    auto id = frida_injector_inject_library_file_sync(m_injector, pid, lib.c_str(), "agent_main", "", nullptr, &error);
    if (error != nullptr) {
        LOGE("inject failed, %s", error->message);
        g_error_free(error);
        return false;
    }
    LOGE("inject suc");
    return true;
}
