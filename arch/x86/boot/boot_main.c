#include "boot.h"
#include "boot_io.h"
#include "libc/string.h"

struct port_io_ops p_io_ops;
struct boot_param_block boot_params __attribute__((aligned(16)));


static void init_boot_params(EFI_HANDLE image, EFI_SYSTEM_TABLE* gST){
    
    memset(&boot_params, 0x0, sizeof(boot_params));

    boot_params.hdr.magic = BOOT_PARAMS_MAGIC;
    boot_params.hdr.majorVersion = BOOT_PARAMS_VERSION;
    boot_params.hdr.size = sizeof(boot_params);
    boot_params.hdr.flags = BOOT_FLAG_ID_MAPPED;

    boot_params.memory_list.next = boot_params.memory_list.prev =
        (UINT64)(uintptr_t)&boot_params.memory_list;
    boot_params.module_list.next = boot_params.module_list.prev =
        (UINT64)(uintptr_t)&boot_params.module_list;
    boot_params.firmwInfo.efi_sys_table = (UINT64)(uintptr_t) gST;

    (void)image;
}

static EFI_STATUS exit_boot(EFI_HANDLE handle, struct boot_param_block* params){
    EFI_STATUS status;

    for(int n = 0; n < 2; n++){
        status = get_mem_map();
        if(EFI_ERROR(status)) return status;

        status = sBS->ExitBootServices(handle, EfiMapKey);
        if (!EFI_ERROR(status)) return EFI_SUCCESS;
    }
    return EFI_SUCCESS;
}

void main(EFI_HANDLE handle, EFI_SYSTEM_TABLE* sys_table){

    /* Init std io */
    init_default_io_ops();

    /* Get boot header */
    init_boot_params(handle, sys_table);

    /* Init console */

    /* Check CPU and set mode */

    /* Detect memory */
    build_mem_list(&boot_params);

    /* Exit boot services / perform last steps*/
    exit_boot(handle, &boot_params);
}