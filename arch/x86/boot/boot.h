/*
 * Header file for handling boot services once called by loader.
 * Specific services are defined in their own file.
 */
#ifndef _BOOT_H
#define _BOOT_H

#define STACK_SIZE 1024

#include <stdlib.h>
#include <os/efi.h>

typedef struct {
    UINT32 magic;
    UINT32 version;
    UINT32 size;
} boot_info_header;

struct boot_param_block {
    boot_info_header hdr;
    // Kernel
    UINT32 loader_signature;
    UINT32 pkernel_addr;
    UINT32 kernerl_size;
    // Memory
    UINT32 memdesc_size;
    UINT32 memdesc_v;
    UINT32 memmap;
    UINT32 memmap_size;

    void* rsdp;
    // runtime sevices
    char* cmdline;
}__attribute__((packed));

// memory.c
// void detectMemory(void);

#endif // _BOOT_H