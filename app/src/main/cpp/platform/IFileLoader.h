//
// Created by zhuyong.joe on 2024/11/24.
//

#ifndef GRAFIKA_IFILELOADER_H
#define GRAFIKA_IFILELOADER_H

#include <string>
#include "stdint.h"

class IFileLoader {
public:
    virtual ~IFileLoader() = default;
    virtual uint8_t* loadFile(std::string fileName) = 0;
};
#endif //GRAFIKA_IFILELOADER_H
