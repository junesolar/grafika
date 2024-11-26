//
// Created by zhuyong.joe on 2024/11/21.
//
#include "NativeRender.h"
#include "Triangle.h"
#include "Image.h"
#include <GLES3/gl3.h>


NativeRender::NativeRender(JNIEnv *env, jobject jFileLoader):env(env) {
    this->jFileLoader = env->NewGlobalRef(jFileLoader);
    fileLoaderImpl = std::make_unique<AndroidFileLoader>(env, this->jFileLoader);
}

NativeRender::~NativeRender() {
    env->DeleteGlobalRef(jFileLoader);
}

void NativeRender::onWindowCreate(ANativeWindow *window) {
    windowSurface = std::make_unique<WindowSurface>(&eglCore, window, false);
    windowSurface->makeCurrent();
    shape = std::make_unique<Image>(std::unique_ptr<IFileLoader>(this));
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

uint8_t *NativeRender::loadFile(std::string fileName) {
    return fileLoaderImpl->loadFile(fileName);
}

