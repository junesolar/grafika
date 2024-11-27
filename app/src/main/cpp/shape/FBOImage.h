//
// Created by zhuyong.joe on 2024/11/27.
//

#ifndef GRAFIKA_FBOIMAGE_H
#define GRAFIKA_FBOIMAGE_H


#include "BaseShape.h"

class FBOImage: public BaseShape {
public:
    FBOImage();
    ~FBOImage() override;
    void draw() override{};
    void draw(int width, int height) override;

private:
    bool CreateFrameBufferObj();
    GLuint m_ImageTextureId;
    GLuint m_FboTextureId;
    GLuint m_FboId;
    GLuint m_VaoIds[2];
    GLuint m_VboIds[4];
    GLint m_SamplerLoc;
    GLuint m_FboProgramObj;
    GLuint m_FboVertexShader;
    GLuint m_FboFragmentShader;
    GLint m_FboSamplerLoc;
};


#endif //GRAFIKA_FBOIMAGE_H
