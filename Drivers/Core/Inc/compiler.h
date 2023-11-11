
#ifndef __CONPILER_H
#define __CONPILER_H

/* IO definitions */
#ifdef __cplusplus
    #define     __I               volatile                  /*  defines 'read only' permissions     */
#else
    #define     __I               volatile const            /*  defines 'read only' permissions     */
#endif
#define       __O               volatile                    /*  defines 'write only' permissions    */
#define       __IO              volatile                    /*  defines 'read / write' permissions  */

#if defined(__CC_ARM)
    #define __ASM                   __asm                   /*!< asm keyword for ARM Compiler          */
    #define __INLINE                __inline                /*!< inline keyword for ARM Compiler       */
    #define __STATIC_FORCEINLINE    __forceinline static inline
    #define __INTERRUPT             __attribute__((interrupt()))
    #define __WEAK                  __attribute__((weak))
#elif defined(__ICCARM__)
    #define __ASM                    __asm                  /*!< asm keyword for IAR Compiler          */
    #define __INLINE                inline                  /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */
    #define __STATIC_FORCEINLINE    _Pragma("inline=forced") static inline
    #define __INTERRUPT             __attribute__((interrupt()))
    #define __WEAK                  __attribute__((weak))
#elif defined(__GNUC__)
    #define __ASM                   __asm                   /*!< asm keyword for GNU Compiler          */
    #define __INLINE                inline                  /*!< inline keyword for GNU Compiler       */
    #define __STATIC_FORCEINLINE    __attribute__((always_inline)) static inline
    #define __INTERRUPT             __attribute__((interrupt()))
    #define __WEAK                  __attribute__((weak))
#elif defined(__TASKING__)
    #define __ASM                   __asm                   /*!< asm keyword for TASKING Compiler      */
    #define __INLINE                inline                  /*!< inline keyword for TASKING Compiler   */
    #define __STATIC_FORCEINLINE    __attribute__((always_inline)) static inline
    #define __INTERRUPT             __attribute__((interrupt()))
    #define __WEAK                  __attribute__((weak))
#endif

#endif /* __CONPILER_H */
