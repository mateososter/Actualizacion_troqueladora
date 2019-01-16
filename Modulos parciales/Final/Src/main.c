
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
  * COPYRIGHT(c) 2019 STMicroelectronics
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
#include "lcd_txt.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define Inicio 0
#define Menu_1 1
#define Menu_2 2
#define Menu_3 3
#define Menu_1x 4
#define Menu_2x 5
#define Menu_3x 6
#define TrabajoEC_G 7 //Trabajo en curso - Golpes
#define TrabajoEC_U 8 //Trabajo en curso - Unidades
#define AgrOp_Maestro 9
#define AgrOp_Nuevo 10
#define AgrOp_Nombre 11
#define Err_TagExiste 12
#define Err_NMaestro 13

//-----------------------
int fila =0;
int col =0;
int f_boton_pres =0; // flag boton presionado
int ms_ar=30; //milisegundos anti-rebote
//-----------------------

int cont_unidades=0;
int f_unidades=0;
int flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART6_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void delayus_block(int n);
void display_escribir(int instancia);
void display_unidades(void);

//-	Seccion teclado	----------------------
void get_boton(void);
void display_tecla(void);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void){
  /* USER CODE BEGIN 1 */

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
  MX_TIM3_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
	
//-	Seccion teclado	----------------------	
	HAL_GPIO_WritePin(GPIOE,0x0F00,GPIO_PIN_SET); //Prende E8, 9, 10 y 11 al mismo tiempo.
//----------------------------------------
	
	LCD_ini();
	HAL_Delay(3);
	LCD_SetPos(0,0);
	HAL_Delay(3);
	LCD_Clear();
	HAL_Delay(3);
	LCD_CursorOff();
	HAL_Delay(3);	
	
	display_escribir(Inicio);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		//-------	Seccion teclado -----------
//		if(!ms_ar&&f_boton_pres){
		if(f_boton_pres){
		if(!(ms_ar)&&f_boton_pres){
			f_boton_pres=0;
			get_boton();
			if(!col) display_tecla();
			
			HAL_GPIO_WritePin(GPIOE,0x0F00,GPIO_PIN_SET);
			
		}
	//---------------------------------------
	}	
//		if(!ms_ar&&f_unidades){
		if(f_unidades){
		if(!(ms_ar)&&f_unidades){
			f_unidades=0;
			cont_unidades++;
			display_unidades();
		}
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}
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

/* TIM3 init function */
static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 0;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
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
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 0;
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

/* USART6 init function */
static void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Teclado_C3_Pin|Display_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Teclado_C2_Pin|Display_E_Pin|Display_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Led_Verde_Pin|Led_Naranja_Pin|Led_Rojo_Pin|Led_Azul_Pin 
                          |Display_D6_Pin|Display_D5_Pin|Display_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Sensor_unidades_Pin Teclado_F4_Pin Teclado_F3_Pin Teclado_F2_Pin 
                           Teclado_F1_Pin */
  GPIO_InitStruct.Pin = Sensor_unidades_Pin|Teclado_F4_Pin|Teclado_F3_Pin|Teclado_F2_Pin 
                          |Teclado_F1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : Teclado_C4_Pin */
  GPIO_InitStruct.Pin = Teclado_C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Teclado_C4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Sensor_golpes_Pin */
  GPIO_InitStruct.Pin = Sensor_golpes_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Sensor_golpes_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Teclado_C3_Pin */
  GPIO_InitStruct.Pin = Teclado_C3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Teclado_C3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Teclado_C2_Pin */
  GPIO_InitStruct.Pin = Teclado_C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Teclado_C2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Teclado_C1_Pin */
  GPIO_InitStruct.Pin = Teclado_C1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Teclado_C1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Led_Verde_Pin Led_Naranja_Pin Led_Rojo_Pin Led_Azul_Pin */
  GPIO_InitStruct.Pin = Led_Verde_Pin|Led_Naranja_Pin|Led_Rojo_Pin|Led_Azul_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : Display_D7_Pin */
  GPIO_InitStruct.Pin = Display_D7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(Display_D7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Display_D6_Pin Display_D5_Pin Display_D4_Pin */
  GPIO_InitStruct.Pin = Display_D6_Pin|Display_D5_Pin|Display_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : Display_E_Pin Display_RS_Pin */
  GPIO_InitStruct.Pin = Display_E_Pin|Display_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
		while(flag == 0) {		}
	}
}

void display_escribir(int instancia){
	char linea1[16];
	char linea2[16];
	
	switch(instancia){
		case 0: sprintf(linea1,"0.INICIO");
						sprintf(linea2,"");
			break;
		case 1: sprintf(linea1,"1.OPERARIO");
						sprintf(linea2,"  ID TAG");
			break;
		case 2: sprintf(linea1,"2.TOTALES");
						sprintf(linea2,"");
			break;
		case 3: sprintf(linea1,"3.PRODUCTIVIDAD");
						sprintf(linea2,"");
			break;
		case 4: sprintf(linea1,"1.1.ROBERTO");
						sprintf(linea2,"123456789ABCDEF0");
			break;
		case 5: sprintf(linea1,"2.1.TOT GOLPES");
						sprintf(linea2,"125643");
			break;
		case 6: sprintf(linea1,"3.1.ROBERTO");
						sprintf(linea2,"     75%%");
			break;
		case 7: sprintf(linea1,"TRABAJO EN CURSO");
						sprintf(linea2,"GOLPES: 1564");
			break;
		case 8: sprintf(linea1,"TRABAJO EN CURSO");
						sprintf(linea2,"UNIDADES: 1532");
			break;
		case 9: sprintf(linea1,"AGREGAR OPERARIO");
						sprintf(linea2,"PASE TAG MAESTRO");
			break;
		case 10:sprintf(linea1,"AGREGAR OPERARIO");
						sprintf(linea2,"PASE TAG NUEVO");
			break;
		case 11:sprintf(linea1,"AGREGAR OPERARIO");
						sprintf(linea2,"NOMBRE: AAAAAAAA");
			break;
		case 12:sprintf(linea1,"AGREGAR OPERARIO");
						sprintf(linea2,"ERROR TAG EXISTE");
			break;
		case 13:sprintf(linea1,"AGREGAR OPERARIO");
						sprintf(linea2,"ERROR NO MAESTRO");
			break;
		}
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String(linea1);
	LCD_SetPos(0,1);
	LCD_String(linea2);
}

//------------ Seccion teclado --------------------
void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	if(GPIO_Pin==GPIO_PIN_7){
		HAL_GPIO_TogglePin(Led_Azul_GPIO_Port, Led_Azul_Pin);
		f_unidades=1;
		ms_ar=30;
	} else {
	fila=GPIO_Pin;
	f_boton_pres=1;
	}
}

void HAL_SYSTICK_Callback(void){
	if (f_boton_pres==1||f_unidades) ms_ar--;
}

void get_boton(void){
	
	if (HAL_GPIO_ReadPin(GPIOE,fila)==GPIO_PIN_SET){
		HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_RESET);
		if (HAL_GPIO_ReadPin(GPIOE,fila)==GPIO_PIN_SET){
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(GPIOE,fila)==GPIO_PIN_SET){
				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,GPIO_PIN_RESET);
				if (HAL_GPIO_ReadPin(GPIOE,fila)==GPIO_PIN_SET){
					col=4;
				}else col=3;
			}else col=2;
		}else col=1;
	} else col=0;
	
	char linea1[16];
	char linea2[16];
	
	switch (fila){
		case 0x0100:
			switch(col){
				case 1: sprintf(linea1,"1    ");
				break;
				case 2:	sprintf(linea1,"2    ");
				break;
				case 3: sprintf(linea1,"3    ");
				break;
				case 4: sprintf(linea1,"A    ");
				break;
			}
		break;	
		case 0x0200:
			switch(col){
				case 1: sprintf(linea1,"4    ");
				break;
				case 2:	sprintf(linea1,"5    ");
				break;
				case 3: sprintf(linea1,"6    ");
				break;
				case 4: sprintf(linea1,"B    ");
				break;
			}
		break;
		case 0x0400:
			switch(col){
				case 1: sprintf(linea1,"7    ");
				break;
				case 2:	sprintf(linea1,"8    ");
				break;
				case 3: sprintf(linea1,"9    ");
				break;
				case 4: sprintf(linea1,"C    ");
				break;
			}
		break;		
		case 0x0800:			
			switch(col){
				case 1: sprintf(linea1,"*    ");
				break;
				case 2:	sprintf(linea1,"0    ");
				break;
				case 3: sprintf(linea1,"#    ");
				break;
				case 4: sprintf(linea1,"D    ");
				break;
			}
		break;
	}
	col=0;
	
	sprintf(linea2,"                ");
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String(linea1);
	LCD_SetPos(0,1);
	LCD_String(linea2);
}

void display_tecla(void){
	
}

//-------------------------------------------------

void display_unidades(void){
	char linea1[16];
	char linea2[16];
	sprintf(linea1,"UNIDADES");
	sprintf(linea2,"%d",cont_unidades);
	
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String(linea1);
	LCD_SetPos(0,1);
	LCD_String(linea2);
}
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
