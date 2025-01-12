/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* CAN Handle Structure */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

/* Configure CAN instance */
		hcan.Instance = CAN1;
	    hcan.Init.Prescaler = 4;                            // Set CAN clock prescaler
	    hcan.Init.Mode = CAN_MODE_NORMAL;                   // Set to normal operation mode
	    hcan.Init.SyncJumpWidth = CAN_SJW_2TQ;              // Set Synchronization Jump Width
	    hcan.Init.TimeSeg1 = CAN_BS1_13TQ;                  // Set Time Segment 1
	    hcan.Init.TimeSeg2 = CAN_BS2_4TQ;                   // Set Time Segment 2
	    hcan.Init.TimeTriggeredMode = DISABLE;              // Disable time-triggered communication
	    hcan.Init.AutoBusOff = DISABLE;                     // Disable automatic bus-off management
	    hcan.Init.AutoWakeUp = DISABLE;                     // Disable automatic wake-up mode
	    hcan.Init.AutoRetransmission = DISABLE;             // Disable automatic retransmission
	    hcan.Init.ReceiveFifoLocked = DISABLE;              // Disable receive FIFO locked mode
	    hcan.Init.TransmitFifoPriority = DISABLE;           // Disable FIFO priority
  {
    Error_Handler();
  }
}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
    /* Enable GPIOA clock for CAN pins */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /* Configure CAN RX (PA11) as input */
    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;		// No pull-up or pull-down resistors
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* Configure CAN TX (PA12) as alternate function push-pull */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	// Set high speed for CAN communication
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();
    /* Deinitialize CAN GPIO pins (PA11, PA12) */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);
    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  }
}
