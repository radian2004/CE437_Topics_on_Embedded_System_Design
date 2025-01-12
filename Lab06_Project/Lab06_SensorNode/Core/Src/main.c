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

#include "main.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/

#include "stdio.h"
#include "SIGNAL.h"
#include "VL53L1_Handler.h"
#include "CAN_Handler.h"

/* Private define ------------------------------------------------------------*/
	VL53L1X sensor1, sensor2;	// Sensors for distance measurement
char buffer[100];			// UART buffer for debug output

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	uint8_t state = 0;             // Current state of the system
	uint8_t prevstate = 0;         // Previous state of the system
	uint8_t forceChange = 0;       // Flag to force state change
/* Callback: Process CAN received message ------------------------------------*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	returnSignal = RxData[0];		// Extract return signal
}
/* Main program entry --------------------------------------------------------*/
int main(void)
{

	/* MCU Configuration--------------------------------------------------------*/
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	MX_CAN_Init();
	MX_TIM3_Init();
	/* Initialize sensors and CAN --------------------------------------------*/
	TOF_InitStruct(&sensor1, &hi2c1, SENSOR1_I2C_ADDR, XSHUT1_GPIO_Port, XSHUT1_Pin);
	TOF_InitStruct(&sensor2, &hi2c1, SENSOR2_I2C_ADDR, XSHUT2_GPIO_Port, XSHUT2_Pin);
	int status = VL53L1_BootDualSensors(&sensor1, &sensor2);
	if (VL53L1_BootDualSensors(&sensor1, &sensor2) != 0) {
		VL53L1_Error_Hanlder(status);
	}
	CAN_FilterInit_SingleFF0(&hcan, &canfilterconfig, ACTUATOR_ADDR);
	CAN_ComInit_Std(&TxHeader, &hcan, SENSOR_ADDR, 2);

  /* Infinite loop */
	while (1) {
		// Force change state if necessary
		if (forceChange != 0) {
			if (forceChange == BACKWARD_RIGHT_STATE) {
				state = LEFT_STATE;
			} else {
				state = RIGHT_STATE;
			}
			forceChange = 0;
		} else {
			// Read distance from sensors
			VL53L1_GetDistance(&sensor1);
			VL53L1_GetDistance(&sensor2);
			// Adjust sensor data for specific scenarios
			if (sensor2.distance >= 55) {
				sensor2.distance += 50;			// Calibration for specific conditions
			}
			// Determine next state based on sensor data
			state = Get_State(sensor1.distance, sensor2.distance, 0, prevstate);
		}
		// State machine to handle system behavior
		switch (state) {
		case LEFT_STATE:
			forceChange = 0;
			prevstate = state;
			HAL_Delay(50);
			while (returnSignal != LEFT_STATE) {
				CAN_Transmit(&hcan, &TxHeader, LEFT);	// Send LEFT command
			}
			break;

		case RIGHT_STATE:
			forceChange = 0;
			prevstate = state;
			CAN_Transmit(&hcan, &TxHeader, RIGHT);
			HAL_Delay(50);
			while (returnSignal != RIGHT_STATE) {
				CAN_Transmit(&hcan, &TxHeader, RIGHT);	// Send RIGHT command
			}
			break;

		case FORWARD_STATE:
			forceChange = 0;
			//prevstate = state;
			CAN_Transmit(&hcan, &TxHeader, FORWARD);	// Send FORWARD command
			//while (returnSignal != FORWARD_STATE) {}
			break;

		case BACKWARD_LEFT_STATE:
			CAN_Transmit(&hcan, &TxHeader, BACKWARD_LEFT);	// Send BACKWARD_LEFT command
			while (state == BACKWARD_LEFT_STATE) {
				VL53L1_GetDistance(&sensor1);
				VL53L1_GetDistance(&sensor2);
				if (sensor2.distance >= 55) {
					sensor2.distance += 50;
				}
				state = Get_State(sensor1.distance, sensor2.distance, 0, prevstate);
			}
			forceChange = BACKWARD_LEFT_STATE;
			break;

		case BACKWARD_RIGHT_STATE:
			CAN_Transmit(&hcan, &TxHeader, BACKWARD_RIGHT);	// Send BACKWARD_RIGHT command
			while (state == BACKWARD_RIGHT_STATE) {
				VL53L1_GetDistance(&sensor1);
				VL53L1_GetDistance(&sensor2);
				if (sensor2.distance >= 55) {
					sensor2.distance += 50;
				}
				state = Get_State(sensor1.distance, sensor2.distance, 0, prevstate);
			}
			forceChange = BACKWARD_RIGHT_STATE;
			break;
//Test sensor (Usually don't run)
		case TEST_SENSORS:
			sprintf(buffer, "\n\rSensor 1\n\r  D1: %dmm\n\n\rSensor 2\n\r  D2: %dmm", sensor1.distance, sensor2.distance);
			Print(buffer, 200);
			break;
		}
		//HAL_Delay(100);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* Error handler -------------------------------------------------------------*/
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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
