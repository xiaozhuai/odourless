#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include <string>
#include <sys/types.h>

class Injector {
public:
    explicit Injector(const std::string &bootstrapLib);

    ~Injector();

    void inject(pid_t pid, const std::string &lib);

private:
    void *module;
    void *bootstrapFunc;
};

#endif