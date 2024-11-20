#include <jni.h>


extern "C"
JNIEXPORT void JNICALL
Java_org_joe_sample_NativeGLView_nativeWindowCreated(JNIEnv *env, jobject thiz,
                                                     jobject asset_manager, jobject surface) {
    // TODO: implement nativeWindowCreated()
}
extern "C"
JNIEXPORT void JNICALL
Java_org_joe_sample_NativeGLView_nativeWindowChange(JNIEnv *env, jobject thiz, jint height,
                                                    jint width) {
    // TODO: implement nativeWindowChange()
}
extern "C"
JNIEXPORT void JNICALL
Java_org_joe_sample_NativeGLView_nativeDestroy(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeDraw()
}