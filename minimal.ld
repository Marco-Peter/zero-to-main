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
                . = ALIGN(4);
                _stext = .;
                KEEP(*(.vectors .vectors.*))
                *(.text .text.*)
                *(.rodata .rodata*)
                _etext = .;
        } > rom

        /* .ARM.exidx is sorted, so has to go in its own output section. */
        PROVIDE_HIDDEN (__exidx_start = .);
        .ARM.exidx :
        {
                *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        } > rom
        PROVIDE_HIDDEN (__exidx_end = .);

        . = ALIGN(4);
        _etext = .;

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
                . = ALIGN(4);
                _sbss = .;
                *(.bss .bss.*)
                *(COMMON)
                . = ALIGN(4);
                _ebss = .;
        } > ram

        .data :
        {
                . = ALIGN(4);
                _sdata = .;
                *(.data .data.*);
                . = ALIGN(4);
                _edata = .;
        } > ram AT > rom

        . = ALIGN(4);
        _end = .;
}