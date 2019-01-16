/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define Sensor_unidades_Pin GPIO_PIN_6
#define Sensor_unidades_GPIO_Port GPIOE
#define Sensor_unidades_EXTI_IRQn EXTI9_5_IRQn
#define Teclado_C4_Pin GPIO_PIN_1
#define Teclado_C4_GPIO_Port GPIOA
#define Sensor_golpes_Pin GPIO_PIN_4
#define Sensor_golpes_GPIO_Port GPIOC
#define Sensor_golpes_EXTI_IRQn EXTI4_IRQn
#define Teclado_C3_Pin GPIO_PIN_5
#define Teclado_C3_GPIO_Port GPIOC
#define Teclado_C2_Pin GPIO_PIN_1
#define Teclado_C2_GPIO_Port GPIOB
#define Teclado_C1_Pin GPIO_PIN_7
#define Teclado_C1_GPIO_Port GPIOE
#define Teclado_F4_Pin GPIO_PIN_9
#define Teclado_F4_GPIO_Port GPIOE
#define Teclado_F4_EXTI_IRQn EXTI9_5_IRQn
#define Teclado_F3_Pin GPIO_PIN_11
#define Teclado_F3_GPIO_Port GPIOE
#define Teclado_F3_EXTI_IRQn EXTI15_10_IRQn
#define Teclado_F2_Pin GPIO_PIN_13
#define Teclado_F2_GPIO_Port GPIOE
#define Teclado_F2_EXTI_IRQn EXTI15_10_IRQn
#define Teclado_F1_Pin GPIO_PIN_15
#define Teclado_F1_GPIO_Port GPIOE
#define Teclado_F1_EXTI_IRQn EXTI15_10_IRQn
#define Led_Verde_Pin GPIO_PIN_12
#define Led_Verde_GPIO_Port GPIOD
#define Led_Naranja_Pin GPIO_PIN_13
#define Led_Naranja_GPIO_Port GPIOD
#define Led_Rojo_Pin GPIO_PIN_14
#define Led_Rojo_GPIO_Port GPIOD
#define Led_Azul_Pin GPIO_PIN_15
#define Led_Azul_GPIO_Port GPIOD
#define Rx_LectorRFID_Pin GPIO_PIN_6
#define Rx_LectorRFID_GPIO_Port GPIOC
#define Tx_LectorRFID_Pin GPIO_PIN_7
#define Tx_LectorRFID_GPIO_Port GPIOC
#define Display_D7_Pin GPIO_PIN_11
#define Display_D7_GPIO_Port GPIOC
#define Display_D6_Pin GPIO_PIN_0
#define Display_D6_GPIO_Port GPIOD
#define Display_D5_Pin GPIO_PIN_2
#define Display_D5_GPIO_Port GPIOD
#define Display_D4_Pin GPIO_PIN_6
#define Display_D4_GPIO_Port GPIOD
#define Display_E_Pin GPIO_PIN_5
#define Display_E_GPIO_Port GPIOB
#define Display_RS_Pin GPIO_PIN_7
#define Display_RS_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
