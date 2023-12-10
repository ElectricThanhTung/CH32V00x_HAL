
#include "ch32v00x_hal.h"

#define __HAL_GetTickInterval()                 ((RCC.HCLK.GetFreq() / 8000U) * TickIntervalMs)

static uint32_t TickIntervalMs = 1;

/**
 * @brief  Initializes the HAL library.
 * @note   This function will also initialize the systick with HCLK/8 and enable interrupts.
 * @retval None.
 */
void HAL_TypeDef::Init(void) {
    SysTick->CTLR = STK_CTLR_STE | STK_CTLR_STIE;
    TickIntervalMs = 1U;

    NVIC_SetPriority(SysTicK_IRQn, 0U);
    NVIC_DisableIRQ(SysTicK_IRQn);
}

/**
 * @brief  Returns the tick value in microseconds.
 * @retval Tick value in microseconds.
 */
uint32_t HAL_TypeDef::GetTickUs(void) {
    return SysTick->CNT / (RCC.HCLK.GetFreq() / 8000000U);
}

/**
 * @brief  Returns the tick value in milliseconds.
 * @retval Tick value in milliseconds.
 */
uint32_t HAL_TypeDef::GetTickMs(void) {
    return SysTick->CNT / (RCC.HCLK.GetFreq() / 8000U);
}

/**
 * @brief  Delay in microseconds.
 * @param  time delay time in microseconds.
 * @retval None.
 */
void HAL_TypeDef::DelayUs(uint32_t time) {
    uint32_t tickstart = SysTick->CNT;
    time *= RCC.HCLK.GetFreq() / 8000000U;
    while((uint32_t)(SysTick->CNT - tickstart) < time);
}

/**
 * @brief  Delay in milliseconds.
 * @param  time delay time in milliseconds.
 * @retval None.
 */
void HAL_TypeDef::DelayMs(uint32_t time) {
    uint32_t tickstart = SysTick->CNT;
    time *= RCC.HCLK.GetFreq() / 8000U;
    while((uint32_t)(SysTick->CNT - tickstart) < time);
}

/**
 * @brief  Interrupt handler for SysTick.
 * @retval None.
 */
__INTERRUPT void SysTick_Handler(void) {
    uint32_t tick = SysTick->CNT;
    SysTick->SR = 0x00;
    SysTick->CMP = tick + __HAL_GetTickInterval();
}

/**
 * @brief  Enable interrupt and set interval value for systick.
 * @param  interval value in milliseconds for systick.
 * @note   The minimum value for time parameter is 1.
 * @retval None.
 */
void HAL_TypeDef::EnabelTickIRQ(uint32_t interval) {
    if(interval == 0U)
        interval = 1U;
    TickIntervalMs = interval;
    SysTick->CMP = SysTick->CNT + __HAL_GetTickInterval();
    NVIC_EnableIRQ(SysTicK_IRQn);
}

/**
 * @brief  Disable systick interrupt.
 * @retval None.
 */
void HAL_TypeDef::DisableTickIRQ(void) {
    NVIC_DisableIRQ(SysTicK_IRQn);
}
