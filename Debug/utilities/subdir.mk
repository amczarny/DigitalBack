################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

OBJS += \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 

C_DEPS += \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MIMXRT1021DAG5A -DCPU_MIMXRT1021DAG5A_cm7 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/drivers" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/xip" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/component/serial_manager" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/utilities" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/component/uart" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/component/lists" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/device" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/CMSIS" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/board" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/source" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/drivers" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/xip" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/component/serial_manager" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/utilities" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/component/uart" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/component/lists" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/CMSIS" -I"/home/amc/Documents/MCUXpresso_11.3.1_5262/workspace/MIMXRT1021_Project_DigitalBack/device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


