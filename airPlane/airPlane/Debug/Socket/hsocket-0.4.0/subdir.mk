################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Socket/hsocket-0.4.0/hsocket.cpp \
../Socket/hsocket-0.4.0/mangchi.cpp 

O_SRCS += \
../Socket/hsocket-0.4.0/libhsocket_a-hsocket.o \
../Socket/hsocket-0.4.0/mangchi-mangchi.o 

OBJS += \
./Socket/hsocket-0.4.0/hsocket.o \
./Socket/hsocket-0.4.0/mangchi.o 

CPP_DEPS += \
./Socket/hsocket-0.4.0/hsocket.d \
./Socket/hsocket-0.4.0/mangchi.d 


# Each subdirectory must supply rules for building sources it contributes
Socket/hsocket-0.4.0/%.o: ../Socket/hsocket-0.4.0/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


