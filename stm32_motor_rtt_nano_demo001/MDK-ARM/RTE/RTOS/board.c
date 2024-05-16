/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <stm32f1xx_hal.h>
#include "main.h"
#include "stm32f1xx_hal_uart.h"
#include <usart.h>


static int uart_init(void);

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (15*1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/* board.c */

/* timer ??????????? rt_os_tick_callback function,cortex-m ???? SysTick_Handler() */
void rt_os_tick_callback(void)
{
  rt_interrupt_enter(); /* ????????? */

  rt_tick_increase();  /* RT-Thread ?????? */

  rt_interrupt_leave(); /* ????????? */
}
/**
 * This function will initial your board.
 */
void rt_hw_board_init(void)
{
  /*
   * TODO 1: OS Tick Configuration
   * Enable the hardware timer and call the rt_os_tick_callback function
   * periodically with the frequency RT_TICK_PER_SECOND.
   */
	
  /* 1????????? */
  HAL_Init(); // ??? HAL ?
  SystemClock_Config(); // ??????
  SystemCoreClockUpdate(); // ?????????
	uart_init();
  /* 2?OS Tick ????,RT_TICK_PER_SECOND = 1000 ?? 1ms ?????? */
  SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

  /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
  rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
  rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

#ifdef RT_USING_CONSOLE

static UART_HandleTypeDef UartHandle;
static int uart_init(void)
{
    /* ???????,?????????? */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
    return 0;
}
INIT_BOARD_EXPORT(uart_init);  /* ??????????:??? INIT_BOARD_EXPORT ??????? */

#endif



/* cortex-m ???? SysTick_Handler() */
void SysTick_Handler()
{
    rt_os_tick_callback();
}






