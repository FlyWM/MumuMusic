/**
 * MumuMusic
 * 基于Qt的模仿网易云音乐PC客户端的app
 *
 * FlyWM_
 * GitHub: https://github.com/FlyWM
 * CSDN: https://blog.csdn.net/a844651990
 */

#ifndef LIBMUMEDIAHANDLER_GLOBAL_H
#define LIBMUMEDIAHANDLER_GLOBAL_H

#if defined(MUMEDIAHANDLER_LIBRARY)
#  define MUMEDIAHANDLERSHARED_EXPORT __declspec(dllexport)
#else
#  define MUMEDIAHANDLERSHARED_EXPORT __declspec(dllimport)
#endif

template <typename T> static inline T *muGetPrtHelper(T *ptr) { return ptr; }
//template <typename Wrapper> static inline typename Wrapper::pointer qGetPtrHelper(const Wrapper &p) { return p.data(); }

#define Mu_DECLARE_PRIVATE(Class) \
    inline Class##Private *d_func() { return reinterpret_cast<Class##Private *>(muGetPrtHelper(d_ptr)); } \
    inline const Class##Private *d_func() const { return reinterpret_cast<const Class##Private *>(muGetPrtHelper(d_ptr)); } \
    friend class Class##Private;

#define Mu_D(Class) Class##Private * const d = d_func()

#endif // LIBMUMEDIAHANDLER_GLOBAL_H
