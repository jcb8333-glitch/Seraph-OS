#ifndef _BOOT_IO_H
#define _BOOT_IO_H

#include <stdint.h>
#include <asm/shared_io.h>

#undef __inw
#undef __inl
#undef __outl

struct port_io_ops {
    uint8_t (*f_inb)(uint16_t port);
    void    (*f_outb)(uint8_t v, uint16_t p);
    void    (*f_outw)(uint16_t v, uint16_t p);
};

extern struct port_io_ops p_io_ops;

static inline void init_default_io_ops(void){
    p_io_ops.f_inb = __inb;
    p_io_ops.f_outb = __outb;
    p_io_ops.f_outw = __outw;
}

#endif // _BOOT_IO_H