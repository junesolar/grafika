#include <jni.h>
#include <assert.h>
#include <android/native_window_jni.h>
#include "NativeRender.h"
#include "jni_helper.h"
#include "service.h"
#include "AndroidFileLoader.h"

void ServiceOnLoad(JNIEnv* env) {
    FileLoaderOnLoad(env);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
    xplay::SetJVM(vm);
    JNIEnv* env = xplay::GetEnv();
    ServiceOnLoad(env);
    return JNI_VERSION_1_6;
}

jlong jlongFromPointer(void* ptr) {
    static_assert(sizeof(intptr_t) <= sizeof(jlong), "jlongFromPointer error ptr to long");//check in compile time
    jlong ret = reinterpret_cast<intptr_t>(ptr); //ptr to long safely by arch
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_org_joe_sample_NativeGLView_nativeWindowCreated(JNIEnv *env, jobject thiz,
                                                     jlong native_render_ptr, jobject surface) {
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    reinterpret_cast<NativeRender *>(native_render_ptr)->onWindowCreate(window);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_joe_sample_NativeGLView_nativeWindowChange(JNIEnv *env, jobject thiz,
                                                    jlong native_render_ptr, jint height,
                                                    jint width) {
    reinterpret_cast<NativeRender *>(native_render_ptr)->onWindowSizeChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_org_joe_sample_NativeGLView_nativeDestroy(JNIEnv *env, jobject thiz, jlong native_render_ptr) {
    auto nativeRender = reinterpret_cast<NativeRender *>(native_render_ptr);
    nativeRender->onWindowDestroy();
    delete nativeRender;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_joe_sample_NativeGLView_nativeInit(JNIEnv *env, jobject thiz) {
    NativeRender* nativeRender = new NativeRender();
    return jlongFromPointer(nativeRender);
}