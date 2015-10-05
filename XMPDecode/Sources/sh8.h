//
//                            Embedded Experts (PTY) LTD
//                            Filename: sh8.h
//                            Header file for common functions for the SH family
//                            Revision: 30 November 2014
//
//                            * Added the macro for setting up the FLL into this library now its done forever...
//
//
//
//
//---------------------------------------------------------------------------------------------------------------------

#ifndef SH8_H
#define SH8_H

#define PWM_MODULUS 0x1123
// Function prototypes
//---------------------
void ICS_FEI_20M(void);
void ICS_FEE_4M(void);
void InitRTI(void);
void ConfigCPU(unsigned char COPE, unsigned char COPT, unsigned char STPMODE, unsigned char I2CPOS, unsigned char BDME, unsigned char RTSE,
          unsigned char COPCLK, unsigned char COPWIN, unsigned char ACIC, unsigned char T1CH1PS, unsigned char T1CH0PS);
void InitPTA(unsigned char Mask, unsigned char IOVal);
void InitPTB(unsigned char Mask, unsigned char IOVal);
void InitPTC(unsigned char Mask, unsigned char IOVal);
void InitTPM1AsPWM(void);


#endif