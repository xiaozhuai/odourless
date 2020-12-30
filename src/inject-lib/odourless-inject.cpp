//
// Created by xiaozhuai on 2019/12/5.
//

#include "Log.h"
#include "Hook.h"
#include "OdourlessUtils.h"
#include "strategy/asepsis_strategy.h"

extern "C" {
void agent_main(const gchar *data, gboolean *stay_resident);
}

void agent_main(const gchar *data, gboolean *stay_resident) {
    *stay_resident = true;
    Log::init(OdourlessUtils::getInjectLogPath());
    LOG("odourless-inject init");
    Hook::init();
    if (!apply_asepsis_strategy()) {
        LOGE("apply asepsis strategy failed!");
    }
}

//void deinit() {
//    LOG("odourless-inject deinit");
//    cancel_asepsis_strategy();
//    Hook::destroy();
//    Log::destroy();
//}