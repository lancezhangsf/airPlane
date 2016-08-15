################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket/hsocket-0.4.0/code/Client.cpp \
../Socket/hsocket-0.4.0/code/Server.cpp \
../Socket/hsocket-0.4.0/code/hsocket.cpp 

O_SRCS += \
../Socket/hsocket-0.4.0/code/Client.o \
../Socket/hsocket-0.4.0/code/hsocket.o 

OBJS += \
./Socket/hsocket-0.4.0/code/Client.o \
./Socket/hsocket-0.4.0/code/Server.o \
./Socket/hsocket-0.4.0/code/hsocket.o 

CPP_DEPS += \
./Socket/hsocket-0.4.0/code/Client.d \
./Socket/hsocket-0.4.0/code/Server.d \
./Socket/hsocket-0.4.0/code/hsocket.d 


# Each subdirectory must supply rules for building sources it contributes
Socket/hsocket-0.4.0/code/%.o: ../Socket/hsocket-0.4.0/code/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


