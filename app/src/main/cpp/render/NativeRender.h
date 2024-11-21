//
// Created by zhuyong.joe on 2024/11/21.
//

#ifndef GRAFIKA_NATIVERENDER_H
#define GRAFIKA_NATIVERENDER_H

#include <memory>
#include "../egl/EglCore.h"
#include "WindowSurface.h"


class NativeRender {
public:
    NativeRender();
    ~NativeRender();
    void onWindowCreate(ANativeWindow *window);
    void onWindowSizeChanged(int width, int height);
    void onWindowDestroy();

private:
    std::unique_ptr<EglCore> eglCore{nullptr};
    std::unique_ptr<WindowSurface> windowSurface{nullptr};
};

#endif //GRAFIKA_NATIVERENDER_H
