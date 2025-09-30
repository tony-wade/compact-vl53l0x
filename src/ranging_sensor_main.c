
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_C8051F380_Register_Enums.h> // SFR declarations
#include "system_init.h"
#include "timer.h"
#include "I2C.h"
#include "VL53L0X.h"

// ----------------------------------------------------------------------------
// VL53L0X defines
// ----------------------------------------------------------------------------
// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

// #define LONG_RANGE

// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

#define HIGH_SPEED
// #define HIGH_ACCURACY

// io_2v8(2.6v~3.5v); address; io_timeout; did_timeout
xdata struct VL53L0X myTOFsensor = {true, 0x29, 500, false}; // 0x29<<1 = 0x52

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
void SiLabs_Startup(void)
{
  PCA0MD = 0x00; // Disable watch-dog timer
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void)
{

  OSCILLATOR_Init();
  Init_Timers();
  PORT_Init();
  I2C_Init();

  IE_EA = 1; // Global interrupt enable


  // I2C_WriteDevice(0x12,0x32,&test,2);   // test ok
  // I2C_ReadDevice(0x12,0x32,&test,2);   // test

  // Init
  if (VL53L0X_init(&myTOFsensor))
  {
    // USART1_transmitString("init successful\n");
  }
  else
  {
    // USART1_transmitString("init error");
    // return 0;
  }

#ifdef LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  VL53L0X_setSignalRateLimit(&myTOFsensor, 0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  VL53L0X_setVcselPulsePeriod(&myTOFsensor, VcselPeriodPreRange, 18);
  VL53L0X_setVcselPulsePeriod(&myTOFsensor, VcselPeriodFinalRange, 14);
#endif
#ifdef HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  VL53L0X_setMeasurementTimingBudget(&myTOFsensor, 20000);
  // USART1_transmitString("step1\n");
#else // HIGH_ACCURACY
  // increase timing budget to 200 ms
  VL53L0X_setMeasurementTimingBudget(&myTOFsensor, 200000);
#endif

  VL53L0X_startContinuous(&myTOFsensor, 0);

  while (1)
  {
    /*
   uint16_t value = VL53L0X_readRangeContinuousMillimeters (&myTOFsensor);
   //sprintf(strbuf, "\t%d\tmm\n", value);
   //USART1_transmitString(strbuf);
   if (VL53L0X_timeoutOccurred (&myTOFsensor))
   {
       //USART1_transmitString ("TIMEOUT\n");
   }*/

    // Check if the switch is pressed and I2C is not busy
    if (SW == 0)
    {
      // Simple debounce
      while (i2c_busy != 0)
      {
      }

      if (i2c_busy == 0)
      {
        VL53L0X_readRangeSingleMillimeters(&myTOFsensor);   // return range
      }
    }
  }
}
