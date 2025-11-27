#ifndef GENLOGGER_H
#define GENLOGGER_H


#include "GenGlobal.h"
#include "GenMessageLogger.h"
#include <string>
#include <functional>

// logger macros

const int MSG_TYPE_MIN = 1;
const int MSG_TYPE_MAX = 31;

const int MSG_TYPE_DEBUG = 1;
const int MSG_TYPE_INFO = 2;
const int MSG_TYPE_WARNING = 3;
const int MSG_TYPE_ERROR = 4;

#ifdef GEN_NO_DEBUG_OUTPUT
#define GEN_DEBUG            while (false) GenMessageLogger().noDebug
#define GEN_DEBUG_PRINT      while (false) GenMessageLogger().noDebug().format
#else
#define GEN_DEBUG            GenMessageLogger(MSG_TYPE_DEBUG).debug
#define GEN_DEBUG_PRINT      GenMessageLogger(MSG_TYPE_DEBUG).debug().format
#endif

#ifdef GEN_NO_INFO_OUTPUT
#define GEN_INFO             while (false) GenMessageLogger().noDebug
#define GEN_INFO_PRINT       while (false) GenMessageLogger().noDebug().format
#else
#define GEN_INFO             GenMessageLogger(MSG_TYPE_INFO).debug
#define GEN_INFO_PRINT       GenMessageLogger(MSG_TYPE_INFO).debug().format
#endif

#ifdef GEN_NO_ERROR_OUTPUT
#define GEN_ERROR            while (false) GenMessageLogger().noDebug
#define GEN_ERROR_PRINT      while (false) GenMessageLogger().noDebug().format
#else
#define GEN_ERROR            GenMessageLogger(MSG_TYPE_ERROR).debug
#define GEN_ERROR_PRINT      GenMessageLogger(MSG_TYPE_ERROR).debug().format
#endif


#define GEN_SYSERR           GenMessageLogger("SYSTEM", "#595959").debug
#define GEN_SYSERR_PRINT     GenMessageLogger("SYSTEM", "#FF0000").debug().format
#define GEN_SYSINFO          GenMessageLogger("SYSTEM", "#595959").debug
#define GEN_SYSINFO_PRINT    GenMessageLogger("SYSTEM", "#FF0000").debug().format
#define GEN_WANING           GenMessageLogger("WARNING", "#FF0000").debug

#define GEN_DLOGN(n)         GenMessageLogger(n, "#595959").debug()
#define GEN_DLOGB(n)         GenMessageLogger(n, "#1079FF").debug()
#define GEN_DLOGR(n)         GenMessageLogger(n, "#FF0000").debug()



#endif // GENLOGGER_H
