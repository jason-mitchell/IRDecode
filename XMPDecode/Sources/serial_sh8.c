//       
//                                 Embedded Experts (PTY) LTD
//                  Filename: serial_sh8.c
//                  Description: MC9S08SH8 Serial Port Routines
//
//
//                  Author: Sonic2k
//                  Version: 1.0
//                  Date: 30 November 2014
//
//
//
//
//------------------------------------------------------------------------------------------------------------------------------------

#include "derivative.h" 		
#include "serial_sh8.h"

#define character_echo                            // Use this define to enable character echo to terminal on AT i/f

unsigned char temp1;
unsigned int rxpointer;
unsigned char RxBuffer[SCIBufferSize];


// Name: InitSCI
// Function: Initialise and enable serial port (SCI)
//------------------------------------------------------
void InitSCI(unsigned int baudrate){

          unsigned char temp;
	SCIBD = (unsigned int)((BUSCLK_FREQ_KHZ * 10) / (16 * (baudrate/100))) + 1;            // At high baudrates, the +1 roundoff is necessary!
          SCIC1 = 0x08;
          SCIC2 = 0x2C;
          SCIS2 = 0x00;
          SCIC3 = 0x00;
          temp = SCIS1;      /* Dummy read */
          rxpointer = 0;
		
}

// Name: TxChar
// Function: Transmit specified byte on SCI
// Parameters: Byte to be transmitted
//-----------------------------------------------------
void TxChar (unsigned char asc_char){
          while(SCIS1_TDRE == 0x00);
          while (SCIS1_TC == 0x00);
          SCID = asc_char;                                 /* Xmitr ready, send byte */
          
}

// Name: RxChar
// Function: Get a character from the serial port when using it as a console
//           This is used to make getch() in C work with a terminal emulator connected to the serial port
//-------------------------------------------------------------------------------------------------------
char RxChar(void){
          char rxcc = 0;
          if (rxpointer > 0){
                    // We have valid characters....
                    rxcc = RxBuffer[0];
                    rxpointer = 0;
                    
          }                   
          return rxcc;         
}
// Interrupt Handlers
//--------------------

// Receive Interrupt Handler for SCI
// Each character is stored in a linear buffer
//-------------------------------------------------
void RxSCI(void){
           if ((SCIS1 & SCIS1_RDRF_MASK) == SCIS1_RDRF_MASK){
                    if (rxpointer < SCIBufferSize){
                              RxBuffer[rxpointer] = SCID;
                              #ifdef character_echo
                              TxChar(RxBuffer[rxpointer]);
                              #endif
                              rxpointer++;
                    } else {
                              temp1 = SCID;                 // Discard the data, buffer is in overflowed state   **FIXES BUG FOUND 22/05/13
                    }
           }          
          
          
}
