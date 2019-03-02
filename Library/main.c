#include "ads7843.h"
#include "GUI.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../sssa.c" // Include the converted
#include "FramewinDLG.h"
//#include <math.h> 

#include "stm32f10x.h"
//#include "../Touchscreen.c"

extern const GUI_BITMAP_METHODS GUI_BitmapMethods444_12;
//extern GUI_CONST_STORAGE GUI_BITMAP bm1qwyp4oz_htroller2_low;
extern GUI_CONST_STORAGE GUI_BITMAP bm11;
extern uint16_t TouchScreen_readPressure();
extern uint16_t TouchScreen_readTouchX();
extern uint16_t TouchScreen_readTouchY();
void DrawBitmap(const void * pData, int xPos, int yPos) {
GUI_BITMAP Bitmap;
GUI_LOGPALETTE Palette;
GUI_CreateBitmapFromStream(&Bitmap, &Palette, pData);
GUI_DrawBitmap(&Bitmap, xPos, yPos);
}
/*************************** End of file ****************************/
//void initLed(void);
//void delay_ms( uint32_t del)
//{
// uint32_t i,j;
// for ( i=0; i<del; i++)
// for(j=0;j<10000;j++);
//}

//int main_first() {
//	int i;
//	float f = 123.45678;
//	initLed();
//	
//GUI_Init();
//	
//	GUI_SetBkColor(GUI_DARKBLUE);GUI_Delay(500);
//	GUI_SetPenSize(120);
//	GUI_COLOR aColor[] = {GUI_RED, GUI_YELLOW,GUI_DARKBLUE};
//	GUI_SetFont(GUI_FONT_32B_1);
//	GUI_DispStringAt("GUI_DispStringAt",120,60);
// GUI_DispString("Hello world!");
//	GUI_JPEG_Draw(_acs, sizeof(_acs), 111, 111);GUI_Delay(500);
//	GPIOC->BSRR = 1 <<  8;
//	GUI_Delay(1000);
//	GPIOC->BRR =1 <<  8;
//	GUI_Delay(1000);
//while(1){
////	GUI_SetFont(&GUI_FontComic24B_ASCII);
////GUI_DispStringAt("while(1)", 100, 100);
//		
////		GUI_GotoX(10);GUI_GotoY(60);
////		GUI_SetFont(&GUI_Font8x8);
////    GUI_DispStringAt("GUI_DispFloat:\n", 30, 30);
////    GUI_DispFloat(f, 9);
//	for (i = 0; i < 3; i++) {
//GUI_Clear();
//GUI_SetColor(aColor[i]);GUI_Delay(100);
//		GUI_JPEG_Draw(_acs, sizeof(_acs), 111, 111);GUI_Delay(500);
//		//GUI_FillCircle(120,60,50);GUI_Delay(200);
//		GUI_SetBkColor(aColor[i]);GUI_Delay(100);

////GUI_Delay(200);
// }
//	GPIOC->BSRR = 1 <<  8;
//	GUI_Delay(100);
//	GPIOC->BRR =1 <<  8;
//	GUI_Delay(100);
//}
//}
//int main0(){
//	float f = 123.45678;
///*Initilize GUI*/
//	initLed();
//	RCC->APB2ENR |= (1UL << 4);                /* Enable GPIOB clock            */
//  
//  GPIOC->CRH    =  0x33333333;               /* PB.8..16 defined as Outputs   */
//	GPIOC->BSRR = 1 <<  8;
//	delay_ms(1000);
//	GPIOC->BRR =1 <<  8;
//	delay_ms(1000);
//	
////ADS7843_Initialize();
//GUI_Init();
//GUI_Clear();
//	GUI_CURSOR_Show(); 
//CreateFramewin();
//	
//GUI_Delay(10);
//	
//	GUI_SetBkColor(GUI_DARKBLUE);GUI_Delay(1000);
//	GUI_SetBkColor(GUI_RED);GUI_Delay(1000);
//GUI_Clear();
//GUI_DrawGradientV(10, 10, 300, 200, GUI_BLUE, GUI_RED);
//GUI_Delay(1000);

//GUI_GotoX(100);GUI_GotoY(100);
//GUI_SetFont(&GUI_Font6x8);
//GUI_DispString("The result is: "); // Disp text

//GUI_Delay(1000);
//GUI_Clear();
//GUI_SetColor(GUI_DARKBLUE);
//GUI_SetPenSize(20);
//GUI_AA_DrawRoundedRect(10, 10, 50, 50, 5);
//GUI_Delay(1000);


////GPIO_WriteBit(GPIOC,GPIO_Pin_3,1);
//  GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);
//	//GPIO_SetBits(GPIOC,GPIO_Pin_5,1)
//	GPIO_WriteBit(GPIOC,GPIO_Pin_5,0);
//	
//	while (1)
//  {
//		GUI_GotoX(10);GUI_GotoY(60);
//		GUI_SetFont(&GUI_Font8x8);
//    GUI_DispStringAt("GUI_DispFloat:\n", 30, 30);
//    GUI_DispFloat(f, 9);
//    GUI_GotoX(100);
//		delay_ms(1000);
//    /* USER CODE END WHILE */
//        GPIOC->BSRR |= 1 << 8;
//        delay_ms( 100 ); 
//        GPIOC->BRR |=  1 << 8;
//        delay_ms(100);
//		    GUI_Clear();delay_ms(1000);
//		
////		GPIO_WriteBit(GPIOC,GPIO_Pin_5,1);
////	  delay_ms(10);
////	GPIO_WriteBit(GPIOC,GPIO_Pin_5,0);
////		delay_ms(10);
//    /* USER CODE BEGIN 3 */
// }
//	
//while(0){
//	GPIOC->BSRR = 1 <<  8;
//	GUI_Delay(100);
//	GPIOC->BRR =1<<  8;
//	GUI_Delay(100);
//	
//	GUI_TOUCH_Exec();
//	GUI_TOUCH_StoreState(GUI_TOUCH_GetxPhys(),GUI_TOUCH_GetyPhys());
//	GUI_CURSOR_SetPosition(GUI_TOUCH_GetxPhys(),GUI_TOUCH_GetyPhys());
////  GUI_TOUCH_StoreState(GUI_TOUCH_GetxPhys(),GUI_TOUCH_GetyPhys());
//	GUI_Delay(10);
// }
//}

//void initLed(){
//  GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);	
//}



//#include "GUI.h"
////#include "LCDConf.h"

///*******************************************************************
//*
//*       Defines
//*
//********************************************************************
//*/
//#define X_START 60
//#define Y_START 40

///*******************************************************************
//*
//*       Types
//*
//********************************************************************
//*/
//typedef struct {
//  int NumBars;

//  GUI_COLOR Color;
//  const char * s;
//} BAR_DATA;

///*******************************************************************
//*
//*       Static data
//*
//********************************************************************
//*/
//static const BAR_DATA _aBarData[] = {
//  { 2, GUI_RED    , "Red" },
//  { 2, GUI_GREEN  , "Green" },
//  { 2, GUI_BLUE   , "Blue" },
//  { 1, GUI_WHITE  , "Grey" },
//  { 2, GUI_YELLOW , "Yellow" },
//  { 2, GUI_CYAN   , "Cyan" },
//  { 2, GUI_MAGENTA, "Magenta" },
//};

//static const GUI_COLOR _aColorStart[] = { GUI_BLACK, GUI_WHITE };

///*******************************************************************
//*
//*       Static code
//*
//********************************************************************
//*/
///*******************************************************************
//*
//*       _DemoShowColorBar
//*/
//static void _DemoShowColorBar(void) {
//  GUI_RECT Rect;
//  int      yStep;
//  int      i;
//  int      j;
//  int      xSize;
//  int      ySize;
//  int      NumBars;
//  int      NumColors;

//  //
//  // Get display size
//  //
//  xSize = LCD_GetXSize();
//  ySize = LCD_GetYSize();
//  //
//  // Get number of bars
//  //
//  NumColors = GUI_COUNTOF(_aBarData);
//  for (i = NumBars = 0, NumBars = 0; i < NumColors; i++) {
//    NumBars += _aBarData[i].NumBars;
//  }
//  yStep = (ySize - Y_START) / NumBars;
//  //
//  // Draw text
//  //
//  Rect.x0 = 0;
//  Rect.x1 = X_START - 1;
//  Rect.y0 = Y_START;
//	GUI_SetFont(&GUI_Font8x16);
//  for (i = 0; i < NumColors; i++) {
//    Rect.y1 = Rect.y0 + yStep * _aBarData[i].NumBars - 1;
//    GUI_DispStringInRect(_aBarData[i].s, &Rect, GUI_TA_LEFT | GUI_TA_VCENTER);
//    Rect.y0 = Rect.y1 + 1;
//  }
//  //
//  // Draw colors
//  //
//  Rect.x0 = X_START;
//  Rect.x1 = xSize - 1;
//  Rect.y0 = Y_START;
//  for (i = 0; i < NumColors; i++) {
//    for (j = 0; j < _aBarData[i].NumBars; j++) {
//      Rect.y1 = Rect.y0 + yStep - 1;
//      GUI_DrawGradientH(Rect.x0, Rect.y0, Rect.x1, Rect.y1, _aColorStart[j], _aBarData[i].Color);
//      Rect.y0 = Rect.y1 + 1;
//    }
//  }
//}

///*********************************************************************
//*
//*       Public code
//*
//**********************************************************************
//*/
///*********************************************************************
//*
//*       MainTask
//*/
//void MainTask(void) {
//	//TFT_SetOrientation(1) ; 
//  GUI_Init();
//	//TFT_SetOrientation(1) ; 
//  GUI_SetBkColor(GUI_CYAN);
//  GUI_Clear();
//  GUI_SetColor(GUI_WHITE);
//  GUI_SetFont(&GUI_Font24_ASCII);
//  //GUI_DispStringHCenterAt("COLOR_ShowColorBar - Sample", 160, 5);
//  _DemoShowColorBar();
//  //while(1)
//   // GUI_Delay(100);
//}



//void DrawArcScale(void) {
//int x0 = 160;
//int y0 = 180;
//int i;
//	char ac[4];
//GUI_SetBkColor(GUI_WHITE);
//GUI_Clear();
//GUI_SetPenSize( 5 );
//GUI_SetTextMode(GUI_TM_TRANS);
//GUI_SetFont(&GUI_FontComic18B_ASCII);
//GUI_SetColor( GUI_BLACK );
//GUI_DrawArc( x0,y0,150, 150,-30, 210 );
//GUI_Delay(1000);
//for (i=0; i<= 23; i++) {
//float a = (-30+i*10)*3.1415926/180;
//int x = -141*cos(a)+x0;
//int y = -141*sin(a)+y0;
//if (i%2 == 0)
//GUI_SetPenSize( 5 );
//else
//GUI_SetPenSize( 4 );
//GUI_DrawPoint(x,y);
//if (i%2 == 0) {
//x = -123*cos(a)+x0;
//y = -130*sin(a)+y0;
//sprintf(ac, "%d", 10*i);
//GUI_SetTextAlign(GUI_TA_VCENTER);
//GUI_DispStringHCenterAt(ac,x,y);
//}
//}
//}

//int main(){
//	MainTask();
//DrawArcScale();
//while(1){
//DrawArcScale();	GUI_Delay(500);
//main_first();	GUI_Delay(500);
//}
//}/*************************** End of file ****************************/





/*********************************************************************
*
*       MainTask
*/
void MainTask1(void) {
  int xPos, yPos, xSize, ySize;
  int i = 0;
	char buffer[32];
	float f = 123.45678;

  GUI_Init();

//  GUI_SetBkColor(GUI_RED);
//  GUI_Clear();
//  GUI_Delay(500);
//  GUI_SetBkColor(GUI_GREEN);
//  GUI_Clear();
//  GUI_Delay(500);
//  GUI_SetBkColor(GUI_BLUE);
//  GUI_Clear();
//  GUI_Delay(500);
//  
		
	//GUI_DrawBitmap(&bms111, 30, 30);
	//GUI_JPEG_Draw(_acs, sizeof(_acs), 11, 11);GUI_Delay(500);
	
	GUI_JPEG_Draw(_acsssa, sizeof(_acsssa), 11, 11);GUI_Delay(500);
	GUI_Delay(1000);
	
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  xSize = LCD_GetXSize();
  ySize = LCD_GetYSize();

  GUI_SetFont(&GUI_FontComic24B_1);
  GUI_SetColor(GUI_CYAN);
  GUI_DispStringHCenterAt("www.keil.com",   xSize / 2, 20);
  GUI_SetColor(GUI_DARKBLUE);
  GUI_DispStringHCenterAt("www.segger.com", xSize / 2,200);// ySize - 40);
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

  xPos = xSize / 2;
  yPos = ySize / 3;
  GUI_SetColor(GUI_WHITE);
  GUI_SetTextMode(GUI_TM_REV);
  GUI_SetFont(GUI_FONT_20F_ASCII);
  GUI_DispStringHCenterAt("Hello world!", xPos, yPos);
  GUI_SetFont(GUI_FONT_D24X32);
  xSize = GUI_GetStringDistX("0000");
  xPos -= xSize / 2;
  yPos += 24 + 10;
  while (1) {
		GUI_Delay(3000);
		GUI_JPEG_Draw(_acsssa, sizeof(_acsssa), 11, 11);GUI_Delay(3000);
    GUI_DispDecAt(i++, xPos, yPos, 4);
    if (i > 9999) {
      i = 0;
    }
  } 
}

/*********************************************************************
*
*       Main
*/
int main () {
  MainTask1();
  for (;;);
}

/*************************** End of file ****************************/