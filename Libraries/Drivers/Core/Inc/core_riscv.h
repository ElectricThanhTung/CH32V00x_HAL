
#ifndef __CORE_RISCV_H
#define __CORE_RISCV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "compiler.h"

typedef enum {
  RESET = 0U, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum {
    DISABLE = 0U,
    ENABLE = !DISABLE
} FunctionalState;

/* memory mapped structure for Program Fast Interrupt Controller (PFIC) */
typedef struct {
    __I  uint32_t ISR[8];
    __I  uint32_t IPR[8];
    __IO uint32_t ITHRESDR;
    __IO uint32_t RESERVED;
    __IO uint32_t CFGR;
    __I  uint32_t GISR;
    __IO uint8_t VTFIDR[4];
    uint8_t RESERVED0[12];
    __IO uint32_t VTFADDR[4];
    uint8_t RESERVED1[0x90];
    __O  uint32_t IENR[8];
    uint8_t RESERVED2[0x60];
    __O  uint32_t IRER[8];
    uint8_t RESERVED3[0x60];
    __O  uint32_t IPSR[8];
    uint8_t RESERVED4[0x60];
    __O  uint32_t IPRR[8];
    uint8_t RESERVED5[0x60];
    __IO uint32_t IACTR[8];
    uint8_t RESERVED6[0xE0];
    __IO uint8_t IPRIOR[256];
    uint8_t RESERVED7[0x810];
    __IO uint32_t SCTLR;
} PFIC_Type;

/* memory mapped structure for SysTick */
typedef struct {
    __IO uint32_t CTLR;
    __IO uint32_t SR;
    __IO uint32_t CNT;
    uint32_t RESERVED0;
    __IO uint32_t CMP;
    uint32_t RESERVED1;
} SysTick_Type;

#define PFIC                    ((PFIC_Type *)0xE000E000)
#define NVIC                    PFIC
#define NVIC_KEY1               ((uint32_t)0xFA050000)
#define	NVIC_KEY2               ((uint32_t)0xBCAF0000)
#define	NVIC_KEY3               ((uint32_t)0xBEEF0000)

#define SysTick                 ((SysTick_Type *) 0xE000F000)

/******************************************************************************/
/*                                System Timer                                */
/******************************************************************************/
/******************  Bit definition for STK_CTLR register  ********************/
#define STK_CTLR_STE_Pos        (0U)
#define STK_CTLR_STE_Msk        (0x01UL << STK_CTLR_STE_Pos)
#define STK_CTLR_STE            STK_CTLR_STE_Msk
#define STK_CTLR_STIE_Pos       (1U)
#define STK_CTLR_STIE_Msk       (0x01UL << STK_CTLR_STIE_Pos)
#define STK_CTLR_STIE           STK_CTLR_STIE_Msk
#define STK_CTLR_STCLK_Pos      (2U)
#define STK_CTLR_STCLK_Msk      (0x01UL << STK_CTLR_STCLK_Pos)
#define STK_CTLR_STCLK          STK_CTLR_STCLK_Msk
#define STK_CTLR_STRE_Pos       (3U)
#define STK_CTLR_STRE_Msk       (0x01UL << STK_CTLR_STRE_Pos)
#define STK_CTLR_STRE           STK_CTLR_STRE_Msk
#define STK_CTLR_SWIE_Pos       (31U)
#define STK_CTLR_SWIE_Msk       (0x01UL << STK_CTLR_SWIE_Pos)
#define STK_CTLR_SWIE           STK_CTLR_SWIE_Msk

/******************  Bit definition for STK_SR register  **********************/
#define STK_SR_CNTIF_Pos        (0U)
#define STK_SR_CNTIF_Msk        (0x01UL << STK_SR_CNTIF_Pos)
#define STK_SR_CNTIF            STK_SR_CNTIF_Msk

/******************  Bit definition for STK_CNTR register  ********************/
#define STK_CNTR_CNTR_Pos       (0U)
#define STK_CNTR_CNTR_Msk       (0xFFFFFFFFUL << STK_CNTR_CNTR_Pos)
#define STK_CNTR_CNTR           STK_CNTR_CNTR_Msk

/******************  Bit definition for STK_CMPR register  ********************/
#define STK_CMPR_CMPR_Pos       (0U)
#define STK_CMPR_CMPR_Msk       (0xFFFFFFFFUL << STK_CMPR_CMPR_Pos)
#define STK_CMPR_CMPR           STK_CMPR_CMPR_Msk

/**
 * @brief  Enable global interrupt.
 * @return None.
 */
__STATIC_FORCEINLINE void __enable_irq(void) {
    uint32_t result;
    __asm volatile("csrr %0, mstatus" : "=r"(result));
    result |= 0x88;
    __asm volatile ("csrw mstatus, %0" : : "r" (result) );
}

/**
 * @brief  Disable global interrupt.
 * @return None.
 */
__STATIC_FORCEINLINE void __disable_irq(void) {
    uint32_t result;
    __asm volatile("csrr %0, mstatus" : "=r"(result));
    result &= ~0x88;
    __asm volatile ("csrw mstatus, %0" : : "r" (result) );
}

/**
 * @brief  Nop.
 * @return None.
 */
__STATIC_FORCEINLINE void __NOP(void) {
    __asm volatile ("nop");
}

/**
 * @brief  Disable interrupt.
 * @param  IRQn interrupt numbers.
 * @return None.
 */
__STATIC_FORCEINLINE void NVIC_EnableIRQ(IRQn_Type IRQn) {
    NVIC->IENR[(uint32_t)IRQn >> 5U] = 1UL << ((uint32_t)IRQn & 0x1F);
}

/**
 * @brief  Disable interrupt.
 * @param  IRQn interrupt numbers.
 * @return None.
 */
__STATIC_FORCEINLINE void NVIC_DisableIRQ(IRQn_Type IRQn) {
    NVIC->IRER[(uint32_t)IRQn >> 5U] = 1UL << ((uint32_t)IRQn & 0x1F);
}

/**
 * @brief  Get interrupt enable state.
 * @param  IRQn interrupt numbers.
 * @return 1 - Interrupt pending enable.
 *         0 - Interrupt pending disable.
 */
__STATIC_FORCEINLINE ITStatus NVIC_GetStatusIRQ(IRQn_Type IRQn) {
    return (NVIC->ISR[(uint32_t)IRQn >> 5U] & (1UL << ((uint32_t)IRQn & 0x1F))) ? SET : RESET;
}

/**
 * @brief  Get interrupt pending state.
 * @param  IRQn interrupt numbers.
 * @return 1 - Interrupt pending enable.
 *         0 - Interrupt pending disable.
 */
__STATIC_FORCEINLINE ITStatus NVIC_GetPendingIRQ(IRQn_Type IRQn) {
    return (NVIC->IPR[(uint32_t)IRQn >> 5U] & (1UL << ((uint32_t)IRQn & 0x1F))) ? SET : RESET;
}

/**
 * @brief  Set interrupt pending.
 * @param  IRQn interrupt numbers.
 * @return None.
 */
__STATIC_FORCEINLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn) {
    NVIC->IPSR[(uint32_t)IRQn >> 5U] = (1UL << ((uint32_t)IRQn & 0x1F));
}

/**
 * @brief  Clear interrupt pending.
 * @param  IRQn interrupt numbers.
 * @return None.
 */
__STATIC_FORCEINLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn) {
    NVIC->IPRR[(uint32_t)IRQn >> 5U] = (1UL << ((uint32_t)IRQn & 0x1F));
}

/**
 * @brief  Get interrupt active state.
 * @param  IRQn interrupt numbers.
 * @return 1 - Interrupt active.
 *         0 - Interrupt no active.
 */
__STATIC_FORCEINLINE ITStatus NVIC_GetActive(IRQn_Type IRQn) {
    return (NVIC->IACTR[(uint32_t)IRQn >> 5U] & (1UL << ((uint32_t)IRQn & 0x1F))) ? SET : RESET;
}

/**
 * @brief  Set interrupt priority.
 * @param  IRQn interrupt numbers.
 * @param  priority: bit[7] - pre-emption priority.
 *                   bit[6] - subpriority.
 *                   bit[5:0] - reserved.
 * @return None.
 */
__STATIC_FORCEINLINE void NVIC_SetPriority(IRQn_Type IRQn, uint8_t priority) {
    NVIC->IPRIOR[(uint32_t)IRQn] = priority;
}

/**
 * @brief  Wait for interrupt.
 * @return None.
 */
__STATIC_FORCEINLINE void __WFI(void) {
    /* wfi */
    NVIC->SCTLR &= ~(1UL << 3U);
    asm volatile ("wfi");
}

/**
 * @brief  Set event.
 * @return None.
 */
__STATIC_FORCEINLINE void _SEV(void) {
    uint32_t t = NVIC->SCTLR;
    NVIC->SCTLR |= (1UL << 3U) | (1UL << 5U);
    NVIC->SCTLR = (NVIC->SCTLR & ~(1UL << 5U)) | (t & (1UL << 5U));
}

/**
 * @brief  Wait for events.
 * @return None.
 */
__STATIC_FORCEINLINE void _WFE(void) {
    NVIC->SCTLR |= (1UL << 3U);
    asm volatile ("wfi");
}

/**
 * @brief  Wait for events.
 * @return None.
 */
__STATIC_FORCEINLINE void __WFE(void) {
    _SEV();
    _WFE();
    _WFE();
}

/**
 * @brief  Set VTF interrupt.
 * @param  addr VTF interrupt service function base address.
 * @param  IRQn interrupt numbers.
 * @param  num VTF Interrupt numbers.
 * @param  newState - DISABLE or ENABLE.
 * @return None.
 */
__STATIC_FORCEINLINE void SetVTFIRQ(uint32_t addr, IRQn_Type IRQn, uint8_t num, FunctionalState newState) {
    if(num > 1U)
        return;
    if(newState != DISABLE) {
        NVIC->VTFIDR[num] = IRQn;
        NVIC->VTFADDR[num] = ((addr & 0xFFFFFFFE) | 0x1);
    }
    else {
        NVIC->VTFIDR[num] = IRQn;
        NVIC->VTFADDR[num] = ((addr & 0xFFFFFFFE) & ~0x1);
    }
}

/**
 * @brief  Initiate a system reset request.
 * @return None.
 */
__STATIC_FORCEINLINE void NVIC_SystemReset(void) {
    NVIC->CFGR = NVIC_KEY3 | (1UL << 7U);
}

/**
 * @brief  Return the machine status register.
 * @return mstatus value.
 */
__STATIC_FORCEINLINE uint32_t __get_MSTATUS(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mstatus" : "=r"(result));
    return (result);
}

/**
 * @brief  Set the machine status register.
 * @param  value mstatus value.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_MSTATUS(uint32_t value) {
    __ASM volatile("csrw mstatus, %0" : : "r"(value));
}

/**
 * @brief  Return the machine ISA register.
 * @return misa value.
 */
__STATIC_FORCEINLINE uint32_t __get_MISA(void) {
    uint32_t result;
    __ASM volatile("csrr %0, misa" : "=r"(result));
    return (result);
}

/**
 * @brief  Set the machine ISA register.
 * @param  value misa value.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_MISA(uint32_t value) {
    __ASM volatile("csrw misa, %0" : : "r"(value));
}

/**
 * @brief  Return the machine trap-vector base-address register.
 * @return mtvec value.
 */
__STATIC_FORCEINLINE uint32_t __get_MTVEC(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mtvec" : "=r"(result));
    return (result);
}

/**
 * @brief  Set the machine trap-vector base-address register.
 * @param  value mtvec value.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_MTVEC(uint32_t value) {
    __ASM volatile("csrw mtvec, %0" : : "r"(value));
}

/**
 * @brief  Return the machine seratch register.
 * @return mscratch value.
 */
__STATIC_FORCEINLINE uint32_t __get_MSCRATCH(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mscratch" : "=r"(result));
    return (result);
}

/**
 * @brief  Set the machine seratch register.
 * @param  value mscratch value.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_MSCRATCH(uint32_t value) {
    __ASM volatile("csrw mscratch, %0" : : "r"(value));
}

/**
 * @brief  Return the machine exception program register.
 * @return mepc value.
 */
__STATIC_FORCEINLINE uint32_t __get_MEPC(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mepc" : "=r"(result));
    return (result);
}

/**
 * @brief  Set the machine exception program register.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_MEPC(uint32_t value) {
    __ASM volatile("csrw mepc, %0" : : "r"(value));
}

/**
 * @brief  Return the machine cause register.
 * @return mcause value.
 */
__STATIC_FORCEINLINE uint32_t __get_MCAUSE(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mcause" : "=r"(result));
    return (result);
}

/**
 * @brief  Set the machine cause register.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_MCAUSE(uint32_t value) {
    __ASM volatile("csrw mcause, %0" : : "r"(value));
}

/**
 * @brief  Return vendor ID register.
 * @return mvendorid value.
 */
__STATIC_FORCEINLINE uint32_t __get_MVENDORID(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mvendorid" : "=r"(result));
    return (result);
}

/**
 * @brief  Return machine architecture ID register.
 * @return marchid value.
 */
__STATIC_FORCEINLINE uint32_t __get_MARCHID(void) {
    uint32_t result;
    __ASM volatile("csrr %0, marchid" : "=r"(result));
    return (result);
}

/**
 * @brief  Return machine implementation ID register.
 * @return mimpid value.
 */
__STATIC_FORCEINLINE uint32_t __get_MIMPID(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mimpid" : "=r"(result));
    return (result);
}

/**
 * @brief  Return hart ID register.
 * @return mhartid value.
 */
__STATIC_FORCEINLINE uint32_t __get_MHARTID(void) {
    uint32_t result;
    __ASM volatile("csrr %0, mhartid" : "=r"(result));
    return (result);
}

/**
 * @brief  Return SP register.
 * @return SP value.
 */
__STATIC_FORCEINLINE uint32_t __get_SP(void) {
    uint32_t result;
    __ASM volatile("mv %0, sp" : "=r"(result));
    return (result);
}

/**
 * @brief  Set SP register.
 * @param  value SP value.
 * @return None.
 */
__STATIC_FORCEINLINE void __set_SP(uint32_t value) {
    __ASM volatile("mv sp, %0" : : "r"(value));
}

#ifdef __cplusplus
}
#endif

#endif/* __CORE_RISCV_H */
