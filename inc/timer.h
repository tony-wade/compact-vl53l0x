#ifndef TIMER_H_
#define TIMER_H_


//-----------------------------------------------------------------------------
// Types/Def
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void Timer1_Init(void);
void Timer2_Init(void);
void Timer3_Init(void);
void Init_Timers(void);

void Countdown_ms(uint8_t ms);
bool Timeout_CheckExpired(void);

#endif /* TIMER_H_ */
