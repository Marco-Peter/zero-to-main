#ifndef __INC_HAL_H
#define __INC_HAL_H

#include <stm32g0xx_ll_rcc.h>
#include <stm32g0xx_ll_bus.h>
#include <stm32g0xx_ll_system.h>
#include <stm32g0xx_ll_cortex.h>
#include <stm32g0xx_ll_utils.h>

void init_system_clock(void);

#endif /* __INC_HAL_H */