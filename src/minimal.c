#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "hal.h"

uint32_t SystemCoreClock = 16000000UL;

int main(void)
{
        init_system_clock();
        init_usart2();
        //printf("Hello World!");
        puts("Hello World!");
}
