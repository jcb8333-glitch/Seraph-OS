/**
 * EFI helper definitions
 */

#ifndef _EFI_LIB_H
#define _EFI_LIB_H

typedef struct {
    struct {
        UINT8 ei_mag0;
        UINT8 ei_mag1;
        UINT8 ei_mag2;
        UINT8 ei_mag3;
        UINT8 ei_class;
        UINT8 ei_data;
        UINT8 ei_version;
        UINT8 ei_osabi;
        UINT8 ei_abiversion;
        UINT8 ei_pad[7];
    } e_ident;

    UINT16 e_type;
    UINT16 e_machine;
    UINT32 e_version;
    UINT64 e_entry;
    UINT64 e_phoff;
    UINT64 e_shoff;
    UINT32 e_flags;
    UINT16 e_ehsize;
    UINT16 e_phentsize;
    UINT16 e_phnum;
    UINT16 e_shentsize;
    UINT16 e_shnum;
    UINT16 e_shstrndx;
} ELF_Header_64;

#endif // _EFI_LIB_H
