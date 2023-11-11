
#ifndef __CH32V00x_HAL_CONF_H
#define __CH32V00x_HAL_CONF_H

/**
 * @brief Internal High Speed oscillator (HSI) value.
 *        This value is used by the RCC HAL module to compute the system frequency
 *        (when HSI is used as system clock source, directly or through the PLL).
 */
#define HSE_VALUE                               (24000000UL)    /*!< Value of the External oscillator in Hz */

/**
 * @brief External High Speed oscillator (HSE) Startup Timeout value.
 */
#define HSE_STARTUP_TIMEOUT                     (0x2000U)       /* Time out for HSE start up */

#endif /* __CH32V00x_HAL_CONF_H */
