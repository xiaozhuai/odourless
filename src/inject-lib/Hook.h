//
// Created by xiaozhuai on 2019/12/11.
//

#ifndef ODOURLESS_HOOK_H
#define ODOURLESS_HOOK_H

#include "frida-gum.h"

#include <string>

class Hook {
public:
    static void init();

    static void destroy();

    template<typename T>
    static T getRealFunc(const std::string &moduleName, const std::string &funcName) {
        return (T) gum_module_find_export_by_name(moduleName.empty() ? nullptr : moduleName.c_str(), funcName.c_str());
    }

    template<typename T>
    static T getRealFunc(const std::string &funcName) {
        return (T) gum_module_find_export_by_name(nullptr, funcName.c_str());
    }

    template<typename T>
    static bool replaceFunc(T real, T replacement) {
        return gum_interceptor_replace(
                instance->m_interceptor,
                (gpointer) real,
                (gpointer) replacement,
                nullptr
        ) == GUM_REPLACE_OK;
    }

    template<typename T>
    static void revertFunc(T real) {
        gum_interceptor_revert(instance->m_interceptor, (gpointer) real);
    }

private:
    Hook();

    ~Hook();

private:
    static Hook *instance;
    GumInterceptor *m_interceptor;

};


#endif //ODOURLESS_HOOK_H
