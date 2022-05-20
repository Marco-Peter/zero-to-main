#ifndef __INC_HAL_H
#define __INC_HAL_H

#include <stm32g0xx_ll_gpio.h>
#include <stm32g0xx_ll_usart.h>

/* virtual COM port on STM32G031K8 */
#ifndef CONSOLE_UART
#define CONSOLE_UART    USART2
#endif

#ifndef CONSOLE_BAUDRATE
#define CONSOLE_BAUDRATE 115200UL
#endif

#ifndef CONSOLE_PARITY
#define CONSOLE_PARITY  LL_USART_PARITY_NONE
#endif

#ifndef CONSOLE_TX_PORT
#define CONSOLE_TX_PORT GPIOA
#endif

#ifndef CONSOLE_TX_PIN
#define CONSOLE_TX_PIN  LL_GPIO_PIN_2
#endif

#ifndef CONSOLE_TX_AF
#define CONSOLE_TX_AF   LL_GPIO_AF_1
#endif

#ifndef CONSOLE_TX_PULL
#define CONSOLE_TX_PULL LL_GPIO_PULL_UP
#endif

#ifndef CONSOLE_RX_PORT
#define CONSOLE_RX_PORT GPIOA
#endif

#ifndef CONSOLE_RX_PIN
#define CONSOLE_RX_PIN  LL_GPIO_PIN_3
#endif

#ifndef CONSOLE_RX_AF
#define CONSOLE_RX_AF   LL_GPIO_AF_1
#endif

#ifndef CONSOLE_RX_PULL
#define CONSOLE_RX_PULL LL_GPIO_PULL_UP
#endif

void hal_init(void);

#endif /* __INC_HAL_H */