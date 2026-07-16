BITS 32

; Make the loader symbol visible to the linker
global loader

extern kernel_main

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
    call kernel_main

    ; move cursor to row 2 and column 5
    mov dx, 0x3D4
    mov al, 0x0E
    out dx, al
    mov dx, 0x3D5
    mov al, (0xA5 >> 8) & 0xFF
    out dx, al

    mov dx, 0x3D4
    mov al, 0x0F
    out dx, al
    mov dx, 0x3D5
    mov al, (0xA5 & 0xFF)
    out dx, al

    ; scroll 2 lines
    mov dx, 0x3D4
    mov al, 0x0C
    out dx, al
    mov dx, 0x3D5
    mov al, (0xA0 >> 8) & 0xFF
    out dx, al

    mov dx, 0x3D4
    mov al, 0x0D
    out dx, al
    mov dx, 0x3D5
    mov al, 0xA0 & 0xFF
    out dx, al

.hang:
    jmp .hang

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .note.GNU-stack noalloc
