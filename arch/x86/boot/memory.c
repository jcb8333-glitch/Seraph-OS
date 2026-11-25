/*
 * Detect memory on boot. Initialize stack and heap.
 */

#include "boot.h"

EFI_STATUS status;
EFI_MEMORY_DESCRIPTOR* memory_map;
UINTN EfiMemoryMapSize;
UINTN EfiMapKey;
UINTN EfiDescriptorSize;
UINT32 EfiDescriptorV;

EFI_STATUS get_mem_map(){
    memory_map = NULL;
    status = sBS->GetMemoryMap(
        &EfiMemoryMapSize,
        memory_map,
        &EfiMapKey,
        &EfiDescriptorSize,
        &EfiDescriptorV
    );
    if (status == EFI_BUFFER_TOO_SMALL) return EFI_LOAD_ERROR;

    if (status != EFI_SUCCESS) return status;

    return EFI_SUCCESS;
}

void mem_free(unsigned long size, unsigned long addr){
    unsigned long nr_pages;
    if (!size) return;

    nr_pages = 0; // TODO: round up(size, alloc align) / page size
    // EFI_FREE_PAGES(addr, nr_pages);
}