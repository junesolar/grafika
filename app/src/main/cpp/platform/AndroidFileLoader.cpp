//
// Created by zhuyong.joe on 2024/11/24.
//
#include "AndroidFileLoader.h"
#include "../service/service.h"
#include "jni_helper.h"

REGISTER_SERVICE(IFileLoader, AndroidFileLoader)

AndroidFileLoader::AndroidFileLoader() {

}

AndroidFileLoader::~AndroidFileLoader() {

}


void AndroidFileLoader::init(JNIEnv *env, jobject jService) {
    auto *inst = dynamic_cast<AndroidFileLoader *>(service::GetService<IFileLoader>());
    inst->jFileLoader = env->NewGlobalRef(jService);
}

uint8_t *AndroidFileLoader::loadFile(std::string fileName) {
    JNIEnv* env = xplay::GetEnv();
    jclass jFileLoaderService = env->FindClass("org/joe/sample/service/FileLoadService");
    if (jFileLoaderService == nullptr) {
        // Handle error
        return nullptr;
    }

    // Locate the instance method `loadImage`
    jmethodID loadImageMethod = env->GetMethodID(
            jFileLoaderService,
            "loadImage",
            "(Ljava/lang/String;)[B"
    );
    if (loadImageMethod == nullptr) {
        // Handle error
        return nullptr;
    }

    // Convert resName to a Java string
    jstring jResName = env->NewStringUTF(fileName.c_str());

    // Call the method
    jbyteArray imageByteArray = (jbyteArray) env->CallObjectMethod(
            jFileLoader,
            loadImageMethod,
            jResName
    );
    // Check and process the result
    if (imageByteArray == nullptr) {
        return nullptr;
    }

    int len = env->GetArrayLength (imageByteArray);
    uint8_t* buf = new uint8_t[len];
    env->GetByteArrayRegion(imageByteArray, 0, len, reinterpret_cast<jbyte*>(buf));

    // Clean up references
    env->DeleteLocalRef(jResName);
    env->DeleteLocalRef(jFileLoaderService);

    return  buf;
}

void FileLoaderOnLoad(JNIEnv* env) {
    jclass jFileloaderClass = env->FindClass("org/joe/sample/service/FileLoadService");
    const JNINativeMethod  methods[] = {
            JNI_METHOD_V(AndroidFileLoader::init, init, void())
    };
    constexpr int methodsSize = sizeof(methods) / sizeof(methods[0]);
    env->RegisterNatives(jFileloaderClass, methods, methodsSize);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }
    env->DeleteLocalRef(jFileloaderClass);
}



