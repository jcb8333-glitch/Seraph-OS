#pragma once
#include <stdint.h>

#define HEADER_MAGIC 0xE85250D6u
#define BOOTLOADER_MAGIC 0x36D72689u

// Kernel header tags
#define BOOT_HTAG_END 0
#define BOOT_HTAG_BOOT_SERVICES 7
#define BOOT_HTAG_EFI_AMD64_ENTRY 9

// Boot tags
#define BOOT_TAG_END 0
#define BOOT_TAG_CMDLINE 1
#define BOOT_TAG_LOADER_NAME 2
#define BOOT_TAG_MMAP 6
#define BOOT_TAG_FRAMEBUFFER 8
#define BOOT_TAG_EFI64 12
#define BOOT_TAG_ACPI_OLD 14
#define BOOT_TAG_ACPI_NEW 15
#define BOOT_TAG_EFI_MMAP 17
#define BOOT_TAG_EFI_BS 18
#define BOOT_TAG_EFI64_IH 20

typedef struct {uint32_t magic, arch, header_len, checksum} boot_header_t;
typedef struct {uint16_t type, flags; uint32_t size;} boot_htag_t;
typedef struct {uint32_t type, size;} boot_tag_t;
typedef struct {uint64_t addr, len; uint32_t type, zero;} boot_mmap_entry_t;
