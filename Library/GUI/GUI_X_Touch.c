/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              µC/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "ads7843.h"

	unsigned int x,y;

int  TOUCH_MeasureX(void)
{
	//unsigned int x,y;
	if(GPIO_ReadInputDataBit(TOUCH_INT_GPIO,TOUCH_INT))
	{
		return 0;
	}
	else
	{
		ADS7843_GetPosition(&x,&y);
//		x = ( x * 400 ) / 3800;
				x = ( x * 320 ) / 3800;

		return x;
	}
}

int  TOUCH_MeasureY(void)
{

	if(GPIO_ReadInputDataBit(TOUCH_INT_GPIO,TOUCH_INT))
	{
		return 0;
	}
	else
	{
		ADS7843_GetPosition(&x,&y);
		y = y - 240;
//		y = ( y * 240 ) / 3800;
				y = ( y * 240 ) / 3800;

		return y;
	}
}



