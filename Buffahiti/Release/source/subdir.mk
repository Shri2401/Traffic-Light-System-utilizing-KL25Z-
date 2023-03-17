################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LEDs.c \
../source/Systick.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/states.c \
../source/switch.c \
../source/touch.c 

C_DEPS += \
./source/LEDs.d \
./source/Systick.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/states.d \
./source/switch.d \
./source/touch.d 

OBJS += \
./source/LEDs.o \
./source/Systick.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/states.o \
./source/switch.o \
./source/touch.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti\board" -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti\source" -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti" -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti\drivers" -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti\CMSIS" -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti\utilities" -I"C:\Users\itssh\Downloads\Buffahiti\Buffahiti\startup" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LEDs.d ./source/LEDs.o ./source/Systick.d ./source/Systick.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/states.d ./source/states.o ./source/switch.d ./source/switch.o ./source/touch.d ./source/touch.o

.PHONY: clean-source

