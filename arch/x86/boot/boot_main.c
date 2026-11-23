#include "boot.h"
#include "boot_io.h"
#include "libc/string.h"

struct port_io_ops p_io_ops;
struct boot_param_block boot_params __attribute__((aligned(16)));

static void init_boot_params(EFI_HANDLE image, EFI_SYSTEM_TABLE* gST){
    
    memset(&boot_params, 0x0, sizeof(boot_params));

    boot_params.hdr.magic = BOOT_PARAMS_MAGIC;
    boot_params.hdr.version = BOOT_PARAMS_VERSION;
    boot_params.hdr.size = sizeof(boot_params);
    boot_params.hdr.flags = BOOT_FLAG_ID_MAPPED;

    boot_params.memory_list.next = boot_params.memory_list.prev =
        (UINT64)(uintptr_t)&boot_params.memory_list;
    boot_params.module_list.next = boot_params.module_list.prev =
        (UINT64)(uintptr_t)&boot_params.module_list;
    boot_params.efi_sys_table = (UINT64)(uintptr_t) gST;

    (void)image;
}

static void init_heap(){

}

void main(EFI_HANDLE handle, EFI_SYSTEM_TABLE* sys_table){
    EFI_STATUS status;

    /* Init std io */
    init_default_io_ops();

    /* Get boot header */
    init_boot_params(handle, sys_table);

    /* Init console */

    /* Check CPU and set mode */

    /* Detect memory */

    /* Exit boot services / perform last steps*/
}