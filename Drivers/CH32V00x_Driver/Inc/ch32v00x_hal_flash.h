
#ifndef __CH32V00x_HAL_FLASH_H
#define __CH32V00x_HAL_FLASH_H

#include "ch32v00x_hal.h"

typedef enum {
    FLASH_ERASE_64B = 0U,
    FLASH_ERASE_1KB = 1U
} FLASH_EraseModeTypeDef;

class FLASH_TypeDef {
public:
    struct {
    public:
        __IO uint32_t ACTLR;
        __IO uint32_t KEYR;
        __IO uint32_t OBKEYR;
        __IO uint32_t STATR;
        __IO uint32_t CTLR;
        __IO uint32_t ADDR;
    private:
        __IO uint32_t RESERVED;
    public:
        __IO uint32_t OBR;
        __IO uint32_t WPR;
        __IO uint32_t MODEKEYR;
        __IO uint32_t BOOT_MODEKEYR;
    } REGS;
public:
    HAL_StatusTypeDef ErasePage(uint32_t address, FLASH_EraseModeTypeDef eraseMode);
    HAL_StatusTypeDef WriteData(uint32_t address, void *data, uint32_t size);
private:
    FLASH_TypeDef(void);
    FLASH_TypeDef(FLASH_TypeDef &);

    void Lock(void);
    HAL_StatusTypeDef Unlock(void);
    HAL_StatusTypeDef GetStatus(void);
    HAL_StatusTypeDef BuffReset(void);
    HAL_StatusTypeDef LoadWord(uint32_t address, uint32_t data);
    HAL_StatusTypeDef StartFastProgram(uint32_t address);
};

#define FLASH           (*(FLASH_TypeDef *)FLASH_R_BASE)

#endif /* __CH32V00x_HAL_FLASH_H */
