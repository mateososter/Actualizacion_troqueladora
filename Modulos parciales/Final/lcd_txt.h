#ifndef __LCD_H__
#define __LCD_H__


#include "stm32f4xx_hal.h"

/* Los pines seteados son:
D4	PD4
D5	PD5
D6	PD6
D7	PD7
RS	PD8
E		PD9
*/

//#define d4_set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
//#define d5_set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_SET);
//#define d6_set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET);
//#define d7_set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

//#define d4_reset() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
//#define d5_reset() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, GPIO_PIN_RESET);
//#define d6_reset() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET);
//#define d7_reset() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

//#define e1    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET) 
//#define e0    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET) 
//#define rs1   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET) 
//#define rs0   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET)

void display_d(int n, int s_r); //n es el numero de D y s_r es set(1) o reset(0)
void display_rs(int s_r);				//s_r es set(1) o reset(0)
void display_e(int s_r);				//s_r es set(1) o reset(0)
void LCD_ini(void);
void delayus_block(int n);
void LCD_SendChar(char ch);
void LCD_Clear(void);
void LCD_String(char* st);
void LCD_SetPos(uint8_t x, uint8_t y);
void LCD_CursorOff(void);
void LCD_CursorOn(void);
	
#endif /* __LCD_H__ */
