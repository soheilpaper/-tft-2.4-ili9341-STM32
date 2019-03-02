#  Arduino 2.4 TFT ILI9341 LCD Converted for STM32F103RE 
 
It is based on one Arduino 2.4 TFT ILI9341 LCD Converted for STM32F103RE in KEIL Software for working with Touch screen library with X Y and Z (pressure) readings as well.
SO you could see some information about this filed in this link:

[electronics.stackexchange Page](https://electronics.stackexchange.com/questions/424146/touch-pins-of-tft-2-4-ili9341-touch-funtion-in-keil-for-arm-mcu?noredirect=1#comment1053882_424146)


The LCD Runing Photo:

*![Alt text](http://i65.tinypic.com/294o3ld.jpg  " Arduino 2.4 TFT ILI9341 LCD Converted for STM32F103RE ")

Usage
-----

To get your custom, you have to do the following:


1. Go to `Touchscreen.c` in main Folder AND change LCD Ports in `#define` parts if is deffent by this setting:

	```
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
	```
as you can see we use this setting:

	```
	YP  ->  LCD_WR   ==   C1 Pin in STM32F103RE  
	XM  ->  LCD_RS   ==   C2 Pin in STM32F103RE
	YM  ->  LCD_D6   ==   A7  Pin in STM32F103RE 
	XP  ->  LCD_D5   ==   A6  Pin in STM32F103RE 
	```


2. You must `GPIO PORT Settings` in this Functions (if you use different ports similar Above):
    - `GPIO_OUTPUT_XP_YM`
	- `GPIO_INPUT_XM_YP`
	- `GPIO_INPUT_XM_YP_end`
	- `GUI_X_Init_touch`
	- `TouchScreen_readTouchX`
	- `TouchScreen_readTouchY`
	
3. you must change LCD Ports in	**.\Library\GUI\GUI_X.c** if you dont use this port settings:

	
	```
	YP  ->  LCD_WR   ->   C1 Pin in STM32F103RE  
	XM  ->  LCD_RS   ->  C2 Pin in STM32F103RE
			LCD_CS   ->   C3 Pin in STM32F103RE 
			LCD_RD   ->   C0 Pin in STM32F103RE 
			LCD_Rest   ->   C4 Pin in STM32F103RE 
			
			LCD_D7   ->   A7  Pin in STM32F103RE
	YM  ->  LCD_D6   ->   A6  Pin in STM32F103RE 
	XP  ->  LCD_D5   ->   A5  Pin in STM32F103RE
			LCD_D4   ->   A4  Pin in STM32F103RE
			LCD_D3   ->   A3  Pin in STM32F103RE
			LCD_D2   ->   A2  Pin in STM32F103RE
			LCD_D1   ->   A1  Pin in STM32F103RE
			LCD_D0   ->   A0  Pin in STM32F103RE
			```

4. you must change LCD Port define if you use different conections in `"./ARM-radio-master/include/LCD_X_8080_8.h"` file, we use this tyoe of connecttions:

	```
	#define LCD_CS_GPIO_PORT      GPIOC
	#define LCD_RS_GPIO_PORT      GPIOC
	#define LCD_WR_GPIO_PORT      GPIOC
	#define LCD_RD_GPIO_PORT      GPIOC
	#define LCD_RESET_GPIO_PORT   GPIOC

	#define LCD_DATA_IN       GPIOA->IDR
	#define LCD_DATA_OUT      GPIOA->ODR
	#define LCD_SET_DIR_IN()  GPIOA->IDR = 0x0
	#define LCD_SET_DIR_OUT() GPIOA->ODR = 0x0
	#define LCD_DELAY(ms)     GUI_X_Delay(ms)

	#define LCD_CS_PIN      GPIO_Pin_3
	#define LCD_RS_PIN      GPIO_Pin_2
	#define LCD_WR_PIN      GPIO_Pin_1
	#define LCD_RD_PIN      GPIO_Pin_0
	#define LCD_RST_PIN     GPIO_Pin_4
	```


5. you can change the `while` loop as you like:

	```
	while (1) {
			GUI_Clear();
			GUI_SetBkColor(GUI_BLACK);
			GUI_SetColor(GUI_CYAN);
		sprintf(buffer, "%d\r\n", (int) TouchScreen_readPressure());GUI_Delay(300);
			// GUI_Init(); GUI_Delay(300);
		GUI_DispStringHCenterAt(buffer, 29, 30);	GUI_Delay(300);
			GUI_DispStringAt("GUI_DispFloat:\n", 11, 11);
			GUI_GotoX(100);
			GUI_GotoY(100);
			GUI_DispString("TouchX:    ");
			f=(float) TouchScreen_readTouchX();GUI_Delay(300);
			GUI_DispFloat(f,9);
			
			GUI_GotoX(100);
			GUI_GotoY(150);
			GUI_DispString("TouchY:    ");
			f=(float) TouchScreen_readTouchY();GUI_Delay(300);
			GUI_DispFloat(f,9);
		GUI_Delay(300);
		}
		```   



  ******************************************************************************
  * @email    gsh.med.co@gmail.com or elasa.group@gmail.com
  * @author  Soheil sabzevari
  * @version V1.0.0
  * @date    2-March-2019
  * @brief   It is based on one Arduino 2.4 TFT ILI9341 LCD Converted for STM32F013RE in KEIL Software.
 		
