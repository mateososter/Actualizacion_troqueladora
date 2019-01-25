#include "lcd_txt.h"
#include "main.h"
#include "stm32f4xx_hal.h"

//---------------------------------------------------------------
void display_d(int n, int s_r){ //n es el numero de D y s_r es set(1) o reset(0)
	uint16_t pin;
	GPIO_PinState state;
	
	switch(n){
		case 4: pin = GPIO_PIN_4;
			break;
		case 5: pin = GPIO_PIN_5;
			break;
		case 6: pin = GPIO_PIN_6;
			break;
		case 7: pin = GPIO_PIN_7;
			break;
	}
	
	switch(s_r){
		case 0: state = GPIO_PIN_RESET;
			break;
		case 1: state = GPIO_PIN_SET;
			break;
	}
	
	HAL_GPIO_WritePin(GPIOD, pin, state);
	
}
//---------------------------------------------------------------
void display_rs(int s_r){				//s_r es set(1) o reset(0)
	GPIO_PinState state;
	
	switch(s_r){
		case 0: state = GPIO_PIN_RESET;
			break;
		case 1: state = GPIO_PIN_SET;
			break;
	}
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, state);
	
}
//---------------------------------------------------------------
void display_e(int s_r){				//s_r es set(1) o reset(0)
	GPIO_PinState state;
	
	switch(s_r){
		case 0: state = GPIO_PIN_RESET;
			break;
		case 1: state = GPIO_PIN_SET;
			break;
	}
	
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, state);
	
}
//---------------------------------------------------------------
void LCD_WriteData(uint8_t dt)

{
        if(((dt >> 3)&0x01)==1) {display_d(7,1);} else {display_d(7,0);}
				if(((dt >> 2)&0x01)==1) {display_d(6,1);} else {display_d(6,0);}
				if(((dt >> 1)&0x01)==1) {display_d(5,1);} else {display_d(5,0);}
				if(((dt >> 0)&0x01)==1) {display_d(4,1);} else {display_d(4,0);}
}

//---------------------------------------------------------------


void LCD_Command(uint8_t dt)

{
        display_rs(0);
        display_e(1);	
				LCD_WriteData(dt>>4);
        delayus_block(1);
        display_e(0);	
				display_e(1);	
				LCD_WriteData(dt);
        delayus_block(1);
        display_e(0);	
}
//---------------------------------------------------------------

 
void LCD_ini(void)

{
        HAL_Delay(40);
        display_rs(0);
				display_e(1);	
				LCD_WriteData(0x3);
//      delayus_block(1);
        delayus_block(100);
        display_e(0);
        HAL_Delay(5);
        display_e(1);
				LCD_WriteData(0x3);
        delayus_block(100);
        display_e(0);
        HAL_Delay(5);
				delayus_block(100);   
        display_e(1);	
				LCD_WriteData(0x3);
        delayus_block(1);
        display_e(0);
        HAL_Delay(5);
        LCD_Command(0x28);
        HAL_Delay(1);
        LCD_Command(0x28);
        HAL_Delay(1);
        LCD_Command(0x0F);
        HAL_Delay(1);
        LCD_Command(0x01);
        HAL_Delay(2);
        LCD_Command(0x06);
        HAL_Delay(1);
        LCD_Command(0x02);
        HAL_Delay(2);
}
//////////////////////////////////////////////////////////////////////////
void LCD_Data(uint8_t dt)

{
        display_rs(1);	
        LCD_WriteData(dt>>4);
        display_e(1);
        HAL_Delay(1);
        display_e(0);
        LCD_WriteData(dt);
        display_e(1);
        HAL_Delay(1);
        display_e(0);
}
//////////////////////////////////////////////////////////////////////////
void LCD_String(char* st)

{
        uint8_t i=0;
        while(st[i]!=0)
        {
                LCD_Data(st[i]);
                HAL_Delay(1);
                i++;
        }
}


/////////////////////////////////////////////////////////////////////////
void LCD_Clear(void)

{
        LCD_Command(0x01);
        HAL_Delay(2);
}


///////////////////////////////////////////////////////////////////////////
void LCD_SendChar(char ch)

{
        LCD_Data((uint8_t) ch);
        HAL_Delay(2); //le puse yo los 2 ms, capaz se queda corto
}

 //////////////////////////////////////////////////////////////////////////


void LCD_SetPos(uint8_t x, uint8_t y) //x columna , y fila

{

        switch(y)
        {
                case 0:
                        LCD_Command(x|0x80);
                        HAL_Delay(1);
                        break;
                case 1:
                        LCD_Command((0x40+x)|0x80);
                        HAL_Delay(1);
                        break;
                case 2:
                        LCD_Command((0x14+x)|0x80);
                        HAL_Delay(1);
                        break;
                case 3:
                        LCD_Command((0x54+x)|0x80);
                        HAL_Delay(1);
                        break;
        }
}
 //////////////////////////////////////////////////////////////////////////

void LCD_CursorOff(void){
	LCD_Command(0x0C);
  HAL_Delay(2);
}
