/*
 * Detect memory on boot. Initialize stack and heap.
 */

#include "boot.h"
#include "libc/string.h"

#define PAGE_SIZE   4096ULL
#define MMAP_SLACK  16

static EFI_STATUS status;
static EFI_MEMORY_DESCRIPTOR* memory_map;
static UINTN EfiMemoryMapSize;
static UINTN EfiDescriptorSize;
static UINT32 EfiDescriptorV;
UINTN EfiMapKey;

static void mem_list_init(BootList* head){
    head->next = head->prev = (UINT64)(uintptr_t)head;
}

static void mem_list_append(BootList* head, BootList* node){
    BootList* tail = (BootList*)(uintptr_t)head->prev;
    node->next = (UINT64)(uintptr_t)head;
    node->prev = (UINT64)(uintptr_t)tail;
    tail->next = (UINT64)(uintptr_t)node;
    head->prev = (UINT64)(uintptr_t)node;
}

EFI_STATUS detect_memory(struct boot_param_block* params){
    BootMemoryDesc* blocks = NULL;
    UINTN raw_cap, block_cap, count;

    if (params == NULL) return EFI_INVALID_PARAMETER;
    mem_list_init(&params->memory_list);

    memory_map = NULL;
    EfiMemoryMapSize = 0;
    status = sBS->GetMemoryMap(
        &EfiMemoryMapSize,
        memory_map,
        &EfiMapKey,
        &EfiDescriptorSize,
        &EfiDescriptorV
    );
    if (status == EFI_BUFFER_TOO_SMALL || EfiDescriptorSize == 0)
        return EFI_LOAD_ERROR;
    if (status != EFI_SUCCESS) return status;

    raw_cap = EfiMemoryMapSize + EfiDescriptorSize * MMAP_SLACK;
    block_cap = raw_cap / EfiDescriptorSize;

    status = sBS->AllocatePool(efiLoaderData, raw_cap, (VOID**)&memory_map);
    if (EFI_ERROR(status)) return status;

    count = EfiMemoryMapSize / EfiDescriptorSize;
    if (count > block_cap) return EFI_OUT_OF_RESOURCES;

    for(int i = 0; i < count; i++){
        EFI_MEMORY_DESCRIPTOR* d = 
            (EFI_MEMORY_DESCRIPTOR*)((UINT8*)memory_map + i * EfiDescriptorSize);
        BootMemoryDesc* b = &blocks[i];

        b->type = d->type;
        b->_pad = 0;
        b->base_page = d->physicalStart / PAGE_SIZE;
        b->page_count = d->numPages;
        b->attr = d->attribute;
        mem_list_append(&params->memory_list, &b->link);
    }

    return EFI_SUCCESS;
}

void mem_free(unsigned long size, unsigned long addr){
    unsigned long nr_pages;
    if (!size) return;

    nr_pages = 0; // TODO: round up(size, alloc align) / page size
    // EFI_FREE_PAGES(addr, nr_pages);
}