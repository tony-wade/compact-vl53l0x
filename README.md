## About
A compact VL53L0X time-of-flight ranging library refactored from the official API into lightweight, function-driven code. Designed for easy integration with resource-constrained MCUs, demonstrated on C8051F380.



## How to use

1. Implement your own `I2C_WriteDevice()` and `I2C_ReadDevice()` in **I2C.c** to match your MCU platform.  
2. Modify the VL53L0X core functions in **VL53L0X.h / VL53L0X.c** if necessary (see comments in code).  
3. For advanced features or detailed reference, please refer to the official VL53L0X API library (STSW-IMG005).



### This project is based in part on code from:
- MarcelMG - VL53L0X-STM32F103
- VL53L0X library by Pololu Corporation (MIT License)
- VL53L0X API by STMicroelectronics (BSD-style License)
