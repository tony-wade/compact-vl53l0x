#include "system_init.h"

// ----------------------------------------------------------------------------
// Port Initialization
// ----------------------------------------------------------------------------
void PORT_Init(void)
{
   P0MDOUT = 0x08; // All P0 pins open-drain output
                   // (GPIO) is for interrupt mode

   XBR0 = 0x04; // Enable SMBus pins
   XBR1 = 0x40; // Enable crossbar and weak pull-ups

   P0 = 0xFF; // init high
}

//-----------------------------------------------------------------------------
// I2C/SMBus Initialization
//-----------------------------------------------------------------------------
void I2C_Init(void)
{
   SMB0CF = 0x5D; // Use Timer1 overflows as SMBus clock
                  // source;
                  // Disable slave mode;
                  // Enable setup & hold time
                  // extensions;
                  // Enable SMBus Free timeout detect;
                  // Enable SCL low timeout detect;

   // SMB0CF &= ~0x02;                    // test-only, disable Free timeout detect

   SMB0CF |= 0x80; // Enable SMBus;

   EIE1 |= 0x01; // Enable the SMBus interrupt
   EIP1 |= 0x01; // make the SMBus interrupt high
                 // priority
}

//-----------------------------------------------------------------------------
// Oscillator Initialization
//-----------------------------------------------------------------------------
void OSCILLATOR_Init(void)
{
   OSCICN = 0x83; // Internal oscillator = 12 MHz
}
