#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include "frida-core.h"
#include <string>
#include <sys/types.h>

class Injector {
public:
    Injector();

    ~Injector();

    bool inject(pid_t pid, const std::string &lib);

private:
    FridaInjector *m_injector = nullptr;
};

#endif