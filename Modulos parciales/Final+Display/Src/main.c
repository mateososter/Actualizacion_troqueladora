
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
  * COPYRIGHT(c) 2020 STMicroelectronics
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
#include "rc522.h"
#include "MY_FLASH.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

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
#define Menu_3x1 32
#define Menu_41 9
#define Menu_411 28
#define Menu_412 29
#define Menu_42 10
#define Menu_43 11
#define Menu_431 30
#define Menu_432 31
#define Menu_44 12
#define Menu_421 14
#define Menu_422 27
#define Menu_441 16
#define Menu_442 17
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
int operario_activo=20;
int operario_chequeado=0;
int operario_a_borrar=1;
int operario_a_master=1;
int i;
int state;
uint8_t leido;
uint8_t rxbuffer[16];
uint8_t txbuffer[16];
uint8_t CardID[5];
uint8_t MasterID[5] = {0,0,0,0,0};
uint8_t str_cont_unidades[4]={4,3,2,1};
uint8_t str_cont_decenas[5]={5,4,3,2,1};
uint8_t str_cont_centenas[6]={5,4,3,2,1};
char leer[32];
char escribir[640];
//-----------------------

struct Operario{
	short condicion; 		//Si condici�n==0, el operario NO est� cargado.
											//Si condici�n==1, el operario SI est� cargado pero NO es master.
											//Si condici�n==2, el operario SI est� cargado y SI es master.
	char nombre[9];
	char id[5];
	int golpes;
	int unidades;
	short productividad;
} operarios[20];


long cont_unidades=0;
long cont_golpes=0;
char str_golpes[17];
char str_unidades[17];
long total_golpes=0;
long total_unidades=0;
char id_display[11];
char str_productividad[17];
int f_unidades=1;
int f_confirmacion=0;
int flag=0;
int evento=0;

int f_boton=0; // flag boton presionado
int f_sensor=0;
int f_tarjeta=0;
int f_desc=0;
int f_desc_rs=0;
int instancia=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM3_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void delayus_block(int n);
void encuesta_teclado(void);
void display_escribir(char* linea1 ,char* linea2);
void display_unidades(void);
void displayu_clear(void);
void displayu_escribir(void);
void introducir_texto(void);
void conv_hex(void);
void flash_guardar_operarios(void);
void flash_guardar_actual(int operario);
void flash_cargar_operarios(void);

uint8_t MFRC522_Check(uint8_t* id);
uint8_t MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID);
void MFRC522_WriteRegister(uint8_t addr, uint8_t val);
uint8_t MFRC522_ReadRegister(uint8_t addr);
void MFRC522_SetBitMask(uint8_t reg, uint8_t mask);
void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask);
uint8_t MFRC522_Request(uint8_t reqMode, uint8_t* TagType);
uint8_t MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen);
uint8_t MFRC522_Anticoll(uint8_t* serNum);
void MFRC522_CalulateCRC(uint8_t* pIndata, uint8_t len, uint8_t* pOutData);
uint8_t MFRC522_SelectTag(uint8_t* serNum);
uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum);
uint8_t MFRC522_Read(uint8_t blockAddr, uint8_t* recvData);
uint8_t MFRC522_Write(uint8_t blockAddr, uint8_t* writeData);
void MFRC522_Init(void);
void MFRC522_Reset(void);
void MFRC522_AntennaOn(void);
void MFRC522_AntennaOff(void);
void MFRC522_Halt(void);

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
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	
	
	LCD_ini();
	HAL_Delay(3);
	LCD_Clear();
	HAL_Delay(3);
	LCD_SetPos(0,0);
	HAL_Delay(3);
	LCD_CursorOff();
	HAL_Delay(3);	
	
	MFRC522_Init();
	
	//TECLADO - Apago todo
	HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_RESET);
		
	//Carga de operarios de tarjetas
	
//	Secuencia de borrado que fue necesaria para inicializar la parte que voy a usar de la flash.	
//	uint8_t borrar[640];
//	for(int l=0;l<640;l++){
//		borrar[l]=0;
//	}
//	MY_FLASH_WriteN(640,borrar,32,DATA_TYPE_8);
	flash_cargar_operarios();
	
//	sprintf(operarios[1].nombre,"LIDER");
//	
//	operarios[1].id[0] = 0xD4;
//	operarios[1].id[1] = 0x8E;
//	operarios[1].id[2] = 0x70;
//	operarios[1].id[3] = 0x1F;
//	operarios[1].id[4] = 0x35;
//	operarios[1].condicion = 1;

//	sprintf(operarios[0].nombre,"JULI");
//	
//	operarios[0].id[0] = 0x49;
//	operarios[0].id[1] = 0x23;
//	operarios[0].id[2] = 0x2F;
//	operarios[0].id[3] = 0x63;
//	operarios[0].id[4] = 0x26;
//	operarios[0].condicion = 2;
	
	//flash_guardar_operarios();
	//operarios[2].condicion = 0; // NO OLVIDAR QUITAR ESTA LINEA DE PRUEBA
	displayu_clear();
	display_escribir("INICIO DE","LA MAQUINA");
  instancia= Inicio;
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)  {
	
		//Descuenta una unidad si se pulsó el botón.
		if(f_desc && f_desc_rs){
			f_desc=0;
			f_desc_rs=0;
			cont_unidades--;
			operarios[operario_activo].unidades--;
			sprintf(str_unidades, "%ld", cont_unidades);
			display_escribir("ACTUAL: UNIDADES",str_unidades);
			//Hasta acá es display LCD. Ahora empieza el display de unidades.
			displayu_escribir();
		}
		
		//Encuesta teclado
		encuesta_teclado();
		
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
					
						case Menu_1x:
							do{
								if(operario_chequeado==19){
									operario_chequeado=0;
								} else {
									operario_chequeado++;
								}
							} while(!operarios[operario_chequeado].condicion);
							conv_hex();
							display_escribir(operarios[operario_chequeado].nombre, id_display);
							break;
						
						case Menu_21:
							instancia=Menu_22;
							total_unidades=0;
							for (int i=0;i<20;i++){
								if(operarios[i].condicion){
									total_unidades+=operarios[i].unidades;
								}
							}
							sprintf(str_unidades, "%ld", total_unidades);
							display_escribir("2.2.TOT UNIDADES",str_unidades);
							break;
					
						case Menu_22:
							instancia=Menu_21;
							total_golpes=0;
							for (int i=0;i<20;i++){
								if(operarios[i].condicion){
									total_golpes+=operarios[i].golpes;
								}
							}
							sprintf(str_golpes, "%ld", total_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
						
						case Menu_3x:
							do{
								if(operario_chequeado==19){
									operario_chequeado=0;
								} else {
									operario_chequeado++;
								}
							} while(!operarios[operario_chequeado].condicion);
							sprintf(str_productividad, "%d %%", operarios[operario_chequeado].productividad);
							display_escribir(operarios[operario_chequeado].nombre, str_productividad);
							break;
							
						case Menu_41:
							instancia=Menu_42;
							display_escribir("4.2.RESET","    TOTALES");
							break;
					
						case Menu_42:
							instancia=Menu_43;
							display_escribir("4.3.ALTA","    TAG MAESTRO");
							break;
						
						case Menu_43:
							instancia=Menu_44;
							display_escribir("4.4.ALTA","    OPERARIO");
							break;
					
						case Menu_44:
							instancia=Menu_41;
							display_escribir("4.1.BORRAR","    OPERARIO");
							break;
						
						case Menu_411:
							do{
								if(operario_chequeado==19){
									operario_chequeado=1;
								} else {
									operario_chequeado++;
								}
							} while(!operarios[operario_chequeado].condicion);
							display_escribir("BORRAR OPERARIO", operarios[operario_chequeado].nombre);
							break;
							
						case Menu_431:
							do{
								if(operario_chequeado==19){
									operario_chequeado=1;
								} else {
									operario_chequeado++;
								}
							} while(!operarios[operario_chequeado].condicion);
							display_escribir("ALTA MAESTRO", operarios[operario_chequeado].nombre);
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
						
						case Menu_1x:
							do{
								if(!operario_chequeado){
									operario_chequeado=19;
								} else {
									operario_chequeado--;
								}
							} while(!operarios[operario_chequeado].condicion);
							conv_hex();
							display_escribir(operarios[operario_chequeado].nombre, id_display);
							break;
							
						case Menu_21:
							instancia=Menu_22;
							total_unidades=0;
							for (int i=0;i<20;i++){
								if(operarios[i].condicion){
									total_unidades+=operarios[i].unidades;
								}
							}
							sprintf(str_unidades, "%ld", total_unidades);
							display_escribir("2.2.TOT UNIDADES",str_unidades);
							break;
					
						case Menu_22:
							instancia=Menu_21;
							total_golpes=0;
							for (int i=0;i<20;i++){
								if(operarios[i].condicion){
									total_golpes+=operarios[i].golpes;
								}
							}
							sprintf(str_golpes, "%ld", total_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
						
						case Menu_3x:
							do{
								if(!operario_chequeado){
									operario_chequeado=19;
								} else {
									operario_chequeado--;
								}
							} while(!operarios[operario_chequeado].condicion);
							sprintf(str_productividad, "%d %%", operarios[operario_chequeado].productividad);
							display_escribir(operarios[operario_chequeado].nombre, str_productividad);
							break;
							
						case Menu_41:
							instancia=Menu_44;
							display_escribir("4.4.ALTA","    OPERARIO");
							break;
					
						case Menu_42:
							instancia=Menu_41;
							display_escribir("4.1.BORRAR","    OPERARIO");
							break;
						
						case Menu_43:
							instancia=Menu_42;
							display_escribir("4.2.RESET","    TOTALES");
							break;
					
						case Menu_44:
							instancia=Menu_43;
							display_escribir("4.3.ALTA","    TAG MAESTRO");
							break;
						
						case Menu_411:
							do{
								if(operario_chequeado==1){
									operario_chequeado=19;
								} else {
									operario_chequeado--;
								}
							} while(!operarios[operario_chequeado].condicion);
							display_escribir("BORRAR OPERARIO", operarios[operario_chequeado].nombre);
							break;
							
						case Menu_431:
							do{
								if(operario_chequeado==1){
									operario_chequeado=19;
								} else {
									operario_chequeado--;
								}
							} while(!operarios[operario_chequeado].condicion);
							display_escribir("ALTA MAESTRO", operarios[operario_chequeado].nombre);
							break;
					}
					break; //Sale de switch(boton)
					
				case b_Abajo:
					switch(instancia){
						case Inicio:
							break;
						
						case Menu_1:
							instancia=Menu_1x;
							operario_chequeado=0;
							conv_hex();
							display_escribir(operarios[operario_chequeado].nombre, id_display);
							break;
					
						case Menu_2:
							instancia=Menu_21;
							total_golpes=0;
							for (int i=0;i<20;i++){
								if(operarios[i].condicion){
									total_golpes+=operarios[i].golpes;
								}
							}
							sprintf(str_golpes, "%ld", total_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
					
						case Menu_3:
							instancia=Menu_3x;
							sprintf(str_productividad, "%d %%",operarios[0].productividad); 
							display_escribir(operarios[0].nombre, str_productividad);
							break;
						
						case Menu_3x:
							instancia=Menu_3x1;
							sprintf(str_unidades, "%ld", operarios[operario_chequeado].unidades);
							display_escribir("UNIDADES",str_unidades);
							break;
						
						case Menu_4:
							instancia=Menu_41;
							display_escribir("4.1.BORRAR","    OPERARIO");
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
						
						case Menu_3x1:
							instancia=Menu_3x;
							sprintf(str_productividad, "%d %%",operarios[0].productividad); 
							display_escribir(operarios[0].nombre, str_productividad);
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
							operario_chequeado=0;
							conv_hex();
							display_escribir(operarios[operario_chequeado].nombre, id_display);
							break;
					
						case Menu_2:
							instancia=Menu_21;
							total_golpes=0;
							for (int i=0;i<20;i++){
								if(operarios[i].condicion){
									total_golpes+=operarios[i].golpes;
								}
							}
							sprintf(str_golpes, "%ld", total_golpes);
							display_escribir("2.1. TOT GOLPES",str_golpes);
							break;
					
						case Menu_3:
							instancia=Menu_3x;
							sprintf(str_productividad, "%d %%",operarios[0].productividad); 
							display_escribir(operarios[0].nombre, str_productividad);
							break;
						
						case Menu_3x:
							instancia=Menu_3x1;
							sprintf(str_unidades, "%ld", operarios[operario_chequeado].unidades);
							display_escribir("UNIDADES",str_unidades);
							break;
						
						case Menu_4:
							instancia=Menu_41;
							display_escribir("4.1.BORRAR","    OPERARIO");
							break;
						
						case Menu_41:
							instancia=Menu_411;
							operario_chequeado=1;
							display_escribir("BORRAR OPERARIO", operarios[operario_chequeado].nombre);
							break;
						
						case Menu_411:
							instancia=Menu_412;
							operario_a_borrar=operario_chequeado;
							display_escribir("PARA CONFIRMAR", "PASE TAG MAESTRO");
							break;
						
						case Menu_42:
							instancia=Menu_421;
							display_escribir("PARA CONFIRMAR", "PASE TAG MAESTRO");
							break;
						
						case Menu_43:
							instancia=Menu_431;
							operario_chequeado=1;
							display_escribir("ALTA MAESTRO", operarios[operario_chequeado].nombre);
							break;
						
						case Menu_431:
							instancia=Menu_432;
							operario_a_master=operario_chequeado;
							display_escribir("PARA CONFIRMAR", "PASE TAG MAESTRO");
							break;
						
						case Menu_44:
							instancia=Menu_441;
							display_escribir("AGREGAR OPERARIO", "PASE TAG MAESTRO");
							break;
										
					}
					break; //Sale de switch(boton)
					
				/*//Boton para prueba de display externo
				case b_A: 
					display_escribir("Probando", "");
					HAL_UART_Transmit(&huart2,str_cont_unidades,4,15);
					str_cont_unidades[3]++;
					break; //Sale de switch(boton)
				*/
					
				case b_Salir: //Ac� tengo que reinicializar todos los flags que levante en el desarrollo
					instancia=Inicio;
					display_escribir("0.INICIO", "");
					break; //Sale de switch(boton)
							
			}  //switch(boton)
			
		}	//rutina boton
				
		if(f_sensor){//RESETEAR EL CONTADOR CUANDO CAMBIA DE OPERARIO.
			if(operario_activo!=20){
				if(f_unidades){
					cont_unidades++;
					operarios[operario_activo].unidades++;
					sprintf(str_unidades, "%ld", cont_unidades);
					display_escribir("ACTUAL: UNIDADES",str_unidades);
					//Hasta acá es display LCD. Ahora empieza el display de unidades.
					displayu_escribir();
					f_desc_rs=1;
					f_desc=0;
					
				}else{
					cont_golpes++;
					operarios[operario_activo].golpes++;
					sprintf(str_golpes, "%ld", cont_golpes);
					display_escribir("ACTUAL: GOLPES",str_golpes);
				}
				if(operarios[operario_activo].golpes){
				operarios[operario_activo].productividad=100*operarios[operario_activo].unidades/operarios[operario_activo].golpes;	
				}
			}
			f_sensor=0;
		}
			
		if(MFRC522_Check(CardID) == MI_OK){
			//Si se acerca una tarjeta puede ser para... Iniciar un trabajo, o bien, dar de alta una tarjeta.
			switch(instancia){
				case Menu_441:
					for(int n=0;n<20;n++){
						if(MFRC522_Compare(CardID,operarios[n].id)== MI_OK){
							operario_chequeado=n;
						}
					}
					if(operarios[operario_chequeado].condicion==2){
						instancia=Menu_442;
						for(int k=0;k<5;k++){
							MasterID[k]=CardID[k];
						}
						display_escribir("AGREGAR OPERARIO", "PASE TAG NUEVO");
					} else {
						instancia=Inicio;
						display_escribir("AGREGAR OPERARIO", "ERR TAG MAESTRO");
					}
					break;
					
				case Menu_412:
					for(int n=0;n<20;n++){
						if(MFRC522_Compare(CardID,operarios[n].id)== MI_OK){
							operario_chequeado=n;
						}
					}
					if(operarios[operario_chequeado].condicion==2){
						instancia=Inicio;
						operarios[operario_a_borrar].condicion=0;
						flash_guardar_operarios();
						display_escribir("BORRAR OPERARIO","CORRECTO");
					} else {
						instancia=Inicio;
						display_escribir("BORRAR OPERARIO", "ERR TAG MAESTRO");
					}
					break;
					
				case Menu_421:
					for(int n=0;n<20;n++){
						if(MFRC522_Compare(CardID,operarios[n].id)== MI_OK){
							operario_chequeado=n;
						}
					}
					if(operarios[operario_chequeado].condicion==2){
						instancia=Inicio;
						for(int n=0;n<20;n++){
							operarios[n].golpes=0;
							operarios[n].unidades=0;
							operarios[n].productividad=0;
						}
						flash_guardar_operarios();
						display_escribir("RESET TOTALES","CORRECTO");
					} else {
						instancia=Inicio;
						display_escribir("RESET TOTALES", "ERR TAG MAESTRO");
					}
					break;
					
				case Menu_432:
					for(int n=0;n<20;n++){
						if(MFRC522_Compare(CardID,operarios[n].id)== MI_OK){
							operario_chequeado=n;
						}
					}
					if(operarios[operario_chequeado].condicion==2){
						instancia=Inicio;
						operarios[operario_a_master].condicion=2;
						flash_guardar_operarios();
						display_escribir("ALTA MAESTRO","CORRECTO");
					} else {
						instancia=Inicio;
						display_escribir("ALTA MAESTRO", "ERR TAG MAESTRO");
					}
					break;
					
				case Menu_442:
					instancia=Inicio;
					if(MFRC522_Compare(CardID,MasterID)!=MI_OK){
						introducir_texto();
					}
					break;
				
				default:
					if(operario_activo==20){
						operario_activo=20;
						for(int n=0;n<20;n++){//Busca una coincidencia de la tarjeta leida con la de algun operario guardado
							if(MFRC522_Compare(CardID,operarios[n].id)== MI_OK){
								operario_activo=n;
							}
						}
						if(operario_activo!=20){
							display_escribir("INICIA TRABAJO",operarios[operario_activo].nombre);
							displayu_clear();
							HAL_Delay(100);
						}
					}else{
						if(MFRC522_Compare(CardID,operarios[operario_activo].id)== MI_OK){
							display_escribir("CIERRA TRABAJO",operarios[operario_activo].nombre);
							operario_activo=20;
							flash_guardar_operarios();
							cont_golpes=0;
							cont_unidades=0;
						}
					}
					break;
					
			} // Sale del switch (instancia)

		}//Sale de rutina de tarjeta			
	
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

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
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

  /*Configure GPIO pin : Boton_desc_unidad_Pin */
  GPIO_InitStruct.Pin = Boton_desc_unidad_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Boton_desc_unidad_GPIO_Port, &GPIO_InitStruct);

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

//----------------IT CALLBACK FUNCTIONS------------------//
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Stop_IT(&htim4);
	flag=1;
}

void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	//HAL_GPIO_TogglePin(Led_Naranja_GPIO_Port, Led_Naranja_Pin);
	if(GPIO_Pin==Sensor_golpes_Pin){ //Si el detector de golpes cuenta una vez, habilita por una única vez al contador de unidades.
		f_sensor=1;
		f_unidades=0;
	
	}else if(GPIO_Pin==Sensor_unidades_Pin && f_unidades==0){ //Hasta que no haya un nuevo golpe de la máquina no puede haber una nueva unidad.
		f_sensor=1;
		f_unidades=1;
		
	}
	
	if(GPIO_Pin==Boton_desc_unidad_Pin){
		HAL_GPIO_TogglePin(Led_Naranja_GPIO_Port, Led_Naranja_Pin);
		f_desc=1;
	}
	
}


void HAL_SYSTICK_Callback(void){
	//if (f_boton==1||f_unidades) ms_ar--; 
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

//------------END IT CALLBACK FUNCTIONS------------------//

//------------TECLADO FUNCTIONS------------------------------//

void encuesta_teclado(void){
		int k=0;
	//Prendo la Columna 1, veo si se activ� alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_SET);
		tecla[0]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[4]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[8]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[12]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C1_GPIO_Port, Teclado_C1_Pin, GPIO_PIN_RESET);
		//Prendo la Columna 2, veo si se activ� alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_SET);
		tecla[1]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[5]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[9]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[13]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C2_GPIO_Port, Teclado_C2_Pin, GPIO_PIN_RESET);
		//Prendo la Columna 3, veo si se activ� alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_SET);
		tecla[2]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[6]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[10]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[14]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C3_GPIO_Port, Teclado_C3_Pin, GPIO_PIN_RESET);
		//Prendo la Columna 2, veo si se activ� alguna entrada y luego la apago.
		HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_SET);
		tecla[3]= 	HAL_GPIO_ReadPin(Teclado_F1_GPIO_Port, Teclado_F1_Pin);
		tecla[7]= 	HAL_GPIO_ReadPin(Teclado_F2_GPIO_Port, Teclado_F2_Pin);
		tecla[11]= 	HAL_GPIO_ReadPin(Teclado_F3_GPIO_Port, Teclado_F3_Pin);
		tecla[15]= 	HAL_GPIO_ReadPin(Teclado_F4_GPIO_Port, Teclado_F4_Pin);
		HAL_GPIO_WritePin(Teclado_C4_GPIO_Port, Teclado_C4_Pin, GPIO_PIN_RESET);
		
		//Veo si alguna tecla fue presionada
		f_boton=0;
		while(!f_boton && k<16){
			f_boton=tecla[k];
			boton=k;
			k++;
		}
}


//-------------DISPLAY FUNCTIONS-------------------------//
void display_escribir(char* linea1, char* linea2){
	int i;
	char l1[17];
	char l2[17];

	//Inicializaci�n de l1 y l2. Ac� lleno 16 caracteres de espacios.
	for (i = 0; i < 16; i++) {
		sprintf(&l1[i], " ");
		sprintf(&l2[i], " ");
	}
	//Relleno de l1. Ac� lleno l1 con los caracteres que haya escrito como primer par�metro y dejo el resto como estaba (espacios).
	i = 0;
	while(linea1[i]){						//Ac� pregunto: "Si el caracter i de linea1 es un caracter..." En lugar de un End Of String.
			l1[i] = linea1[i];
			i++;
		}
	//Relleno de l2. Ac� lleno l2 con los caracteres que haya escrito como segundo par�metro y dejo el resto como estaba (espacios).
	i = 0;
	while (linea2[i]) {						//Ac� pregunto: "Si el caracter i de linea2 es un caracter..." En lugar de un End Of String.
			l2[i] = linea2[i];
			i++;
		}
	
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String(l1);
	LCD_SetPos(0,1);
	LCD_String(l2);

}
//Esto anda re piola, pero cada vez que pulsas el bot�n toma como 300 pulsaciones.
//Esto anda re piola, lo de arriba ya no pasa.

void introducir_texto(void){
	char nombre[9];
	int j = 0;
	for (j = 0; j < 8; j++) {
		sprintf(&nombre[j], "A");
	}
	boton=0;
	int op_vacio=1;
	char str_op_vacio[12];
	int offset;
	uint8_t escribir[26];
	for (j = 0; j < 26; j++) {
		escribir[j]=0;
	}
	j = 0;
	display_escribir("AGREGAR OPERARIO", "NOMBRE: AAAAAAAA");
	LCD_CursorOn();
	LCD_SetPos(8+j,1); //Porqe el "AAAAAAAA" arranca en la columna 9 (0-index) y la fila 2 (0-index)
	while (boton != b_Enter)
		{
				//Encuesta teclado
				encuesta_teclado();
			
				if(f_boton) {
				f_boton=0;
				switch (boton)
				{
				case b_Arriba:
					if (nombre[j] >= 65 && nombre[j] < 90) nombre[j]++;
					else if (nombre[j] == 32) nombre[j] = 65;
					else nombre[j] = 32;
					LCD_SendChar(nombre[j]);
					LCD_SetPos(8+j,1);
					break;

				case b_Abajo:
					if (nombre[j] > 65 && nombre[j] <= 90) nombre[j]--;
					else if (nombre[j] == 32) nombre[j] = 90;
					else nombre[j] = 32;
					LCD_SendChar(nombre[j]);
					LCD_SetPos(8+j,1);	
					break;

				case b_Izquierda:
					if (j) j--;
					else j = 7;
					LCD_SetPos(8+j,1);
					break;

				case b_Derecha:
					if (j!=7) j++;
					else j = 0;
					LCD_SetPos(8+j,1);
					break;
				
				default:
					break;
				}
			}
			HAL_Delay(100);
		}//Esto es que apreto Enter, entonces, guarda el operario.
		
		while(operarios[op_vacio].condicion && op_vacio<=19){
			op_vacio++;
		}
		if(op_vacio==20){
			display_escribir("NO HAY ESPACIO","MEMORIA COMPLETA");
			instancia=Inicio;
		} else {//Esto lo hace si encontro lugar en la memoria.
			operarios[op_vacio].condicion=1;
			for(int i=0;i<9;i++){
				operarios[op_vacio].nombre[i]=nombre[i];
			}
			for(int i=0;i<5;i++){
				operarios[op_vacio].id[i]=CardID[i];
			}
			operarios[op_vacio].golpes=0;
			operarios[op_vacio].unidades=0;
			operarios[op_vacio].productividad=0;
			
			flash_guardar_operarios();
			sprintf(str_op_vacio, "ORDEN: %d OK",op_vacio);
			display_escribir("AGREGAR OPERARIO",str_op_vacio);

		}
}

void display_unidades(void){
	
	char linea1[16];
	char linea2[16];
	sprintf(str_unidades, "%ld", cont_unidades);
	display_escribir("2.2.TOT UNIDADES",str_unidades);
							
	LCD_Clear();
	LCD_SetPos(0,0);
	LCD_String(linea1);
	LCD_SetPos(0,1);
	LCD_String(linea2);
}

void conv_hex(void){
	
	for(int i=0;i<11;i++) id_display[i]=0x00;
	for(int i=0;i<10;i++){
		if(i%2){
			id_display[i]=operarios[operario_chequeado].id[i/2]&0xF;
		}else{
			id_display[i]=operarios[operario_chequeado].id[i/2]>>4;
		}
		switch(id_display[i]){
			case 0x0:
				id_display[i]=0x30;
				break;
			case 0x1:
				id_display[i]=0x31;
				break;
			case 0x2:
				id_display[i]=0x32;
				break;
			case 0x3:
				id_display[i]=0x33;
				break;
			case 0x4:
				id_display[i]=0x34;
				break;
			case 0x5:
				id_display[i]=0x35;
				break;
			case 0x6:
				id_display[i]=0x36;
				break;
			case 0x7:
				id_display[i]=0x37;
				break;
			case 0x8:
				id_display[i]=0x38;
				break;
			case 0x9:
				id_display[i]=0x39;
				break;
			case 0xA:
				id_display[i]=0x41;
				break;
			case 0xB:
				id_display[i]=0x42;
				break;
			case 0xC:
				id_display[i]=0x43;
				break;
			case 0xD:
				id_display[i]=0x44;
				break;
			case 0xE:
				id_display[i]=0x45;
				break;
			case 0xF:
				id_display[i]=0x46;
				break;
		}
	}
}

void displayu_clear(void){
	uint8_t cclear[1]= {0x76};
	HAL_UART_Transmit(&huart2,cclear,1,15);
}

void displayu_escribir(){
	if(cont_unidades<10){
						str_cont_unidades[0]=0x76;
						str_cont_unidades[1]=0x79;
						str_cont_unidades[2]=0x03;
						str_cont_unidades[3]=str_unidades[0];
						HAL_UART_Transmit(&huart2,str_cont_unidades,4,15);
					}else if(cont_unidades<100){
						str_cont_decenas[0]=0x76;
						str_cont_decenas[1]=0x79;
						str_cont_decenas[2]=0x02;
						str_cont_decenas[3]=str_unidades[0];
						str_cont_decenas[4]=str_unidades[1];
						HAL_UART_Transmit(&huart2,str_cont_decenas,5,15);
					}else if(cont_unidades<1000){
						str_cont_centenas[0]=0x76;
						str_cont_centenas[1]=0x79;
						str_cont_centenas[2]=0x01;
						str_cont_centenas[3]=str_unidades[0];
						str_cont_centenas[4]=str_unidades[1];
						str_cont_centenas[5]=str_unidades[2];
						HAL_UART_Transmit(&huart2,str_cont_centenas,6,15);
					}else{
						str_cont_centenas[0]=0x79;
						str_cont_centenas[1]=0x00;
						str_cont_centenas[2]=str_unidades[0];
						str_cont_centenas[3]=str_unidades[1];
						str_cont_centenas[4]=str_unidades[2];
						str_cont_centenas[5]=str_unidades[3];
						HAL_UART_Transmit(&huart2,str_cont_centenas,6,15);
					}
}
//-------------END DISPLAY FUNCTIONS-------------------//

//-------------FLASH FUNCTIONS-------------------------//

void flash_guardar_operarios(){
	int desfasaje=0;
	for (int i=0;i<20;i++){
		desfasaje=32*i;
		if(operarios[i].condicion){
			escribir[desfasaje]=(uint16_t)operarios[i].condicion;
			for (int k=0;k<9;k++){
				escribir[desfasaje+2+k]=operarios[i].nombre[k];
			}
			for (int k=0;k<5;k++){
				escribir[desfasaje+11+k]=operarios[i].id[k];
			}
			escribir[desfasaje+16]=(uint32_t)operarios[i].golpes;
			escribir[desfasaje+20]=(uint32_t)operarios[i].unidades;
			escribir[desfasaje+24]=(uint16_t)operarios[i].productividad;
			for (int k=0;k<6;k++){//Relleno los ultimos bytes de memoria con FF. Por las dudas
				escribir[desfasaje+26+k]=0xFF;
			}
		}else{
			for (int k=0;k<32;k++){
				escribir[desfasaje+k]=0x00;
			}
		}
	}
	MY_FLASH_WriteN(0,escribir,640,DATA_TYPE_8);
	HAL_Delay(10);
}

void flash_cargar_operarios(void){
	
	MY_FLASH_SetSectorAddrs(7,0x08060000);
	
	for (int i=0;i<20;i++){
		MY_FLASH_ReadN(32*i,leer,32,DATA_TYPE_8);
		HAL_Delay(10);
		if(leer[0]){
			operarios[i].condicion=((uint16_t)leer[1]<<8)|leer[0];
			for (int k=0;k<9;k++){
				operarios[i].nombre[k]=leer[2+k];
			}
			for (int k=0;k<5;k++){
				operarios[i].id[k]=leer[11+k];
			}
			operarios[i].golpes=((uint32_t)leer[19]<<24)|((uint32_t)leer[18]<<16)|((uint32_t)leer[17]<<8)|leer[16];
			operarios[i].unidades=((uint32_t)leer[23]<<24)|((uint32_t)leer[22]<<16)|((uint32_t)leer[21]<<8)|leer[20];
			operarios[i].productividad=((uint16_t)leer[25]<<8)|leer[24];
		}
	}
}


//-------------END FLASH FUNCTIONS---------------------//
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
