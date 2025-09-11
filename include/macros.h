#ifndef _H_MACROS_
#define _H_MACROS_

#if DEBUG
#define ASSERTLINE(line, cond) \
    ((cond) || (OSPanic(__FILE__, line, "Failed assertion " #cond), 0))

#define ASSERTMSGLINE(line, cond, msg) \
    ((cond) || (OSPanic(__FILE__, line, msg), 0))

// This is dumb but we dont have a Metrowerks way to do variadic macros in the macro to make this done in a not scrubby way.
#define ASSERTMSG1LINE(line, cond, msg, arg1) \
    ((cond) || (OSPanic(__FILE__, line, msg, arg1), 0))
    
#define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) \
    ((cond) || (OSPanic(__FILE__, line, msg, arg1, arg2), 0))

#define ASSERTMSGLINEV(line, cond, ...) \
    ((cond) || (OSPanic(__FILE__, line, __VA_ARGS__), 0))

#else
#define ASSERTLINE(line, cond) (void)0
#define ASSERTMSGLINE(line, cond, msg) (void)0
#define ASSERTMSG1LINE(line, cond, msg, arg1) (void)0
#define ASSERTMSG2LINE(line, cond, msg, arg1, arg2) (void)0
#define ASSERTMSGLINEV(line, cond, ...) (void)0
#endif
    
#define ASSERT(cond) ASSERTLINE(__LINE__, cond)

#ifdef __MWERKS__
#define ASM asm
#else
#define ASM
#endif

#define LOAD_LE_u32(v)                                                                                          \
    ((u32)(((((u8*)&(v))[3] & 0xFF) << 24) | ((((u8*)&(v))[2] & 0xFF) << 16) | ((((u8*)&(v))[1] & 0xFF) << 8) | \
           ((((u8*)&(v))[0] & 0xFF) << 0)))

#define LOAD_LE_u16(v) ((u16)(((((u8*)&(v))[1] << 8) & 0xFF00) | ((((u8*)&(v))[0] & 0xFF) << 0)))

#endif // _H_MACROS_
