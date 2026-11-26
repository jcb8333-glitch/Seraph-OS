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
} BootList;

/*
 * This struct is how the data from the memory map is stored in the kernel.
 * BootList is used to form a doubly linked list where the nodes are a block
 * of memory. A memory block's previous and next blocks point to physical
 * addresses.
 */
typedef struct {
    BootList link;
    UINT32 type;
    UINT32 _pad;
    UINT64 base_page;
    UINT64 page_count;
    UINT64 attr;
} BootMemoryDesc;

typedef struct {
    UINT32 magic;
    UINT32 majorVersion;
    UINT32 minorVersion;
    UINT32 size;
    UINT32 _reserved0;
    UINT64 flags;
} BootHeader;

typedef struct {
    UINT64 rsdp;
    UINT32 acpi_revision;
    UINT64 efi_sys_table;
    UINT64 efi_runtime_services;
} FirmwareData;

/*
 * Data in this struct is filled during boot services
 * and used to prepare for control to be passed to the
 * kernel.
 */
struct boot_param_block {
    BootHeader hdr;

    BootList memory_list;
    BootList module_list;
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
    FirmwareData firmwInfo;
    UINT64 loader_base;
    UINT64 loader_size;
}__attribute__((packed));

// memory.c
void get_mem_map(struct boot_param_block params);

#endif // _BOOT_H