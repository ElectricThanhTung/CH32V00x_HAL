
#ifndef __CH32V00x_HAL_PWR_H
#define __CH32V00x_HAL_PWR_H

#include "ch32v00x_hal.h"

typedef enum {
    PWR_PVD_LEVEL_NONE = 0xFFU,
    PWR_PVD_LEVEL_2V9 = 0U,
    PWR_PVD_LEVEL_3V1 = 1U,
    PWR_PVD_LEVEL_3V3 = 2U,
    PWR_PVD_LEVEL_3V5 = 3U,
    PWR_PVD_LEVEL_3V7 = 4U,
    PWR_PVD_LEVEL_3V9 = 5U,
    PWR_PVD_LEVEL_4V1 = 6U,
    PWR_PVD_LEVEL_4V4 = 7U
} PWR_PvdLevelTypeDef;

typedef enum {
    PWR_AWU_DIV_NONE = 0xFFU,
    PWR_AWU_DIV_1 = 0U,
    PWR_AWU_DIV_2 = 2U,
    PWR_AWU_DIV_4 = 3U,
    PWR_AWU_DIV_8 = 4U,
    PWR_AWU_DIV_16 = 5U,
    PWR_AWU_DIV_32 = 6U,
    PWR_AWU_DIV_64 = 7U,
    PWR_AWU_DIV_128 = 8U,
    PWR_AWU_DIV_256 = 9U,
    PWR_AWU_DIV_512 = 10U,
    PWR_AWU_DIV_1024 = 11U,
    PWR_AWU_DIV_2048 = 12U,
    PWR_AWU_DIV_4096 = 13U,
    PWR_AWU_DIV_10240 = 14U,
    PWR_AWU_DIV_61440 = 15U
} PWR_AwuDivTypeDef;

typedef enum {
    PWR_STANDBY_ENTRY_WFI = 1U,
    PWR_STANDBY_ENTRY_WFE = 2U
} PWR_StanbyModeTypeDef;

class PWR_TypeDef {
public:
    struct {
        __IO uint32_t CTLR;
        __IO uint32_t CSR;
        __IO uint32_t AWUCSR;
        __IO uint32_t AWUWR;
        __IO uint32_t AWUPSC;
    } REGS;
public:
    void EnableClock(void);
    void DisableClock(void);
    void SetPVD(PWR_PvdLevelTypeDef level);
    void SetAWU(PWR_AwuDivTypeDef div, uint8_t windowValue = 0x3FU);
    void EnterStandbyMode(PWR_StanbyModeTypeDef mode);
    HAL_FlagStatusTypeDef GetPVD0(void);
    void DeInit(void);
private:
    PWR_TypeDef(void);
    PWR_TypeDef(PWR_TypeDef &);
};

#define PWR             (*(PWR_TypeDef *)PWR_BASE)

#endif /* __CH32V00x_HAL_PWR_H */
