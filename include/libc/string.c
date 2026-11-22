#include "string.h"

void* memcpy(void* dst, const void* src, size_t len){
    char* d = (char*)dst;
    const char* s = (const char*)src;
    if (((uintptr_t)s % sizeof(unsigned long)) == ((uintptr_t)d % sizeof(unsigned long))){
        while (((uintptr_t)d % sizeof(unsigned long)) != 0 && len > 0){
            *d++ = *s++;
            len--;
        }

        unsigned long *wd = (unsigned long*)d;
        const unsigned long *ws = (const unsigned long*)s;

        while (len >= sizeof(unsigned long)){
            *wd++ = *ws++;
            len -= sizeof(unsigned long);
        }

        d = (char*)wd;
        s = (char*)ws;
    }

    while (len--){
        *d++ = *s++;
    }
    return dst;
}

void* memmove(void* dst, const void* src, size_t len){
    char* tmp;
    const char* s;
    if (dst <= src){
        tmp = dst;
        s = src;
        while (len--){
            *tmp++ = *s++;
        }
    } else {
        tmp = dst;
        tmp += len;
        s = src;
        s += len;
        while (len--){
            *--tmp = *--s;
        }
    }
}