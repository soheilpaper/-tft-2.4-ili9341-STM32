#include "stm32f10x.h"
//#include "stxng.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

#define ARRAY_SIZE 16//32
#define  ADC_CONV_BUFF_SIZE 1
#define NUMSAMPLES 7

uint16_t ADC1ConvertedValue;//[2] = {0,0};//Stores converted vals
uint16_t samples[NUMSAMPLES];
/**
 * Classic delay
 */
void badprogDelay(u32 myTime) {
    u32 i;
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);
    // i = myTime * 68
    i = myTime * (RCC_Clocks.SYSCLK_Frequency >> 20);

    for (; i != 0; i--)
        ;
}

//void ADC_DMA_init(){
//  DMA_InitTypeDef DMA_InitStruct;
///* DMA2 Stream0 channel0 configuration **************************************/
//	DMA_InitStruct.DMA_Channel = DMA_Channel_0;
//	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//ADC3's data register
//	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&ADC1ConvertedValue;
//	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
//	DMA_InitStruct.DMA_BufferSize = 2;
//	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//Reads 16 bit values
//	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//Stores 16 bit values
//	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
//	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
//	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//	DMA_Init(DMA2_Stream0, &DMA_InitStruct);
//	DMA_Cmd(DMA2_Stream0, ENABLE);
//	
//}

void ADC_DMA_init0()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
  
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  /* De-initialise  DMA */
  DMA_DeInit(DMA1_Channel1);
  
  //DMA_InitTypeDef DMA_InitStructure;
	
	/* DMA1 channel1 configuration */
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);	     		 // Set DMA channel Peripheral base address to ADC Data register
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1ConvertedValue;  // Set DMA channel Memeory base addr to ADC_ConvertedValueBuff address
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                         // Set DMA channel direction to peripheral to memory
  DMA_InitStructure.DMA_BufferSize = ADC_CONV_BUFF_SIZE;                     // Set DMA channel buffersize to peripheral to ADC_CONV_BUFF_SIZE
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	     		 // Disable DMA channel Peripheral address auto increment
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                    // Enable Memeory increment (To be verified ....)
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;// set Peripheral data size to 8bit 
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	     	 // set Memeory data size to 8bit 
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                              // Set DMA in normal mode
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;	                     	 // Set DMA channel priority to High
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                               // Disable memory to memory option 
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);		// Use Init structure to initialise channel1 (channel linked to ADC)

  /* Enable Transmit Complete Interrup for DMA channel 1 */ 
  DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
  
  /* Setup NVIC for DMA channel 1 interrupt request */
  NVIC_InitStructure.NVIC_IRQChannel =   DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  DMA_Cmd(DMA1_Channel1, ENABLE);

}

void ADC_DMA_init(void) {
//enable DMA1 clock
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//create DMA structure
DMA_InitTypeDef DMA_InitStructure;
//reset DMA1 channe1 to default values;
DMA_DeInit(DMA1_Channel1);
//channel will be used for memory to memory transfer
DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//setting normal mode (non circular)
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//medium priority
DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//source and destination data size word=32bit
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//automatic memory destination increment enable.
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//source address increment disable
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//Location assigned to peripheral register will be source
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//chunk of data to be transfered
DMA_InitStructure.DMA_BufferSize = 1;
//source and destination start addresses
DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)&ADC1->DR;;
//adc values is: volatile uint16_t ADC_values[ARRAYSIZE];
DMA_InitStructure.DMA_MemoryBaseAddr =  (uint32_t)&ADC1ConvertedValue; 
//send values to DMA registers
DMA_Init(DMA1_Channel1, &DMA_InitStructure);
// Enable DMA1 Channel Transfer Complete interrupt
DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
DMA_Cmd(DMA1_Channel1, ENABLE); //Enable the DMA1 - Channel1
}

int Get_ADC_Converted_Value()//int Get_ADC_Converted_Value()
{
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
  {


    return ADC_GetConversionValue(ADC1);
  }
}
/**
 * Initialization of ADC and the poentiomenter's GPIO
 */
uint16_t  badprogADC(uint8_t ADC_Channel_01) {
  int i;
	int ADC_Z=0;  
	/// declaring GPIO stuff
    GPIO_InitTypeDef GPIO_InitStructure;
    // declaring ADC struct
    ADC_InitTypeDef ADC_InitStructure;
    
	
	
    // deinit ADC
    ADC_DeInit(ADC1);

    // enabling clock
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    // enabling ADC clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

//    // B - Init the GPIO with the structure - Testing ADC
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
//	  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//The pins are configured in analog mode
//	  
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //GPIO_ResetBits(GPIOB,GPIO_Pin_7);
		//GPIO_ResetBits(GPIOB,GPIO_Pin_6);
		
    // init ADC struct
    ADC_StructInit(&ADC_InitStructure);

    // setting the ADC struct
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;

    ADC_DMA_init();
		
	
		// init adc
    ADC_Init(ADC1, &ADC_InitStructure);

    // enable ADC
    ADC_Cmd(ADC1, ENABLE);
    
		
		ADC_DMACmd(ADC1, DISABLE);	
   /* Enable DMA mode for ADC1 */  
    ADC_DMACmd(ADC1, ENABLE);


    // start ADC1 calibration and check the end
    ADC_StartCalibration(ADC1);

    // configure ADC_IN6
    ADC_RegularChannelConfig(ADC1, ADC_Channel_01, 1, ADC_SampleTime_7Cycles5);
		//ADC_RegularChannelConfig(ADC1, ADC_Channel_02, 1, ADC_SampleTime_7Cycles5); ///added

    // start ADC -> retrieve the ADC value from the potentiometer
    // and add it into ADC1->DR with:
    // ADCx->CR2 |= CR2_EXTTRIG_SWSTART_Set;
    // this without using ADC1->DR o_O
    // CR2 = Configuration Register2 -> it seems to be a config with
    // a binary number -> for example 1000010100101010 which sets all
    // registers with default values
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		 // Make sure we have conversion completion
    while( ADC_GetFlagStatus( ADC1, ADC_FLAG_EOC ) == RESET )
{
    // do nothing (or something useful perhaps)
}
		// Wait until ADC is ready
    //while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);
    // check the end of the ADC1 calibration
    // setting ADC1->DR with:
    // if ((ADCx->CR2 & CR2_CAL_Set) != (uint32_t)RESET)
    while (ADC_GetCalibrationStatus(ADC1) == SET);
      
   

    // convert valueADC to valueVolt -> valueADC * (MAX VOLT / 2^12)
    // and also :
    // ADC_SoftwareStartConvCmdsoftwareS,
    // ADC_GetCalibrationStatus
    // with
    // return (uint16_t) ADCx->DR;
    //uint16_t valueADC = ADC_GetConversionValue(ADC1);

//		for (i=0; i<NUMSAMPLES; i++) {
//					samples[i] = ADC_GetConversionValue(ADC1);//analogRead(_yp);
//			}
//		for (i=0; i<NUMSAMPLES; i++) {
//					ADC_Z=samples[i]+ADC_Z;
//			}
//    ADC_Z=ADC_Z/NUMSAMPLES;
		
			
		for (i=0; i<NUMSAMPLES; i++) {
			     ADC_GetConversionValue(ADC1);
					samples[i] = ADC1ConvertedValue;//analogRead(_yp);
			}
		ADC_Z=0;
		for (i=0; i<NUMSAMPLES; i++) {
					ADC_Z=(int) samples[i]+ADC_Z;
			}
    ADC_Z=(int) ADC_Z/NUMSAMPLES;	
    // convert the "uint_16 valueADC" into a "float valueVolt"
    // Volt = 3.3
    // ADC = 12 bits, so 2^12 = 4096
    //float valueVolt = valueADC * (3.3 / 4095);
      // Reset the flag
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
		
		
    //return valueVolt;
		//return  ADC_GetConversionValue(ADC1);
		//return  ADC1ConvertedValue; //YP B7
		//return Get_ADC_Converted_Value();
		return ADC_Z;
}

/**
 * Init the array with '\0';
 */
void badprogInitArray(float *myArray, int size) {
    int i = 0;
    while (i < size) {
        myArray[i] = '\0';
        ++i;
    }
}

/*******************************************************************************
 * Main, what else?
 *******************************************************************************/
int main11(void) {
    float theArray[ARRAY_SIZE];
    int i = 0;

    // init with 0 the whole array
    badprogInitArray(theArray, ARRAY_SIZE);

    // our beautiful infinite loop while i < 32
    while (-2013) {
        if (i < ARRAY_SIZE) {
            theArray[i] = badprogADC(ADC_Channel_11);
            badprogDelay(100000);                          // 1 sec
            ++i;
        }
    }
    return 0;
}