#ifndef _INJECTOR_H_
#define _INJECTOR_H_

#include <string>
#include <sys/types.h>

class Injector {
public:
    explicit Injector(const std::string &bootstrapLib);

    ~Injector();

    int inject(pid_t pid, const std::string &lib);

private:
    void *module = nullptr;
    void *bootstrapFunc = nullptr;
};

#endif