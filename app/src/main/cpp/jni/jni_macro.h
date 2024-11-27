// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <jni.h>
#include <type_traits>

// phantom type for ByteBuffer
class _jbyteBuffer : public _jobject {};
using jbyteBuffer = _jbyteBuffer *;

#define SET_METHOD(name, sig, method_name) \
  { #name, sig, reinterpret_cast < void *>(method_name) }
namespace jni {
template <typename>
struct MethodNotDefined;
// helper to get signature from native method
template <typename F>
inline constexpr char Signature[] = MethodNotDefined<F>::signature;
}  // namespace jni

// commonly used types
#define ARG_LEN(...) ARG_LEN_(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define ARG_LEN_(...) ARG_LEN_N(__VA_ARGS__)
#define ARG_LEN_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define CONCATENATE(arg1, arg2) CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2) arg1##arg2

#define CONCAT_TYPES(...) \
  CONCATENATE(CONCAT_TYPES_, ARG_LEN(__VA_ARGS__))(__VA_ARGS__)

#define CONCAT_TYPES_0()
#define CONCAT_TYPES_1(T) JNI_SIGN_##T
#define CONCAT_TYPES_2(T, U) JNI_SIGN_##T JNI_SIGN_##U
#define CONCAT_TYPES_3(T, U, V) CONCAT_TYPES_2(T, U) JNI_SIGN_##V
#define CONCAT_TYPES_4(T, U, V, W) CONCAT_TYPES_3(T, U, V) JNI_SIGN_##W
#define CONCAT_TYPES_5(T, U, V, W, X) CONCAT_TYPES_4(T, U, V, W) JNI_SIGN_##X
#define CONCAT_TYPES_6(T, U, V, W, X, Y) \
  CONCAT_TYPES_5(T, U, V, W, X) JNI_SIGN_##Y
#define CONCAT_TYPES_7(T, U, V, W, X, Y, Z) \
  CONCAT_TYPES_6(T, U, V, W, X, Y) JNI_SIGN_##Z

#define JNI_SIGN_
#define JNI_SIGN_void "V"
#define JNI_SIGN_jboolean "Z"
#define JNI_SIGN_jbyte "B"
#define JNI_SIGN_jchar "C"
#define JNI_SIGN_jshort "S"
#define JNI_SIGN_jint "I"
#define JNI_SIGN_jfloat "F"
#define JNI_SIGN_jdouble "D"
#define JNI_SIGN_jlong "J"
#define JNI_SIGN_jbooleanArray "[Z"
#define JNI_SIGN_jbyteArray "[B"
#define JNI_SIGN_jcharArray "[C"
#define JNI_SIGN_jshortArray "[S"
#define JNI_SIGN_jintArray "[I"
#define JNI_SIGN_jfloatArray "[F"
#define JNI_SIGN_jdoubleArray "[D"
#define JNI_SIGN_jlongArray "[J"
#define JNI_SIGN_jstring "Ljava/lang/String;"
#define JNI_SIGN_jobject "Ljava/lang/Object;"
#define JNI_SIGN_jthrowable "Ljava/lang/Throwable;"
#define JNI_SIGN_jbyteBuffer "Ljava/nio/ByteBuffer;"
#define JNI_SIGN_arrayOf(T) "[" JNI_SIGN_##T

#define METHOD_SIGN_(R, ...) "(" CONCAT_TYPES(__VA_ARGS__) ")" JNI_SIGN_##R

#define METHOD_SIGN_void(...) METHOD_SIGN_(void, __VA_ARGS__)
#define METHOD_SIGN_jboolean(...) METHOD_SIGN_(jboolean, __VA_ARGS__)
#define METHOD_SIGN_jbyte(...) METHOD_SIGN_(jbyte, __VA_ARGS__)
#define METHOD_SIGN_jshort(...) METHOD_SIGN_(jshort, __VA_ARGS__)
#define METHOD_SIGN_jchar(...) METHOD_SIGN_(jchar, __VA_ARGS__)
#define METHOD_SIGN_jint(...) METHOD_SIGN_(jint, __VA_ARGS__)
#define METHOD_SIGN_jlong(...) METHOD_SIGN_(jlong, __VA_ARGS__)
#define METHOD_SIGN_jdouble(...) METHOD_SIGN_(jdouble, __VA_ARGS__)
#define METHOD_SIGN_jbooleanArray(...) METHOD_SIGN_(jbooleanArray, __VA_ARGS__)
#define METHOD_SIGN_jbyteArray(...) METHOD_SIGN_(jbyteArray, __VA_ARGS__)
#define METHOD_SIGN_jshortArray(...) METHOD_SIGN_(jshortArray, __VA_ARGS__)
#define METHOD_SIGN_jcharArray(...) METHOD_SIGN_(jcharArray, __VA_ARGS__)
#define METHOD_SIGN_jintArray(...) METHOD_SIGN_(jintArray, __VA_ARGS__)
#define METHOD_SIGN_jlongArray(...) METHOD_SIGN_(jlongArray, __VA_ARGS__)
#define METHOD_SIGN_jdoubleArray(...) METHOD_SIGN_(jdoubleArray, __VA_ARGS__)
#define METHOD_SIGN_jstring(...) METHOD_SIGN_(jstring, __VA_ARGS__)
#define METHOD_SIGN_jobject(...) METHOD_SIGN_(jobject, __VA_ARGS__)
#define METHOD_SIGN_jthrowable(...) METHOD_SIGN_(jthrowable, __VA_ARGS__)
#define METHOD_SIGN_jbyteBuffer(...) METHOD_SIGN_(jbyteBuffer, __VA_ARGS__)

#define JNI_METHOD_V(fn, name, t) \
  { #name, METHOD_SIGN_##t, (void *)fn }
#define JNI_METHOD(name, t) JNI_METHOD_V(name, name, t)

#define DEFINE_METHOD(M) \
  template <>            \
  inline constexpr char ::jni::Signature<M>[] = METHOD_SIGN_##M

#define DEFINE_TYPE_METHODS(T)                                \
  template <>                                                 \
  inline constexpr char ::jni::Signature<T>[] = JNI_SIGN_##T; \
  DEFINE_METHOD(T());                                         \
  DEFINE_METHOD(void(T))

DEFINE_METHOD(void());
DEFINE_TYPE_METHODS(jboolean);
DEFINE_TYPE_METHODS(jbyte);
DEFINE_TYPE_METHODS(jshort);
DEFINE_TYPE_METHODS(jchar);
DEFINE_TYPE_METHODS(jint);
DEFINE_TYPE_METHODS(jlong);
DEFINE_TYPE_METHODS(jdouble);
DEFINE_TYPE_METHODS(jstring);
DEFINE_METHOD(void(jstring, jlong));
DEFINE_METHOD(void(jint, jstring));
DEFINE_METHOD(void(jstring, jstring));
DEFINE_METHOD(void(jthrowable));
DEFINE_METHOD(void(jbyteBuffer));
// kotlin functions
DEFINE_METHOD(jobject());
DEFINE_METHOD(jobject(jobject));
DEFINE_METHOD(jobject(jobject, jobject));
// kotlin pair constructor
DEFINE_METHOD(void(jobject, jobject));

// Methods, Fields, Constructors
namespace jni {
// helper to access field
template <typename T>
struct FieldHelper {
  static_assert(std::is_convertible_v<T, jobject>,
                "type is not sub class of jobject");

  static inline T Get(JNIEnv *env, jobject o, jfieldID id) {
    return (T)env->GetObjectField(o, id);
  }

  static inline T Get(JNIEnv *env, jclass cls, jfieldID id) {
    return (T)env->GetStaticObjectField(cls, id);
  }

  static inline void Set(JNIEnv *env, jobject o, jfieldID id, T v) {
    env->SetObjectField(o, id, v);
  }

  static inline void Set(JNIEnv *env, jclass cls, jfieldID id, T v) {
    env->SetStaticObjectField(cls, id, v);
  }
};

template <>
struct FieldHelper<jlong> {
  static inline jlong Get(JNIEnv *env, jobject o, jfieldID id) {
    return env->GetLongField(o, id);
  }

  static inline jlong Get(JNIEnv *env, jclass cls, jfieldID id) {
    return env->GetStaticLongField(cls, id);
  }

  static inline void Set(JNIEnv *env, jobject o, jfieldID id, jlong v) {
    env->SetLongField(o, id, v);
  }

  static inline void Set(JNIEnv *env, jclass cls, jfieldID id, jlong v) {
    env->SetStaticLongField(cls, id, v);
  }
};

template <typename T>
inline T Get(JNIEnv *env, jobject o, const char *name) {
  jclass cls = env->GetObjectClass(o);
  jfieldID id = env->GetFieldID(cls, name, Signature<T>);
  env->DeleteLocalRef(cls);
  return FieldHelper<T>::Get(env, o, id);
}

template <typename T>
inline T Get(JNIEnv *env, jclass c, const char *name) {
  jfieldID id = env->GetStaticFieldID(c, name, Signature<T>);
  return FieldHelper<T>::Get(env, c, id);
}

// helper to make method call
template <typename F>
struct CallHelper;

template <typename... ARGS>
struct CallHelper<void(ARGS...)> {
  static inline void Call(JNIEnv *env, jobject o, jmethodID id, ARGS... args) {
    return env->CallVoidMethod(o, id, args...);
  }

  static inline void Call(JNIEnv *env, jobject o, jclass cls, jmethodID id,
                          ARGS... args) {
    return env->CallNonvirtualVoidMethod(o, cls, id, args...);
  }
  static inline void Call(JNIEnv *env, jclass cls, jmethodID id, ARGS... args) {
    return env->CallStaticVoidMethod(cls, id, args...);
  }
};

template <typename... ARGS>
struct CallHelper<jint(ARGS...)> {
  static inline jint Call(JNIEnv *env, jobject o, jmethodID id, ARGS... args) {
    return env->CallIntMethod(o, id, args...);
  }

  static inline jint Call(JNIEnv *env, jobject o, jclass cls, jmethodID id,
                          ARGS... args) {
    return env->CallNonvirtualIntMethod(o, cls, id, args...);
  }

  static inline jint Call(JNIEnv *env, jclass cls, jmethodID id, ARGS... args) {
    return env->CallStaticIntMethod(cls, id, args...);
  }
};

template <typename R, typename... ARGS>
struct CallHelper<R(ARGS...)> {
  static_assert(std::is_convertible_v<R, jobject>,
                "return type is not sub class of jobject");

  static inline R Call(JNIEnv *env, jobject o, jmethodID id, ARGS... args) {
    return (R)env->CallObjectMethod(o, id, args...);
  }

  static inline R Call(JNIEnv *env, jobject o, jclass cls, jmethodID id,
                       ARGS... args) {
    return (R)env->CallNonvirtualObjectMethod(o, cls, id, args...);
  }

  static inline R Call(JNIEnv *env, jclass cls, jmethodID id, ARGS... args) {
    return (R)env->CallStaticObjectMethod(cls, id, args...);
  }
};

/**
 * call a static method
 *
 * @param cls class to be called
 * @param name method name
 */
template <typename R, typename... ARGS>
inline R Call(JNIEnv *env, jclass cls, const char *name, ARGS... args) {
  using F = R(ARGS...);
  using C = CallHelper<F>;

  jmethodID id = env->GetStaticMethodID(cls, name, Signature<F>);
  return C::Call(env, cls, id, args...);
}

/**
 * call a member method
 *
 * @param o object to be called
 * @param name method name
 */
template <typename R, typename... ARGS>
inline R Call(JNIEnv *env, jobject o, const char *name, ARGS... args) {
  using F = R(ARGS...);
  using C = CallHelper<F>;

  jclass cls = env->GetObjectClass(o);
  jmethodID id = env->GetMethodID(cls, name, Signature<F>);
  if constexpr (std::is_same_v<R, void>) {
    C::Call(env, o, cls, id, args...);
    env->DeleteLocalRef(cls);
  } else {
    R ret = C::Call(env, o, cls, id, args...);
    env->DeleteLocalRef(cls);
    return ret;
  }
}

// kotlin helper
namespace kotlin {

inline void Invoke(JNIEnv *env, jobject fn) {
  if (jobject unit = Call<jobject>(env, fn, "invoke")) {
    env->DeleteLocalRef(unit);
  }
}

inline void Invoke(JNIEnv *env, jobject fn, jobject arg0) {
  if (jobject unit = Call<jobject>(env, fn, "invoke", arg0)) {
    env->DeleteLocalRef(unit);
  }
}

inline void Invoke(JNIEnv *env, jobject fn, jobject arg0, jobject arg1) {
  if (jobject unit = Call<jobject>(env, fn, "invoke", arg0, arg1)) {
    env->DeleteLocalRef(unit);
  }
}

}  // namespace kotlin

struct FieldBase {
  inline void init(jfieldID id_) { id = id_; }

  inline operator bool() const { return id != nullptr; }

 protected:
  jfieldID id;
};

template <typename T>
class Field : public FieldBase {
  using H = FieldHelper<T>;

 public:
  using FieldBase::init;

  inline void init(JNIEnv *env, jclass cls, const char *name) {
    id = env->GetFieldID(cls, name, Signature<T>);
  }

  inline T get(JNIEnv *env, jobject o) const { return H::Get(env, o, id); }

  inline void set(JNIEnv *env, jobject o, T v) const { H::Set(env, o, id, v); }
};

template <typename T>
class StaticField : public FieldBase {
  using H = FieldHelper<T>;

 public:
  using FieldBase::init;

  inline void init(JNIEnv *env, jclass cls, const char *name) {
    id = env->GetStaticFieldID(cls, name, Signature<T>);
  }

  inline T get(JNIEnv *env, jclass c) const { return H::Get(env, c, id); }

  inline void set(JNIEnv *env, jclass c, T v) const { H::Set(env, c, id, v); }
};

struct MethodBase {
  inline void init(jmethodID id_) { id = id_; }

  inline operator bool() const { return id != nullptr; }

 protected:
  jmethodID id;
};

template <typename R, typename... ARGS>
class VirtualMethod : public MethodBase {
 protected:
  using F = R(ARGS...);
  using C = CallHelper<F>;

 public:
  using MethodBase::init;

  inline void init(JNIEnv *env, jclass cls, const char *name,
                   const char *sign = Signature<F>) {
    id = env->GetMethodID(cls, name, sign);
  }

  inline R operator()(JNIEnv *env, jobject o, ARGS... args) const {
    return C::Call(env, o, id, args...);
  }

  inline R operator()(JNIEnv *env, jobject o, jclass cls, ARGS... args) const {
    return C::Call(env, o, cls, id, args...);
  }
};

template <typename>
class Method;

// special call helper for void(jbyteBuffer)
template <>
class Method<void(jbyteBuffer)> : public VirtualMethod<void, jbyteBuffer> {
 public:
  inline void operator()(JNIEnv *env, jobject o, const void *p,
                         size_t len) const {
    jobject buf = env->NewDirectByteBuffer((void *)p, len);
    C::Call(env, o, id, (jbyteBuffer)buf);
    env->DeleteLocalRef(buf);
  }

  template <typename T>
  inline void operator()(JNIEnv *env, jobject o, const T &t) const {
    (*this)(env, o, t.data(), t.size());
  }
};

template <typename R, typename... ARGS>
class Method<R(ARGS...)> : public VirtualMethod<R, ARGS...> {};

template <typename>
class StaticMethod;

template <typename R, typename... ARGS>
class StaticMethod<R(ARGS...)> : public MethodBase {
  using F = R(ARGS...);

 public:
  using MethodBase::init;

  inline void init(JNIEnv *env, jclass cls, const char *name,
                   const char *sign = Signature<F>) {
    id = env->GetStaticMethodID(cls, name, sign);
  }

  inline R operator()(JNIEnv *env, jclass cls, ARGS... args) const {
    return CallHelper<F>::Call(env, cls, id, args...);
  }
};

template <typename>
class Constructor;

template <typename R, typename... ARGS>
class Constructor<R(ARGS...)> : public MethodBase {
 public:
  using MethodBase::init;

  inline void init(JNIEnv *env, jclass cls,
                   const char *sign = Signature<void(ARGS...)>) {
    id = env->GetMethodID(cls, "<init>", sign);
  }

  inline R operator()(JNIEnv *env, jclass cls, ARGS... args) const {
    return (R)env->NewObject(cls, id, args...);
  }
};

template <typename... ARGS>
inline jobject NewInstance(JNIEnv *env, const char *className, ARGS... args) {
  jclass cls = env->FindClass(className);
  jmethodID ctor = env->GetMethodID(cls, "<init>", Signature<void(ARGS...)>);
  jobject ret = env->NewObject(cls, ctor, args...);
  env->DeleteLocalRef(cls);
  return ret;
}

}  // namespace jni
