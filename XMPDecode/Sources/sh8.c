//
//                            Embedded Experts (PTY) LTD
//                       sh8.c - a library of useful standard SH8 peripheral functions
//                                  Update: 30 November 2014
//
//
//
//
//
//--------------------------------------------------------------------------------------------------------------------------------------------

#include "derivative.h"
#include "sh8.h"
#include "bool_types.h"

// Name: ICS_FEI_20M
// Function: A clone of a processor expert bean to configure the FLL for 20MHz core clock
// Arguments: void
// Returns: void
//-----------------------------------------------------------------------------------------
void ICS_FEI_20M(void) 
{
          ICSC1_CLKS  = 0;
          ICSC1_IREFS = 1;
          ICSC1_RDIV  = 0;
          ICSC2_BDIV  = 0;
          ICSTRM      = 0x58;
}

// Name: ICS_FEE_4MM
// Function: Configure the FLL for 4MHz, using external resonator as a clock source
// Arguments: void
// Returns: void
//--------------------------------------------------------------------------------
void ICS_FEE_4M(void){

      // Copy TRIM value, if set
      if (*(unsigned char*)0xFFAF != 0xFF){
          ICSTRM = *(unsigned char*)0xFFAF;  
          ICSSC = *(unsigned char*)0xFFAE;   
      }
      // ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0
      ICSC1 = 0x06;
      // ICSC2: BDIV=2,RANGE=1,HGO=0,LP=0,EREFS=1,ERCLKEN=1,EREFSTEN=0 */
      ICSC2 = 0xA6;
      while(!ICSSC_IREFST){               
          ;
      }

}

// Name: InitRTI
// Function: Initialises and starts up the real-time interrupt (RTI
// Arguments: void
// Returns: void
//-----------------------------------------------------------------------------------------
void InitRTI(void){
          RTCSC = 0x18;                           // Configure RTC    0x13
          RTCMOD = 0x00;                          // Set modulo count     0x09
          RTCSC_RTIF = 1;               // Clear the interrupt...
          
}

// Name: ConfigCPU
// Function: Writes parameters to SOPT1 and SOPT2 registers to configure the overall CPU
// Arguments: COP Enable bit, COP Timeout period, STOP mode bit, IIC position, BDM enable, RESET enable
//            COP clock source, COP window operation, Analog comparator Enable, T1CH1 pin select, T1CH0 pin select
// Returns: void
//--------------------------------------------------------------------------------------
void ConfigCPU(unsigned char COPE, unsigned char COPT, unsigned char STPMODE, unsigned char I2CPOS, unsigned char BDME, unsigned char RTSE,
          unsigned char COPCLK, unsigned char COPWIN, unsigned char ACIC, unsigned char T1CH1PS, unsigned char T1CH0PS){
          unsigned char temp_sopt1 = 0;
          unsigned char temp_sopt2 = 0;

          
          // Process COP configuration bits
          //-------------------------------
          if (COPE == true){
                    COPT = COPT << 6;                       // Align the bits
                    COPT = COPT & 0xC0;                     // Mask off stuff we are not using
                    temp_sopt1 = temp_sopt1 | COPT;         // Insert bits                   
                    
          }
          
          // Process STOP mode enable bit
          //------------------------------
          if (STPMODE == true){
                    temp_sopt1 |= 0x20;
          }
          
          
          // Process I2C Pin selection
          //---------------------------
          if (I2CPOS == true){
                    temp_sopt1 |= 0x04;
          }
          
          // Process BDM pin selection
          //----------------------------
          if (BDME == true){
                    temp_sopt1 |= 0x02;
          }
          
          // Process RTSE
          //-------------
          if (RTSE == true){
                    temp_sopt1 |= 0x01;
          }
          
          //---------------------------------------------------------------------------------------------
          
          // Process COPCLK
          //---------------
          if (COPCLK == true){
                    temp_sopt2 |= 0x80;
          }
          
          if (COPWIN == true){
                    temp_sopt2 |= 0x40;
          }
          
          if (ACIC == true){
                    temp_sopt2 |= 0x20;
          }
          
          if (T1CH1PS == true){
                    temp_sopt2 |= 0x02;         
          }
          
          if (T1CH0PS == true){
                    temp_sopt2 |= 0x01;
          }
          
          
          SOPT1 = temp_sopt1;
          SOPT2 = temp_sopt2;
          
}


// I/O Port Setup Routines
//--------------------------------------------------------------------

void InitPTA(unsigned char Mask, unsigned char IOVal){
          PTAD = 0x00;                  	// initial reset of the port
          PTADD = Mask;                 	// initialize I/O pin directions
          PTAD = IOVal;                 	// initialise I/O port pin logic levels
}

void InitPTB(unsigned char Mask, unsigned char IOVal){
          PTBD = 0x00;                  	// initial reset of the port
          PTBDD = Mask;                 	// initialize I/O pin directions
          PTBD = IOVal;                 	// initialise I/O port pin logic levels
}

void InitPTC(unsigned char Mask, unsigned char IOVal){
          PTCD = 0x00;                  	// initial reset of the port
          PTCDD = Mask;                 	// initialize I/O pin directions
          PTCD = IOVal;                 	// initialise I/O port pin logic levels
}

// TPM Configuration routines
//-----------------------------------------------------------------------------------

void InitTPM1AsPWM(void){
  
        TPM1SC = 0x01;
        TPM1MOD = PWM_MODULUS;
        //TPM1MODH = 0x11;
        //TPM1MODL = 0x23;
        
        // Channel 0 is PWM out... 
        TPM1C0SC_MS0B = 1;
        TPM1C0SC_MS0A = 0;
        TPM1C0SC_ELS0B = 1;
        TPM1C0SC_ELS0A = 0;
        
        // Channel 1 is PWM out...
        TPM1C1SC_MS1B = 1;
        TPM1C1SC_MS1A = 0;
        TPM1C1SC_ELS1B = 1;
        TPM1C1SC_ELS1A = 0;
        
        // Enable timer and start PWM
        TPM1SC_CLKSA = 1;
        TPM1SC_CLKSB = 0;
        
        TPM1C0V = 0x00;
        TPM1C1V = 0x00;
        
  
  
}




