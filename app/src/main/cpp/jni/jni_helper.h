#pragma once

#include <jni.h>
#include <pthread.h>
#include <string>

namespace xplay {
void deInitJavaVMEnv(JNIEnv* env);
bool ThreadAttachEnv(JNIEnv** env);
void ThreadDetachEnv(void *);
void SetJVM(JavaVM *javaVm);
JavaVM* GetJVM();
JNIEnv* GetEnv();
void string2Jstring(JNIEnv *env, const std::string &str, jstring &jstr);
void cstr2Jstring(JNIEnv *env, const char* str, size_t strLen, jstring &jstr);
jlong jlongFromPointer(void* ptr);
}
