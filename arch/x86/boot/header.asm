bits 64

B_MAGIC equ 0xE85250D6

section .boot progbits alloc noexec nowrite align=8

b_start:
    dd B_MAGIC
    dd 0                ; i386 code
    dd b_end - b_start
    dd 0x100000000 - (B_MAGIC + 0 + (b_end - b_start))

    dw 9, 0             ; EFI amd64 entry address tag
    dd 12
    dd efi64_entry
    dd 0                ; 8 byte pad tag

    dw 0, 0             ; end tag
    dd 8
b_end:

section .text
global efi64_entry
extern kernel_main

efi64_entry:
    cli
    mov edi, ebx
    mov esi, eax
    lea rsp, [rel boot_stack_top]
    xor ebp, ebp
    call kernel_main

.hang:
    hlt
    jmp .hang

section .bss align=16
boot_stack: resb
boot_stack_top: