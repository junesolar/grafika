package org.joe.sample

import android.app.Activity
import android.os.Bundle

class SampleActivity: Activity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(GLView(this))
    }

    override fun onDestroy() {
        super.onDestroy()
    }
}