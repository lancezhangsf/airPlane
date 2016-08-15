################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cfgini/inifile.cpp \
../Cfgini/main.cpp 

O_SRCS += \
../Cfgini/inifile.o \
../Cfgini/main.o 

OBJS += \
./Cfgini/inifile.o \
./Cfgini/main.o 

CPP_DEPS += \
./Cfgini/inifile.d \
./Cfgini/main.d 


# Each subdirectory must supply rules for building sources it contributes
Cfgini/%.o: ../Cfgini/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


