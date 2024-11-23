//
// Created by zhuyong.joe on 2024/11/23.
//

#ifndef GRAFIKA_BASESHAPE_H
#define GRAFIKA_BASESHAPE_H

#include "../util/GLUtils.h"

class BaseShape {
public:
    BaseShape() = default;
    ~BaseShape() = default;
    virtual void draw() = 0;

protected:
    GLuint m_ProgramObj = GL_NONE;
};

#endif //GRAFIKA_BASESHAPE_H
