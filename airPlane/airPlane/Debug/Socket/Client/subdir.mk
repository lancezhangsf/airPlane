################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket/Client/client.cpp \
../Socket/Client/clientsocket.cpp 

OBJS += \
./Socket/Client/client.o \
./Socket/Client/clientsocket.o 

CPP_DEPS += \
./Socket/Client/client.d \
./Socket/Client/clientsocket.d 


# Each subdirectory must supply rules for building sources it contributes
Socket/Client/%.o: ../Socket/Client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


