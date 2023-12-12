
#include "ch32v00x_hal_esig.h"

/**
 * @brief  Return flash capacity in byte.
 * @retval Flash size (in byte).
 */
uint32_t ESIG_TypeDef::GetFlashCapacity(void) {
    return REGS.FLACAP * 1024U;
}

/**
 * @brief  Get 96 bits unique identifier (UID).
 * @param  uid pointer to a 96-bit buffer to get the result.
 *         A minimum of 24 bytes (3 uint32_t elements) is
 *         required to contain the result.
 * @retval The lower 32 bits of the UID.
 */
uint32_t ESIG_TypeDef::GetUID(uint32_t *uid) {
    if(uid != NULL_PTR) {
        uid[0] = REGS.UNIID1;
        uid[1] = REGS.UNIID2;
        uid[2] = REGS.UNIID3;
    }
    return REGS.UNIID1;
}
