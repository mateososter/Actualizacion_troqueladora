#include "lcd_txt.h"
#include "main.h"
#include "stm32f4xx_hal.h"

//---------------------------------------------------------------
//EN ESTA FUNCION PUEDO PROGRAMAR EN QUÉ GPIO VAN A ESTAR CONECTADOS LOS DATA BITS
//SOLO PARA FUNCION 4 BITS

void display_d(int n, int s_r){ //n es el numero de D y s_r es set(1) o reset(0)
	uint16_t pin;
	uint32_t port;
	GPIO_PinState state;
	
	
	switch(n){
		case 4: 
			pin = GPIO_PIN_6;
			port = GPIOD_BASE;
			break;
		case 5: 
			pin = GPIO_PIN_2;
			port = GPIOD_BASE;
			break;
		case 6: 
			pin = GPIO_PIN_0;
			port = GPIOD_BASE;
			break;
		case 7: 
			pin = GPIO_PIN_11;
			port = GPIOC_BASE;
			break;
	}
	
	switch(s_r){
		case 0: state = GPIO_PIN_RESET;
			break;
		case 1: state = GPIO_PIN_SET;
			break;
	}
	
	HAL_GPIO_WritePin(((GPIO_TypeDef *) port), pin, state);
	
}
//---------------------------------------------------------------
//EN ESTA FUNCION PUEDO PROGRAMAR EN QUÉ GPIO VA A ESTAR CONECTADO EL PIN RS

void display_rs(int s_r){				//s_r es set(1) o reset(0)
	GPIO_PinState state;
	
	switch(s_r){
		case 0: state = GPIO_PIN_RESET;
			break;
		case 1: state = GPIO_PIN_SET;
			break;
	}
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, state);
	
}
//---------------------------------------------------------------
//EN ESTA FUNCION PUEDO PROGRAMAR EN QUÉ GPIO VA A ESTAR CONECTADO EL PIN E (enable)

void display_e(int s_r){				//s_r es set(1) o reset(0)
	GPIO_PinState state;
	
	switch(s_r){
		case 0: state = GPIO_PIN_RESET;
			break;
		case 1: state = GPIO_PIN_SET;
			break;
	}
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state);
	
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
        delayus_block(10);
        display_e(0);	
				delayus_block(10);
				display_e(1);	
				LCD_WriteData(dt);
        delayus_block(10);
        display_e(0);	
}
//---------------------------------------------------------------

 
void LCD_ini(void)

{
        HAL_Delay(40); //More than 40ms
        display_rs(0);
				
				display_e(1);
				LCD_WriteData(0x03);
        delayus_block(10);
        display_e(0);
        
				delayus_block(4500); //More than 4.1ms
        
				display_e(1);
				LCD_WriteData(0x03);
        delayus_block(10);
        display_e(0);
        
				delayus_block(150); //More than 100us
        
				display_e(1);	
				LCD_WriteData(0x03);
        delayus_block(10);
        display_e(0);
        
				delayus_block(150);
				
				display_e(1);
				LCD_WriteData(0x02);
        delayus_block(10);
        display_e(0);
				
				delayus_block(150);
				//HAL_Delay(1);
				
				LCD_Command(0x28);
				
				LCD_Command(0x08);
				
				LCD_Command(0x01);
				
				LCD_Command(0x06);
				
				LCD_Command(0x0C);
				
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

void LCD_CursorOn(void){
	LCD_Command(0x0F);
  HAL_Delay(2);
}
