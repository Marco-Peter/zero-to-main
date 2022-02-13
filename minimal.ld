MEMORY
{
        rom (rx)        : ORIGIN = 0x08000000, LENGTH = 64K
        ram (rwx)       : ORIGIN = 0x20000000, LENGTH = 8K
}

STACK_SIZE = 0x1000;

SECTIONS
{
        .text :
        {
                KEEP(*(.vectors .vectors.*))
                *(.text .text.*)
                *(.rodata.*)
                _etext = .;
        } > rom

        .stack (NOLOAD) :
        {
                . = ALIGN(8);
                _sstack = .;
                . = . + STACK_SIZE;
                . = ALIGN(8);
                _estack = .;
        } > ram

        .bss (NOLOAD) :
        {
                _sbss = .;
                *(.bss .bss.*)
                *(COMMON)
                _ebss = .;
        } > ram

        .data :
        {
                _sdata = .;
                *(.data*);
                _edata = .;
        } > ram AT > rom

        . = ALIGN(4);
        _end = .;
}