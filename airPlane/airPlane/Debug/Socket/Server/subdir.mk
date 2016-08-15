################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket/Server/server.cpp \
../Socket/Server/serversocket.cpp 

OBJS += \
./Socket/Server/server.o \
./Socket/Server/serversocket.o 

CPP_DEPS += \
./Socket/Server/server.d \
./Socket/Server/serversocket.d 


# Each subdirectory must supply rules for building sources it contributes
Socket/Server/%.o: ../Socket/Server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


