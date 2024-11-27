//
// Created by zhuyong.joe on 2024/7/4.
//

#ifndef JNI_COMMON_H
#define JNI_COMMON_H
#ifdef LLAMA_ENABLE_LOG
#include <android/log.h>
#else
#define __android_log_print(...)
#endif
#endif //JNI_COMMON_H
