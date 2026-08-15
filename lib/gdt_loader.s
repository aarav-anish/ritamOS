BITS 32

global gdt_flush

gdt_flush:
    mov eax, [esp+4]

    lgdt[eax]

    mov ax, 0x10    ; 0x10 is the selector for your GDT data-segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.return    ; far jump to load CS. 0x08 is code-segment selector

.return:
    ret
