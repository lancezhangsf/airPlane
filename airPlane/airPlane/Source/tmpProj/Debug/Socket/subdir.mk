################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket/fileoperator.cpp \
../Socket/socket.cpp 

O_SRCS += \
../Socket/client.o \
../Socket/clientsocket.o 

OBJS += \
./Socket/fileoperator.o \
./Socket/socket.o 

CPP_DEPS += \
./Socket/fileoperator.d \
./Socket/socket.d 


# Each subdirectory must supply rules for building sources it contributes
Socket/%.o: ../Socket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


