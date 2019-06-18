
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
#include "tm_stm32f4_mfrc522.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define Inicio 0
#define Menu_1 1
#define Menu_2 2
#define Menu_3 3
#define Menu_4 4
#define Menu_1x 5
#define Menu_21 6
#define Menu_22 7
#define Menu_3x 8
#define Menu_41 9
#define Menu_42 10
#define Menu_43 11
#define Menu_44 12
#define Menu_41c 13
#define Menu_42c 14
#define Menu_43c 15
#define Menu_441 16
#define Menu_442 17
#define Menu_443 18
#define Menu_44c 19
#define TrabajoEC_G 20 //Trabajo en curso - Golpes
#define TrabajoEC_U 21 //Trabajo en curso - Unidades
#define AgrOp_Maestro 22
#define AgrOp_Nuevo 23
#define AgrOp_Nombre 24
#define Err_TagExiste 25
#define Err_NMaestro 26

#define b_Arriba 1 
#define b_Abajo 9
#define b_Derecha 6
#define b_Izquierda 4
#define b_Enter 14
#define b_Salir 12
#define b_A 3
#define b_B 7 
#define b_C 11
#define b_D 15


//-----------------------
int ms_ar=30; //milisegundos anti-rebote
int tecla[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int boton=0;
int operario_activo=0;
int i;
uint8_t rxbuffer[16];
//-----------------------

struct Operario{
	int master;
	char nombre[9];
	char id[17];
	long golpes;
	long unidades;
	int productividad;
} operarios[20];

long cont_unidades=0;
long cont_golpes=0;
char str_golpes[17];
char str_unidades[17];
char str_productividad[17];
int f_unidades=0;
int flag=0;
int evento=0;

int f_boton=0; // flag boton presionado
int f_sensor=0;
int f_tarjeta=0;
int instancia=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_SPI1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void delayus_block(int n);
void display_escribir(char* linea1 ,char* linea2);
void display_unidades(void);
void introducir_nombre(void);

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
		
	LCD_ini();
	HAL_Delay(3);
	LCD_Clear();
	HAL_Delay(3);
	LCD_SetPos(0,0);
	HAL_Delay(3);
	LCD_CursorOff();
	HAL_Delay(3);	
	
	//TECLADO - Apago todo
	HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_RESET);
		
	display_escribir("INICIO DE","LA MAQUINA");
  instancia= Inicio;
	HAL_UART_Receive_IT(&huart6,rxbuffer,16);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  {
	
		//Encuesta teclado
		//Prendo la Columna 1, veo si se activó alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_SET);
		tecla[0]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[4]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[8]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[12]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_RESET);
		//Prendo la Columna 2, veo si se activó alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_SET);
		tecla[1]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[5]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[9]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[13]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_RESET);
		//Prendo la Columna 3, veo si se activó alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_SET);
		tecla[2]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[6]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[10]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[14]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_RESET);
		//Prendo la Columna 2, veo si se activó alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_SET);
		tecla[3]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[7]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[11]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[15]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_RESET);
		
		//Veo si alguna tecla fue presionada
		f_boton=0;
		i=0;
		while(!f_boton && i<16){
			f_boton=tecla[i];
			boton=i;
			i++;
		}
		
		if(f_boton){
			switch(boton){
				case b_Derecha:
					switch(instancia){
						case Inicio:
							instancia=Menu_1;
							display_escribir("1.OPERARIOS", "  ID TARJETA");
							break;
						
						case Menu_1:
							instancia=Menu_2;
							display_escribir("2.TOTALES", "");
							break;
					
						case Menu_2:
							instancia=Menu_3;
							display_escribir("3.PRODUCTIVIDAD", "");
							break;
					
						case Menu_3:
							instancia=Menu_4;
							display_escribir("4.CONFIGURACION", "");
							break;
					
						case Menu_4:
							instancia=Inicio;
							display_escribir("0.INICIO", "");
							break;
					
						case Menu_21:
							instancia=Menu_22;
							sprintf(str_unidades, "%ld", cont_unidades);
							display_escribir("2.1. TOT UNIDADES",str_unidades);
							break;
					
						case Menu_22:
							instancia=Menu_21;
							sprintf(str_golpes, "%ld", cont_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
						
						case Menu_41:
							instancia=Menu_42;
							display_escribir("4.2.RESET","    TOTALES");
							break;
					
						case Menu_42:
							instancia=Menu_43;
							display_escribir("4.3.RESET","    MASTER ID");
							break;
						
						case Menu_43:
							instancia=Menu_44;
							display_escribir("4.4.ALTA","    OPERARIO");
							break;
					
						case Menu_44:
							instancia=Menu_41;
							display_escribir("4.1.RESET","    OPERARIOS");
							break;
					}
					break; //Sale de switch(boton) 
									
				case b_Izquierda:
					switch(instancia){
						case Inicio:
							instancia=Menu_4;
							display_escribir("4.CONFIGURACION", "");
							break;
											
						case Menu_1:
							instancia=Inicio;
							display_escribir("0.INICIO", "");
							break;
					
						case Menu_2:
							instancia=Menu_1;
							display_escribir("1.OPERARIOS", "  ID TARJETA");
							break;
					
						case Menu_3:
							instancia=Menu_2;
							display_escribir("2.TOTALES", "");
							break;
					
						case Menu_4:
							instancia=Menu_3;
							display_escribir("3.PRODUCTIVIDAD", "");
							break;
						
						case Menu_21:
							instancia=Menu_22;
							sprintf(str_unidades, "%ld", cont_unidades);
							display_escribir("2.1. TOT UNIDADES",str_unidades);
							break;
					
						case Menu_22:
							instancia=Menu_21;
							sprintf(str_golpes, "%ld", cont_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
						
						case Menu_41:
							instancia=Menu_44;
							display_escribir("4.4.ALTA","    OPERARIO");
							break;
					
						case Menu_42:
							instancia=Menu_41;
							display_escribir("4.1.RESET","    OPERARIOS");
							break;
						
						case Menu_43:
							instancia=Menu_42;
							display_escribir("4.2.RESET","    TOTALES");
							break;
					
						case Menu_44:
							instancia=Menu_43;
							display_escribir("4.3.RESET","    MASTER ID");
							break;
					}
					break; //Sale de switch(boton)
					
				case b_Abajo:
					switch(instancia){
						case Inicio:
							break;
						
						case Menu_1:
							instancia=Menu_1x;
							display_escribir(operarios[0].nombre, operarios[0].id);
							break;
					
						case Menu_2:
							instancia=Menu_21;
							sprintf(str_golpes, "%ld", cont_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
					
						case Menu_3:
							instancia=Menu_3x;
							sprintf(str_productividad, "%d %%",operarios[0].productividad); 
							display_escribir(operarios[0].nombre, str_productividad);
							break;
						
						case Menu_4:
							instancia=Menu_41;
							display_escribir("4.1.RESET","    OPERARIOS");
							break;
												
					}
					break; //Sale de switch(boton)
				
				case b_Arriba:
					switch(instancia){
						case Menu_1x:
							instancia=Menu_1;
							display_escribir("1.OPERARIOS", "  ID TARJETA");
							break;
						
						case Menu_21:
							instancia=Menu_2;
							display_escribir("2.TOTALES", "");
							break;
					
						case Menu_22:
							instancia=Menu_2;
							display_escribir("2.TOTALES", "");
							break;
					
						case Menu_3x:
							instancia=Menu_3;
							display_escribir("3.PRODUCTIVIDAD", "");
							break;
						
						case Menu_41:
							instancia=Menu_4;
							display_escribir("4.CONFIGURACION", "");
							break;
						
						case Menu_42:
							instancia=Menu_4;
							display_escribir("4.CONFIGURACION", "");
							break;
						
						case Menu_43:
							instancia=Menu_4;
							display_escribir("4.CONFIGURACION", "");
							break;
						
						case Menu_44:
							instancia=Menu_4;
							display_escribir("4.CONFIGURACION", "");
							break;
							
					}		
					break; //Sale de switch(boton)
			
				case b_Enter:
					switch(instancia){
						case Inicio:
							break;
						
						case Menu_1:
							instancia=Menu_1x;
							display_escribir(operarios[0].nombre, operarios[0].id);
							break;
					
						case Menu_2:
							instancia=Menu_21;
							sprintf(str_golpes, "%ld", cont_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
					
						case Menu_3:
							instancia=Menu_3x;
							sprintf(str_productividad, "%d %%",operarios[0].productividad); 
							display_escribir(operarios[0].nombre, str_productividad);
							break;
						
						case Menu_4:
							instancia=Menu_41;
							display_escribir("4.1.RESET","    OPERARIOS");
							break;
						
						case Menu_41:
							instancia=Menu_41c;
							display_escribir("PARA CONFIRMAR", "PASE TAG MAESTRO");
							break;
						
						case Menu_42:
							instancia=Menu_42c;
							display_escribir("PARA CONFIRMAR", "PASE TAG MAESTRO");
							break;
						
						case Menu_43:
							instancia=Menu_43c;
							display_escribir("PARA CONFIRMAR", "PASE TAG MAESTRO");
							break;
						
						case Menu_44:
							instancia=Menu_441;
							display_escribir("AGREGAR OPERARIO", "PASE TAG MAESTRO");
							break;
						
						case Menu_443:
							instancia=Menu_44c;
							display_escribir("AGREGAR OPERARIO","  CORRECTO");
							break;					
					}
					break; //Sale de switch(boton)
					
				case b_Salir: //Acá tengo que reinicializar todos los flags que levante en el desarrollo
					instancia=Inicio;
					display_escribir("0.INICIO", "");
					break; //Sale de switch(boton)
							
			}  //switch(boton)
			
			//Prende las columnas para que las puedan detectar las filas.
			HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_SET);
			
		}	//rutina boton
				
		if(f_sensor){
			if(f_unidades){
				HAL_GPIO_TogglePin(Led_Verde_GPIO_Port, Led_Verde_Pin);
				cont_unidades++;
				sprintf(str_unidades, "%ld", cont_unidades);
				display_escribir("ACTUAL: UNIDADES",str_unidades);
				if(operario_activo){
					operarios[operario_activo].unidades++;
				}
			}else{
				HAL_GPIO_TogglePin(Led_Azul_GPIO_Port, Led_Azul_Pin);
				cont_golpes++;
				sprintf(str_golpes, "%ld", cont_golpes);
				display_escribir("ACTUAL: GOLPES",str_golpes);
				if(operario_activo){
					operarios[operario_activo].golpes++;
				}
			}
			f_sensor=0;
		}
			
		if(f_tarjeta){
			HAL_GPIO_TogglePin(Led_Rojo_GPIO_Port, Led_Rojo_Pin);
		}
		
		
		/* Esto son los antirrebotes, lo tengo que analizar a lo ultimo
		//-------	Seccion teclado -----------
		if(!ms_ar&&f_boton_pres){
			if(f_boton_pres){
				if(!(ms_ar)&&f_boton_pres){
					f_boton_pres=0;
					get_boton();
					if(!col) display_tecla();
					HAL_GPIO_WritePin(GPIOE,0x0F00,GPIO_PIN_SET);
				}
			}
		}	
		//---------------------------------------
		//		if(!ms_ar&&f_unidades){
		if(f_unidades){
		if(!(ms_ar)&&f_unidades){
			f_unidades=0;
			cont_unidades++;
			display_unidades();
		}
		*/
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	
  } // End while(1)
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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

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
  htim4.Init.Period = 16;
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
  HAL_GPIO_WritePin(GPIOA, Teclado_C4_Pin|RFID_SDA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Teclado_C3_Pin|Display_D7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Teclado_C2_Pin|Display_E_Pin|Display_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, Led_Verde_Pin|Led_Naranja_Pin|Led_Rojo_Pin|Led_Azul_Pin 
                          |Display_D6_Pin|Display_D5_Pin|Display_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Sensor_unidades_Pin */
  GPIO_InitStruct.Pin = Sensor_unidades_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Sensor_unidades_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Teclado_C4_Pin RFID_SDA_Pin */
  GPIO_InitStruct.Pin = Teclado_C4_Pin|RFID_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

  /*Configure GPIO pins : Teclado_F4_Pin Teclado_F3_Pin Teclado_F2_Pin Teclado_F1_Pin */
  GPIO_InitStruct.Pin = Teclado_F4_Pin|Teclado_F3_Pin|Teclado_F2_Pin|Teclado_F1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

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

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Stop_IT(&htim4);
	flag=1;
}

void delayus_block(int n){
	if (n) {
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

void display_escribir(char* linea1, char* linea2){
	int i;
	char l1[17];
	char l2[17];

	//Inicialización de l1 y l2. Acá lleno 16 caracteres de espacios.
	for (i = 0; i < 16; i++) {
		sprintf(&l1[i], " ");
		sprintf(&l2[i], " ");
	}
	//Relleno de l1. Acá lleno l1 con los caracteres que haya escrito como primer parámetro y dejo el resto como estaba (espacios).
	i = 0;
	while(linea1[i]){						//Acá pregunto: "Si el caracter i de linea1 es un caracter..." En lugar de un End Of String.
			l1[i] = linea1[i];
			i++;
		}
	//Relleno de l2. Acá lleno l2 con los caracteres que haya escrito como segundo parámetro y dejo el resto como estaba (espacios).
	i = 0;
	while (linea2[i]) {						//Acá pregunto: "Si el caracter i de linea2 es un caracter..." En lugar de un End Of String.
			l2[i] = linea2[i];
			i++;
		}
	
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String(l1);
	LCD_SetPos(0,1);
	LCD_String(l2);

}


void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	HAL_GPIO_TogglePin(Led_Naranja_GPIO_Port, Led_Naranja_Pin);
	if(GPIO_Pin==Sensor_golpes_Pin){
		f_sensor=1;
		f_unidades=0;
	
	}else if(GPIO_Pin==Sensor_unidades_Pin){
		f_sensor=1;
		f_unidades=1;
		
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	f_tarjeta=1;
}

void HAL_SYSTICK_Callback(void){
	//if (f_boton==1||f_unidades) ms_ar--; 
}

void rfid_init(void){
	HAL_GPIO_WritePin(RFID_SDA_GPIO_Port, RFID_SDA_Pin,GPIO_PIN_SET);
	
}

void rfid_sub_WriteRegister(uint8_t address, uint8_t value){
	//CS low
	HAL_GPIO_WritePin(RFID_SDA_GPIO_Port, RFID_SDA_Pin,GPIO_PIN_RESET);
	//Send address
	HAL_SPI_Transmit(&hspi1,&
	TM_SPI_Send(MFRC522_SPI, (addr << 1) & 0x7E);
	//Send data	
	TM_SPI_Send(MFRC522_SPI, val);
	//CS high
	MFRC522_CS_HIGH;
}
void introducir_texto(void){
	char nombre[9];
	int i = 0;
	for (i = 0; i < 8; i++) {
		sprintf(&nombre[i], "A");
	}
	int boton=0;
	i = 0;
	display_escribir("AGREGAR OPERARIO", "NOMBRE: AAAAAAAA");
	LCD_CursorOn();
	LCD_SetPos(8+i,1); //Porqe el "AAAAAAAA" arranca en la columna 9 (0-index) y la fila 2 (0-index)
	while (boton != b_Enter)
		{
				while(!f_boton) {};
				f_boton=0;
				switch (boton)
				{
				case b_Arriba:
					if (nombre[i] >= 65 && nombre[i] < 90) nombre[i]++;
					else if (nombre[i] == 32) nombre[i] = 65;
					else nombre[i] = 32;
					LCD_SendChar(nombre[i]);
					break;

				case b_Abajo:
					if (nombre[i] > 65 && nombre[i] <= 90) nombre[i]--;
					else if (nombre[i] == 32) nombre[i] = 90;
					else nombre[i] = 32;
					LCD_SendChar(nombre[i]);
					break;

				case b_Izquierda:
					if (i) i--;
					else i = 7;
					LCD_SetPos(8+i,1);
					break;

				case b_Derecha:
					if (i!=7) i++;
					else i = 0;
					LCD_SetPos(8+i,1);
					break;
				}
		}
}

//-------------------------------------------------

void display_unidades(void){
	char linea1[16];
	char linea2[16];
	sprintf(str_unidades, "%ld", cont_unidades);
	display_escribir("2.1. TOT UNIDADES",str_unidades);
							
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
