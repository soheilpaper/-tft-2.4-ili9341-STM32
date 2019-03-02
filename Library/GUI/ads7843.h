#ifndef ADS7843_H
#define ADS7843_H
#include "stm32f10x.h"
//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#define __ARMCLIB_VERSION 5060019


  #ifndef __cplusplus /* In C++, 'bool', 'true' and 'false' and keywords */
    #define bool _Bool
    #define true 1
    #define false 0
  #else
    #ifdef __GNUC__
      /* GNU C++ supports direct inclusion of stdbool.h to provide C99
         compatibility by defining _Bool */
      #define _Bool bool
    #endif
  #endif

#endif /* __bool_true_false_are_defined */

#define TOUCH_INT             GPIO_Pin_7
#define TOUCH_INT_GPIO        GPIOC
#define TOUCH_INT_GPIO_CLK    RCC_APB2Periph_GPIOC

//------------------------------------------------------------------------------
//         Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern void ADS7843_Initialize(void);

extern void ADS7843_Reset(void);

extern void ADS7843_GetPosition(unsigned int* , unsigned int* py_pos);

extern void pinNssConfig(void);

#endif //#ifdef BOARD_TSC_ADS7843
