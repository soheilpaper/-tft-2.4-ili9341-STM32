/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2012  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.16 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCD_X_SPI_LPC1700.c
Purpose     : Port routines for LPC1700 SPI
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "stm32f10x.h"
//#include <board.h>
//#include <ssc/ssc.h>
//#include <pio/pio.h>
//#include "../ssd1963/ssd1963.h"
//#include <tftlcd_functions.h>

/*********************************************************************
*
*       Hardware configuration
*
**********************************************************************
*/

// const Pin LCD_CS = LCDCS;
// const Pin LCD_RS = LCDRS;
// const Pin LCD_WR = LCDWR;
// const Pin LCD_RD = LCDRD;



#define Set_Cs  	   GPIO_SetBits(GPIOC,GPIO_Pin_3);
#define Clr_Cs  	   GPIO_ResetBits(GPIOC,GPIO_Pin_3);

#define Set_Rs  	   GPIO_SetBits(GPIOC,GPIO_Pin_2);
#define Clr_Rs  	   GPIO_ResetBits(GPIOC,GPIO_Pin_2);

#define Set_nWr 	   GPIO_SetBits(GPIOC,GPIO_Pin_1);
#define Clr_nWr 	   GPIO_ResetBits(GPIOC,GPIO_Pin_1);

#define Set_nRd 	   GPIO_SetBits(GPIOC,GPIO_Pin_0);
#define Clr_nRd 	   GPIO_ResetBits(GPIOC,GPIO_Pin_0);

#define Set_Rst    	 GPIO_SetBits(GPIOC,GPIO_Pin_4); 		
#define Clr_Rst 	   GPIO_ResetBits(GPIOC,GPIO_Pin_4);


#define LCD_CS(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_3)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_3)));
/* Pin RS setting to 0 or 1                                                   */
#define LCD_RS(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_2)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_2)));
/* Pin WR setting to 0 or 1                                                   */
#define LCD_WR(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_1)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_1)));
/* Pin RD setting to 0 or 1                                                   */
#define LCD_RD(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_0)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_0)));



/*******************************************************************************
* Send 1 byte over serial communication                                        *
*   Parameter:    byte:   byte to be sent                                      *
*   Return:                                                                    *
*******************************************************************************/

static __inline unsigned char lcd_send (unsigned short byte) 
{
  GPIO_Write(GPIOA,byte);
  return(1);
}


/*******************************************************************************
* read 1 byte over serial communication                                        *
*   Parameter:    byte:   byte to be sent                                      *
*   Return:                                                                    *
*******************************************************************************/

static __inline unsigned short lcd_read (void) 
{
  unsigned short id;
	
	id = GPIO_ReadInputData(GPIOA);
                                 
  return(id); 
}

__asm void wait()
{
    nop
    BX lr
}


/*********************************************************************
*
*       Static data
*
**********************************************************************/


/*********************************************************************
*
*       Exported code
*
*********************************************************************
*/
static void delay (int cnt) {
  cnt <<= 15;
  while (cnt--);
}

/*********************************************************************
*
*       LCD_X_Init
*
* Purpose:
*   This routine should be called from your application program
*   to set port pins to their initial values
*/
void LCD_X_Init(void) {
	  Clr_Rst
    delay(500);
	  Set_Rst	
	  
}

/*********************************************************************
*
*       LCD_X_Write00_16
*
* Purpose:
*   Write to controller, with A0 = 0 register
*/
void LCD_X_Write00_16(U16 c) {

  LCD_RS(0)
  LCD_RD(1)
  lcd_send(c);
  LCD_WR(0)
  wait();
  LCD_WR(1)
	
}

/*********************************************************************
*
*       LCD_X_Write01_16
*
* Purpose:
*   Write to controller, with A0 = 1   data
*/
void LCD_X_Write01_16(U16 c) {
  LCD_RS(1)
  LCD_RD(1)
  lcd_send(c);
  LCD_WR(0)
  wait();
  LCD_WR(1)
}

/*********************************************************************
*
*       LCD_X_Read01_16
*
* Purpose:
*   Read from controller, with A0 = 1
*/
U16 LCD_X_Read01_16(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  U16 c =0;
  LCD_RS(1)
  LCD_WR(1)
  LCD_RD(0)
  c = lcd_read();
  LCD_RD(1)
	
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  return c;
}

/*********************************************************************
*
*       LCD_X_WriteM01_16
*
* Purpose:
*   Write multiple bytes to controller, with A0 = 1
*/
void LCD_X_WriteM01_16(U16 * pData, int NumWords) {
	
   for (; NumWords; NumWords--)
	 {
		 LCD_X_Write01_16(*pData);
		 pData++;
   }
	 
}

/*********************************************************************
*
*       LCD_X_ReadM01_16
*
* Purpose:
*   Read multiple bytes from controller, with A0 = 1
*/


void LCD_X_ReadM01_16(U16 * pData, int NumWords) {
	GPIO_InitTypeDef GPIO_InitStructure;
//	int i;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  LCD_RS(1)
  LCD_WR(1)
  LCD_RD(0)
	  
		 for (; NumWords; NumWords--)
		 {
			 //*pData = LCD_X_Read01_16() ;
			 *pData = lcd_read();
			 pData++;
		 }
	 
	  LCD_RD(1)
	 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*************************** End of file ****************************/
