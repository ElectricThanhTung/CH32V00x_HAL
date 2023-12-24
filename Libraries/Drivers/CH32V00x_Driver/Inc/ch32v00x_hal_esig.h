
#ifndef __CH32V00x_HAL_ESIG_H
#define __CH32V00x_HAL_ESIG_H

#include "ch32v00x_hal.h"

class ESIG_TypeDef {
public:
    struct {
    public:
        __I uint16_t FLACAP;
    private:
        __I uint16_t RESERVED0;
        __I uint32_t RESERVED1;
    public:
        __I uint32_t UNIID1;
        __I uint32_t UNIID2;
        __I uint32_t UNIID3;
    } REGS;
public:
    uint32_t GetFlashCapacity(void);
    uint32_t GetUID(uint32_t *uid = NULL_PTR);
private:
    ESIG_TypeDef(void);
    ESIG_TypeDef(const ESIG_TypeDef &);
};

#define ESIG            (*(ESIG_TypeDef *)ESIG_BASE)

#endif /* __CH32V00x_HAL_ESIG_H */
