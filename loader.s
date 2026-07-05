BITS 32

; Make the loader symbol visible to the linker
global loader

extern testfunc

MAGIC_NUMBER        equ 0x1BADB002
FLAGS               equ 0x0
CHECK_SUM           equ - (MAGIC_NUMBER + FLAGS)
KERNEL_STACK_SIZE   equ 4096

; --------------------------------------
; Multiboot Header
; Required by GRUB to recognize
; this kernel as Multiboot-compliant.
; --------------------------------------
section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECK_SUM

; --------------------------------------
; Kernel Entry Point
; --------------------------------------
section .text
loader:
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    push dword 3
    push dword 2
    push dword 1
    call testfunc
    add esp, 12
.hang:
    jmp .hang

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .note.GNU-stack noalloc
