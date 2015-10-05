//----------------------------------------------------------------------------------------------------------------
//
//        Filename: termio.c
//        by s0nic2k for Freescale Codewarrior For Microcontrollers v6.x
//
//        Copyright (C) 2013 - Jason Mitchell (s0nic2k)
//
//        This library is free software; you can redistribute it and/or
//        modify it under the terms of the GNU Lesser General Public
//        License as published by the Free Software Foundation; either
//        version 2.1 of the License, or (at your option) any later version.
//
//        This library is distributed in the hope that it will be useful,
//        but WITHOUT ANY WARRANTY; without even the implied warranty of
//        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//        Lesser General Public License for more details.
//
//        You should have received a copy of the GNU Lesser General Public
//        License along with this library; if not, write to the Free Software
//        Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//        Freescale make really good silicon- help leverage this platform to the Open Source community
//        by helping to develop open source tools for these great microcontrollers and liberate developers
//        from expensive, shitty and proprietary CodeWarrior tools.
//
//        This code is adapted from the REALLY SHITTY version that ships with that pathetic Codewarrior toolchain.
//        In this way, the PutChar() stuff can be redirected to things such as LCD displays and devices, even
//        if they are bit-banged aka provide yer own drivers!
//
//
//
//        Dependencies:
//                     ansifs.lib
//                     stdio.h
//
//
//----------------------------------------------------------------------------------------------------------------

#include <hidef.h>
#include <termio.h>
#include "serial_sh8.h"     // This is to be included here because debug implements a virtual UART i.e. its bit-banged on I/O pins
                       // feel free to do your own thing there, even if it is a hedgehog-to-Eggman obfuscator!


// These things are required for HIWAVE- which shall change when we can build an open-source BDM
// These affect how the linker lays out things in memory, which, if messed with, will cause HIWAVE to give problems
//------------------------------------------------------------------------------------------------------------------
#ifdef __ELF_OBJECT_FILE_FORMAT__
          #define HIWAVE  1                       /* only HI-WAVE can handle ELF/Dwarf object files */
#elif defined(__H8_500__)
  #define HIWAVE  0                               /* H8/500 simulator not available in HI-WAVE yet and never will be */
#elif defined(__MWERKS__) && !defined(__HIWARE__)
          #define HIWAVE  0                       /* LT not applicable for CW */
#else
          #define HIWAVE  1                       /* set to one for HI-WAVE, to zero for HI-CROSS Simulators/Debuggers */
#endif


#if defined(__HC16__) && (defined(__SMALL__) || defined(__MEDIUM__))
  /* NOTE: For the HC16 CPU, this module must be compiled with command line
           option "-Cp0" telling the compiler that the data page will be page 0,
           thus enabling it to generate efficient access code for the on-chip
           I/O. */
  #pragma OPTION ADD "-Cp0"       // force the option even if not set in the compiler settings dialog.
#endif



//-------------------------------------------------------------------------------------------------------------
// Here we start with a decent implementation
//-------------------------------------------------------------------------------------------------------------

// Name: TERMIO_GetChar(void)
// Function: Standard C function implementation for reading characters from the terminal
//----------------------------------------------------------------------------------------
char TERMIO_GetChar(void) {
          char ch;
          
          //ch = 'Z';
         
          // Put your code here that gets data from your serial or other device
          ch = RxChar();         
  
  return ch;
}


// Name: TERMIO_PutChar(char ch)
// Function: Standard C function implementation for sending characters to the terminal
//-------------------------------------------------------------------------------------
void TERMIO_PutChar(char ch) {

          // Put your code here that calls directly to your drivers...
          TxChar(ch);

}

// Name: TERMIO_Init(void)
// Function: Standard C function to initialize the communication channel
//-------------------------------------------------------------------------
void TERMIO_Init(void) {
  
  // You can put your code here to initialise the UART of choice, or leave it empty and unused
  // Personally I prefer to use init functions in my own code so that all that changes is the drivers, NOT these
  // files.
  
  

}


