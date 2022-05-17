#include <stdint.h>
#include <stdlib.h>
#include "hal.h"

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sstack;
extern uint32_t _estack;

typedef void (*interrupt_function)(void);

void __libc_init_array(void);
static void reset_handler(void);
static void nmi_handler(void);
static void hardfault_handler(void);
static void copy_initvals(void);
static void clear_bss(void);
int main(void);

__attribute__ ((section(".vectors")))
const struct {
        void *stack_pointer;
        interrupt_function reset_handler;
        interrupt_function nmi_handler;
        interrupt_function hardfault_handler;
} exception_table = {
        .stack_pointer = (void *)&_estack,
        .reset_handler = reset_handler,
        .nmi_handler = nmi_handler,
        .hardfault_handler = hardfault_handler,
};

static void reset_handler(void)
{
        copy_initvals();
        clear_bss();

        /* Run constructors / initializers */
        //__libc_init_array();
        init_system_clock();
        init_usart2();

        /* Branch to main function */
        main();

        /* Do not run off into the weeds, should main ever return */
        while (1);
}

static void nmi_handler(void)
{
        while (1);
}

static void hardfault_handler(void)
{
        while (1);
}

/** Copy initial values from text to data */
static void copy_initvals(void)
{
        const uint32_t *init_values_ptr = &_etext;
        uint32_t *data_ptr = (uint32_t *)&_sdata;

        if (init_values_ptr != data_ptr) {
                while (data_ptr < &_edata) {
                        *data_ptr++ = *init_values_ptr++;
                }
        }
}

/** Clear the zero segment */
static void clear_bss(void)
{
        for (uint32_t *bss_ptr = (uint32_t *)&_sbss; bss_ptr < &_ebss;) {
                *bss_ptr++ = 0;
        }
}
