#include "string.h"
#include "os/types.h"

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
    return dst;
}

void* memset(void* dst, int data, size_t len){
    char* xs = dst;
    while(len--){
        *xs++ = data;
    }
    return dst;
}

int memcmp(void* seg1, void* seg2, size_t len){
    unsigned char *su1, *su2;
    int res = 0;

    if(len >= sizeof(unsigned long)){
        const unsigned long* u1 = seg1;
        const unsigned long* u2 = seg2;
        do {
            if (get_unaligned(u1) != get_unaligned(u2))
                break;
            u1++;
            u2++;
            len -= sizeof(unsigned long);
        } while (len >= sizeof(unsigned long));
        seg1 = u1;
        seg2 = u2;
    }

    for (su1 = seg1, su2 = seg2; 0 < len; ++su1, ++su2, len--){
        if ((res = *su1 - *su2) != 0) break;
    }
    return res;
}