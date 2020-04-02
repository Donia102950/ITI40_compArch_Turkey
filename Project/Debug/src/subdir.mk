################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DSYSTICK.c \
../src/GPIO_program.c \
../src/HLCD.c \
../src/HLCD_config.c \
../src/HLED.c \
../src/HSwitch_Config.c \
../src/HSwitch_program.c \
../src/NVIC_Program.c \
../src/RCC_program.c \
../src/Sched.c \
../src/Sched_config.c \
../src/UARTHandler_program.c \
../src/UART_program.c \
../src/_write.c \
../src/main.c 

OBJS += \
./src/DSYSTICK.o \
./src/GPIO_program.o \
./src/HLCD.o \
./src/HLCD_config.o \
./src/HLED.o \
./src/HSwitch_Config.o \
./src/HSwitch_program.o \
./src/NVIC_Program.o \
./src/RCC_program.o \
./src/Sched.o \
./src/Sched_config.o \
./src/UARTHandler_program.o \
./src/UART_program.o \
./src/_write.o \
./src/main.o 

C_DEPS += \
./src/DSYSTICK.d \
./src/GPIO_program.d \
./src/HLCD.d \
./src/HLCD_config.d \
./src/HLED.d \
./src/HSwitch_Config.d \
./src/HSwitch_program.d \
./src/NVIC_Program.d \
./src/RCC_program.d \
./src/Sched.d \
./src/Sched_config.d \
./src/UARTHandler_program.d \
./src/UART_program.d \
./src/_write.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


