
#include "ch32v00x_hal_afio.h"

/**
 * @brief  Enable the AFIO peripheral clock.
 * @note   This function will use RCC module to enable clock for AFIO peripheral.
 * @retval None.
 */
void AFIO_TypeDef::EnableClock(void) {
    if(this == &AFIO)
        RCC.REGS.APB2PCENR |= RCC_APB2PCENR_AFIOEN;
}

/**
 * @brief  Disable the AFIO peripheral clock.
 * @note   This function will use RCC module to disable clock for AFIO peripheral.
 * @retval None.
 */
void AFIO_TypeDef::DisableClock(void) {
    if(this == &AFIO)
        RCC.REGS.APB2PCENR &= ~RCC_APB2PCENR_AFIOEN;
}

/**
 * @brief  Disable or enable the remapping of SPI1.
 * @param  remap: DISABLE (NSS/PC1, CK/PC5, MISO/PC7, MOSI/PC6).
 *                ENABLE (NSS/PC0, CK/PC5, MISO/PC7, MOSI/PC6).
 * @note   Default mapping (NSS/PC1, CK/PC5, MISO/PC7, MOSI/PC6).
 * @retval None.
 */
void AFIO_TypeDef::RemapSPI1(HAL_StateTypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_SPI1_RM) | (remap << AFIO_PCFR1_SPI1_RM_Pos);
}

/**
 * @brief  Disable the remapping of I2C1.
 * @param  remap: AFIO_REMAPI2C1_DISABLE (SCL/PC2, SDA/PC1).
 *                AFIO_REMAPI2C1_1 (SCL/PD1, SDA/PD0).
 *                AFIO_REMAPI2C1_2 (SCL/PC5, SDA/PC6).
 * @note   Default mapping (SCL/PC2, SDA/PC1).
 * @retval None.
 */
void AFIO_TypeDef::RemapI2C1(AFIO_RemapI2C1TypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_I2C1_RM) | (remap << AFIO_PCFR1_I2C1_RM_Pos);
}

/**
 * @brief  Disable the remapping of USART1.
 * @param  remap: AFIO_REMAPUSART1_DISABLE (CK/PD4, TX/PD5, RX/PD6, CTS/PD3, RTS/PC2).
 *                AFIO_REMAPUSART1_1 (CK/PD7, TX/PD0, RX/PD1, CTS/PC3, RTS/PC2, SW_RX/PD0).
 *                AFIO_REMAPUSART1_2 (CK/PD7, TX/PD6, RX/PD5, CTS/PC6, RTS/PC7, SW_RX/PD6).
 *                AFIO_REMAPUSART1_3 (CK/PC5, TX/PC0, RX/PC1, CTS/PC6, RTS/PC7, SW_RX/PC0).
 * @note   Default mapping (CK/PD4, TX/PD5, RX/PD6, CTS/PD3, RTS/PC2).
 * @retval None.
 */
void AFIO_TypeDef::RemapUSART1(AFIO_RemapUSART1TypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_USART1_RM) | (remap << AFIO_PCFR1_USART1_RM_Pos);
}

/**
 * @brief  Disable the remapping of TIM1.
 * @param  remap: AFIO_REMAP_TIM1_DISABLE (ETR/PC5, CH1/PD2, CH2/PA1, CH3/PC3, CH4/PC4, BKIN/PC2, CH1N/PD0, CH2N/PA2, CH3N/PD1).
 *                AFIO_REMAP_TIM1_1 (ETR/PC5, CH1/PC6, CH2/PC7, CH3/PC0, CH4/PD3, BKIN/PC1, CH1N/PC3, CH2N/PC4, CH3N/PD1).
 *                AFIO_REMAP_TIM1_2 (ETR/PD4, CH1/PD2, CH2/PA1, CH3/PC3, CH4/PC4, BKIN/PC2, CH1N/PD0, CH2N/PA2, CH3N/PD1).
 *                AFIO_REMAP_TIM1_3 (ETR/PC2, CH1/PC4, CH2/PC7, CH3/PC5, CH4/PD4, BKIN/PC1, CH1N/PC3, CH2N/PD2, CH3N/PC6).
 * @note   Default mapping (ETR/PC5, CH1/PD2, CH2/PA1, CH3/PC3, CH4/PC4, BKIN/PC2, CH1N/PD0, CH2N/PA2, CH3N/PD1).
 * @retval None.
 */
void AFIO_TypeDef::RemapTIM1(AFIO_RemapTIM1TypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_TIM1_RM) | (remap << AFIO_PCFR1_TIM1_RM_Pos);
}

/**
 * @brief  Disable the remapping of TIM2.
 * @param  remap: AFIO_REMAP_TIM2_DISABLE (CH1/ETR/PD4, CH2/PD3, CH3/PC0, CH4/PD7).
 *                AFIO_REMAP_TIM2_1 (CH1/ETR/PC5, CH2/PC2, CH3/PD2, CH4/PC1).
 *                AFIO_REMAP_TIM2_2 (CH1/ETR/PC1, CH2/PD3, CH3/PC0, CH4/PD7).
 *                AFIO_REMAP_TIM2_3 (CH1/ETR/PC1, CH2/PC7, CH3/PD6, CH4/PD5).
 * @note   Default mapping (CH1/ETR/PD4, CH2/PD3, CH3/PC0, CH4/PD7).
 * @retval None.
 */
void AFIO_TypeDef::RemapTIM2(AFIO_RemapTIM2TypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_TIM2_RM) | (remap << AFIO_PCFR1_TIM2_RM_Pos);
}

/**
 * @brief  Disable the remapping of ADC_ETRGINJ.
 * @param  remap: DISABLE (ADC_ETRGINJ connected to PD3)
 *                ENABLE (ADC_ETRGINJ connected to PC2).
 * @note   Default mapping (ADC_ETRGINJ connected to PD3).
 * @retval None.
 */
void AFIO_TypeDef::RemapADCETRGINJ(HAL_StateTypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_ADC_ETRGINJ_RM) | (remap << AFIO_PCFR1_ADC_ETRGINJ_RM_Pos);
}

/**
 * @brief  Disable the remapping of ADC_ETRGREG.
 * @param  remap: DISABLE (ADC_ETRGREG connected to PD3)
 *                ENABLE (ADC_ETRGREG connected to PC2).
 * @note   Default mapping (ADC_ETRGREG connected to PD3).
 * @retval None.
 */
void AFIO_TypeDef::RemapADCETRGREG(HAL_StateTypeDef remap) {
    REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_ADC_ETRGREG_RM) | (remap << AFIO_PCFR1_ADC_ETRGREG_RM_Pos);
}

/**
 * @brief  Disable the remapping of SWD.
 * @param  remap: DISABLE (SWD enabled)
 *                ENABLE (Turn off SWD, which functions as a GPIO).
 * @note   Default mapping (SWD enabled).
 * @retval None.
 */
void AFIO_TypeDef::RemapSWD(HAL_StateTypeDef remap) {
    if(remap == DISABLE)
        REGS.PCFR1 &= ~AFIO_PCFR1_SWCFG_RM;
    else
        REGS.PCFR1 = (REGS.PCFR1 & ~AFIO_PCFR1_SWCFG_RM) | (4UL << AFIO_PCFR1_SWCFG_RM_Pos);
}

/**
 * @brief  De-Initialize the AFIO peripheral.
 * @retval None.
 */
void AFIO_TypeDef::DeInit(void) {
    if(this == &AFIO) {
        RCC.REGS.APB2PRSTR |= RCC_APB2PRSTR_AFIORST;
        RCC.REGS.APB2PRSTR &= ~RCC_APB2PRSTR_AFIORST;
    }
}
