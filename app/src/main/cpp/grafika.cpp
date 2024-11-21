#include <jni.h>
#include <assert.h>
#include <android/native_window_jni.h>
#include "NativeRender.h"


jlong jlongFromPointer(void* ptr) {
    static_assert(sizeof(intptr_t) <= sizeof(jlong), "jlongFromPointer error ptr to long");//check in compile time
    jlong ret = reinterpret_cast<intptr_t>(ptr); //ptr to long safely by arch
    return ret;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_org_joe_sample_NativeGLView_nativeWindowCreated(JNIEnv *env, jobject thiz,
                                                     jobject asset_manager, jobject surface) {
    NativeRender* nativeRender = new NativeRender();
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    nativeRender->onWindowCreate(window);
    return jlongFromPointer(nativeRender);
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
    reinterpret_cast<NativeRender *>(native_render_ptr)->onWindowDestroy();
}

