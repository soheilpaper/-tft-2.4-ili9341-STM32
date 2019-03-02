
#include "GUI.h"
#include "stm32f10x.h"
//#include <board.h>
//#include <ssc/ssc.h>
//#include <pio/pio.h>
//#include "../ssd1963/ssd1963.h"
//#include "ADC_SETUP.c"
uint16_t  theArray[2]={0,0};

#define Set_Cs  	   GPIO_SetBits(GPIOC,GPIO_Pin_3);
#define Clr_Cs  	   GPIO_ResetBits(GPIOC,GPIO_Pin_3);

#define Set_T_XM  	   GPIO_SetBits(GPIOC,GPIO_Pin_2);
#define Clr_T_XM   	   GPIO_ResetBits(GPIOC,GPIO_Pin_2);

#define Set_nT_YP 	   GPIO_SetBits(GPIOC,GPIO_Pin_1);
#define Clr_nT_YP 	   GPIO_ResetBits(GPIOC,GPIO_Pin_1);

#define Set_T_XP 	   GPIO_SetBits(GPIOA,GPIO_Pin_6);
#define Clr_T_XP 	   GPIO_ResetBits(GPIOA,GPIO_Pin_6);

#define Set_T_YM    	 GPIO_SetBits(GPIOA,GPIO_Pin_7); 		
#define Clr_T_YM 	   GPIO_ResetBits(GPIOA,GPIO_Pin_7);


#define LCD_CS(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_3)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_3)));
/* Pin RS setting to 0 or 1                                                   */
#define LCD_T_XM(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_2)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_2)));
/* Pin WR setting to 0 or 1                                                   */
#define LCD_T_YP(x)     ((x) ? (GPIO_SetBits(GPIOC,GPIO_Pin_1)) : (GPIO_ResetBits(GPIOC,GPIO_Pin_1)));
/* Pin T_XP setting to 0 or 1                                                   */
#define LCD_T_XP(x)     ((x) ? (GPIO_SetBits(GPIOA,GPIO_Pin_6)) : (GPIO_ResetBits(GPIOA,GPIO_Pin_6)));
/* Pin T_YM setting to 0 or 1                                                   */
#define LCD_T_YM(x)     ((x) ? (GPIO_SetBits(GPIOA,GPIO_Pin_7)) : (GPIO_ResetBits(GPIOA,GPIO_Pin_7)));

extern uint16_t  badprogADC(uint8_t ADC_Channel_01);
/*********************************************************************
*
*       GPIO_OUTPUT_XP_YM
*
* 
*/
void GPIO_OUTPUT_XP_YM(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_6  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
}

/*********************************************************************
*
*       GPIO_OUTPUT_XP_YM
*
* 
*/
void GPIO_INPUT_XM_YP(void) {
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_1  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//Clr_T_XM;
	//Clr_nT_YP;

	
}

void GPIO_INPUT_XM_YP_end(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2  ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	//Clr_T_XM;
	//Clr_nT_YP;
	

	
}

void GUI_X_Init_touch(void) {
	
	
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA , ENABLE);
	
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_10 | GPIO_Pin_6 | GPIO_Pin_8 ;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//systeam tick timer for GUI_Delay
	if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }
}

uint16_t TouchScreen_readPressure(void)
{
	//float theArray[2];
	uint16_t _rxplate; 
	uint16_t x,z;
	
	
	LCD_CS(1);//turn off lcd data
	// Set X+ to ground
	GPIO_OUTPUT_XP_YM();//pinMode(_xp, OUTPUT);
	LCD_T_XP(0);//digitalWrite(_xp, LOW);
	// Set Y- to VCC
	//GPIO_OUTPUT_XP_YM();//pinMode(_ym, OUTPUT);
	 LCD_T_YM(1);//digitalWrite(_ym, HIGH);
	// Hi-Z X- and Y+
	//LCD_T_XM(0);
	//LCD_T_YP(0);
	//GPIO_INPUT_XM_YP();//pinMode(_xm, INPUT);
	GPIO_INPUT_XM_YP();//pinMode(_yp, INPUT);
	// read ADC
	theArray[0] = badprogADC(ADC_Channel_12);//* (3.3 / 4095);
	theArray[1] = badprogADC(ADC_Channel_11);//* (3.3 / 4095);
	
	uint16_t z1= badprogADC(ADC_Channel_12);//int z1 = readADC(_xm); C2
	uint16_t z2= badprogADC(ADC_Channel_11);//int z2 = readADC(_yp); C1
	
	
		
	GPIO_INPUT_XM_YP_end();
	
	if (_rxplate != 0) {
     // now read the x 
     float rtouch;
     rtouch = z2;
     rtouch /= z1;
     rtouch -= 1;
     //rtouch *= x;
     //rtouch *= _rxplate;
     rtouch /= 4095;
     
     z = (uint16_t) rtouch;
		//z = (4095-(z2+z1)/2);
   } else {
     z = (4095-(z2-z1)/2);
   }

		
	// enable ADC
  //ADC_Cmd(ADC1, DISABLE);
	//GUI_X_Init_touch();
	//return theArray[0];
	return (z-2054);
}


//TSPoint TouchScreen::getPoint(void) {
//  int x, y, z;
//  int samples[NUMSAMPLES];
//  uint8_t i, valid;
//  

//  uint8_t xp_port = digitalPinToPort(_xp);
//  uint8_t yp_port = digitalPinToPort(_yp);
//  uint8_t xm_port = digitalPinToPort(_xm);
//  uint8_t ym_port = digitalPinToPort(_ym);

//  uint8_t xp_pin = digitalPinToBitMask(_xp);
//  uint8_t yp_pin = digitalPinToBitMask(_yp);
//  uint8_t xm_pin = digitalPinToBitMask(_xm);
//  uint8_t ym_pin = digitalPinToBitMask(_ym);


//  valid = 1;

//  pinMode(_yp, INPUT);
//  pinMode(_ym, INPUT);
//  
//  *portOutputRegister(yp_port) &= ~yp_pin;
//  *portOutputRegister(ym_port) &= ~ym_pin;
//  //digitalWrite(_yp, LOW);
//  //digitalWrite(_ym, LOW);
//   
//  pinMode(_xp, OUTPUT);
//  pinMode(_xm, OUTPUT);
//  //digitalWrite(_xp, HIGH);
//  //digitalWrite(_xm, LOW);
//  *portOutputRegister(xp_port) |= xp_pin;
//  *portOutputRegister(xm_port) &= ~xm_pin;
//   
//   for (i=0; i<NUMSAMPLES; i++) {
//     samples[i] = analogRead(_yp);
//   }
//#if NUMSAMPLES > 2
//   insert_sort(samples, NUMSAMPLES);
//#endif
//#if NUMSAMPLES == 2
//   if (samples[0] != samples[1]) { valid = 0; }
//#endif
//   x = (1023-samples[NUMSAMPLES/2]);

//   pinMode(_xp, INPUT);
//   pinMode(_xm, INPUT);
//   *portOutputRegister(xp_port) &= ~xp_pin;
//   //digitalWrite(_xp, LOW);
//   
//   pinMode(_yp, OUTPUT);
//   *portOutputRegister(yp_port) |= yp_pin;
//   //digitalWrite(_yp, HIGH);
//   pinMode(_ym, OUTPUT);
//  
//   for (i=0; i<NUMSAMPLES; i++) {
//     samples[i] = analogRead(_xm);
//   }

//#if NUMSAMPLES > 2
//   insert_sort(samples, NUMSAMPLES);
//#endif
//#if NUMSAMPLES == 2
//   if (samples[0] != samples[1]) { valid = 0; }
//#endif

//   y = (1023-samples[NUMSAMPLES/2]);

//   // Set X+ to ground
//   pinMode(_xp, OUTPUT);
//   *portOutputRegister(xp_port) &= ~xp_pin;
//   //digitalWrite(_xp, LOW);
//  
//   // Set Y- to VCC
//   *portOutputRegister(ym_port) |= ym_pin;
//   //digitalWrite(_ym, HIGH); 
//  
//   // Hi-Z X- and Y+
//   *portOutputRegister(yp_port) &= ~yp_pin;
//   //digitalWrite(_yp, LOW);
//   pinMode(_yp, INPUT);
//  
//   int z1 = analogRead(_xm); 
//   int z2 = analogRead(_yp);

//   if (_rxplate != 0) {
//     // now read the x 
//     float rtouch;
//     rtouch = z2;
//     rtouch /= z1;
//     rtouch -= 1;
//     rtouch *= x;
//     rtouch *= _rxplate;
//     rtouch /= 1024;
//     
//     z = rtouch;
//   } else {
//     z = (1023-(z2-z1));
//   }

//   if (! valid) {
//     z = 0;
//   }

//   return TSPoint(x, y, z);
//}

uint16_t TouchScreen_readTouchX(void) {
  
   
   
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1  ;  //pinMode(_yp, INPUT);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7  ;//pinMode(_ym, INPUT);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LCD_T_YP(0);//digitalWrite(_yp, LOW);
	LCD_T_YM(0);//digitalWrite(_ym, LOW);
	
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2  ;//xm     pinMode(_xm, OUTPUT);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6  ;//xp  pinMode(_xp, OUTPUT);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
   
   
   LCD_T_XP(1);//digitalWrite(_xp, HIGH);
   LCD_T_XM(0);//digitalWrite(_xm, LOW);
   
	 theArray[0] = badprogADC(ADC_Channel_11);//* (3.3 / 4095);yp
	 theArray[1] = badprogADC(ADC_Channel_11);//* (3.3 / 4095);
   
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1  ;  //pinMode(_yp, INPUT);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7  ;//pinMode(_ym, INPUT);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 return theArray[0];
	 //return (1023-analogRead(_yp));
}

//int TouchScreen::readTouchX(void) {
//   pinMode(_yp, INPUT);
//   pinMode(_ym, INPUT);
//   digitalWrite(_yp, LOW);
//   digitalWrite(_ym, LOW);
//   
//   pinMode(_xp, OUTPUT);
//   digitalWrite(_xp, HIGH);
//   pinMode(_xm, OUTPUT);
//   digitalWrite(_xm, LOW);
//   
//   return (1023-analogRead(_yp));
//}

uint16_t TouchScreen_readTouchY(void) {
  
   
   
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2  ;  //pinMode(_XM, INPUT);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6  ;//pinMode(_XP, INPUT);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LCD_T_XP(0);//digitalWrite(_yp, LOW);
	LCD_T_XM(0);//digitalWrite(_ym, LOW);
	
	
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1  ;//YP    pinMode(_YP, OUTPUT);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7  ;//xp  pinMode(_YM, OUTPUT);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
   
   
   LCD_T_YP(1);//digitalWrite(_xp, HIGH);
   LCD_T_YM(0);//digitalWrite(_xm, LOW);
   
	 theArray[0] = badprogADC(ADC_Channel_12);//* (3.3 / 4095);
	 theArray[1] = badprogADC(ADC_Channel_7);//* (3.3 / 4095);
   
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2  ;  //pinMode(_XM, INPUT);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_IPD;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6  ;//pinMode(_XP, INPUT);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	 return theArray[0];
	 //return (1023-analogRead(_yp));
}


//int TouchScreen::readTouchY(void) {
//   pinMode(_xp, INPUT);
//   pinMode(_xm, INPUT);
//   digitalWrite(_xp, LOW);
//   digitalWrite(_xm, LOW);
//   
//   pinMode(_yp, OUTPUT);
//   digitalWrite(_yp, HIGH);
//   pinMode(_ym, OUTPUT);
//   digitalWrite(_ym, LOW);
//   
//   return (1023-analogRead(_xm));
//}

