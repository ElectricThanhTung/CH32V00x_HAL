
#ifndef __CH32V00x_HAL_GPIO_H
#define __CH32V00x_HAL_GPIO_H

#include "ch32v00x_hal.h"

typedef enum {
    GPIO_MODE_ANALOG_IN = 0x00,
    GPIO_MODE_INPUT = 0x04,
    GPIO_MODE_INPUT_PD = 0x28,
    GPIO_MODE_INPUT_PU = 0x48,
    GPIO_MODE_OUTPUT_OD = 0x14,
    GPIO_MODE_OUTPUT_PP = 0x10,
    GPIO_MODE_AF_OD = 0x1C,
    GPIO_MODE_AF_PP = 0x18
} GPIO_ModeTypeDef;

typedef enum {
    GPIO_SPEED_10MHZ = 0U,
    GPIO_SPEED_2MHZ = 1U,
    GPIO_SPEED_50MHZ = 2U
} GPIO_SpeedTypeDef;

typedef enum {
  GPIO_STATE_RESET = 0U,
  GPIO_STATE_SET = 1U
} GPIO_StateTypeDef;

class GPIO_TypeDef {
public:
    struct {
    public:
        __IO uint32_t CFGLR;
        __IO uint32_t CFGHR;
        __IO uint32_t INDR;
        __IO uint32_t OUTDR;
        __IO uint32_t BSHR;
        __IO uint32_t BCR;
        __IO uint32_t LCKR;
    } REGS;
public:
    void EnableClock(void);
    void DisableClock(void);
    void SetMode(uint32_t pin, GPIO_ModeTypeDef mode, GPIO_SpeedTypeDef speed = GPIO_SPEED_50MHZ);
    GPIO_StateTypeDef ReadPin(uint32_t pin);
    void WritePin(uint32_t pin, GPIO_StateTypeDef state);
    void SetPin(uint32_t pin);
    void ResetPin(uint32_t pin);
    void TogglePin(uint32_t pin);
    void LockPin(uint32_t pin);
    void DeInit(uint32_t pin);
private:
    GPIO_TypeDef(void);
    GPIO_TypeDef(GPIO_TypeDef &);
};

/**
 * @brief  Definition for GPIO PIN
 */
#define GPIO_PIN_0      (1UL << 0U)
#define GPIO_PIN_1      (1UL << 1U)
#define GPIO_PIN_2      (1UL << 2U)
#define GPIO_PIN_3      (1UL << 3U)
#define GPIO_PIN_4      (1UL << 4U)
#define GPIO_PIN_5      (1UL << 5U)
#define GPIO_PIN_6      (1UL << 6U)
#define GPIO_PIN_7      (1UL << 7U)
#define GPIO_PIN_8      (1UL << 8U)
#define GPIO_PIN_9      (1UL << 9U)
#define GPIO_PIN_10     (1UL << 10U)
#define GPIO_PIN_11     (1UL << 11U)
#define GPIO_PIN_12     (1UL << 12U)
#define GPIO_PIN_13     (1UL << 13U)
#define GPIO_PIN_14     (1UL << 14U)
#define GPIO_PIN_15     (1UL << 15U)
#define GPIO_PIN_ALL    (0xFFFF)

#define GPIOA           (*(GPIO_TypeDef *)GPIOA_BASE)
#define GPIOC           (*(GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD           (*(GPIO_TypeDef *)GPIOD_BASE)

#endif /* __CH32V00x_HAL_GPIO_H */
