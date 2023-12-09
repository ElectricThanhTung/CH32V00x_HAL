
#include "ch32v00x_hal_flash.h"

#define FLASH_KEY1      (0x45670123UL)
#define FLASH_KEY2      (0xCDEF89ABUL)

/**
 * @brief  Unlock the FLASH.
 * @note   Before each erase or program flash action needs to be unlocked first.
 *         After an unsuccessful unlock operation, the bit will not be changed
 *         again until the next system reset
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::Unlock(void) {
    if(REGS.CTLR & FLASH_CTLR_LOCK) {
        REGS.KEYR = FLASH_KEY1;
        REGS.KEYR = FLASH_KEY2;

        if(REGS.CTLR & FLASH_CTLR_LOCK)
            return HAL_ERROR;
    }
    if(REGS.CTLR & FLASH_CTLR_FLOCK) {
        REGS.MODEKEYR = FLASH_KEY1;
        REGS.MODEKEYR = FLASH_KEY2;

        if(REGS.CTLR & FLASH_CTLR_FLOCK)
            return HAL_ERROR;
    }
    return HAL_OK;
}

/**
 * @brief  Lock the FLASH.
 * @note   After flash lock, erase or write operations cannot be performed
 *         without first unlocking
 * @retval HAL status.
 */
void FLASH_TypeDef::Lock(void) {
    REGS.CTLR |= FLASH_CTLR_FLOCK | FLASH_CTLR_LOCK;
}

/**
 * @brief  Get FLASH status.
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::GetStatus(void) {
    if(REGS.STATR & FLASH_STATR_BUSY)
        return HAL_BUSY;
    else if(REGS.STATR & FLASH_STATR_WRPRTERR)
        return HAL_ERROR;
    else if(REGS.STATR & FLASH_STATR_EOP)
        return HAL_OK;
    return HAL_ERROR;
}

/**
 * @brief  Reset BUF.
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::BuffReset(void) {
    HAL_StatusTypeDef status;
    REGS.STATR |= FLASH_STATR_EOP;
    REGS.CTLR |= FLASH_CTLR_FTPG;
    REGS.CTLR |= FLASH_CTLR_BUFRST;
    do {
        status = GetStatus();
    } while(status == HAL_BUSY);
    REGS.CTLR &= ~FLASH_CTLR_FTPG;
    return status;
}

/**
 * @brief  Load a word to BUF.
 * @param  address specifies address to be loaded.
 * @param  data specifies data to be loaded.
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::LoadWord(uint32_t address, uint32_t data) {
    HAL_StatusTypeDef status;
    *(uint32_t *)address = data;
    REGS.STATR |= FLASH_STATR_EOP;
    REGS.CTLR |= FLASH_CTLR_FTPG;
    REGS.CTLR |= FLASH_CTLR_BUFLOAD;
    do {
        status = GetStatus();
    } while(status == HAL_BUSY);
    REGS.CTLR &= ~FLASH_CTLR_FTPG;
    return status;
}

/**
 * @brief  Start fast program data from BUF to flash.
 * @param  address specifies FLASH page address to be programmed, it must be the starting address
 *         of FLASH page 64B.
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::StartFastProgram(uint32_t address) {
    HAL_StatusTypeDef status;
    REGS.STATR |= FLASH_STATR_EOP;
    REGS.CTLR |= FLASH_CTLR_FTPG;
    REGS.ADDR = address;
    REGS.CTLR |= FLASH_CTLR_STRT;
    do {
        status = GetStatus();
    } while(status == HAL_BUSY);
    REGS.CTLR &= ~FLASH_CTLR_FTPG;
    return status;
}

/**
 * @brief  Erases a specified FLASH page 64B or 1KB depending on the mode specified in eraseMode.
 * @param  address specifies FLASH page address to be erased, it must be the starting address
 *         of FLASH page 64B or 1KB depending on the mode specified in eraseMode.
 * @param  eraseMode specifies the mode for 64B or 1KB FLASH page size.
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::ErasePage(uint32_t address, FLASH_EraseModeTypeDef eraseMode) {
    HAL_StatusTypeDef status;
    uint32_t ctlr;
    if(eraseMode == FLASH_ERASE_1KB) {
        if(address & 0x03FF)
            return HAL_ERROR;
        ctlr = FLASH_CTLR_PER;
    }
    else {
        if(address & 0x3F)
            return HAL_ERROR;
        ctlr = FLASH_CTLR_FTER;
    }
    if((status = Unlock()) == HAL_OK) {
        REGS.STATR |= FLASH_STATR_EOP;
        REGS.CTLR |= ctlr;
        REGS.ADDR = address;
        REGS.CTLR |= FLASH_CTLR_STRT;
        do {
            status = GetStatus();
        } while(status == HAL_BUSY);
        REGS.CTLR &= ~ctlr;
        Lock();
    }
    return status;
}

/**
 * @brief  Erases a specified FLASH page 64B or 1KB depending on the mode specified in eraseMode.
 * @param  address specifies the starting address where FLASH is written.
 * @param  data pointer to data that needs to be written to FLASH.
 * @param  size size of data to write.
 * @retval HAL status.
 */
HAL_StatusTypeDef FLASH_TypeDef::WriteData(uint32_t address, void *data, uint32_t size) {
    HAL_StatusTypeDef status = HAL_OK;
    uint32_t addrEnd = address + size;
    uint32_t temp = 0xFFFFFFFF;
    uint8_t *buff = (uint8_t *)data;

    if((status = Unlock()) == HAL_OK) {
        do {
            if((status = BuffReset()) != HAL_OK)
                break;
            if(address % 4U) {
                while(address % 4U) {
                    ((uint8_t *)&temp)[address % 4U] = *(uint8_t *)buff;
                    address++;
                    buff++;
                }
                if((status = LoadWord(address - 4U, temp)) != HAL_OK)
                    break;
                if((address % 64U) == 0U) {
                    if((status = StartFastProgram(address - 64U)) != HAL_OK)
                        break;
                }
                temp = 0xFFFFFFFF;
            }
            if(((uint32_t)buff % 4U) == 0U) {
                while((address + 4U) <= addrEnd) {
                    if((status = LoadWord(address, *(uint32_t *)buff)) != HAL_OK)
                        break;
                    address += 4U;
                    if((address % 64U) == 0U) {
                        if((status = StartFastProgram(address - 64U)) != HAL_OK)
                            break;
                        BuffReset();
                    }
                    buff += 4U;
                }
            }
            if(status == HAL_OK) {
                while(address < addrEnd) {
                    ((uint8_t *)&temp)[address % 4U] = *(uint8_t *)buff;
                    address++;
                    if((address % 4U) == 0U) {
                        if((status = LoadWord(address - 4U, temp)) != HAL_OK)
                            break;
                        if((address % 64U) == 0U) {
                            if((status = StartFastProgram(address - 64U)) != HAL_OK)
                                break;
                            BuffReset();
                        }
                        temp = 0xFFFFFFFF;
                    }
                    buff++;
                }
                if(status == HAL_OK) {
                    if(address % 4U)
                        if((status = LoadWord(address & 0xFFFFFFFC, temp)) != HAL_OK)
                            break;
                    if(address % 64U)
                        status = StartFastProgram(address & 0xFFFFFFC0);
                }
            }
        } while(0U);

        Lock();
    }
    return status;
}
