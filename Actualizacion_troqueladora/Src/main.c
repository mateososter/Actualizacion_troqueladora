
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define READ  0x80; // con OR
#define WRITE 0x7F; // con AND
#define SS_PIN GPIO_PIN_4; // Del puerto C
#define RST_PIN GPIO_PIN_5; // Del puerto C

//PCD_Registers
		// Page 0: Command and status
		//						  			0x00			// reserved for future use
		uint8_t CommandReg=				0x01 << 1;	// starts and stops command execution
		uint8_t ComIEnReg=					0x02 << 1;	// enable and disable interrupt request control bits
		uint8_t DivIEnReg=					0x03 << 1;	// enable and disable interrupt request control bits
		uint8_t ComIrqReg=					0x04 << 1;	// interrupt request bits
		uint8_t DivIrqReg=					0x05 << 1;	// interrupt request bits
		uint8_t ErrorReg=					0x06 << 1;	// error bits showing the error status of the last command executed 
		uint8_t Status1Reg=					0x07 << 1;	// communication status bits
		uint8_t Status2Reg=					0x08 << 1;	// receiver and transmitter status bits
		uint8_t FIFODataReg=					0x09 << 1;	// input and output of 64 byte FIFO buffer
		uint8_t FIFOLevelReg=				0x0A << 1;	// number of bytes stored in the FIFO buffer
		uint8_t WaterLevelReg=				0x0B << 1;	// level for FIFO underflow and overflow warning
		uint8_t ControlReg=					0x0C << 1;	// miscellaneous control Reg=isters
		uint8_t BitFramingReg=				0x0D << 1;	// adjustments for bit-oriented frames
		uint8_t CollReg=						0x0E << 1;	// bit position of the first bit-collision detected on the RF interface
		//						  			0x0F			// reserved for future use
		
		// Page 1: Command
		// 						  			0x10			// reserved for future use
		uint8_t ModeReg=						0x11 << 1;	// defines general modes for transmitting and receiving 
		uint8_t TxModeReg=					0x12 << 1;	// defines transmission data rate and framing
		uint8_t RxModeReg=					0x13 << 1;	// defines reception data rate and framing
		uint8_t TxControlReg=				0x14 << 1;	// controls the logical behavior of the antenna driver pins TX1 and TX2
		uint8_t TxASKReg=					0x15 << 1;	// controls the setting of the transmission modulation
		uint8_t TxSelReg=					0x16 << 1;	// selects the internal sources for the antenna driver
		uint8_t RxSelReg=					0x17 << 1;	// selects internal receiver settings
		uint8_t RxThresholdReg=				0x18 << 1;	// selects thresholds for the bit decoder
		uint8_t DemodReg=					0x19 << 1;	// defines demodulator settings
		// 						  			0x1A			// reserved for future use
		// 						  			0x1B			// reserved for future use
		uint8_t MfTxReg=						0x1C << 1;	// controls some MIFARE communication transmit parameters
		uint8_t MfRxReg=						0x1D << 1;	// controls some MIFARE communication receive parameters
		// 						  			0x1E			// reserved for future use
		uint8_t SerialSpeedReg=				0x1F << 1;	// selects the speed of the serial UART interface
		
		// Page 2: Configuration
		// 						  			0x20			// reserved for future use
		uint8_t CRCResultRegH=				0x21 << 1;	// shows the MSB and LSB values of the CRC calculation
		uint8_t CRCResultRegL=				0x22 << 1;
		// 						  			0x23			// reserved for future use
		uint8_t ModWidthReg=					0x24 << 1;	// controls the ModWidth setting?
		// 						  			0x25			// reserved for future use
		uint8_t RFCfgReg=					0x26 << 1;	// configures the receiver gain
		uint8_t GsNReg=						0x27 << 1;	// selects the conductance of the antenna driver pins TX1 and TX2 for modulation 
		uint8_t CWGsPReg=					0x28 << 1;	// defines the conductance of the p-driver output during periods of no modulation
		uint8_t ModGsPReg=					0x29 << 1;	// defines the conductance of the p-driver output during periods of modulation
		uint8_t TModeReg=					0x2A << 1;	// defines settings for the internal timer
		uint8_t TPrescalerReg=				0x2B << 1;	// the lower 8 bits of the TPrescaler value. The 4 high bits are in TModeReg=.
		uint8_t TReloadRegH=					0x2C << 1;	// defines the 16-bit timer reload value
		uint8_t TReloadRegL=					0x2D << 1;
		uint8_t TCounterValueRegH=			0x2E << 1;	// shows the 16-bit timer value
		uint8_t TCounterValueRegL=			0x2F << 1;
		
		// Page 3: Test Registers
		// 						  			0x30			// reserved for future use
		uint8_t TestSel1Reg=					0x31 << 1;	// general test signal configuration
		uint8_t TestSel2Reg=					0x32 << 1;	// general test signal configuration
		uint8_t TestPinEnReg=				0x33 << 1;	// enables pin output driver on pins D1 to D7
		uint8_t TestPinValueReg=				0x34 << 1;	// defines the values for D1 to D7 when it is used as an I/O bus
		uint8_t TestBusReg=					0x35 << 1;	// shows the status of the internal test bus
		uint8_t AutoTestReg=					0x36 << 1;	// controls the digital self-test
		uint8_t VersionReg=					0x37 << 1;	// shows the software version
		uint8_t AnalogTestReg=				0x38 << 1;	// controls the pins AUX1 and AUX2
		uint8_t TestDAC1Reg=					0x39 << 1;	// defines the test value for TestDAC1
		uint8_t TestDAC2Reg=					0x3A << 1;	// defines the test value for TestDAC2
		uint8_t TestADCReg=					0x3B << 1;	// shows the value of ADC I and Q channels
		// 						  			0x3C			// reserved for production tests
		// 						  			0x3D			// reserved for production tests
		// 						  			0x3E			// reserved for production tests
		// 						  			0x3F			// reserved for production tests
		
//PCD_Command 
		uint8_t PCD_Idle				= 0x00;		// no action, cancels current command execution
		uint8_t PCD_Mem					= 0x01;		// stores 25 bytes into the internal buffer
		uint8_t PCD_GenerateRandomID	= 0x02;		// generates a 10-byte random ID number
		uint8_t PCD_CalcCRC				= 0x03;		// activates the CRC coprocessor or performs a self-test
		uint8_t PCD_Transmit			= 0x04;		// transmits data from the FIFO buffer
		uint8_t PCD_NoCmdChange			= 0x07;		// no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
		uint8_t PCD_Receive				= 0x08;		// activates the receiver circuits
		uint8_t PCD_Transceive 			= 0x0C;		// transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
		uint8_t PCD_MFAuthent 			= 0x0E;		// performs the MIFARE standard authentication as a reader
		uint8_t PCD_SoftReset			= 0x0F;		// resets the MFRC522

int flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_SPI1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void delayus_block(int n);

/* Prototipos de funciones del lector de tarjetas RFID */
void RFID_init(void);
void RFID_Reset(void);
void RFID_WriteRegister(uint8_t, uint8_t);
void RFID_AntennaOn(void);
uint8_t RFID_ReadRegister(uint8_t);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t spi_rx_buffer[10];
	uint8_t spi_tx_buffer[2];	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */


  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	
	spi_rx_buffer[0] = 0;
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET);
	spi_tx_buffer[0] = 0x27|READ;
	spi_tx_buffer[1] = 0x00;
	HAL_SPI_Transmit(&hspi1, (uint8_t*) spi_tx_buffer, (uint16_t) 1, (uint32_t) 5);
	HAL_SPI_Receive(&hspi1, (uint8_t*) spi_rx_buffer, (uint16_t) 1, (uint32_t) 5);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM4 init function */
static void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 15;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC4 PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PD12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Stop_IT(&htim4);
	flag=1;
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}

void delayus_block(int n){
	if (n !=0) {
		flag = 0;
		htim4.Init.Period = (16*n);
		if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
		HAL_TIM_Base_Start_IT(&htim4);
		while(flag == 0) {
		}
	}
}

void RFID_init(void){
	uint8_t hardReset = 0;

	// EL SS_PIN debe estar seteado como salida. Lo ponemos en 1 (Esto quiere decir que NO seleccionamos el dispositivo aun)
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);
	
	//EL RST_PIN debe estar seteado como salida.
	if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) == 0) {	// The MFRC522 chip is in power down mode.
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);		// Exit power down mode. This triggers a hard reset.
		// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74µs. Let us be generous: 50ms.
		HAL_Delay(50);
		hardReset = 1;
	}
	
	if (!hardReset) { // Perform a soft reset if we haven't triggered a hard reset above.
		RFID_Reset();
	}	
	
	// Reset baud rates
	RFID_WriteRegister(TxModeReg, 0x00);
	RFID_WriteRegister(RxModeReg, 0x00);
	// Reset ModWidthReg
	RFID_WriteRegister(ModWidthReg, 0x26);
	
	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	RFID_WriteRegister(TModeReg, 0x80);			// TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	RFID_WriteRegister(TPrescalerReg, 0xA9);		// TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25µs.
	RFID_WriteRegister(TReloadRegH, 0x03);		// Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
	RFID_WriteRegister(TReloadRegL, 0xE8);
	
	RFID_WriteRegister(TxASKReg, 0x40);		// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
	RFID_WriteRegister(ModeReg, 0x3D);		// Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363 (ISO 14443-3 part 6.2.4)
	RFID_AntennaOn();						// Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset)
} // Termina RFID_init

void RFID_Reset(void){
	RFID_WriteRegister(CommandReg, PCD_SoftReset);	// Issue the SoftReset command.
	// The datasheet does not mention how long the SoftRest command takes to complete.
	// But the MFRC522 might have been in soft power-down mode (triggered by bit 4 of CommandReg) 
	// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74µs. Let us be generous: 50ms.
	HAL_Delay(50);
	// Wait for the PowerDown bit in CommandReg to be cleared
	while (RFID_ReadRegister(CommandReg) & (1<<4)) {
		// PCD still restarting - unlikely after waiting 50ms, but better safe than sorry.
	}
}// Termina RFID_Reset

void RFID_WriteRegister(uint8_t Reg, uint8_t Value){
	SPI.beginTransaction(SPISettings(MFRC522_SPICLOCK, MSBFIRST, SPI_MODE0));	// Set the settings to work with SPI bus
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_RESET);		// Select slave
	SPI.transfer(reg);						// MSB == 0 is for writing. LSB is not used in address. Datasheet section 8.1.2.3.
	SPI.transfer(value);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET);		// Release slave again
	SPI.endTransaction(); // Stop using the SPI bus
} // Termina RFID_WriteRegister

uint8_t RFID_ReadRegister(uint8_t Reg){
	
} // Termina RFID_ReadRegister


void RFID_AntennaOn(void){
	
} //Termina RFID_AntennaOn

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
