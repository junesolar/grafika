package org.joe.sample.utils

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import java.io.IOException
import java.io.InputStream
import java.nio.ByteBuffer

fun loadRGBAImageFromAsset(context: Context, resName: String): ByteArray? {
    val inputStream: InputStream = context.assets.open(resName)
    var bitmap: Bitmap? = null
    var byteArray: ByteArray? = null
    try {
        bitmap = BitmapFactory.decodeStream(inputStream)
        if (bitmap != null) {
            val bytes = bitmap.byteCount
            val buf = ByteBuffer.allocate(bytes)
            bitmap.copyPixelsToBuffer(buf)
            byteArray = buf.array()
        }
    } finally {
        try {
            inputStream.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }
    return byteArray
}