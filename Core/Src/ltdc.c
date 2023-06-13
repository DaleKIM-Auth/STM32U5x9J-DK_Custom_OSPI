/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */
extern DSI_HandleTypeDef hdsi;
/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AH;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AH;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 1;
  hltdc.Init.VerticalSync = 19;
  hltdc.Init.AccumulatedHBP = 2;
  hltdc.Init.AccumulatedVBP = 31;
  hltdc.Init.AccumulatedActiveW = 482;
  hltdc.Init.AccumulatedActiveH = 512;
  hltdc.Init.TotalWidth = 483;
  hltdc.Init.TotalHeigh = 712;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 480;
  pLayerCfg.WindowY0 = 1;
  pLayerCfg.WindowY1 = 481;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = 0x0;
  pLayerCfg.ImageWidth = 480;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */
	HAL_Delay(10);
  HAL_DSI_EnterULPM(&hdsi);
  HAL_Delay(10);

  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
  HAL_Delay(10);
  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
  HAL_Delay(150);

  HAL_DSI_ExitULPM(&hdsi);
  HAL_Delay(10);

  // CMD Mode
  uint8_t InitParam1[3] = {0xFF ,0x83 , 0x79};
  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 3, 0xB9, InitParam1) != HAL_OK)
  {
    Error_Handler();
  }

  // SETPOWER
  uint8_t InitParam3[16] = {0x44,0x1C,0x1C,0x37,0x57,0x90,0xD0,0xE2,0x58,0x80,0x38,0x38,0xF8,0x33,0x34,0x42};
  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 16, 0xB1, InitParam3) != HAL_OK)
  {
    Error_Handler();
  }

  // SETDISP
  uint8_t InitParam4[9] = {0x80,0x14,0x0C,0x30,0x20,0x50,0x11,0x42,0x1D};
  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 9, 0xB2, InitParam4) != HAL_OK)
  {
    Error_Handler();
  }

  // Set display cycle timing
  uint8_t InitParam5[10] = {0x01,0xAA,0x01,0xAF,0x01,0xAF,0x10,0xEA,0x1C,0xEA};
  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 10, 0xB4, InitParam5) != HAL_OK)
  {
    Error_Handler();
  }

  // SETVCOM
  uint8_t InitParam60[4] = {00,00,00,0xC0};
  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 4, 0xC7, InitParam60) != HAL_OK)
  {
    Error_Handler();
  }

  // Set Panel Related Registers
  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xCC, 0x02) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xD2, 0x77) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam50[37] = {
    0x00,0x07,0x00,0x00,0x00,0x08,0x08,0x32,0x10,0x01,0x00,0x01,0x03,0x72,0x03,0x72,0x00,0x08,0x00,
    0x08,0x33,0x33,0x05,0x05,0x37,0x05,0x05,0x37,0x0A,0x00,0x00,0x00,0x0A,0x00,0x01,0x00,0x0E
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 37, 0xD3, InitParam50) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam51[34] = {
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x19,0x18,0x18,0x18,0x18,0x19,0x19,0x01,0x00,
    0x03,0x02,0x05,0x04,0x07,0x06,0x23,0x22,0x21,0x20,0x18,0x18,0x18,0x18,0x00,0x00
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 34, 0xD5, InitParam51) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam52[35] = {
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x19,0x18,0x18,0x19,0x19,0x18,0x18,0x06,0x07,
    0x04,0x05,0x02,0x03,0x00,0x01,0x20,0x21,0x22,0x23,0x18,0x18,0x18,0x18
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 35, 0xD6, InitParam52) != HAL_OK)
  {
    Error_Handler();
  }

  // SET GAMMA
  uint8_t InitParam8[42] = {
    0x00,0x16,0x1B,0x30,0x36,0x3F,0x24,0x40,0x09,0x0D,0x0F,0x18,0x0E,0x11,0x12,0x11,0x14,0x07,
    0x12,0x13,0x18,0x00,0x17,0x1C,0x30,0x36,0x3F,0x24,0x40,0x09,0x0C,0x0F,0x18,0x0E,0x11,0x14,
    0x11,0x12,0x07,0x12,0x14,0x18
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 42, 0xE0, InitParam8) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam44[3] = {0x2C,0x2C,00};
  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 3, 0xB6, InitParam44) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xBD, 0x00) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam14[] = {
    0x01,0x00,0x07,0x0F,0x16,0x1F,0x27,0x30,0x38,0x40,0x47,0x4E,0x56,0x5D,0x65,0x6D,0x74,0x7D,
    0x84,0x8A,0x90,0x99,0xA1,0xA9,0xB0,0xB6,0xBD,0xC4,0xCD,0xD4,0xDD,0xE5,0xEC,0xF3,0x36,0x07,
    0x1C,0xC0,0x1B,0x01,0xF1,0x34,0x00
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 42, 0xC1, InitParam14) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xBD, 0x01) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam15[] = {
    0x00,0x08,0x0F,0x16,0x1F,0x28,0x31,0x39,0x41,0x48,0x51,0x59,0x60,0x68,0x70,0x78,0x7F,0x87,
    0x8D,0x94,0x9C,0xA3,0xAB,0xB3,0xB9,0xC1,0xC8,0xD0,0xD8,0xE0,0xE8,0xEE,0xF5,0x3B,0x1A,0xB6,
    0xA0,0x07,0x45,0xC5,0x37,0x00
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 42, 0xC1, InitParam15) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xBD, 0x02) != HAL_OK)
  {
    Error_Handler();
  }

  uint8_t InitParam20[42] = {
    0x00,0x09,0x0F,0x18,0x21,0x2A,0x34,0x3C,0x45,0x4C,0x56,0x5E,0x66,0x6E,0x76,0x7E,0x87,0x8E,
    0x95,0x9D,0xA6,0xAF,0xB7,0xBD,0xC5,0xCE,0xD5,0xDF,0xE7,0xEE,0xF4,0xFA,0xFF,0x0C,0x31,0x83,
    0x3C,0x5B,0x56,0x1E,0x5A,0xFF
  };

  if (HAL_DSI_LongWrite(&hdsi, 0, DSI_DCS_LONG_PKT_WRITE, 42, 0xC1, InitParam20) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0xBD, 0x00) != HAL_OK)
  {
    Error_Handler();
  }

  // Exit Sleep Mode
  if (HAL_DSI_ShortWrite(&hdsi, 0, DSI_DCS_SHORT_PKT_WRITE_P0, DSI_EXIT_SLEEP_MODE, 0x00) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_Delay(120);
  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */
    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
    HAL_NVIC_SetPriority(LTDC_ER_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(LTDC_ER_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
    HAL_NVIC_DisableIRQ(LTDC_ER_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
