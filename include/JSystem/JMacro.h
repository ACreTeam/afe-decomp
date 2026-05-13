#ifndef JMACRO_H
#define JMACRO_H

#include "dolphin/os.h"
#include "libforest/osreport.h"
#include "JSystem/JUtility/JUTException.h"

#define JLOG(msg) (OSReport(msg))
#define JLOGF(msg, ...) (OSReport(msg, __VA_ARGS__))

/* Macros which will remove debug OSReport calls when not compiled for debug */
#ifdef JSYSTEM_DEBUG
#define JREPORT(msg) OSReport(msg)
#define JREPORTF(msg, ...) OSReport(msg, __VA_ARGS__)
#else
#define JREPORT(msg)
#define JREPORTF(msg, ...)
#endif

#ifdef JSYSTEM_DEBUG
#define JPANICLINE(line) ()
#define JPANIC(line, msg) ()       /* TODO: JUTException */
#define JPANICF(line, msg, ...) () /* TODO: JUTException */
#else
#if VERSION == VER_GAEJ01_00
#define JPANICLINE(line) (OSErrorLine(line, "Abort."))
#define JPANIC(line, msg) (OSErrorLine(line, msg))
#define JPANICF(line, msg, ...) (OSErrorLine(line, msg, __VA_ARGS__))
#else
#define JPANICLINE(line) (JUTException::panic(__FILE__, line, "Abort."))
#define JPANIC(line, msg) (JUTException::panic(__FILE__, line, msg))
#define JPANICF(line, msg, ...) (JUTException::panic_f(__FILE__, line, msg, __VA_ARGS__))
#endif
#endif

#endif
