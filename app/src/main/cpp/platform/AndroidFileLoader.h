//
// Created by zhuyong.joe on 2024/11/24.
//

#ifndef GRAFIKA_ANDROIDFILELOADER_H
#define GRAFIKA_ANDROIDFILELOADER_H

#include <jni.h>
#include "IFileLoader.h"

class AndroidFileLoader: public IFileLoader {
public:
    AndroidFileLoader(JNIEnv *env, jobject jFileLoader);
    ~AndroidFileLoader();
    uint8_t* loadFile(std::string fileName);
private:
    JNIEnv *env;
    jobject jFileLoader;
};

#endif //GRAFIKA_ANDROIDFILELOADER_H
