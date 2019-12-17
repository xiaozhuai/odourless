//
// Created by xiaozhuai on 2019/12/11.
//

#ifndef ODOURLESS_ALL_DSSTOREHELPER_H
#define ODOURLESS_ALL_DSSTOREHELPER_H

#include <string>


class DSStoreHelper {
public:
    static bool isDSStore(const std::string &path);

    static std::string makeCagePath(const std::string &path);

};


#endif //ODOURLESS_ALL_DSSTOREHELPER_H
