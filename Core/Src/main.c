/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "switches.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//SWITCH B12
//DATA   B13
//CLK    B14



uint8_t current_counter = 0, previous_counter = 0;
uint8_t sign_position = 0;
uint8_t full_menu[4] = {0,1,2,3};
uint8_t current_menu[2] = {0,1};
uint8_t full_menu_num = 3;
uint8_t last_menu_position = 1;
char buff[4]={"\0"};

typedef enum{
	Main_menu_pos,
	Cell_num_menu_pos,
	Cell_volt_menu_pos
}menu_positions_t;

char *menu_titles[4]={
		"PackageV:",
		"CellV:",
		"Cell Number:",
		"Cell Voltage:"
};



typedef struct {
	float pack_voltage;
	float pack_per_cell_voltage;
	uint8_t sel_cell_number;
	float sel_cell_voltage;
	uint8_t position;
}menu_values_t, *menu_values_ptr_t;

void draw_menu(menu_values_ptr_t ptr){
	LCD_clear();
	if(ptr->position <= 2){
		LCD_set_cursor(0, 0);
		LCD_write_string(menu_titles[0]);
		LCD_set_cursor(1, 0);
		LCD_write_string(menu_titles[1]);
		LCD_set_cursor(ptr->position, 15);
		LCD_write_string("<");
	}else if(ptr->position >=2 && ptr->position < 3){
		LCD_set_cursor(0, 0);
		LCD_write_string(menu_titles[1]);
		LCD_set_cursor(1, 0);
		LCD_write_string(menu_titles[2]);
		LCD_set_cursor(1, 15);
		LCD_write_string("<");
	}else{
		LCD_set_cursor(0, 0);
		LCD_write_string(menu_titles[2]);
		LCD_set_cursor(1, 0);
		LCD_write_string(menu_titles[3]);
		LCD_set_cursor(1, 15);
		LCD_write_string("<");
	}
}
uint8_t index_arr[2]={0,1};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  LCD_init();
  LCD_backlight(1); // Turn on backlight
  menu_values_t menu_values;
  char line0[16];

  LCD_set_cursor(0, 0);
  LCD_write_string("0");
  LCD_set_cursor(0, 15);
  LCD_write_string("<");
  LCD_set_cursor(1, 0);
  LCD_write_string("1");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  current_counter = Switches_getCounter();
	  if(current_counter > 3) current_counter = 3;
	  if(current_counter > 200) current_counter = 0;

	  if(current_counter > previous_counter){
		  previous_counter = current_counter;
		  if(sign_position!=1){
			  sign_position++;
		  }else if(last_menu_position != full_menu_num){
			  last_menu_position++;
			  current_menu[0] = current_menu[1];
			  current_menu[1] = full_menu[last_menu_position];
		  }



		  LCD_clear();
		  LCD_set_cursor(sign_position, 15);
		  LCD_write_string("<");

		  LCD_set_cursor(sign_position, 7);
		  sprintf(buff,"%d", last_menu_position);
		  LCD_write_string(buff);

		  LCD_set_cursor(0, 0);
		  sprintf(buff,"%d",current_menu[0]);
		  LCD_write_string(buff);

		  LCD_set_cursor(1, 0);
		  sprintf(buff,"%d",current_menu[1]);
		  LCD_write_string(buff);

	  }else if(current_counter < previous_counter){

		  previous_counter = current_counter;
		  if(sign_position!=0){
			  sign_position--;
			  last_menu_position--;
		  }else if(last_menu_position != 0){
			  last_menu_position--;
			  current_menu[1] = current_menu[0];
			  current_menu[0] = full_menu[last_menu_position];
		  }

		  LCD_clear();
		  LCD_set_cursor(sign_position, 15);
		  LCD_write_string("<");

		  LCD_set_cursor(sign_position, 7);
		  sprintf(buff,"%d", last_menu_position);
		  LCD_write_string(buff);

		  LCD_set_cursor(0, 0);
		  sprintf(buff,"%d",current_menu[0]);
		  LCD_write_string(buff);

		  LCD_set_cursor(1, 0);
		  sprintf(buff,"%d",current_menu[1]);
		  LCD_write_string(buff);
		  if(last_menu_position == 0){
			  last_menu_position = 1;
			  current_counter = 0;
			  previous_counter = 0;
		  }
	  }


	  /*if(c != p){
		  if(c > 3) c = 3;
		  if(c > 250) c = 0;
		  if(c <= 3) LCD_clear();
		  if(c == 0){
			  LCD_set_cursor(0, 0);
			  LCD_write_string(menu_titles[0]);
			  LCD_set_cursor(0, 15);
			  LCD_write_string("<");
			  LCD_set_cursor(1, 0);
			  LCD_write_string(menu_titles[1]);
		  }
		  if(c == 3){
			  LCD_set_cursor(0, 0);
			   LCD_write_string(menu_titles[2]);
			  LCD_set_cursor(1, 15);
			  LCD_write_string("<");
			  LCD_set_cursor(1, 0);
			  LCD_write_string(menu_titles[3]);
		  }
		  if(c > p && c == 1){
			  LCD_set_cursor(0, 0);
			  LCD_write_string(menu_titles[0]);
			  LCD_set_cursor(1, 15);
			  LCD_write_string("<");
			  LCD_set_cursor(1, 0);
			  LCD_write_string(menu_titles[1]);
		  }
		  if(c > p && c == 2){
			  LCD_set_cursor(0, 0);
			  LCD_write_string(menu_titles[1]);
			  LCD_set_cursor(1, 15);
			  LCD_write_string("<");
			  LCD_set_cursor(1, 0);
			  LCD_write_string(menu_titles[2]);
		  }


		  if(c < p && c == 1){
			  LCD_set_cursor(0, 0);
			  LCD_write_string(menu_titles[1]);
			  LCD_set_cursor(0, 15);
			  LCD_write_string("<");
			  LCD_set_cursor(1, 0);
			  LCD_write_string(menu_titles[2]);
		  }

		  if(c < p && c == 2){
		  	LCD_set_cursor(0, 0);
		  	LCD_write_string(menu_titles[2]);
		  	LCD_set_cursor(0, 15);
		  	LCD_write_string("<");
		  	LCD_set_cursor(1, 0);
		  	LCD_write_string(menu_titles[3]);
		  }
		  p = c;
	  }*/

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_Pin DATA_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin|DATA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : CLOCK_Pin */
  GPIO_InitStruct.Pin = CLOCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CLOCK_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
