################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera/FlyCapture2Test.cpp \
../Camera/stdafx.cpp 

O_SRCS += \
../Camera/FlyCapture2Test.o \
../Camera/stdafx.o 

OBJS += \
./Camera/FlyCapture2Test.o \
./Camera/stdafx.o 

CPP_DEPS += \
./Camera/FlyCapture2Test.d \
./Camera/stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
Camera/%.o: ../Camera/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


