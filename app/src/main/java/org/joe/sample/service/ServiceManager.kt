package org.joe.sample.service

import android.support.annotation.Keep
import java.lang.RuntimeException
import java.util.concurrent.ConcurrentHashMap

@Keep
object ServiceManager {

    private val serviceInstanceMap = ConcurrentHashMap<String, IService>()

    /**
     * 注册 Unisus Service
     */
    @JvmStatic
    fun <T : IService> registerService(service: Class<T>, instance: T) {
        serviceInstanceMap[service.name] = instance
    }

    /**
     * 获取 Unisus Service
     */
    @JvmStatic
    fun <T : IService> getService(service: Class<T>): T {
        val instance = serviceInstanceMap[service.name]
            ?: throw RuntimeException("${service.name} must register service before")
        return instance as T
    }

    /**
     * 获取 Unisus Service
     */
    @JvmStatic
    fun <T : IService> getServiceOrNull(service: Class<T>): T? {
        val instance = serviceInstanceMap[service.name] ?: return null
        return instance as T
    }
}
