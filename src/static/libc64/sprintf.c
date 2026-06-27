#include "libc64/sprintf.h"

#include "libultra/xprintf.h"
#include "_mem.h"


static void* proutPrintf(void* dst, const char* fmt, int size) {
    return (void*)((u8*)memcpy(dst, fmt, size) + size);
}

typedef struct {
    char* dst;
    int remaining;
} SnprintfCtx;

static void* proutSnprintf(void* ctx, const char* fmt, int size) {
    SnprintfCtx* c = (SnprintfCtx*)ctx;
    int copy_size = size < c->remaining ? size : c->remaining;
    if (copy_size > 0) {
        memcpy(c->dst, fmt, copy_size);
        c->dst += copy_size;
        c->remaining -= copy_size;
    }
    return ctx;
}

int sprintf(char* dst, const char* fmt, ...) {
    int ret;
    va_list args;
    va_start(args, fmt);

    ret = _Printf(&proutPrintf, dst, fmt, args);
    if (ret >= 0) {
        dst[ret] = '\0';
    }

    va_end(args);

    return ret;
}

int snprintf(char* dst, int n, const char* fmt, ...) {
    int ret;
    va_list args;
    SnprintfCtx ctx;
    if (n <= 0) {
        return 0;
    }
    ctx.dst = dst;
    ctx.remaining = n - 1;
    va_start(args, fmt);
    ret = _Printf(&proutSnprintf, &ctx, fmt, args);
    va_end(args);
    *ctx.dst = '\0';
    return ret;
}
