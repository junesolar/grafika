package org.joe.sample.service

import android.content.Context
import android.support.annotation.Keep
import org.joe.sample.utils.loadRGBAImageFromAsset

interface IService

@Keep
class FileLoadService(val context: Context): IService {

    init {
        init()
    }

    //call by native
    fun loadImage(resName: String): ByteArray? {
        return loadRGBAImageFromAsset(context, resName)
    }

    external fun init()
}