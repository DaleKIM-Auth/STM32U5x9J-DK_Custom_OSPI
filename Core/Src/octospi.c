/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    octospi.c
  * @brief   This file provides code for the configuration
  *          of the OCTOSPI instances.
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
#include "octospi.h"

/* USER CODE BEGIN 0 */

XSPI_HandleTypeDef hxspi;

static void OSPI_WriteEnable(XSPI_HandleTypeDef *hospi);
static void OSPI_AutoPollingMemReady(XSPI_HandleTypeDef *hospi);
static void OSPI_OctalModeCfg(XSPI_HandleTypeDef *hospi);
static void OSPI_ChipErase(XSPI_HandleTypeDef *hospi);
static void OSPI_SectorErase(XSPI_HandleTypeDef *hospi, uint32_t address);
static void OSPI_MemoryMappedMode(XSPI_HandleTypeDef *hospi);

/* USER CODE END 0 */

OSPI_HandleTypeDef hospi1;

/* OCTOSPI1 init function */
void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */
  hxspi.Instance = OCTOSPI1;
  
  HAL_XSPI_DeInit(&hxspi);

  hxspi.Init.FifoThresholdByte         = 4;
  hxspi.Init.MemoryType                = HAL_XSPI_MEMTYPE_MICRON;
  hxspi.Init.MemorySize                = HAL_XSPI_SIZE_512MB;
  hxspi.Init.ChipSelectHighTimeCycle   = 2;
  hxspi.Init.FreeRunningClock          = HAL_XSPI_FREERUNCLK_DISABLE;
  hxspi.Init.ClockMode                 = HAL_XSPI_CLOCK_MODE_0;
  hxspi.Init.WrapSize                  = HAL_XSPI_WRAP_NOT_SUPPORTED;
  hxspi.Init.ClockPrescaler            = 1;
  hxspi.Init.SampleShifting            = HAL_XSPI_SAMPLE_SHIFT_NONE;
  hxspi.Init.DelayHoldQuarterCycle     = HAL_XSPI_DHQC_ENABLE;
  hxspi.Init.ChipSelectBoundary        = HAL_XSPI_BONDARYOF_NONE;

  HAL_XSPI_Init(&hxspi);

  OSPI_OctalModeCfg(&hxspi);

  /* Memory-Mapped Mode configuration */
  OSPI_MemoryMappedMode(&hxspi);

  #if 0
  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};
  HAL_OSPI_DLYB_CfgTypeDef HAL_OSPI_DLYB_Cfg_Struct = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 4;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_MICRON;
  hospi1.Init.DeviceSize = 26;
  hospi1.Init.ChipSelectHighTime = 1;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_0;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 1;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.DQSPort = 1;
  sOspiManagerCfg.NCSPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  sOspiManagerCfg.IOHighPort = HAL_OSPIM_IOPORT_1_HIGH;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_OSPI_DLYB_Cfg_Struct.Units = 0;
  HAL_OSPI_DLYB_Cfg_Struct.PhaseSel = 0;
  if (HAL_OSPI_DLYB_SetConfig(&hospi1, &HAL_OSPI_DLYB_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */
  #endif
  /* USER CODE END OCTOSPI1_Init 2 */

}

void HAL_OSPI_MspInit(OSPI_HandleTypeDef* ospiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspInit 0 */
  __HAL_RCC_PWR_CLK_ENABLE();
  /* Enable VDDIO2 supply */
  HAL_PWREx_EnableVddIO2();

    /* Reset the OctoSPI memory interface */
  __HAL_RCC_OSPI1_FORCE_RESET();
  __HAL_RCC_OSPI1_RELEASE_RESET();  
  /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* OCTOSPI1 clock enable */
    __HAL_RCC_OSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**OCTOSPI1 GPIO Configuration
    PF10     ------> OCTOSPIM_P1_CLK
    PF7     ------> OCTOSPIM_P1_IO2
    PF9     ------> OCTOSPIM_P1_IO1
    PC1     ------> OCTOSPIM_P1_IO4
    PF6     ------> OCTOSPIM_P1_IO3
    PF8     ------> OCTOSPIM_P1_IO0
    PA2     ------> OCTOSPIM_P1_NCS
    PC3     ------> OCTOSPIM_P1_IO6
    PC2     ------> OCTOSPIM_P1_IO5
    PC0     ------> OCTOSPIM_P1_IO7
    PA1     ------> OCTOSPIM_P1_DQS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_OCTOSPI1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_6|GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF3_OCTOSPI1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN OCTOSPI1_MspInit 1 */
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_10);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOA, GPIO_PIN_2);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOA, GPIO_PIN_1);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_8);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_9);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_7);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_6);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_1);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_2);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_3);
  HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_0);
  /* USER CODE END OCTOSPI1_MspInit 1 */
  }
}

void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* ospiHandle)
{

  if(ospiHandle->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

  /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /**OCTOSPI1 GPIO Configuration
    PF10     ------> OCTOSPIM_P1_CLK
    PF7     ------> OCTOSPIM_P1_IO2
    PF9     ------> OCTOSPIM_P1_IO1
    PC1     ------> OCTOSPIM_P1_IO4
    PF6     ------> OCTOSPIM_P1_IO3
    PF8     ------> OCTOSPIM_P1_IO0
    PA2     ------> OCTOSPIM_P1_NCS
    PC3     ------> OCTOSPIM_P1_IO6
    PC2     ------> OCTOSPIM_P1_IO5
    PC0     ------> OCTOSPIM_P1_IO7
    PA1     ------> OCTOSPIM_P1_DQS
    */
    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10|GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_6
                          |GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_1);

  /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

  /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief  This function send a Write Enable and wait it is effective.
  * @param  hospi: OSPI handle
  * @retval None
  */
static void OSPI_WriteEnable(XSPI_HandleTypeDef *hospi)
{
    XSPI_RegularCmdTypeDef  sCommand = {0};
    XSPI_AutoPollingTypeDef sConfig = {0};

    /* Enable write operations ------------------------------------------ */
    sCommand.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction        = OCTAL_WRITE_ENABLE_CMD;
    sCommand.InstructionMode    = HAL_XSPI_INSTRUCTION_8_LINES;
    sCommand.InstructionWidth   = HAL_XSPI_INSTRUCTION_16_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    sCommand.AlternateBytesMode = HAL_XSPI_BONDARYOF_NONE;
    sCommand.DataMode           = HAL_XSPI_DATA_NONE;
    sCommand.DummyCycles        = 0;
    sCommand.DQSMode            = HAL_XSPI_DQS_DISABLE;
    sCommand.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Configure automatic polling mode to wait for write enabling ---- */
    sCommand.Instruction    = OCTAL_READ_STATUS_REG_CMD;
    sCommand.Address        = 0x0;
    sCommand.AddressMode    = HAL_XSPI_ADDRESS_8_LINES;
    sCommand.AddressWidth   = HAL_XSPI_ADDRESS_32_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.DataMode       = HAL_XSPI_DATA_8_LINES;
    sCommand.DataDTRMode    = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength     = 1;
    sCommand.DummyCycles    = DUMMY_CLOCK_CYCLES_READ_REG;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

		HAL_Delay(50);
		
    sConfig.MatchValue      = WRITE_ENABLE_MATCH_VALUE;
    sConfig.MatchMask       = WRITE_ENABLE_MASK_VALUE;
    sConfig.MatchMode       = HAL_XSPI_MATCH_MODE_AND;
    sConfig.IntervalTime    = AUTO_POLLING_INTERVAL;
    sConfig.AutomaticStop   = HAL_XSPI_AUTOMATIC_STOP_ENABLE;

    HAL_XSPI_AutoPolling(hospi, &sConfig, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);
}

/**
  * @brief  This function read the SR of the memory and wait the EOP.
  * @param  hospi: OSPI handle
  * @retval None
  */
static void OSPI_AutoPollingMemReady(XSPI_HandleTypeDef *hospi)
{
    XSPI_RegularCmdTypeDef  sCommand = {0};
    XSPI_AutoPollingTypeDef sConfig = {0};

    /* Configure automatic polling mode to wait for memory ready ------ */
    sCommand.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction        = OCTAL_READ_STATUS_REG_CMD;
    sCommand.InstructionMode    = HAL_XSPI_INSTRUCTION_8_LINES;
    sCommand.InstructionWidth   = HAL_XSPI_INSTRUCTION_16_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address            = 0x0;
    sCommand.AddressMode        = HAL_XSPI_ADDRESS_8_LINES;
    sCommand.AddressWidth       = HAL_XSPI_ADDRESS_32_BITS;
    sCommand.AddressDTRMode     = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode           = HAL_XSPI_DATA_8_LINES;
    sCommand.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength         = 1;
    sCommand.DummyCycles        = DUMMY_CLOCK_CYCLES_READ_REG;
    sCommand.DQSMode            = HAL_XSPI_DQS_DISABLE;
    sCommand.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    sConfig.MatchValue      = MEMORY_READY_MATCH_VALUE;
    sConfig.MatchMask       = MEMORY_READY_MASK_VALUE;
    sConfig.MatchMode       = HAL_XSPI_MATCH_MODE_AND;
    sConfig.IntervalTime    = AUTO_POLLING_INTERVAL;
    sConfig.AutomaticStop   = HAL_XSPI_AUTOMATIC_STOP_ENABLE;

    HAL_XSPI_AutoPolling(hospi, &sConfig, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);
}
/**
  * @brief  This function configure the memory in Octal mode.
  * @param  hospi: OSPI handle
  * @retval None
  */
static void OSPI_OctalModeCfg(XSPI_HandleTypeDef *hospi)
{
    XSPI_RegularCmdTypeDef  sCommand = {0};
    XSPI_AutoPollingTypeDef sConfig = {0};
    uint8_t reg;

    /* Enable write operations ---------------------------------------- */
    sCommand.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction        = WRITE_ENABLE_CMD;
    sCommand.InstructionMode    = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.InstructionWidth   = HAL_XSPI_INSTRUCTION_8_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode           = HAL_XSPI_DATA_NONE;
    sCommand.DummyCycles        = 0;
    sCommand.DQSMode            = HAL_XSPI_DQS_DISABLE;
    sCommand.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);


    /* Configure automatic polling mode to wait for write enabling ---- */
    sCommand.Instruction    = READ_STATUS_REG_CMD;
    sCommand.DataMode       = HAL_XSPI_DATA_1_LINE;
    sCommand.DataDTRMode    = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DataLength     = 1;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    sConfig.MatchValue      = WRITE_ENABLE_MATCH_VALUE;
    sConfig.MatchMask       = WRITE_ENABLE_MASK_VALUE;
    sConfig.MatchMode       = HAL_XSPI_MATCH_MODE_AND;
    sConfig.IntervalTime    = AUTO_POLLING_INTERVAL;
    sConfig.AutomaticStop   = HAL_XSPI_AUTOMATIC_STOP_ENABLE;

    HAL_XSPI_AutoPolling(hospi, &sConfig, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);
  
    /* Write Configuration register 2 (with new dummy cycles) --------- */
    sCommand.Instruction    = WRITE_CFG_REG_2_CMD;
    sCommand.Address        = CONFIG_REG2_ADDR3;
    sCommand.AddressMode    = HAL_XSPI_ADDRESS_1_LINE;
    sCommand.AddressWidth   = HAL_XSPI_ADDRESS_32_BITS;
    sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    reg = CR2_DUMMY_CYCLES_66MHZ;

    HAL_XSPI_Transmit(hospi, &reg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Wait that the memory is ready ---------------------------------- */
    sCommand.Instruction = READ_STATUS_REG_CMD;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    sConfig.MatchValue = MEMORY_READY_MATCH_VALUE;
    sConfig.MatchMask  = MEMORY_READY_MASK_VALUE;

    HAL_XSPI_AutoPolling(hospi, &sConfig, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Enable write operations ---------------------------------------- */
    sCommand.Instruction = WRITE_ENABLE_CMD;
    sCommand.DataMode    = HAL_XSPI_DATA_NONE;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Configure automatic polling mode to wait for write enabling ---- */
    sCommand.Instruction = READ_STATUS_REG_CMD;
    sCommand.DataMode    = HAL_XSPI_DATA_1_LINE;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    sConfig.MatchValue = WRITE_ENABLE_MATCH_VALUE;
    sConfig.MatchMask  = WRITE_ENABLE_MASK_VALUE;

    HAL_XSPI_AutoPolling(hospi, &sConfig, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Write Configuration register 2 (with octal mode) --------------- */
    sCommand.Instruction = WRITE_CFG_REG_2_CMD;
    sCommand.Address     = CONFIG_REG2_ADDR1;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_1_LINE;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    reg = CR2_STR_OPI_ENABLE;

    HAL_XSPI_Transmit(hospi, &reg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Wait that the configuration is effective and check that memory is ready */
    HAL_Delay(MEMORY_REG_WRITE_DELAY);

    /* Wait that the memory is ready ---------------------------------- */
    OSPI_AutoPollingMemReady(hospi);
}

static void OSPI_ChipErase(XSPI_HandleTypeDef *hospi)
{
    XSPI_RegularCmdTypeDef  sCommand = {0};

    OSPI_WriteEnable(hospi);

    sCommand.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction        = OCTAL_BULK_ERASE_CMD;
    sCommand.InstructionMode    = HAL_XSPI_INSTRUCTION_8_LINES;
    sCommand.InstructionWidth   = HAL_XSPI_INSTRUCTION_16_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.AddressMode        = HAL_XSPI_ADDRESS_NONE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode           = HAL_XSPI_DATA_NONE;
    sCommand.DummyCycles        = 0;
    sCommand.DQSMode            = HAL_XSPI_DQS_DISABLE;
    sCommand.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Wait for end of erasing operation */
    OSPI_AutoPollingMemReady(hospi);
}

static void OSPI_SectorErase(XSPI_HandleTypeDef *hospi, uint32_t address)
{
    XSPI_RegularCmdTypeDef  sCommand = {0};

    OSPI_WriteEnable(hospi);

    sCommand.OperationType      = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.Instruction        = OCTAL_SECTOR_ERASE_CMD;
    sCommand.InstructionMode    = HAL_XSPI_INSTRUCTION_8_LINES;
    sCommand.InstructionWidth   = HAL_XSPI_INSTRUCTION_16_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.AddressMode        = HAL_XSPI_ADDRESS_8_LINES;
    sCommand.Address            = address;
    sCommand.AddressWidth       = HAL_XSPI_ADDRESS_32_BITS;
    sCommand.AddressDTRMode     = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode           = HAL_XSPI_DATA_NONE;
    sCommand.DummyCycles        = 0;
    sCommand.DQSMode            = HAL_XSPI_DQS_DISABLE;
    sCommand.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    /* Wait for end of erasing operation */
    OSPI_AutoPollingMemReady(hospi);
}

static void OSPI_MemoryMappedMode(XSPI_HandleTypeDef *hospi)
{
    XSPI_RegularCmdTypeDef    sCommand = {0};
    XSPI_MemoryMappedTypeDef  sMemMappedCfg = {0};

    OSPI_WriteEnable(hospi);

    sCommand.OperationType      = HAL_XSPI_OPTYPE_WRITE_CFG;
    sCommand.Instruction        = OCTAL_PAGE_PROG_CMD;
    sCommand.InstructionMode    = HAL_XSPI_INSTRUCTION_8_LINES;
    sCommand.InstructionWidth   = HAL_XSPI_INSTRUCTION_16_BITS;
    sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
    sCommand.Address            = 0U;
    sCommand.AddressMode        = HAL_XSPI_ADDRESS_8_LINES;
    sCommand.AddressWidth       = HAL_XSPI_ADDRESS_32_BITS;
    sCommand.AddressDTRMode     = HAL_XSPI_ADDRESS_DTR_DISABLE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode           = HAL_XSPI_DATA_8_LINES;
    sCommand.DataLength         = 1;
    sCommand.DataDTRMode        = HAL_XSPI_DATA_DTR_DISABLE;
    sCommand.DQSMode            = HAL_XSPI_DQS_ENABLE;
    sCommand.SIOOMode           = HAL_XSPI_SIOO_INST_EVERY_CMD;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    sCommand.OperationType      = HAL_XSPI_OPTYPE_READ_CFG;
    sCommand.Instruction        = OCTAL_IO_READ_CMD;
    sCommand.DummyCycles        = DUMMY_CLOCK_CYCLES_READ;
    sCommand.DQSMode            = HAL_XSPI_DQS_DISABLE;

    HAL_XSPI_Command(hospi, &sCommand, HAL_XSPI_TIMEOUT_DEFAULT_VALUE);

    sMemMappedCfg.TimeOutActivation   = HAL_XSPI_TIMEOUT_COUNTER_ENABLE;
    sMemMappedCfg.TimeoutPeriodClock  = 0x40;
		
    HAL_XSPI_MemoryMapped(hospi, &sMemMappedCfg);

}
/**
  * @brief  Initialize the XSPI MSP.
  * @param  hxspi : XSPI handle
  * @retval None
  */
void HAL_XSPI_MspInit(XSPI_HandleTypeDef *hxspi)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	
    if(hxspi->Instance==OCTOSPI1){
  
        __HAL_RCC_PWR_CLK_ENABLE();
        /* Enable VDDIO2 supply */
        HAL_PWREx_EnableVddIO2();

        /* Reset the OctoSPI memory interface */
        __HAL_RCC_OSPI1_FORCE_RESET();
        __HAL_RCC_OSPI1_RELEASE_RESET();  
  
        /** Initializes the peripherals clock
         */
        PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
        PeriphClkInit.OspiClockSelection = RCC_OSPICLKSOURCE_SYSCLK;
        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

        /* OCTOSPI1 clock enable */
        __HAL_RCC_OSPIM_CLK_ENABLE();
        __HAL_RCC_OSPI1_CLK_ENABLE();

        __HAL_RCC_GPIOF_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
		
        /*  Activate HSLV  */
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_10);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOA, GPIO_PIN_2);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOA, GPIO_PIN_1);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_8);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_9);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_7);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOF, GPIO_PIN_6);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_1);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_2);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_3);
        HAL_GPIO_EnableHighSPeedLowVoltage(GPIOC, GPIO_PIN_0);
		
        /**OCTOSPI1 GPIO Configuration
           PF10     ------> OCTOSPIM_P1_CLK
           PF7     ------> OCTOSPIM_P1_IO2
           PF9     ------> OCTOSPIM_P1_IO1
           PC1     ------> OCTOSPIM_P1_IO4
           PF6     ------> OCTOSPIM_P1_IO3
           PF8     ------> OCTOSPIM_P1_IO0
           PA2     ------> OCTOSPIM_P1_NCS
           PC3     ------> OCTOSPIM_P1_IO6
           PC2     ------> OCTOSPIM_P1_IO5
           PC0     ------> OCTOSPIM_P1_IO7
           PA1     ------> OCTOSPIM_P1_DQS
        */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF3_OCTOSPI1;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_9|GPIO_PIN_6|GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_1;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF3_OCTOSPI1;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    }
}

/* USER CODE END 1 */
