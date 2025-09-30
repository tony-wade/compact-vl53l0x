#ifndef SYSTEM_INIT_H_
#define SYSTEM_INIT_H_

#include <SI_C8051F380_Register_Enums.h>

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define I2C_CLOCK 100000 // I2C clock (100kHz)
#define SYSCLK 12000000  // System clock frequency in Hz

//-----------------------------------------------------------------------------
// GPIO Setting
//-----------------------------------------------------------------------------
SI_SBIT(SDA, SFR_P0, 0); // I2C/SMBus on P0.0
SI_SBIT(SCL, SFR_P0, 1); // and P0.1

// XSHUT與Standby mode有關，開機拉高就好

SI_SBIT(SW, SFR_P2, 0); // P2.0 as SWitch (Silicon Labs macro)

//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void PORT_Init(void);
void I2C_Init(void);
void OSCILLATOR_Init(void);

#endif /* SYSTEM_INIT_H_ */
