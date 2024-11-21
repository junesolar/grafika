//
// Created by zhuyong.joe on 2024/11/21.
//
#include "NativeRender.h"
#include <GLES3/gl3.h>


NativeRender::NativeRender() {

}

NativeRender::~NativeRender() {
}

void NativeRender::onWindowCreate(ANativeWindow *window) {
    eglCore = std::make_unique<EglCore>(nullptr, FLAG_RECORDABLE);
    windowSurface = std::make_unique<WindowSurface>(eglCore.get(), window, false);
    windowSurface->makeCurrent();
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
//    checkGlError("glClearColor");
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//    checkGlError("glClear");
    windowSurface->swapBuffers();
}

void NativeRender::onWindowSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void NativeRender::onWindowDestroy() {
    eglCore->release();
    windowSurface->release();
}

