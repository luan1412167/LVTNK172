
#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <lcd.h>

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
__IO ITStatus UartReady = RESET; 
__IO ITStatus UartReadyI2C = RESET;  
uint8_t BCD2DEC(uint8_t data);
uint8_t DEC2BCD(uint8_t data);
#define	DS3231_ADD 0x68

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_I2C1_Init(void);
void Hienthi(void);
uint8_t	receive_data[7],send_data[7];
uint8_t second,minute,hour,day,date,month,year;
char *timecv;
#define TXBUFFERSIZE    8
#define RXBUFFERSIZE    9
//MFM383A
uint8_t DA1TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x00,0x00,0x02,0x71,0xCB};
uint8_t DA1RxBuffer[RXBUFFERSIZE]; 
uint8_t DA2TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x02,0x00,0x02,0xD0,0x0B};
uint8_t DA2RxBuffer[RXBUFFERSIZE]; 
uint8_t DA3TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x04,0x00,0x02,0x30,0x0A};
uint8_t DA3RxBuffer[RXBUFFERSIZE]; 
uint8_t DD1TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x10,0x00,0x02,0x70,0x0E};
uint8_t DD1RxBuffer[RXBUFFERSIZE]; 
uint8_t DD2TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x12,0x00,0x02,0xD1,0xCE};
uint8_t DD2RxBuffer[RXBUFFERSIZE]; 
uint8_t DD3TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x14,0x00,0x02,0x31,0xCF};
uint8_t DD3RxBuffer[RXBUFFERSIZE]; 
uint8_t CS1TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x18,0x00,0x02,0xF1,0xCC};
uint8_t CS1RxBuffer[RXBUFFERSIZE];
uint8_t CS2TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x1A,0x00,0x02,0x50,0x0C};
uint8_t CS2RxBuffer[RXBUFFERSIZE];
uint8_t CS3TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x1C,0x00,0x02,0xB0,0x0D};
uint8_t CS3RxBuffer[RXBUFFERSIZE];
uint8_t NLTxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x3A,0x00,0x02,0x51,0xC6};
uint8_t NLRxBuffer[RXBUFFERSIZE];  

//MFM383C
//uint8_t DA1TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x00,0x00,0x02,0x71,0xCB};
//uint8_t DA1RxBuffer[RXBUFFERSIZE]; 
//uint8_t DA2TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x02,0x00,0x02,0xD0,0x0B};
//uint8_t DA2RxBuffer[RXBUFFERSIZE]; 
//uint8_t DA3TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x04,0x00,0x02,0x30,0x0A};
//uint8_t DA3RxBuffer[RXBUFFERSIZE]; 
//uint8_t DD1TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x10,0x00,0x02,0x70,0x0E};
//uint8_t DD1RxBuffer[RXBUFFERSIZE]; 
//uint8_t DD2TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x12,0x00,0x02,0xD1,0xCE};
//uint8_t DD2RxBuffer[RXBUFFERSIZE]; 
//uint8_t DD3TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x14,0x00,0x02,0x31,0xCF};
//uint8_t DD3RxBuffer[RXBUFFERSIZE]; 
//uint8_t CS1TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x18,0x00,0x02,0xF1,0xCC};
//uint8_t CS1RxBuffer[RXBUFFERSIZE];
//uint8_t CS2TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x1A,0x00,0x02,0x50,0x0C};
//uint8_t CS2RxBuffer[RXBUFFERSIZE];
//uint8_t CS3TxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x1C,0x00,0x02,0xB0,0x0D};
//uint8_t CS3RxBuffer[RXBUFFERSIZE];
//uint8_t NLTxBuffer[TXBUFFERSIZE]= {0x01,0x04,0x00,0x2E,0x00,0x02,0x11,0xC2};
//uint8_t NLRxBuffer[RXBUFFERSIZE]; 
 
uint8_t	 vBuffer[40]; 
char buffer[20];
char secondstr[2];
char minutestr[2];
char hourstr[2];
char daystr[2];
char datestr[2];
char monthstr[2];
char yearstr[2];
float f=0;



int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_I2C1_Init();
	LCD_ini();
	LCD_Clear();
  while (1)
  {
		    
	      UartReady = RESET;
			  HAL_UART_Transmit_IT(&huart2,(uint8_t*)DA1TxBuffer,TXBUFFERSIZE);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)DA1RxBuffer,RXBUFFERSIZE);
				while (!UartReady){}
					vBuffer[0]=DA1RxBuffer[4];
					vBuffer[1]=DA1RxBuffer[3];
					vBuffer[2]=DA1RxBuffer[6];
					vBuffer[3]=DA1RxBuffer[5];
        UartReady = RESET;
				HAL_Delay(5);
	      HAL_UART_Transmit_IT(&huart2,(uint8_t*)DA2TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)DA2RxBuffer,9);
				while (!UartReady){}
					
					vBuffer[4]=DA2RxBuffer[4];
					vBuffer[5]=DA2RxBuffer[3];
					vBuffer[6]=DA2RxBuffer[6];
					vBuffer[7]=DA2RxBuffer[5];
				UartReady = RESET;	
        HAL_Delay(5);					
        HAL_UART_Transmit_IT(&huart2,(uint8_t*)DA3TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)DA3RxBuffer,9);
				while (!UartReady){}
					
					vBuffer[8]=DA3RxBuffer[4];
					vBuffer[9]=DA3RxBuffer[3];
					vBuffer[10]=DA3RxBuffer[6];
					vBuffer[11]=DA3RxBuffer[5];
				UartReady = RESET;
			  HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)DD1TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)DD1RxBuffer,9);
				while (!UartReady){}
					
				vBuffer[12]=DD1RxBuffer[4];
					vBuffer[13]=DD1RxBuffer[3];
					vBuffer[14]=DD1RxBuffer[6];
					vBuffer[15]=DD1RxBuffer[5];
					
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)DD2TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)DD2RxBuffer,9);
				while (!UartReady){}
					
					vBuffer[16]=DD2RxBuffer[4];
          vBuffer[17]=DD2RxBuffer[3];
					vBuffer[18]=DD2RxBuffer[6];
					vBuffer[19]=DD2RxBuffer[5];
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)DD3TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)DD3RxBuffer,9);
				while (!UartReady){}
					
					vBuffer[20]=DD3RxBuffer[4];
					vBuffer[21]=DD3RxBuffer[3];
					vBuffer[22]=DD3RxBuffer[6];
					vBuffer[23]=DD3RxBuffer[5];
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)CS1TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)CS1RxBuffer,9);
				while (!UartReady){}
					
					vBuffer[24]=CS1RxBuffer[4];
					vBuffer[25]=CS1RxBuffer[3];
					vBuffer[26]=CS1RxBuffer[6];
					vBuffer[27]=CS1RxBuffer[5];
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)CS2TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)CS2RxBuffer,9);
				while (!UartReady){}
					
					vBuffer[28]=CS2RxBuffer[4];
					vBuffer[29]=CS2RxBuffer[3];
					vBuffer[30]=CS2RxBuffer[6];
					vBuffer[31]=CS2RxBuffer[5];
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)CS3TxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)CS3RxBuffer,9);
				while (!UartReady){}
				
					vBuffer[32]=CS3RxBuffer[4];
					vBuffer[33]=CS3RxBuffer[3];
					vBuffer[34]=CS3RxBuffer[6];
					vBuffer[35]=CS3RxBuffer[5];
				
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Transmit_IT(&huart2,(uint8_t*)NLTxBuffer,8);
	      while (!UartReady){} 
				UartReady = RESET;
				HAL_Delay(5);
				HAL_UART_Receive_IT(&huart2,(uint8_t*)NLRxBuffer,9);
				while (!UartReady){}
					
					vBuffer[36]=NLRxBuffer[4];
					vBuffer[37]=NLRxBuffer[3];
					vBuffer[38]=NLRxBuffer[6];
					vBuffer[39]=NLRxBuffer[5];
					
				UartReady = RESET;
				HAL_Delay(5);			
		    HAL_UART_Transmit_IT(&huart3,(uint8_t*)vBuffer,40);
				while (!UartReady){} 
HAL_Delay(5000);
  }
 

}
void Hienthi(void){
	f = *((float*)&vBuffer);
  LCD_SetPos(1,0);
  sprintf(daystr,"%d",day);
	LCD_String(&daystr[0]);
	LCD_SetPos(2,0);
	LCD_String("/");
	LCD_SetPos(3,0);
	sprintf(datestr,"%d",date);
	LCD_String(datestr);
	LCD_SetPos(5,0);
	LCD_String("/");
	LCD_SetPos(6,0);
	sprintf(monthstr,"%d",month);
	LCD_String(monthstr);
	LCD_SetPos(8,0);
	LCD_String("/");
	LCD_SetPos(9,0);
	sprintf(yearstr,"%d",year);
	LCD_String(yearstr);
	LCD_SetPos(11,0);
	LCD_String("-");
	LCD_SetPos(12,0);
	sprintf(hourstr,"%d",hour);
	LCD_String(hourstr);
	LCD_SetPos(14,0);
	LCD_String(":");
	LCD_SetPos(15,0);
	sprintf(minutestr,"%d",minute);
	LCD_String(minutestr);
	LCD_SetPos(17,0);
	LCD_String(":");
	LCD_SetPos(18,0);
	if(second<10){
		LCD_String("0");
		LCD_SetPos(19,0);
		sprintf(secondstr,"%d",second);
		LCD_String(&secondstr[0]);
	}
	else{
	sprintf(secondstr,"%d",second);
	LCD_String(secondstr);}
	LCD_SetPos(2,1);
	LCD_String("CONG SUAT : ");
	LCD_SetPos(12,1);
	sprintf(buffer,"%0.4f",f);
	LCD_String(buffer);
	
}
void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c){
if(hi2c->Instance==hi2c1.Instance)
{
	second= BCD2DEC(receive_data[0]);
	minute=BCD2DEC(receive_data[1]);
	hour=BCD2DEC(receive_data[2]);
	day=BCD2DEC(receive_data[3]);
	date=BCD2DEC(receive_data[4]);
	month=BCD2DEC(receive_data[5]);
	year=BCD2DEC(receive_data[6]);
	UartReadyI2C=SET;
}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart2.Instance)
	{ 
		UartReady=SET;
		huart->gState = HAL_UART_STATE_READY;
	}
		
	if(huart->Instance==huart3.Instance)
	{
		UartReady=SET;
		huart->gState = HAL_UART_STATE_READY;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==huart2.Instance)
	{ 
		UartReady=SET;	
	}
}
uint8_t BCD2DEC(uint8_t data){
return(data>>4)*10+(data&0x0f);
}
uint8_t DEC2BCD(uint8_t data){
return(data/10)<<4|(data%10);
}
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
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

/* USART3 init function */
static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE9 PE10 PE11 PE12 
                           PE13 PE14 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
