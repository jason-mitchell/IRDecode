//                            
//                            Embbeded Experts (PTY) LTD
//                            Filename: timer.h
//                            Author: Sonic2k
//                            Purpose: Header file for the timer library
//
//                            Revision History
//                            ----------------
//                               30-03-14: New version that uses TimerTask()
//
//
//-------------------------------------------------------------------------------------------------------------
#ifndef _decode_h
#define _decode_h

// Definitions
//-------------

#define POWER_BUTTON 0x3FC639C0   // See documentation for button code
#define VOL_UP 0x3FC857A0
#define VOL_DWN 0x3FC87780
#define PGM_UP 0x3FC89760
#define PGM_DN 0x3FC8B740

// External, static or other variables
//--------------------------------------




// Function Prototypes
//---------------------
void InitDecode(void);
void DecodeToOutputsC(unsigned long code);
void DecodeToOutputs(unsigned long code);




#endif