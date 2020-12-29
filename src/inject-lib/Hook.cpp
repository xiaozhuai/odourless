//
// Created by xiaozhuai on 2019/12/11.
//

#include "Hook.h"

Hook *Hook::instance = nullptr;

void Hook::init() {
    if (instance == nullptr) {
        instance = new Hook();
    }
}

void Hook::destroy() {
    delete instance;
}

Hook::Hook() {
    gum_init_embedded();
    m_interceptor = gum_interceptor_obtain();
}

Hook::~Hook() {
    g_object_unref(m_interceptor);
    gum_deinit_embedded();
}
