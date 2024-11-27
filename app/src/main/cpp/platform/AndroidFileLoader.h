//
// Created by zhuyong.joe on 2024/11/24.
//

#ifndef GRAFIKA_ANDROIDFILELOADER_H
#define GRAFIKA_ANDROIDFILELOADER_H

#include <jni.h>
#include "IFileLoader.h"
#include "jni_macro.h"

class AndroidFileLoader: public IFileLoader {
public:
    AndroidFileLoader();
    ~AndroidFileLoader();
    static void init(JNIEnv *env, jobject jService);
    uint8_t* loadFile(std::string fileName);
    jobject jFileLoader;
};

void FileLoaderOnLoad(JNIEnv* env);

#endif //GRAFIKA_ANDROIDFILELOADER_H
