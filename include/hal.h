#ifndef __INC_HAL_H
#define __INC_HAL_H

#include <stm32g0xx_ll_gpio.h>
#include <stm32g0xx_ll_usart.h>

/* virtual COM port on STM32G031K8 */
#define CONSOLE_UART    USART2
#define CONSOLE_BAUDRATE 115200UL
#define CONSOLE_PARITY  LL_USART_PARITY_NONE

#define CONSOLE_TX_PORT GPIOA
#define CONSOLE_TX_PIN  LL_GPIO_PIN_2
#define CONSOLE_TX_AF   LL_GPIO_AF_1
#define CONSOLE_TX_PULL LL_GPIO_PULL_UP

#define CONSOLE_RX_PORT GPIOA
#define CONSOLE_RX_PIN  LL_GPIO_PIN_3
#define CONSOLE_RX_AF   LL_GPIO_AF_1
#define CONSOLE_RX_PULL LL_GPIO_PULL_UP


void hal_init(void);

#endif /* __INC_HAL_H */