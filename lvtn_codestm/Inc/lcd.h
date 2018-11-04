#ifndef LCD_H_
#define LCD_H_
//------------------------------------------------
#include "stm32f4xx_hal.h"
//------------------------------------------------
#define d4_set() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET)
#define d5_set() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET)
#define d6_set() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET)
#define d7_set() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET)
#define d4_reset() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET)
#define d5_reset() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET)
#define d6_reset() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET)
#define d7_reset() HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET)
#define e1 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET)  //��������� ����� � � 1
#define e0 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET) //��������� ����� � � 0
#define rs1 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET) //��������� ����� RS � 1
#define rs0 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET) //��������� ����� RS � 0
#define Monday 7
#define Tuesday 2
#define Wednesday 3
#define Thursday 4
#define Friday 5
#define Saturday 6
#define Sunday 1
//------------------------------------------------
void LCD_ini(void);
void LCD_Clear(void);
void LCD_SendChar(char ch);
void LCD_String(char* st);
void LCD_SetPos(uint8_t x, uint8_t y);
//------------------------------------------------
#endif /* LCD_H_ */
