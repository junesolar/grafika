//
// Created by zhuyong.joe on 2024/11/23.
//

#ifndef GRAFIKA_BASESHAPE_H
#define GRAFIKA_BASESHAPE_H

#include "../util/GLUtils.h"
#include "IFileLoader.h"

class BaseShape {
public:
    BaseShape() {};
    virtual ~BaseShape() = default;
    virtual void draw() = 0;

protected:
    GLuint m_ProgramObj = GL_NONE;
};

#endif //GRAFIKA_BASESHAPE_H
