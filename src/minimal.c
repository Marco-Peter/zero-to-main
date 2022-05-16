#include <stdint.h>
#include <stdbool.h>

#include "hal.h"

uint32_t SystemCoreClock = 16000000UL;

int main(void)
{
        init_system_clock();
}

void _exit(int status)
{
        __asm("BKPT #0");
        while(true);
}
