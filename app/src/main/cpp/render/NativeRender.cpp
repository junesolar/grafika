//
// Created by zhuyong.joe on 2024/11/21.
//
#include "NativeRender.h"
#include "Triangle.h"
#include <GLES3/gl3.h>


NativeRender::NativeRender() {
}

NativeRender::~NativeRender() {
}

void NativeRender::onWindowCreate(ANativeWindow *window) {
    windowSurface = std::make_unique<WindowSurface>(&eglCore, window, false);
    windowSurface->makeCurrent();
    shape = std::make_unique<Triangle>();
    shape->draw();
    windowSurface->swapBuffers();
}

void NativeRender::onWindowSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void NativeRender::onWindowDestroy() {
    eglCore.release();
    windowSurface->release();
}

