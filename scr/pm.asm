bits 16


start:

    cli
    xor ax, ax
    mov ds, ax
    mov es, ax


    mov ax, 0x4F01
    mov cx, 0x110
    mov di, 0x7000
    int 0x10
    cmp ax, 0x4F
    jne vbe_fail


    mov ax, 0x4F02
    mov bx, 0x4110
    int 0x10
    cmp ax, 0x4F
    jne vbe_fail


    mov si, 0x7000
    mov ax, si


    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_pm

bits 32
init_pm:

    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    extern stack_top
    mov esp, stack_top


    extern main
    call main

.hang:
    jmp .hang

    vbe_fail:
        jmp $

gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF ; code
    dq 0x00CF92000000FFFF ; data
gdt_end:




gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10


