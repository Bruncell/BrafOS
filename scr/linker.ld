ENTRY(start)

SECTIONS {
    . = 0x8000;

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .rodata : {
        *(.rodata*)
    }

    .bss : {
        *(.bss)
        *(COMMON)
    

    /* Поместим стек после всех остальных данных */
    . = ALIGN(16);
    stack_bottom = .;
    . = . + 0x4000; /* 16 KB */
    stack_top = .;
    }
}

