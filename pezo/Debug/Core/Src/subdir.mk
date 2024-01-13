################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GSM_A6_Driver_STM32F407.c \
../Core/Src/fonts.c \
../Core/Src/lsm303dlhc.c \
../Core/Src/main.c \
../Core/Src/st7735.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/usb_device.c \
../Core/Src/usbd_cdc.c \
../Core/Src/usbd_cdc_if.c \
../Core/Src/usbd_conf.c \
../Core/Src/usbd_core.c \
../Core/Src/usbd_ctlreq.c \
../Core/Src/usbd_desc.c \
../Core/Src/usbd_ioreq.c 

OBJS += \
./Core/Src/GSM_A6_Driver_STM32F407.o \
./Core/Src/fonts.o \
./Core/Src/lsm303dlhc.o \
./Core/Src/main.o \
./Core/Src/st7735.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/usb_device.o \
./Core/Src/usbd_cdc.o \
./Core/Src/usbd_cdc_if.o \
./Core/Src/usbd_conf.o \
./Core/Src/usbd_core.o \
./Core/Src/usbd_ctlreq.o \
./Core/Src/usbd_desc.o \
./Core/Src/usbd_ioreq.o 

C_DEPS += \
./Core/Src/GSM_A6_Driver_STM32F407.d \
./Core/Src/fonts.d \
./Core/Src/lsm303dlhc.d \
./Core/Src/main.d \
./Core/Src/st7735.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/usb_device.d \
./Core/Src/usbd_cdc.d \
./Core/Src/usbd_cdc_if.d \
./Core/Src/usbd_conf.d \
./Core/Src/usbd_core.d \
./Core/Src/usbd_ctlreq.d \
./Core/Src/usbd_desc.d \
./Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/stm32f103_pezodatchik/pezo/Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/GSM_A6_Driver_STM32F407.d ./Core/Src/GSM_A6_Driver_STM32F407.o ./Core/Src/GSM_A6_Driver_STM32F407.su ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/lsm303dlhc.d ./Core/Src/lsm303dlhc.o ./Core/Src/lsm303dlhc.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/st7735.d ./Core/Src/st7735.o ./Core/Src/st7735.su ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/usb_device.d ./Core/Src/usb_device.o ./Core/Src/usb_device.su ./Core/Src/usbd_cdc.d ./Core/Src/usbd_cdc.o ./Core/Src/usbd_cdc.su ./Core/Src/usbd_cdc_if.d ./Core/Src/usbd_cdc_if.o ./Core/Src/usbd_cdc_if.su ./Core/Src/usbd_conf.d ./Core/Src/usbd_conf.o ./Core/Src/usbd_conf.su ./Core/Src/usbd_core.d ./Core/Src/usbd_core.o ./Core/Src/usbd_core.su ./Core/Src/usbd_ctlreq.d ./Core/Src/usbd_ctlreq.o ./Core/Src/usbd_ctlreq.su ./Core/Src/usbd_desc.d ./Core/Src/usbd_desc.o ./Core/Src/usbd_desc.su ./Core/Src/usbd_ioreq.d ./Core/Src/usbd_ioreq.o ./Core/Src/usbd_ioreq.su

.PHONY: clean-Core-2f-Src

