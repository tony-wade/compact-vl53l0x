#include <SI_C8051F380_Register_Enums.h>                // SFR declarations
#include "system_init.h"
#include "I2C.h"
#include "timer.h"

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
bool timer2_done = 0;


/* Oscillator Initialization is in system_init.h */
//-----------------------------------------------------------------------------
// Timer Initialization
//-----------------------------------------------------------------------------
void Init_Timers(void)
{
  Timer1_Init();
  Timer2_Init();
  Timer3_Init();
}


// - Timer1 used as I2C/SMBus clock source. The maximum SCL frequency will be
//   approximately 1/3 the Timer1 overflow rate
void Timer1_Init(void) {
#if ((SYSCLK/I2C_CLOCK/3) < 255)
   #define SCALE 1
      CKCON |= 0x08;                   // Timer1 clock source = SYSCLK
#elif ((SYSCLK/I2C_CLOCK/4/3) < 255)
   #define SCALE 4
      CKCON |= 0x01;
      CKCON &= ~0x0A;                  // Timer1 clock source = SYSCLK / 4
#elif ((SYSCLK/I2C_CLOCK/12/3) < 255)
   #define SCALE 8
      CKCON &= ~0x0B;                  // Timer1 clock source = SYSCLK / 12
#elif ((SYSCLK/I2C_CLOCK/48/3) < 255)
   #define SCALE 4
      CKCON |= 0x02;
      CKCON &= ~0x09;                  // Timer1 clock source = SYSCLK / 48
#else
   #error "Error: Timer1 cannot produce the desired SMBus frequency"
#endif

   TMOD = 0x20;                        // Timer1 in 8-bit auto-reload mode

   // reload value
   TH1 = -(SYSCLK/I2C_CLOCK/SCALE/3);
   TL1 = TH1;                          // Init Timer1

   TCON_TR1 = 1;                       // Timer1 enabled
}

// General micro-second counter
void Timer2_Init (void)
{
  TMR2CN = 0x00;
  TMR2CN_T2XCLK = 0;  //  Timer2 clock source = SYSCLK/12 = 1MHz

  IE_ET2 = 1;   // Timer2 interrupt enable
}


// -Timer3 configured for use by the SMBus low timeout detect
void Timer3_Init (void)
{
   TMR3CN = 0x00;                      // Timer3 configured for 16-bit auto-
                                       // reload, low-byte interrupt disabled

   CKCON &= ~0x40;                     // Timer3 uses SYSCLK/12

   TMR3RL = (uint16_t) -(SYSCLK/12/40);  // Timer3 configured to overflow after
   TMR3 = TMR3RL;                      // ~25ms (for SMBus low timeout detect):
                                       // 1/.025 = 40

   EIE1 |= 0x80;                       // Timer3 interrupt enable
   TMR3CN |= 0x04;                     // Start Timer3
}

//-----------------------------------------------------------------------------
// Countdown function
//-----------------------------------------------------------------------------
// 1 time counter, Timer2 clk = 1MHz
void Countdown_ms(uint8_t ms)
{
  uint16_t us = ms * 1000;

  if (us > 65535){us = 65535;}  // max value
  TMR2RL = (uint16_t) -us;  // set reload value

  timer2_done = 0;  //reset flag
  TMR2CN_TR2 = 1;  // Start Timer2
}

bool Timeout_CheckExpired(void)
{
  return timer2_done;
}

//-----------------------------------------------------------------------------
// ISR is unique so can't be in .h
//-----------------------------------------------------------------------------
// -Times-up
SI_INTERRUPT(TIMER2_ISR, TIMER2_IRQn)
{
  timer2_done = 1;

  TMR2CN &= ~0xC4;  // clear interrupt flags,
                    // stop timer2 from reload
}



// -Timeout
SI_INTERRUPT(TIMER3_ISR, TIMER3_IRQn)
{
   SMB0CF &= ~0x80;                    // Disable SMBus
   SMB0CF |= 0x80;                     // Re-enable SMBus
   TMR3CN &= ~0x80;                    // Clear Timer3 interrupt-pending flag
   SMB0CN_STA = 0;
   i2c_busy = 0;                       // Free SMBus/I2C
}

