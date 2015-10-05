//
//
//                                      Embedded Experts (PTY) LTD
//                            Filename: serial_sh8.h
//                            Purpose: Header file for Serial Port Driver- SH8 edition 
//                            Date: 30 November 2014
//
//
//
//----------------------------------------------------------------------------------------------------------------------------------------
#ifndef _serial_sh8_h_
#define _serial_sh8_h_
                  //19716494
#define BUS_SPEED 21016483                        // Actual value our PLL outputs to the core
#define CONST (BUS_SPEED / 1000 /*ms*/ / 8 /* loop cycles*/ )	
#define BUSCLK_FREQ_KHZ                 21016L 
                                        //21016                                       
                                        
#define SCIBufferSize 8


// External, static or other variables
//--------------------------------------

extern unsigned char RxBuffer[SCIBufferSize];

extern unsigned int rxpointer;

// Function Prototypes
//---------------------

void InitSCI(unsigned int baudrate);
void TxChar (unsigned char asc_char);
char RxChar(void);
void RxSCI(void);

#endif