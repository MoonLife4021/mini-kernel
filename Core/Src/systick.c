#include "systick.h"

// STM32F103 SysTick 寄存器
#define SYSTICK_CTRL (*(volatile uint32_t *)0xE000E010)
#define SYSTICK_LOAD (*(volatile uint32_t *)0xE000E014)
#define SYSTICK_VAL (*(volatile uint32_t *)0xE000E018)

#define CTRL_ENABLE (1 << 0)
#define CTRL_TICKINT (1 << 1)
#define CTRL_CLKSRC (1 << 2)

static volatile uint32_t s_tick_ms = 0;

void systick_init(void)
{
    /* 72MHz / 1000 = 72000 -> 1ms 中断一次 */
    SYSTICK_LOAD = 72000 - 1;
    SYSTICK_VAL = 0;
    SYSTICK_CTRL = CTRL_ENABLE | CTRL_TICKINT | CTRL_CLKSRC;
}

uint32_t systick_get_ms(void)
{
    return s_tick_ms;
}

/*在stm32f1xx_it.c的SysTick_Handler中调用*/
void systick_inc(void)
{
    s_tick_ms++;
}
