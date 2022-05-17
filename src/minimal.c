#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "hal.h"

uint32_t SystemCoreClock = 16000000UL;

int main(void)
{
        static int count;

        count = printf("Hello World!\n");
        //count = puts("Hello World!");
        count++;
}
