/*
 * Header file for handling boot services once called by loader.
 * Specific services are defined in their own file.
 */
#ifndef _BOOT_H
#define _BOOT_H

#define STACK_SIZE 1024
#define BOOT_PARAMS_MAGIC 0x48505253u
#define BOOT_PARAMS_VERSION 1u
#define BOOT_FLAG_ID_MAPPED (1ULL << 0)

#include <stddef.h>
#include <os/efi.h>

EFI_SYSTEM_TABLE* sST;
EFI_BOOT_SERVICES* sBS;

typedef struct {
    UINT64 next;
    UINT64 prev;
} BOOT_LIST;

typedef struct {
    UINT32 magic;
    UINT32 version;
    UINT32 size;
    UINT32 _reserved0;
    UINT64 flags;
} BOOT_HEADER;

struct boot_param_block {
    BOOT_HEADER hdr;

    BOOT_LIST memory_list;
    BOOT_LIST module_list;
    UINT64 setup_data;
    UINT64 kernel_phys_addr;
    UINT64 kernel_vert_addr;

    UINT64 kernel_entry;
    UINT64 kernel_size;
    UINT64 pm14_phys;
    UINT64 stack_base;
    UINT64 stack_size;
    UINT64 cmdline;
    UINT32 cmdline_len;
    UINT32 _reserved1;
    UINT64 rsdp;
    UINT32 acpi_revision;
    UINT32 _reserved2;
    UINT64 efi_sys_table;
    UINT64 efi_runtime_services;
    UINT64 loader_base;
    UINT64 loader_size;
}__attribute__((packed));

// memory.c
// void detectMemory(void);

#endif // _BOOT_H