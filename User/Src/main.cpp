
#include "ch32v00x_hal.h"
#include "stopwatch.h"

void RCC_Init(void) {
    RCC.HSI.Enable();
    RCC.PLL.SetSource(RCC_PLLSRC_HSI);
    RCC.HSE.Disable();
    RCC.SysClk.SetSource(RCC_SYSCLKSRC_PLL);
    RCC.HCLK.SetDiv(RCC_SYSCLK_DIV1);
}

void GPIO_Init(void) {
    GPIOC.EnableClock();
    GPIOC.SetMode(GPIO_PIN_ALL, GPIO_MODE_OUTPUT_PP);
    GPIOC.WritePin(GPIO_PIN_ALL, GPIO_STATE_SET);
}

int main(void) {
    HAL.Init();
    RCC_Init();
    GPIO_Init();
    while(1) {
        GPIOC.TogglePin(GPIO_PIN_ALL);
        HAL.DelayMs(500);
    }
}
