#include "ads7843.h"

//------------------------------------------------------------------------------
//         Defines
//------------------------------------------------------------------------------

#define ADS_CTRL_PD0              (1 << 0)        // PD0
#define ADS_CTRL_PD1              (1 << 1)        // PD1
#define ADS_CTRL_DFR              (1 << 2)        // SER/DFR
#define ADS_CTRL_EIGHT_BITS_MOD   (1 << 3)        // Mode
#define ADS_CTRL_START            (1 << 7)        // Start Bit
#define ADS_CTRL_SWITCH_SHIFT     4               // Address setting

#if defined(cortexm3)
// Get X position command
#define CMD_Y_POSITION ((1 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START | ADS_CTRL_PD0 | ADS_CTRL_PD1)
// Get Y position command
#define CMD_X_POSITION ((5 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START | ADS_CTRL_PD0 | ADS_CTRL_PD1)
#else
// Get X position command
#define CMD_X_POSITION ((1 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START | ADS_CTRL_PD0 | ADS_CTRL_PD1)
// Get Y position command
#define CMD_Y_POSITION ((5 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START | ADS_CTRL_PD0 | ADS_CTRL_PD1)
#endif

// Enable penIRQ
#define CMD_ENABLE_PENIRQ  ((1 << ADS_CTRL_SWITCH_SHIFT) | ADS_CTRL_START)


#define AT91C_TOUCHSCREEN_TIMEOUT        5000000

#define DELAY_BEFORE_SPCK          (200 << 16) // 2us min (tCSS) <=> 200/100 000 000 = 2us
#define DELAY_BETWEEN_CONS_COM     (0xf << 24) // 5us min (tCSH) <=> (32 * 15) / (100 000 000) = 5us


#define SPI_FLASH                 SPI3
#define SPI_FLASH_CLK             RCC_APB1Periph_SPI3
#define SPI_FLASH_GPIO            GPIOC
#define SPI_FLASH_GPIO_CLK        RCC_APB2Periph_GPIOC
#define SPI_FLASH_PIN_SCK         GPIO_Pin_10
#define SPI_FLASH_PIN_MISO        GPIO_Pin_11
#define SPI_FLASH_PIN_MOSI        GPIO_Pin_12


#define SPI_FLASH_CS             GPIO_Pin_2
#define SPI_FLASH_CS_GPIO        GPIOB
#define SPI_FLASH_CS_GPIO_CLK    RCC_APB2Periph_GPIOB




/* Select SPI FLASH: Chip Select pin low  */
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(SPI_FLASH_CS_GPIO, SPI_FLASH_CS)
/* Deselect SPI FLASH: Chip Select pin high */
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(SPI_FLASH_CS_GPIO, SPI_FLASH_CS)
  
//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//static unsigned char SPI_RW (unsigned char output)
//{
//  uint8_t RxData = 0;
//  /* Loop while DR register in not emplty */
//  //while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_TXE) == RESET);

//  /* Send byte through the SPI1 peripheral */
//  SPI_I2S_SendData(SPI_FLASH, output);

//  /* Wait to receive a byte */
//  while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_RXNE) == RESET);

//  /* Return the byte read from the SPI bus */
//  RxData=SPI_I2S_ReceiveData(SPI_FLASH);

//  return (uint8_t)RxData;
//}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *   from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{

  uint8_t RxData = 0;
  /* Loop while DR register in not empty */
  //while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI_FLASH, byte);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI_FLASH, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  RxData=SPI_I2S_ReceiveData(SPI_FLASH);

  return (uint8_t)RxData;
}


static unsigned int SendCommand(unsigned char bCmd)
{
unsigned int uResult =0;
	
   SPI_FLASH_CS_LOW() ;
   SPI_FLASH_SendByte(bCmd);
   uResult=SPI_FLASH_SendByte(0x00);
   uResult <<= 8;
   uResult += SPI_FLASH_SendByte(0x00);
   uResult = uResult >> 3;
	 SPI_FLASH_CS_HIGH() ; ;
	 return uResult;	
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/// Get position of the pen by ask the ADS controller (SPI)
/// \param px_pos pointer to the horizontal position
/// \param py_pos pointer to the vertical position
//-----------------------------------------------------------------------------
void ADS7843_GetPosition(unsigned int* px_pos, unsigned int* py_pos)
{
    // Get X position
    *px_pos = 4095 - SendCommand(CMD_X_POSITION);
    // Get Y position
    *py_pos = SendCommand(CMD_Y_POSITION);

    // Switch to full power mode
    SendCommand(CMD_ENABLE_PENIRQ);
}
/************************************************************************/
void GPIO_INT_INIT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( TOUCH_INT_GPIO_CLK, ENABLE);

  /* Configure SPI pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = TOUCH_INT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TOUCH_INT_GPIO, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TOUCH_INT_GPIO, &GPIO_InitStructure);

  GPIO_ResetBits(TOUCH_INT_GPIO,GPIO_Pin_15);
 // GPIO_SetBits(TOUCH_INT_GPIO,GPIO_Pin_15);
}
//-----------------------------------------------------------------------------
/// Initialization of the SPI for communication with ADS7843 component
//-----------------------------------------------------------------------------
void ADS7843_Initialize(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	

  /* Enable SPI and GPIO clocks */
  RCC_APB2PeriphClockCmd( SPI_FLASH_GPIO_CLK | SPI_FLASH_CS_GPIO_CLK, ENABLE);
  RCC_APB1PeriphClockCmd(SPI_FLASH_CLK,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SPI3, ENABLE);

  /* Configure SPI pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI_FLASH_PIN_SCK | SPI_FLASH_PIN_MISO | SPI_FLASH_PIN_MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SPI_FLASH_GPIO, &GPIO_InitStructure);

  /* Configure I/O for Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = SPI_FLASH_CS;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI_FLASH_CS_GPIO, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_FLASH, &SPI_InitStructure);

  /* Enable the SPI  */
  SPI_Cmd(SPI_FLASH, ENABLE);

  SendCommand(CMD_ENABLE_PENIRQ);

  GPIO_INT_INIT();
}
//-----------------------------------------------------------------------------
/// Reset the ADS7843
//-----------------------------------------------------------------------------
void ADS7843_Reset(void)
{
    // Disable SPI 0
    SPI_Cmd(SPI_FLASH, DISABLE);
}


