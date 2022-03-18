#include <stdint.h>
#include <stdbool.h>

#include <stm32g0xx_ll_rcc.h>
#include <stm32g0xx_ll_bus.h>
#include <stm32g0xx_ll_system.h>
#include <stm32g0xx_ll_cortex.h>
#include <stm32g0xx_ll_utils.h>

uint32_t SystemCoreClock = 16000000UL;

int main(void)
{
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);


        LL_RCC_HSI_Enable();
        while(LL_RCC_HSI_IsReady() != 1)
        {
        }

        LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
        LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
        while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
        {
        }
        LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

        LL_Init1msTick(16000000);
        LL_SetSystemCoreClock(16000000);
 
        return 0;
}

void _exit(int status)
{
        __asm("BKPT #0");
        while(true);
}
