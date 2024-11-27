//
// Created by zhuyong.joe on 2024/11/25.
//

#ifndef GRAFIKA_IMAGE_H
#define GRAFIKA_IMAGE_H


#include "BaseShape.h"

class Image: public BaseShape{
public:
    Image();
    ~Image() override;
    void draw() override;

private:
    GLuint m_TextureId;
    GLint m_SamplerLoc;
    uint8_t *imageData{nullptr};
};


#endif //GRAFIKA_IMAGE_H
