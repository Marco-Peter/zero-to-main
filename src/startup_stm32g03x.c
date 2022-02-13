#include <stdint.h>

extern const uint32_t _etext;
extern const uint32_t _sdata;
extern const uint32_t _edata;
extern const uint32_t _sbss;
extern const uint32_t _ebss;
extern const uint32_t _sstack;
extern const uint32_t _estack;

typedef void (*interrupt_function)(void);

static void reset_handler(void);
static void nmi_handler(void);
static void hardfault_handler(void);
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
        /* Copy init values from text to data */
        const uint32_t *init_values_ptr = &_etext;
        uint32_t *data_ptr = (uint32_t *)&_sdata;

        if (init_values_ptr != data_ptr) {
                while (data_ptr < &_edata) {
                        *data_ptr++ = *init_values_ptr++;
                }
        }

        /* Clear the zero segment */
        for (uint32_t *bss_ptr = (uint32_t *)&_sbss; bss_ptr < &_ebss;) {
                *bss_ptr++ = 0;
        }

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
