//
// Created by zhuyong.joe on 2024/11/28.
//

#ifndef GRAFIKA_CUBE3D_H
#define GRAFIKA_CUBE3D_H


#include "BaseShape.h"

class Cube3D:public BaseShape {
public:
    Cube3D();
    ~Cube3D() override;
    void draw() override{};
    void draw(int width, int height) override;
    void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio, float scale, const glm::vec3& transVec3);
    void release() override;
private:
    GLuint mVao;
    GLint m_MVPMatLoc;
    glm::mat4 m_MVPMatrix;
    glm::mat4 m_ModelMatrix;
    bool mIsRelease = false;
};


#endif //GRAFIKA_CUBE3D_H
