#ifndef _ASM_SHARED_IO_H
#define _ASM_SHARED_IO_H

#include <stdint.h>

#define BUILDIO(bwl, bw, type) \
static inline type __in##bwl(uint16_t port) { \
    type value; \
    asm volatile("in" #bw " %1, %0" : "=a"(value) : "Nd"(port)); \
    return value; \
} \
static inline void __out##bwl(type value, uint16_t port) { \
    asm volatile("out" #bw " %0, %1" : : "a"(value), "Nd"(port)); \
}

BUILDIO(b, b, uint8_t)
BUILDIO(w, w, uint16_t)
BUILDIO(l, l, uint32_t)
#undef BUILDIO

#define inb __inb
#define inw __inw
#define inl __inl
#define outb __outb
#define outw __outw
#define outl __outl

#endif // _ASM_IO_H