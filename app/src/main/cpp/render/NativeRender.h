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

class NativeRender {
public:
    NativeRender();
    ~NativeRender();
    void onWindowCreate(ANativeWindow *window);
    void onWindowSizeChanged(int width, int height);
    void onWindowDestroy();

private:
    EglCore eglCore{nullptr, FLAG_RECORDABLE};
    std::unique_ptr<WindowSurface> windowSurface{nullptr};
    std::unique_ptr<BaseShape> shape{nullptr};
};

#endif //GRAFIKA_NATIVERENDER_H
