// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

namespace service {

template <typename T>
extern T *GetService();

template <typename T>
inline T &GetInstance() {
  auto *p = GetService<T>();
#ifndef NDEBUG
  if (!p) {
    __builtin_trap();
  }
#endif
  return *p;
}
}  // namespace service

#if defined(__APPLE__)

// ios 使用 dynamic alloc 以防止进程退出时触发析构
#define REGISTER_SERVICE(TYPE, IMPL) \
  namespace service {           \
  template <>                        \
  TYPE *GetService<TYPE>() {         \
    static TYPE *inst = new IMPL();  \
    return inst;                     \
  }                                  \
  }

#else

#define REGISTER_SERVICE(TYPE, IMPL) \
  namespace service {           \
  template <>                        \
  TYPE *GetService<TYPE>() {         \
    static IMPL inst{};              \
    return &inst;                    \
  }                                  \
  }
#endif
