
#ifndef __CH32V00x_HAL_SRAM_H
#define __CH32V00x_HAL_SRAM_H

#include "ch32v00x_hal.h"

class SRAM_TypeDef {
public:
    void EnableClockInSleepMode(void);
    void DisableClockInSleepMode(void);
private:
    SRAM_TypeDef(void);
    SRAM_TypeDef(SRAM_TypeDef &);
};

#define SRAM            (*(SRAM_TypeDef *)0x20000000UL)

#endif /* __CH32V00x_HAL_SRAM_H */
