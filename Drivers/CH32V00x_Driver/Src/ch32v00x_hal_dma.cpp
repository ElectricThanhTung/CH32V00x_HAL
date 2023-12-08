
#include "ch32v00x_hal_dma.h"

#define SET_SIZE(mSize, pSize) {                                        \
    REGS.CFGR = (REGS.CFGR & ~(DMA_CFGR_MSIZE | DMA_CFGR_PSIZE)) |      \
    ((mSize) << DMA_CFGR_MSIZE_Pos) |                                   \
    ((pSize) << DMA_CFGR_PSIZE_Pos);                                    \
}

/**
 * @brief  Setup source and destination infomation for DMA channel.
 * @param  src pointer to source data.
 * @param  sSize element size of the source data.
 * @param  dest pointer to destination data.
 * @param  dSize element size of the destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(void *src, uint8_t sSize, void *dest, uint8_t dSize, uint32_t count) {
    if(GetStatus() != HAL_OK)
        return HAL_ERROR;
    REGS.CFGR &= ~(DMA_CFGR_MEM2MEM | DMA_CFGR_DIR | DMA_CFGR_EN);
    REGS.PADDR = (uint32_t)src;
    REGS.MADDR = (uint32_t)dest;
    REGS.CNTR = count;
    SET_SIZE(sSize, dSize);
    REGS.CFGR |= DMA_CFGR_EN;
    return HAL_OK;
}

/**
 * @brief  Perform data copying by DMA channel.
 * @param  src pointer to source data.
 * @param  dest pointer to destination data.
 * @param  size size of data to copy.
 * @param  copyMode specifies blocking mode or non-blocking mode
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::MemCopy(void *src, void *dest, uint32_t size, DMA_CopyModeTypeDef copyMode) {
    uint8_t elemSize;
    if(GetStatus() != HAL_OK)
        return HAL_ERROR;
    if((size >= 4) && ((size % 4U) == 0) && (((uint32_t)src % 4U) == 0) && (((uint32_t)dest % 4U) == 0)) {
        elemSize = 2U;
        size /= 4;
    }
    else if((size >= 2) && ((size % 4U) == 0) && (((uint32_t)src % 2U) == 0) && (((uint32_t)dest % 2U) == 0)) {
        elemSize = 1U;
        size /= 2;
    }
    else
        elemSize = 0U;
    REGS.CFGR &= ~(DMA_CFGR_DIR | DMA_CFGR_EN);
    REGS.CFGR |= DMA_CFGR_MEM2MEM;
    REGS.PADDR = (uint32_t)src;
    REGS.MADDR = (uint32_t)dest;
    REGS.CNTR = size;
    SET_SIZE(elemSize, elemSize);
    REGS.CFGR |= DMA_CFGR_EN;
    if(copyMode == DMA_COPYMODE_BLOCKING)
        while(GetStatus() != HAL_OK);
    return HAL_OK;
}

/**
 * @brief  Setup tranfer from uint8_t source to uint8_t destination for DMA.
 * @param  src pointer to uint8_t source data.
 * @param  dest pointer to uint8_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint8_t *src, uint8_t *dest, uint32_t count) {
    return Setup((void *)src, 0U, (void *)dest, 0U, count);
}

/**
 * @brief  Setup tranfer from uint8_t source to uint16_t destination for DMA.
 * @param  src pointer to uint8_t source data.
 * @param  dest pointer to uint16_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint8_t *src, uint16_t *dest, uint32_t count) {
    return Setup((void *)src, 0U, (void *)dest, 1U, count);
}

/**
 * @brief  Setup tranfer from uint8_t source to uint32_t destination for DMA.
 * @param  src pointer to uint8_t source data.
 * @param  dest pointer to uint32_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint8_t *src, uint32_t *dest, uint32_t count) {
    return Setup((void *)src, 0U, (void *)dest, 2U, count);
}

/**
 * @brief  Setup tranfer from uint16_t source to uint8_t destination for DMA.
 * @param  src pointer to uint16_t source data.
 * @param  dest pointer to uint8_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint16_t *src, uint8_t *dest, uint32_t count) {
    return Setup((void *)src, 1U, (void *)dest, 0U, count);
}

/**
 * @brief  Setup tranfer from uint16_t source to uint16_t destination for DMA.
 * @param  src pointer to uint16_t source data.
 * @param  dest pointer to uint16_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint16_t *src, uint16_t *dest, uint32_t count) {
    return Setup((void *)src, 1U, (void *)dest, 1U, count);
}

/**
 * @brief  Setup tranfer from uint16_t source to uint32_t destination for DMA.
 * @param  src pointer to uint16_t source data.
 * @param  dest pointer to uint32_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint16_t *src, uint32_t *dest, uint32_t count) {
    return Setup((void *)src, 1U, (void *)dest, 2U, count);
}

/**
 * @brief  Setup tranfer from uint32_t source to uint8_t destination for DMA.
 * @param  src pointer to uint32_t source data.
 * @param  dest pointer to uint8_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint32_t *src, uint8_t *dest, uint32_t count) {
    return Setup((void *)src, 2U, (void *)dest, 0U, count);
}

/**
 * @brief  Setup tranfer from uint32_t source to uint16_t destination for DMA.
 * @param  src pointer to uint32_t source data.
 * @param  dest pointer to uint16_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint32_t *src, uint16_t *dest, uint32_t count) {
    return Setup((void *)src, 2U, (void *)dest, 1U, count);
}

/**
 * @brief  Setup tranfer from uint32_t source to uint32_t destination for DMA.
 * @param  src pointer to uint32_t source data.
 * @param  dest pointer to uint32_t destination data.
 * @param  count number of elements to be transmitted by DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::Setup(uint32_t *src, uint32_t *dest, uint32_t count) {
    return Setup((void *)src, 2U, (void *)dest, 2U, count);
}

/**
 * @brief  Setup priority for DMA channel.
 * @param  priority specifies priority for DMA channel.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::SetPriority(DMA_PriorityTypeDef priority) {
    if(GetStatus() != HAL_OK)
        return HAL_ERROR;
    REGS.CFGR = (REGS.CFGR & ~DMA_CFGR_PL) | priority;
    return HAL_OK;
}

/**
 * @brief  Enable or disable memory address incremental mode.
 * @param  enabled specifies state for memory address incremental mode.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::SetMINC(HAL_StateTypeDef enabled) {
    if(GetStatus() != HAL_OK)
        return HAL_ERROR;
    if(enabled == ENABLE)
        REGS.CFGR |= DMA_CFGR_MINC;
    else
        REGS.CFGR &= ~DMA_CFGR_MINC;
    return HAL_OK;
}

/**
 * @brief  Enable or disable pripheral address incremental mode.
 * @param  enabled specifies state for pripheral address incremental mode.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::SetPINC(HAL_StateTypeDef enabled) {
    if(GetStatus() != HAL_OK)
        return HAL_ERROR;
    if(enabled == ENABLE)
        REGS.CFGR |= DMA_CFGR_PINC;
    else
        REGS.CFGR &= ~DMA_CFGR_PINC;
    return HAL_OK;
}

/**
 * @brief  Return current status according to the internal DMA channel
 *         registers.
 * @retval HAL status.
 */
HAL_StatusTypeDef DMA_ChannelTypeDef::GetStatus(void) {
    if(!(REGS.CFGR & DMA_CFGR_EN))
        return HAL_OK;
    else if(!(REGS.CFGR & DMA_CFGR_CIRC) && REGS.CNTR == 0)
        return HAL_OK;
    return HAL_BUSY;
}

/**
 * @brief  Stop tranfer.
 * @retval None.
 */
void DMA_ChannelTypeDef::Stop(void) {
    REGS.CFGR &= ~DMA_CFGR_EN;
}

/**
 * @brief  Resets the DMA channel configuration to the default reset state.
 * @retval None.
 */
void DMA_ChannelTypeDef::DeInit(void) {
    REGS.CFGR = 0U;
    REGS.CNTR = 0U;
    REGS.MADDR = 0U;
    REGS.PADDR = 0U;
}

/**
 * @brief  Enable the DMA peripheral clock.
 * @note   This function will use RCC module to enable clock for DMA peripheral.
 * @retval None.
 */
void DMA_TypeDef::EnableClock(void) {
    if(this == &DMA1)
        RCC.REGS.AHBPCENR |= RCC_AHBPCENR_DMA1EN;
}

/**
 * @brief  Disable the DMA peripheral clock.
 * @note   This function will use RCC module to disable clock for DMA peripheral.
 * @retval None.
 */
void DMA_TypeDef::DisableClock(void) {
    if(this == &DMA1)
        RCC.REGS.AHBPCENR &= ~RCC_AHBPCENR_DMA1EN;
}

/**
 * @brief  Automatically selects a free DMA channel to perform data copying.
 * @note   This function will return used DMA channel. If no DMA is available,
 *         the function will return a null pointer.
 * @retval Pointer to a DMA channel.
 */
DMA_ChannelTypeDef *DMA_TypeDef::MemCopy(void *src, void *dest, uint32_t size, DMA_CopyModeTypeDef copyMode) {
    if(CHANNEL1.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL1;
    else if(CHANNEL2.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL2;
    else if(CHANNEL3.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL3;
    else if(CHANNEL4.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL4;
    else if(CHANNEL5.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL5;
    else if(CHANNEL6.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL6;
    else if(CHANNEL7.MemCopy(src, dest, size, copyMode) == HAL_OK)
        return &CHANNEL7;
    return NULL_PTR;
}

/**
 * @brief  Resets all DMA channel configuration to the default reset state.
 * @retval None.
 */
void DMA_TypeDef::DeInit(void) {
    REGS.INTFCR = 0U;
    CHANNEL1.DeInit();
    CHANNEL2.DeInit();
    CHANNEL3.DeInit();
    CHANNEL4.DeInit();
    CHANNEL5.DeInit();
    CHANNEL6.DeInit();
    CHANNEL7.DeInit();
}
