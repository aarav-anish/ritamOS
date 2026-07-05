BITS 32

; Make the loader symbol visible to the linker
global loader

MAGIC_NUMBER    equ 0x1BADB002
FLAGS           equ 0x0
CHECK_SUM       equ - (MAGIC_NUMBER + FLAGS)

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
    mov eax, 0xABCDEF00
.hang:
    jmp .hang
