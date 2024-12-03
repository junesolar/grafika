//
// Created by zhuyong.joe on 2024/11/28.
//

#include "Cube3D.h"
#include "LogUtil.h"
#include "gtc/matrix_transform.hpp"

Cube3D::Cube3D() {
    char vShaderStr[] =
            "#version 300 es                                  \n"
            "layout (location = 0) in vec3 aPos; // 顶点位置   \n"
            "layout (location = 1) in vec3 aColor; // 顶点颜色 \n"
            "uniform mat4 u_MVPMatrix;\n"
            "out vec3 vertexColor; // 传递到片元着色器的颜色      \n"
            "void main()                                      \n"
            "{                                                \n"
            "    gl_Position = u_MVPMatrix * vec4(aPos, 1.0);               \n"
            "    vertexColor = aColor;                        \n"
            "}";
    char fShaderStr[] =
            "#version 300 es\n"
            "precision mediump float;\n"
            "in vec3 vertexColor; // 从顶点着色器传入的颜色\n"
            "out vec4 FragColor; // 输出颜色\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(vertexColor, 1.0);\n"
            "}";
    m_ProgramObj = GLUtils::CreateProgram(vShaderStr, fShaderStr);
    if (m_ProgramObj == GL_NONE)
    {
        LOGCATE("FBOSample::Init m_ProgramObj == GL_NONE");
        return;
    }

    m_MVPMatLoc = glGetUniformLocation(m_ProgramObj, "u_MVPMatrix");

    GLfloat vertices[] = {
            // 前面 (红色)
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 左下
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 右下
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 右上
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 左下
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 右上
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 左上

            // 后面 (绿色)
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

            // 左面 (蓝色)
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

            // 右面 (黄色)
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

            // 上面 (青色)
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

            // 下面 (紫色)
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    };

    unsigned int VBO;
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &VBO);
    // 绑定并填充 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 绑定 VAO
    glBindVertexArray(mVao);

    // 绑定并填充 VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 设置顶点属性指针
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    GO_CHECK_GL_ERROR();

    // 解绑 VAO
    glBindVertexArray(0);
}

Cube3D::~Cube3D() {
    if (m_ProgramObj != GL_NONE)
    {
        glDeleteProgram(m_ProgramObj);
        m_ProgramObj = GL_NONE;
    }
}

void Cube3D::draw(int width, int height) {
    LOGCATE("Cube3D::Draw");

    if(m_ProgramObj == GL_NONE)
        return;

    glm::vec3 transPos = glm::vec3( 0.0f,  0.0f,  -90.0f);


    this->UpdateMVPMatrix(m_MVPMatrix, 60, 0, (float)width / height, 1.0, transPos);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Use the program object
    glUseProgram (m_ProgramObj);
    glBindVertexArray(mVao);
    glUniformMatrix4fv(m_MVPMatLoc, 1, GL_FALSE, &m_MVPMatrix[0][0]);

    GO_CHECK_GL_ERROR();
    glDrawArrays (GL_TRIANGLES, 0, 36);

    GO_CHECK_GL_ERROR();
    glUseProgram (GL_NONE);
}

void Cube3D::UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio, float scale, const glm::vec3& transVec3)
{
    LOGCATE("CoordSystemSample::UpdateMVPMatrix angleX = %d, angleY = %d, ratio = %f", angleX, angleY, ratio);
    angleX = angleX % 360;
    angleY = angleY % 360;

    //转化为弧度角
    float radiansX = static_cast<float>(MATH_PI / 180.0f * angleX);
    float radiansY = static_cast<float>(MATH_PI / 180.0f * angleY);


    // Projection matrix
    //glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    //glm::mat4 Projection = glm::frustum(-ratio, ratio, -1.0f, 1.0f, 4.0f, 100.0f);
    glm::mat4 Projection = glm::perspective(45.0f,ratio, 0.1f,100.f);

    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::translate(Model, transVec3);
    Model = glm::scale(Model, glm::vec3(scale, scale, 1.0f));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));

    mvpMatrix = Projection * View * Model;
}

void Cube3D::release() {

}
