//
// Created by zhuyong.joe on 2024/11/24.
//
#include "AndroidFileLoader.h"

AndroidFileLoader::AndroidFileLoader(JNIEnv *env, jobject jFileLoader):env(env),jFileLoader(jFileLoader) {

}

AndroidFileLoader::~AndroidFileLoader() {

}

uint8_t *AndroidFileLoader::loadFile(std::string fileName) {
    jclass nativeGLViewClass = env->FindClass("org/joe/sample/NativeGLView");
    if (nativeGLViewClass == nullptr) {
        // Handle error
        return nullptr;
    }

    // Get the constructor method ID
    jmethodID constructor = env->GetMethodID(nativeGLViewClass, "<init>","(Landroid/content/Context;)V");
    if (constructor == nullptr) {
        // Handle error
        return nullptr;
    }

    // Locate the instance method `loadImage`
    jmethodID loadImageMethod = env->GetMethodID(
            nativeGLViewClass,
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
    env->DeleteLocalRef(nativeGLViewClass);

    return  buf;
}



