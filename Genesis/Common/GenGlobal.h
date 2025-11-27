#ifndef GENGLOBAL_H
#define GENGLOBAL_H

#if defined(__linux__) || defined(__linux)
#define GEN_OS_LINUX
#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
#define GEN_OS_WIN64
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define GEN_OS_WIN32
#endif

#if defined(GEN_OS_WIN32) || defined(GEN_OS_WIN64)
#define GEN_OS_WIN
#endif

typedef unsigned short      Genuint16;
typedef int                 Genint32;
typedef unsigned int        Genuint32;
typedef long long           Genint64;
typedef unsigned long long  Genuint64;

#define GEN_UNUSED(v)        (void)(v)

#endif // GENGLOBAL_H
