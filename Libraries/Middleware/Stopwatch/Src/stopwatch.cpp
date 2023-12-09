
#include "stopwatch.h"

/**
 * @brief  Constructor of stopwatch.
 * @retval None.
 */
Stopwatch::Stopwatch(void) {
    enabled = false;
}

/**
 * @brief  Start the stopwatch.
 * @retval None.
 */
void Stopwatch::Start(void) {
    if(enabled == false) {
        startTick = SysTick->CNT;
        enabled = true;
    }
}

/**
 * @brief  Stop the stopwatch.
 * @retval None.
 */
void Stopwatch::Stop(void) {
    enabled = false;
}

/**
 * @brief  Return the elapsed ticks value since stopwatch was started.
 * @retval Elapsed ticks.
 */
uint32_t Stopwatch::ElapsedTicks(void) {
    return (enabled == true) ? SysTick->CNT - startTick : 0U;
}

/**
 * @brief  Return the elapsed value in milliseconds since stopwatch was started.
 * @retval Elapsed in milliseconds.
 */
uint32_t Stopwatch::ElapsedMilliseconds(void) {
    if(enabled == true)
        return (SysTick->CNT - startTick) / (RCC.GetHCLKFreq() / 8000U);
    return 0U;
}

/**
 * @brief  Return the elapsed value in microseconds since stopwatch was started.
 * @retval Elapsed in microseconds.
 */
uint32_t Stopwatch::ElapsedMicroseconds(void) {
    if(enabled == true)
        return (SysTick->CNT - startTick) / (RCC.GetHCLKFreq() / 8000000U);
    return 0U;
}
