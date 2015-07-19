################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ConfigurationManager.cpp \
../LocalizationManager.cpp \
../Manager.cpp \
../Map.cpp \
../Node.cpp \
../Particle.cpp \
../PathPlanner.cpp \
../Robot.cpp \
../WaypointsManager.cpp \
../lodepng.cpp \
../main.cpp \
../pngUtil.cpp 

OBJS += \
./ConfigurationManager.o \
./LocalizationManager.o \
./Manager.o \
./Map.o \
./Node.o \
./Particle.o \
./PathPlanner.o \
./Robot.o \
./WaypointsManager.o \
./lodepng.o \
./main.o \
./pngUtil.o 

CPP_DEPS += \
./ConfigurationManager.d \
./LocalizationManager.d \
./Manager.d \
./Map.d \
./Node.d \
./Particle.d \
./PathPlanner.d \
./Robot.d \
./WaypointsManager.d \
./lodepng.d \
./main.d \
./pngUtil.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/player-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


