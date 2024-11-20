package org.joe.sample.shape

import android.opengl.GLES20
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class Triangle: BaseShape() {

    // 简单的顶点着色器
    private val vertexShaderCode: String =
        """attribute vec4 vPosition;
             void main() {
                 gl_Position   = vPosition;
             }"""

    // 简单的片元着色器
    private val fragmentShaderCode: String =
        """ precision mediump float;
             uniform vec4 vColor;
             void main() {
                 gl_FragColor = vColor;
             }"""

    // 定义三角形的坐标
    private var triangleCoords: FloatArray = floatArrayOf(
        0.5f, 0.5f, 0.0f,  // top
        -0.5f, -0.5f, 0.0f,  // bottom left
        0.5f, -0.5f, 0.0f // bottom right
    )

    // 定义三角形的颜色——白色
    private var color: FloatArray = floatArrayOf(1.0f, 1.0f, 1.0f, 1.0f)

    // 顶点个数
    private val vertexCount: Int = triangleCoords.size / COORDS_PER_VERTEX

    var vertexBuffer: FloatBuffer? = null

    var mProgram: Int = 0

    init {
//        GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f) // 申请底色空间

        //将坐标数据转换为FloatBuffer，用以传入给OpenGL ES程序
        vertexBuffer = ByteBuffer.allocateDirect(triangleCoords.size * 4)
            .order(ByteOrder.nativeOrder())
            .asFloatBuffer().apply {
                put(triangleCoords)
                position(0)
            }

        mProgram = createOpenGLProgram(vertexShaderCode, fragmentShaderCode)
    }

    fun draw() {
        //将程序加入到OpenGLES2.0环境
        GLES20.glUseProgram(mProgram)
        //获取顶点着色器的vPosition成员句柄
        val mPositionHandle = GLES20.glGetAttribLocation(mProgram, "vPosition")
        //启用三角形顶点的句柄
        GLES20.glEnableVertexAttribArray(mPositionHandle)
        //准备三角形的坐标数据
        GLES20.glVertexAttribPointer(
            mPositionHandle,
            COORDS_PER_VERTEX,
            GLES20.GL_FLOAT,
            false,
            vertexStride,
            vertexBuffer
        )
        //获取片元着色器的vColor成员的句柄
        val mColorHandle = GLES20.glGetUniformLocation(mProgram, "vColor")
        //设置绘制三角形的颜色
        GLES20.glUniform4fv(mColorHandle, 1, color, 0)
        //绘制三角形
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, vertexCount)
        //禁止顶点数组的句柄
        GLES20.glDisableVertexAttribArray(mPositionHandle)
    }
}