package org.joe.sample

import android.content.Context
import android.content.res.AssetManager
import android.util.Log
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView

class NativeGLView (context: Context): SurfaceView(context), SurfaceHolder.Callback {

    private var mNativeRenderPtr: Long = -1

    companion object {
        const val TAG = "GLView"

        init {
            System.loadLibrary("grafika");
        }
    }


    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder?) {
        Log.d(TAG,
            "surfaceCreated size=" + width + "x" + height +
                    " holder=" + holder
        )
        mNativeRenderPtr = nativeWindowCreated(context.assets, holder?.surface)
    }

    override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
        Log.d(TAG,
            "surfaceChanged fmt=" + format + " size=" + width + "x" + height +
                    " holder=" + holder
        )
        nativeWindowChange(mNativeRenderPtr, height, width)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder?) {
        Log.d(TAG, "surfaceDestroyed holder=$holder")
        nativeDestroy(mNativeRenderPtr)
    }

    external fun nativeWindowCreated(assetManager: AssetManager, surface: Surface?): Long
    external fun nativeWindowChange(nativeRenderPtr: Long, height: Int, width: Int)
    external fun nativeDestroy(nativeRenderPtr: Long)
}