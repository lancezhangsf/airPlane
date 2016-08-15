################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Gps/SerialPort.cpp \
../Gps/gps.cpp \
../Gps/maingps.cpp 

O_SRCS += \
../Gps/SerialPort.o \
../Gps/gps.o \
../Gps/maingps.o 

OBJS += \
./Gps/SerialPort.o \
./Gps/gps.o \
./Gps/maingps.o 

CPP_DEPS += \
./Gps/SerialPort.d \
./Gps/gps.d \
./Gps/maingps.d 


# Each subdirectory must supply rules for building sources it contributes
Gps/%.o: ../Gps/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


