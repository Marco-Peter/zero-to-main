#include "hal.h"
#include <sys/stat.h>
#include <stdbool.h>

#define SYS_CLOCK_RATE 16000000
#define BAUDRATE 115200

unsigned char _end;

static void send_character(unsigned char c);
static char receive_character(void);

void init_system_clock(void)
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

        LL_Init1msTick(SYS_CLOCK_RATE);
        LL_SetSystemCoreClock(SYS_CLOCK_RATE);
}

void init_usart2()
{
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
        LL_USART_Disable(USART2);
        LL_USART_SetTransferDirection(USART2, LL_USART_DIRECTION_TX_RX);
        LL_USART_ConfigCharacter(USART2, LL_USART_DATAWIDTH_8B,
                                 LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
        LL_USART_SetBaudRate(USART2, SYS_CLOCK_RATE, LL_USART_PRESCALER_DIV1,
                             LL_USART_OVERSAMPLING_8, BAUDRATE);
}

int _close(int fd) {
        return -1;
}

int _fstat(int file, struct stat *st)
{
        st->st_mode = S_IFCHR;
        return 0;
}

int _isatty(int file)
{
        return 1;
}

int _lseek(int file, int offset, int whence) {
        return 0;
}

void _exit(int status)
{
        __asm("BKPT #0");
        while(true);
}

void _kill(int pid, int sig)
{
        return;
}

int _getpid(void)
{
        return -1;
}

int _write(int fd, char *buf, int count)
{
        int written;

        for (written = 0; written < count; ++written) {
                send_character(buf[written]);
        }
        return written;
}

int _read(int fd, char *buf, int count)
{
        int read;

        for (read = 0; read < count; ++read) {
                buf[read] = receive_character();
        }
        return read;
}

void *_sbrk(int incr)
{
        static unsigned char *heap = &_end;
        unsigned char *prev_heap = heap;

        heap += incr;
        return prev_heap;
}

static void send_character(unsigned char c)
{
        while(!LL_USART_IsActiveFlag_TXE(USART2));
        LL_USART_TransmitData8(USART2, (uint8_t)c);
}

static char receive_character(void)
{
        while(!LL_USART_IsActiveFlag_RXNE(USART2));
        return (char)LL_USART_ReceiveData8(USART2);
}
