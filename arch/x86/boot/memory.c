/*
 * Detect memory on boot
 */

#include "boot.h"

EFI_STATUS Status;
EFI_MEMORY_DESCRIPTOR* memory_map;
UINTN EfiMemoryMapSize;
UINTN EfiMapKey;
UINTN EfiDescriptorSize;
uint32_t EfiDescriptorV;

EfiMemoryMapSize = 0;
EfiMemoryMap = NULL;
Status = gBS->GetMemoryMap (
    &EfiMemoryMapSize,
    EfiMemoryMap,
    &EfiMapKey,
    &EfiDescriptorSize,
    &EfiDescriptorV
);
ASSERT (Status == EFI_BUFFER_TOO_SMALL);


void detect_memory(void){
    /* GetMemoryMap() */
}