//
// Created by zhuyong.joe on 2024/11/21.
//
#include "NativeRender.h"
#include "Triangle.h"
#include "Image.h"
#include "FBOImage.h"
#include "Cube3D.h"
#include <GLES3/gl3.h>


NativeRender::NativeRender() {
}

NativeRender::~NativeRender() {
}

void NativeRender::onWindowCreate(ANativeWindow *window) {
    windowSurface = std::make_unique<WindowSurface>(&eglCore, window, false);
    windowSurface->makeCurrent();
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shape = std::make_unique<Cube3D>();
    shape->draw();
    windowSurface->swapBuffers();
}

void NativeRender::onWindowSizeChanged(int width, int height) {
    glViewport(0, 0, width, height);
    mScreenH = height;
    mScreenW = width;
    shape->draw(width, height);
    windowSurface->swapBuffers();
}

void NativeRender::onWindowDestroy() {
    eglCore.release();
    windowSurface->release();
}

