//
// Created by zhuyong.joe on 2024/11/21.
//

#ifndef GRAFIKA_NATIVERENDER_H
#define GRAFIKA_NATIVERENDER_H

#include <memory>
#include <jni.h>
#include "../egl/EglCore.h"
#include "WindowSurface.h"
#include "BaseShape.h"
#include "AndroidFileLoader.h"


class NativeRender: public IFileLoader{
public:
    NativeRender(JNIEnv *env, jobject jFileLoader);
    ~NativeRender();
    void onWindowCreate(ANativeWindow *window);
    void onWindowSizeChanged(int width, int height);
    void onWindowDestroy();
    virtual uint8_t* loadFile(std::string fileName);

private:
    EglCore eglCore{nullptr, FLAG_RECORDABLE};
    std::unique_ptr<WindowSurface> windowSurface{nullptr};
    std::unique_ptr<BaseShape> shape{nullptr};
    std::unique_ptr<AndroidFileLoader> fileLoaderImpl{nullptr};
    JNIEnv *env;
    jobject jFileLoader;
};

#endif //GRAFIKA_NATIVERENDER_H
