//----------------------------------------------------------------------------------------------------------------
//
//        Filename: termio.h
//              HEADER FILE FOR termio.c
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
//
//
//----------------------------------------------------------------------------------------------------------------

#ifndef TERMIO_H
#define TERMIO_H

#ifdef __cplusplus
extern "C" {
#endif


// Function Prototypes
//---------------------
void TERMIO_PutChar(char ch);
char TERMIO_GetChar(void);
void TERMIO_Init(void);

// Optimizations...
//------------------
#ifdef _TERMIO_HAS_PUT_STRING_
          void TERMIO_PutString(const char *p);
#endif

#ifdef __cplusplus
}
#endif

#endif

