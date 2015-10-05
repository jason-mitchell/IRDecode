//
//                  Embedded Experts (PTY) LTD
//	     	Filename: timer.c
//		Purpose: Timer Library
//	     	Author: Sonic2k
//		Date: 30/04/2014
//
//
//		Revision History:
//		-----------------
//                  30-04-2013: Standalone library (no dependencies)
//
//
//--------------------------------------------------------------------------------------------------------------
#define CODEWARRIOR

#ifdef CODEWARRIOR
         #include "derivative.h"   
#endif
         
#include "timer.h"

// Variables
//----------
unsigned int TIMER_PRESCALE;
unsigned int TIMER_COUNTER;

// Name: TimerTask
// Function: The actual timer instantiation, to be called in the ISR
//-------------------------------------------------------------------
void TimerTask(void){

          // Process main timer
          if (TIMER_COUNTER > 0){
                    TIMER_COUNTER--;
          }
}


// Name: InitTimer
// Function: Initialisation function, used to reset all the variables and flags
//------------------------------------------------------------------------------
void InitTimer(void){
          TIMER_COUNTER = 0;
          TIMER_PRESCALE = 0;        
          
          
          
}

// Name: Timer
// Function: General-purpose time delay (blocking function)
// Arguments: Time delay in 10ms increments i.e. 100 = 0.01 x 100 = 1s
// Returns: void
//------------------------------------------------------------------------
void Timer (unsigned int delay){
          TIMER_COUNTER = delay;                  // copy time value over
          while (TIMER_COUNTER > 0){
                    ;
          }   
                                     
}