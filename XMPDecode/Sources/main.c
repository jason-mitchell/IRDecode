//--------------------------------------------------------------------------------
//
//              Project: XMPDecode
//              Decoding of UEI XMP Protocol IR handsets
//
//
//--------------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Headers
//-----------------------------------------------------------------------------

#include <hidef.h>
#include <stdio.h>
#include "derivative.h"
#include "bool_types.h"
#include "bsp.h"
#include "sh8.h"
#include "timer.h"
#include "serial_sh8.h"
#include "decode.h"

unsigned char pulse_time;
unsigned int pulse_width;
unsigned long rx_stream;
unsigned long rx_stream_previous;
unsigned char a;
unsigned char b;
unsigned char array[4];
unsigned int keytimer;

// Function prototypes
void SendPacket(unsigned char *data);

//--------------------------------------------------------------
// Name: ReadStrappings
// Function: Read state of two external pins and return a code
// Parameters: void
// Returns: 0 ~ 3
//--------------------------------------------------------------
unsigned char ReadStrappings(void){

    if(STRAP0 == 0 && STRAP1 == 0){
        return 0;
    }
    
    if(STRAP0 == 1 && STRAP1 == 0){
        return 1;
    }

    if(STRAP0 == 0 && STRAP1 == 1){
        return 2;
    }

    if(STRAP0 == 1 && STRAP1 == 1){
        return 3;
    }
  
  
}


//---------------------------------
// Initialisation function
//---------------------------------
void InitIR(void){
  
    keytimer = 0; 
    rx_stream = 0;
    rx_stream_previous = 0; 
  
}     

//-------------------------------------------------------------
// Name: SendPressPacket
// Function: Sends IR key pressed packet containing key code
// Parameters: Key code (32 bits)
// Returns: void
//-------------------------------------------------------------
void SendPressPacket(unsigned long code){

        array[0] = *(((char *)&code)+0);
        array[1] = *(((char *)&code)+1);
        array[2] = *(((char *)&code)+2);
        array[3] = *(((char *)&code)+3);
        
        if(ReadStrappings() == 0){
            SendPacket(array);
        }
        
        if(ReadStrappings() == 1){
            (void)printf("MAK_%02X%02X%02X%02X\r\n", array[0], array[1], array[2], array[3]);
        }
  
  
  
}
//-----------------------------------------------------
// Name: SendReleasePacket
// Function: Sends IR key released packet
// Parameters: none
// Returns: void
//-----------------------------------------------------
void SendReleasePacket(void){
  
      if(ReadStrappings() == 0){
          SendPacket("\xFF\xFF\xFF\xFF"); 
      }
      
      if (ReadStrappings() == 1){
          (void)printf("BRK\r\n");  
      }
  
}

//-----------------------------------------------------
// Key timing function - called in a timer interrupt
//-----------------------------------------------------
void KeyTiming(void){
  
      if (keytimer > 0){
            keytimer--;
            if (keytimer == 0){
              rx_stream_previous = 0;
              IR_VALID = 0;
              SendReleasePacket();
            }
      }
}

//-----------------------------------------------------------
//   RC Code validation - validate address and data field
//-----------------------------------------------------------
unsigned char Validate(void){

  
    // Validate the code received
    a = *(((char *)&rx_stream)+0);
    b = *(((char *)&rx_stream)+1);
    a = a & 0xF0;
    b = ~b;
    b = b & 0xF0;
    
    if (a == b){
        // Address is validated, check command
            a = *(((char *)&rx_stream)+2);
            b = *(((char *)&rx_stream)+3);
            a = a & 0xF0;
            b = ~b;
            b = b & 0xF0;
            if (a == b){
              return 0;
            } else {
              return 0x01;
            }
    } else {
      return 0x01;
    }  
}

//---------------------------------
//   Demodulation function
//---------------------------------
void Demodulate(void){
      unsigned char bitcount;
      rx_stream = 0;
      // Wait for falling edge of start
      while(IR_IN == 1){
        ;
      }
      
      // Falling edge has occured
      pulse_time = 0;
      
      // Wait for it to rise again
      while(IR_IN == 0){
        ;
      }
      // Signal has returned to 1- check the time we captured
      if (pulse_time > 7){
          // Leading pulse was good... we can start demodulation...
          pulse_time = 0;
          // High-period of 4mS now expected
          while(IR_IN == 1){
            ;
          }
          if (pulse_time > 3){
            
              // High period validated... we can now measure pulse widths...
              for(bitcount = 0; bitcount < 32; bitcount++){
              
                  // Spin here while signal = 0
                  while(IR_IN == 0){
                    ;
                  }
                  pulse_width = 0;
                  while(IR_IN == 1){
                    pulse_width++;
                  }
                                      // Falling edge
                  if (pulse_width > 0x0556){
                    
                    rx_stream |= 0x00001;
                  } else {
                    
                    rx_stream &= ~0x00001;
                  }
                  
                  rx_stream = rx_stream << 1;

                
              }
              
              // Pulse train reception complete, wait for data to go high
              while(IR_IN == 0){
                ;
              }
            
          }
          
      }
}
//-----------------------------------------------------------------------------
// Name: SendPacket
// Function: Send packet to host receiver
//-----------------------------------------------------------------------------
void SendPacket(unsigned char *data){
      unsigned char outpacket[6];
      unsigned char n;
      
      outpacket[0] = 0xAA;
      outpacket[1] = data[0];
      outpacket[2] = data[1];
      outpacket[3] = data[2];
      outpacket[4] = data[3];
      outpacket[5] = 0x55;
      
      for(n = 0; n < 6; n++){
            (void)putchar(outpacket[n]);       
      }
}
  
//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
void main(void){

          // Hardware initialisation
          ConfigCPU(0,0,1,0,1,1,0,0,0,1,1);       // Configure the CPU
          ICS_FEI_20M();                          // Set FLL to clock CPU @ 20MHz
          InitIR();                               // Initialise IR stuff
          InitPTA(0x00, 0x00);                    // PTA0 is digital in
          InitPTB(0x08, 0x00);
          InitPTC(0x04, 0x00);		                // PTC2 has an LED on it...    
          InitRTI();                              // Initialise real-time interrupt.
          InitTimer();                            // Initialise timer library
          InitSCI(9600);
          InitTPM1AsPWM();
          EnableInterrupts;
          rx_stream = 0;                          // Clear receive register
          rx_stream_previous = 0;
          InitDecode();
          (void)printf("OK\r\n");                 // Send OK message to host
          SendReleasePacket();                    // We have started up let the host know no keys are down
          

          for(;;){
          
                Demodulate();
                if(rx_stream != 0){
                      // A code has been received, check it for validity
                      if (Validate() == 0){
                          DecodeToOutputsC(rx_stream);
                          if (rx_stream != rx_stream_previous){
                          
                              // The keypress could be a new one, if so, we will still have
                              // valid time in the key timer, send release code
                              if (keytimer != 0){
                                 SendReleasePacket();
                              }
                          
                              // We have a new keypress that is unique...
                              IR_VALID = 1;                         // Pull IR_VALID pin high
                              SendPressPacket(rx_stream);
                              DecodeToOutputs(rx_stream);
                              rx_stream_previous = rx_stream;
                              keytimer = 130;
                          } else {
                              // Previous transmission same as current one, keep resetting the key timer...
                              keytimer = 130; 
                            
                          }
              
                    
                      }
                }
          }
}

//----------------------------------------------------------------------------
// Interrupt Handlers
//----------------------------------------------------------------------------
// RTI Interrupt
//--------------
interrupt 25 void RTCInt(void){         

          RTCSC |= RTCSC_RTIF_MASK;               // Clear interrupt flag by setting it
          pulse_time++;
          TimerTask();
          KeyTiming();


}    

// SCI Interrupt
//---------------
interrupt 17 void SCIRxInt(void){
          RxSCI();    
}

