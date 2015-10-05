//
//                            Embedded Experts (PTY) LTD
//                       decode.c - Code to drive decoded outputs from the remote
//                       There are currently three decoded channels from these remote control
//                       buttons:
//                         ON/OFF
//                         P+ and P+
//                         V+ and V-
//
//
//
//
//
//--------------------------------------------------------------------------------------------------------------------------------------------
#include "bsp.h"
#include "derivative.h"
#include "sh8.h"
#include "bool_types.h"
#include "decode.h"


unsigned int PWM0;
unsigned int PWM1;



// Name: InitDecode
// Function: Initialise decode signal states
// Parameters: void
// Returns: void
//------------------------------------------------------------------------
void InitDecode(void){
  
    POWER = 0;  
    PWM0 = 0;
    PWM1 = 0;
  
}

// Name: DecodeToOutputsC
// Function: Decode remote control button to physically mapped output constantly
// Parameter: remote button code
// Returns: void
//--------------------------------------------------------------------------------
void DecodeToOutputsC(unsigned long code){
  
      if (code == VOL_UP){
          PWM0 += 100;
          if (PWM0 > PWM_MODULUS){
            PWM0 = PWM_MODULUS;
          }
        
      }
      if (code == VOL_DWN){
        PWM0 -= 100;
        if (PWM0 > PWM_MODULUS + 10){
          PWM0 = 0;
        }
      }
      
      
      if (code == PGM_UP){
          PWM1 += 100;
          if (PWM1 > PWM_MODULUS){
            PWM1 = PWM_MODULUS;
          }
        
      }
      if (code == PGM_DN){
        PWM1 -= 100;
        if (PWM1 > PWM_MODULUS + 10){
          PWM1 = 0;
        }
      }
      
      // Update the PWM channels
      TPM1C0V = PWM0;
      TPM1C1V = PWM1;  
  
  
}


// Name: DecodeToOutputs
// Function: Decode remote control button to physically mapped output in a single-shot
// Parameter: remote button code
// Returns: void
//-------------------------------------------------------------------------
void DecodeToOutputs(unsigned long code){

      if(code == POWER_BUTTON){
        POWER = ~POWER;
  
      }
      
}