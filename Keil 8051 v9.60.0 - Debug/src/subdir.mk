################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
A51_UPPER_SRCS += \
C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 

C_SRCS += \
../src/I2C.c \
../src/VL53L0X.c \
../src/ranging_sensor_main.c \
../src/system_init.c \
../src/timer.c 

OBJS += \
./src/I2C.OBJ \
./src/SILABS_STARTUP.OBJ \
./src/VL53L0X.OBJ \
./src/ranging_sensor_main.OBJ \
./src/system_init.OBJ \
./src/timer.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/I2C.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/I2C.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/SILABS_STARTUP.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/SILABS_STARTUP.A51 src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Assembler'
	AX51 "@$(patsubst %.OBJ,%.__ia,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/VL53L0X.OBJ: C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/VL53L0X.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/I2C.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/timer.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/ranging_sensor_main.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/system_init.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/timer.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/I2C.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/VL53L0X.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/system_init.OBJ: C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/system_init.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h

src/timer.OBJ: C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Register_Enums.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/system_init.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/I2C.h C:/Users/User/Desktop/Laser_ranging/ranging_sensor/inc/timer.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/C8051F380/inc/SI_C8051F380_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.3.1/Device/shared/si8051Base/stdbool.h


