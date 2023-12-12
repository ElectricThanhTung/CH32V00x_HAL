
#ifndef __CH32V00x_HAL_IWDG_H
#define __CH32V00x_HAL_IWDG_H

#include "ch32v00x_hal.h"

typedef enum {
    IWDG_DIV_4 = 0U,
    IWDG_DIV_8 = 1U,
    IWDG_DIV_16 = 2U,
    IWDG_DIV_32 = 3U,
    IWDG_DIV_64 = 4U,
    IWDG_DIV_128 = 5U,
    IWDG_DIV_256 = 6U
} IWDG_DivTypeDef;

class IWDG_TypeDef {
public:
    struct {
    public:
        __IO uint32_t CTLR;
        __IO uint32_t PSCR;
        __IO uint32_t RLDR;
        __IO uint32_t STATR;
    } REGS;
public:
    void SetPrescaler(IWDG_DivTypeDef div);
    void SetReload(uint16_t value);
    void Reset(void);
    void Start(void);
private:
    IWDG_TypeDef(void);
    IWDG_TypeDef(IWDG_TypeDef &);
};

#define IWDG            ((IWDG_TypeDef *)IWDG_BASE)

#endif /* __CH32V00x_HAL_IWDG_H */
