//
// Created by xiaozhuai on 2019/12/5.
//

#include "Log.h"
#include "Hook.h"
#include "strategy/asepsis_strategy.h"

extern "C" {
__attribute__ ((constructor)) static void init();
__attribute__ ((destructor)) static void deinit();
}

void init() {
    Log::init(CAGE_DIRECTORY_PATH "/inject.log");
    LOG("odourless-inject init");
    Hook::init();
    if (!apply_asepsis_strategy()) {
        LOGE("apply asepsis strategy failed!");
    }
}

void deinit() {
    LOG("odourless-inject deinit");
    cancel_asepsis_strategy();
    Hook::destroy();
    Log::destroy();
}