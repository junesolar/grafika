package org.joe.sample

import android.content.Context
import android.opengl.GLES20
import android.util.Log
import android.view.SurfaceHolder
import android.view.SurfaceView
import com.android.grafika.gles.Drawable2d
import com.android.grafika.gles.EglCore
import com.android.grafika.gles.GlUtil
import com.android.grafika.gles.Sprite2d
import com.android.grafika.gles.Texture2dProgram
import com.android.grafika.gles.Texture2dProgram.ProgramType
import com.android.grafika.gles.WindowSurface
import org.joe.sample.egl.EglHelper
import org.joe.sample.shape.Triangle


class GLView(context: Context): SurfaceView(context), SurfaceHolder.Callback {

    companion object {
        const val TAG = "GLView"
    }

    private var mEglCore: EglCore? = null
    private var mDisplaySurface: WindowSurface? = null

    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder?) {
        Log.d(TAG,
            "surfaceCreated size=" + width + "x" + height +
                    " holder=" + holder
        )
        mEglCore = EglCore(null, EglCore.FLAG_RECORDABLE)
        mDisplaySurface = WindowSurface(mEglCore, holder?.surface, false)
        mDisplaySurface?.makeCurrent()
        GLES20.glViewport(0, 0, width, height)
        GLES20.glClearColor(0.0f, 1.0f, 0.0f, 1.0f)
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)
        Triangle().draw()

//        val program = Texture2dProgram(ProgramType.TEXTURE_2D)
//        val rectDrawable = Drawable2d(Drawable2d.Prefab.RECTANGLE)
//        val rect = Sprite2d(rectDrawable)
//        rect.setScale(200f, 200f)
//        rect.setColor(1f, 0f,0f)
//        rect.setPosition(0f, 0f)
//        rect.draw(program, GlUtil.IDENTITY_MATRIX)

        mDisplaySurface?.swapBuffers()
    }

    override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
        GLES20.glViewport(0, 0, width, height)
        Log.d(TAG,
            "surfaceChanged fmt=" + format + " size=" + width + "x" + height +
                    " holder=" + holder
        )
    }

    override fun surfaceDestroyed(holder: SurfaceHolder?) {
        Log.d(TAG, "surfaceDestroyed holder=$holder")
        mDisplaySurface?.release()
        mEglCore?.release()
    }
}