
#include "jni_helper.h"
#include "jni_common.h"
#include <assert.h>

namespace xplay {

JavaVM* g_jvm = nullptr;
pthread_key_t g_thread_key;
const char* kEventHandlerTagAndroid = "XplayJNI";

void SetJVM(JavaVM *javaVm) {
    g_jvm = javaVm;
    pthread_key_create(&g_thread_key, ThreadDetachEnv);
}

JavaVM* GetJVM() {
    return g_jvm;
}

JNIEnv* GetEnv() {
    JNIEnv* env = nullptr;
    JavaVM* jvm = GetJVM();

    if (jvm == nullptr) {
        return nullptr;
    }

    //query if need attach cur thread to env.
    int res = jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (res == JNI_OK) {
        return env;
    } else if(res == JNI_EDETACHED && ThreadAttachEnv((JNIEnv **) &env)) {
        return env;
    } else {
        return nullptr;
    }
}

bool ThreadAttachEnv(JNIEnv** env) {
    JavaVM* jvm = GetJVM();
    if (jvm == nullptr) {
        return false;
    }

    int ret = jvm->AttachCurrentThread(env, nullptr);
    if (ret != JNI_OK) {
        return false;
    }

    //*needsDetach = true;
    //设置env为当前子线程私有数据.
    __android_log_print(ANDROID_LOG_DEBUG, kEventHandlerTagAndroid,
                        "attach thread to env success!");
    if (pthread_getspecific(g_thread_key) == NULL) {
        pthread_setspecific(g_thread_key, *env);
    }
    return true;
}

void ThreadDetachEnv(void *) {
    JavaVM* jvm = GetJVM();
    if (jvm == nullptr) {
        return;
    }
    if (g_jvm->DetachCurrentThread() != JNI_OK) {
        __android_log_print(ANDROID_LOG_DEBUG, kEventHandlerTagAndroid, "thread detach env fail!");
    } else {
        __android_log_print(ANDROID_LOG_DEBUG, kEventHandlerTagAndroid, "thread detach env success!");
    }
}


jlong jlongFromPointer(void* ptr) {
    static_assert(sizeof(intptr_t) <= sizeof(jlong), "jlongFromPointer error ptr to long");//check in compile time
    jlong ret = reinterpret_cast<intptr_t>(ptr); //ptr to long safely by arch
    assert(reinterpret_cast<void*>(ret) == ptr); //check in runtime
    return ret;
}

}
