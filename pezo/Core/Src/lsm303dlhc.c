/**
  ******************************************************************************
  * @file    lsm303dlhc.c
  * @author  MCD Application Team
  * @brief   This file provides a set of functions needed to manage the lsm303dlhc
  *          MEMS Accelmeter.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "lsm303dlhc.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup LSM303DLHC
  * @{
  */

/** @defgroup LSM303DLHC_Private_TypesDefinitions
  * @{
  */
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Defines
  * @{
  */

/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Variables
  * @{
  */
ACCELERO_DrvTypeDef Lsm303dlhcDrv =
{
  LSM303DLHC_AccInit,
  LSM303DLHC_AccDeInit,
  LSM303DLHC_AccReadID,
  LSM303DLHC_AccRebootCmd,
  0,
  LSM303DLHC_AccZClickITConfig,
  0,
  0,
  0,
  0,
  LSM303DLHC_AccFilterConfig,
  LSM303DLHC_AccFilterCmd,
  LSM303DLHC_AccReadXYZ
};

/**
  * @}
  */

/** @defgroup LSM303DLHC_Private_Functions
  * @{
  */

/**
  * @brief  Set LSM303DLHC Initialization.
  * @param  InitStruct: Init parameters
  * @retval None
  */

void Error(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void LSM303DLHC_AccInit(uint16_t InitStruct)
{
  uint8_t ctrl = 0x00;

  /* Write value to ACC MEMS CTRL_REG1 register */
  ctrl = (uint8_t) InitStruct;
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG1_A, ctrl);

  /* Write value to ACC MEMS CTRL_REG4 register */
  ctrl = (uint8_t) (InitStruct << 8);
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, ctrl);
}

/**
  * @brief  LSM303DLHC De-initialization.
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccDeInit(void)
{
}

/**
  * @brief  Read LSM303DLHC ID.
  * @param  None
  * @retval ID
  */
uint8_t LSM303DLHC_AccReadID(void)
{
  uint8_t ctrl = 0x00;

  /* Low level init */
  Accel_IO_Init();

  /* Read value at Who am I register address */
  ctrl = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_WHO_AM_I_ADDR);

  return ctrl;
}

/**
  * @brief  Reboot memory content of LSM303DLHC
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccRebootCmd(void)
{
  uint8_t tmpreg;

  /* Read CTRL_REG5 register */
  tmpreg = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A);

  /* Enable or Disable the reboot memory */
  tmpreg |= LSM303DLHC_BOOT_REBOOTMEMORY;

  /* Write value to ACC MEMS CTRL_REG5 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A, tmpreg);
}

/**
  * @brief  Set High Pass Filter Modality
  * @param  FilterStruct: contains data for filter config
  * @retval None
  */
void LSM303DLHC_AccFilterConfig(uint8_t FilterStruct)
{
  uint8_t tmpreg;

  /* Read CTRL_REG2 register */
  tmpreg = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A);

  tmpreg &= 0x0C;
  tmpreg |= FilterStruct;

  /* Write value to ACC MEMS CTRL_REG2 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, tmpreg);
}

/**
  * @brief  Enable or Disable High Pass Filter
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be:
  *         @arg: LSM303DLHC_HIGHPASSFILTER_DISABLE
  *         @arg: LSM303DLHC_HIGHPASSFILTER_ENABLE
  * @retval None
  */
void LSM303DLHC_AccFilterCmd(uint8_t HighPassFilterState)
{
  uint8_t tmpreg;

  /* Read CTRL_REG2 register */
  tmpreg = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A);

  tmpreg &= 0xF7;

  tmpreg |= HighPassFilterState;

  /* Write value to ACC MEMS CTRL_REG2 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, tmpreg);
}

/**
  * @brief  Read X, Y & Z Acceleration values
  * @param  pData: Data out pointer
  * @retval None
  */
void LSM303DLHC_AccReadXYZ(int16_t* pData)
{
  int16_t pnRawData[3];
  uint8_t ctrlx[2]={0,0};
  int8_t buffer[6];
  uint8_t i = 0;
  uint8_t sensitivity = LSM303DLHC_ACC_SENSITIVITY_2G;

  /* Read the acceleration control register content */
  ctrlx[0] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A);
  ctrlx[1] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG5_A);

  /* Read output register X, Y & Z acceleration */
  buffer[0] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A);
  buffer[1] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_H_A);
  buffer[2] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Y_L_A);
  buffer[3] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Y_H_A);
  buffer[4] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Z_L_A);
  buffer[5] = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Z_H_A);

  /* Check in the control register4 the data alignment*/
  if(!(ctrlx[0] & LSM303DLHC_BLE_MSB))
  {
    for(i=0; i<3; i++)
    {
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i]);
    }
  }
  else /* Big Endian Mode */
  {
    for(i=0; i<3; i++)
    {
      pnRawData[i]=((int16_t)((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]);
    }
  }

  /* Normal mode */
  /* Switch the sensitivity value set in the CRTL4 */
  switch(ctrlx[0] & LSM303DLHC_FULLSCALE_16G)
  {
  case LSM303DLHC_FULLSCALE_2G:
    sensitivity = LSM303DLHC_ACC_SENSITIVITY_2G;
    break;
  case LSM303DLHC_FULLSCALE_4G:
    sensitivity = LSM303DLHC_ACC_SENSITIVITY_4G;
    break;
  case LSM303DLHC_FULLSCALE_8G:
    sensitivity = LSM303DLHC_ACC_SENSITIVITY_8G;
    break;
  case LSM303DLHC_FULLSCALE_16G:
    sensitivity = LSM303DLHC_ACC_SENSITIVITY_16G;
    break;
  }

  /* Obtain the mg value for the three axis */
  for(i=0; i<3; i++)
  {
    pData[i]=(pnRawData[i] * sensitivity);
  }
}

/**
  * @brief  Enable or Disable High Pass Filter on CLick
  * @param  HighPassFilterState: new state of the High Pass Filter feature.
  *      This parameter can be:
  *         @arg: LSM303DLHC_HPF_CLICK_DISABLE
  *         @arg: LSM303DLHC_HPF_CLICK_ENABLE
  * @retval None
  */
void LSM303DLHC_AccFilterClickCmd(uint8_t HighPassFilterClickState)
{
  uint8_t tmpreg = 0x00;

  /* Read CTRL_REG2 register */
  tmpreg = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A);

  tmpreg &= ~(LSM303DLHC_HPF_CLICK_ENABLE);

  tmpreg |= HighPassFilterClickState;

  /* Write value to ACC MEMS CTRL_REG2 regsister */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG2_A, tmpreg);
}

/**
  * @brief Enable LSM303DLHC Interrupt1
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be enabled.
  *           This parameter can be any combination of the following values:
  *         @arg   LSM303DLHC_IT1_CLICK
  *         @arg   LSM303DLHC_IT1_AOI1
  *         @arg   LSM303DLHC_IT1_AOI2
  *         @arg   LSM303DLHC_IT1_DRY1
  *         @arg   LSM303DLHC_IT1_DRY2
  *         @arg   LSM303DLHC_IT1_WTM
  *         @arg   LSM303DLHC_IT1_OVERRUN
  * @retval None
  */
void LSM303DLHC_AccIT1Enable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;

  /* Read CTRL_REG3 register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A);

  /* Enable IT1 */
  tmpval |= LSM303DLHC_IT;

  /* Write value to MEMS CTRL_REG3 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A, tmpval);
}

/**
  * @brief Disable LSM303DLHC Interrupt1
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be disabled.
  *           This parameter can be any combination of the following values:
  *         @arg   LSM303DLHC_IT1_CLICK
  *         @arg   LSM303DLHC_IT1_AOI1
  *         @arg   LSM303DLHC_IT1_AOI2
  *         @arg   LSM303DLHC_IT1_DRY1
  *         @arg   LSM303DLHC_IT1_DRY2
  *         @arg   LSM303DLHC_IT1_WTM
  *         @arg   LSM303DLHC_IT1_OVERRUN
  * @retval None
  */
void LSM303DLHC_AccIT1Disable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;

  /* Read CTRL_REG3 register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A);

  /* Disable IT1 */
  tmpval &= ~LSM303DLHC_IT;

  /* Write value to MEMS CTRL_REG3 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG3_A, tmpval);
}

/**
  * @brief Enable LSM303DLHC Interrupt2
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be enabled.
  *           This parameter can be any combination of the following values:
  *         @arg   LSM303DLHC_IT2_CLICK
  *         @arg   LSM303DLHC_IT2_INT1
  *         @arg   LSM303DLHC_IT2_INT2
  *         @arg   LSM303DLHC_IT2_BOOT
  *         @arg   LSM303DLHC_IT2_ACT
  *         @arg   LSM303DLHC_IT2_HLACTIVE
  * @retval None
  */
void LSM303DLHC_AccIT2Enable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;

  /* Read CTRL_REG3 register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A);

  /* Enable IT2 */
  tmpval |= LSM303DLHC_IT;

  /* Write value to MEMS CTRL_REG3 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A, tmpval);
}

/**
  * @brief Disable LSM303DLHC Interrupt2
  * @param  LSM303DLHC_IT: specifies the LSM303DLHC interrupt source to be disabled.
  *           This parameter can be any combination of the following values:
  *         @arg   LSM303DLHC_IT2_CLICK
  *         @arg   LSM303DLHC_IT2_INT1
  *         @arg   LSM303DLHC_IT2_INT2
  *         @arg   LSM303DLHC_IT2_BOOT
  *         @arg   LSM303DLHC_IT2_ACT
  *         @arg   LSM303DLHC_IT2_HLACTIVE
  * @retval None
  */
void LSM303DLHC_AccIT2Disable(uint8_t LSM303DLHC_IT)
{
  uint8_t tmpval = 0x00;

  /* Read CTRL_REG3 register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A);

  /* Disable IT2 */
  tmpval &= ~LSM303DLHC_IT;

  /* Write value to MEMS CTRL_REG3 register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG6_A, tmpval);
}

/**
  * @brief  INT1 interrupt enable
  * @param  ITCombination: Or or And combination
  *         ITAxes: Axes to be enabled
  * @retval None
  */
void LSM303DLHC_AccINT1InterruptEnable(uint8_t ITCombination, uint8_t ITAxes)
{
  uint8_t tmpval = 0x00;

  /* Read INT1_CFR register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A);

  /* Enable the selected interrupt */
  tmpval |= (ITAxes | ITCombination);

  /* Write value to MEMS INT1_CFR register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A, tmpval);
}

/**
  * @brief  INT1 interrupt disable
  * @param  ITCombination: Or or And combination
  *         ITAxes: Axes to be enabled
  * @retval None
  */
void LSM303DLHC_AccINT1InterruptDisable(uint8_t ITCombination, uint8_t ITAxes)
{
  uint8_t tmpval = 0x00;

  /* Read INT1_CFR register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A);

  /* Disable the selected interrupt */
  tmpval &= ~(ITAxes | ITCombination);

  /* Write value to MEMS INT1_CFR register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT1_CFG_A, tmpval);
}

/**
  * @brief  INT2 interrupt enable
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled
  * @retval None
  */
void LSM303DLHC_AccINT2InterruptEnable(uint8_t ITCombination, uint8_t ITAxes)
{
  uint8_t tmpval = 0x00;

  /* Read INT2_CFR register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A);

  /* Enable the selected interrupt */
  tmpval |= (ITAxes | ITCombination);

  /* Write value to MEMS INT2_CFR register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A, tmpval);
}

/**
  * @brief  INT2 interrupt config
  * @param  ITCombination: Or or And combination
  *         ITAxes: axes to be enabled
  * @retval None
  */
void LSM303DLHC_AccINT2InterruptDisable(uint8_t ITCombination, uint8_t ITAxes)
{
  uint8_t tmpval = 0x00;

  /* Read INT2_CFR register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A);

  /* Disable the selected interrupt */
  tmpval &= ~(ITAxes | ITCombination);

  /* Write value to MEMS INT2_CFR register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_INT2_CFG_A, tmpval);
}

/**
  * @brief  Click interrupt enable
  * @param  ITClick: the selected interrupt to enable
  * @retval None
  */
void LSM303DLHC_AccClickITEnable(uint8_t ITClick)
{
  uint8_t tmpval = 0x00;

  /* Read CLICK_CFR register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A);

  /* Enable the selected interrupt */
  tmpval |= ITClick;

  /* Write value to MEMS CLICK CFG register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A, tmpval);

  /* Configure Click Threshold on Z axis */
  tmpval = 0x0A;
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_THS_A, tmpval);

  /* Configure Time Limit */
  tmpval = 0x05;
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_TIME_LIMIT_A, tmpval);

  /* Configure Latency */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_TIME_LATENCY_A, tmpval);

  /* Configure Click Window */
  tmpval = 0x32;
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_TIME_WINDOW_A, tmpval);
}

/**
  * @brief  Click interrupt disable
  * @param  ITClick: the selected click interrupt to disable
  * @retval None
  */
void LSM303DLHC_AccClickITDisable(uint8_t ITClick)
{
  uint8_t tmpval = 0x00;

  /* Read CLICK_CFR register */
  tmpval = Accel_IO_Read(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A);

  /* Disable the selected interrupt */
  tmpval &= ~ITClick;

  /* Write value to MEMS CLICK_CFR register */
  Accel_IO_Write(ACC_I2C_ADDRESS, LSM303DLHC_CLICK_CFG_A, tmpval);
}

/**
  * @brief  Click on Z axis interrupt config
  * @param  None
  * @retval None
  */
void LSM303DLHC_AccZClickITConfig(void)
{
  /* Configure low level IT config */
  Accel_IO_ITConfig();

  /* Select click IT as INT1 interrupt */
  LSM303DLHC_AccIT1Enable(LSM303DLHC_IT1_CLICK);

  /* Enable High pass filter for click IT */
  LSM303DLHC_AccFilterClickCmd(LSM303DLHC_HPF_CLICK_ENABLE);

  /* Enable simple click IT on Z axis, */
  LSM303DLHC_AccClickITEnable(LSM303DLHC_Z_SINGLE_CLICK);
}

/**
  * @}
  */
static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t value = 0;
	status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
	if(status != HAL_OK) Error();
	return value;
}
//--------------------------------------------
static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
	HAL_StatusTypeDef status = HAL_OK;
	status = HAL_I2C_Mem_Write(&hi2c1, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x10000);
	if(status != HAL_OK) Error();
}
//--------------------------------------------
uint8_t Accel_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr)
{
	return I2Cx_ReadData(DeviceAddr, RegisterAddr);
}
//--------------------------------------------
void Accel_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr, uint8_t Value)
{
	I2Cx_WriteData(DeviceAddr, RegisterAddr, Value);
}
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
