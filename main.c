



#define White                                                                            0xFFFF
#define Black                                                                            0x0000
#define Grey                                                                             0xF7DE
#define Grey2                                                                            0x8430
#define Light_Grey                                                                       0xC618
#define Dark_Grey                                                                        0x8410
#define Purple                                                                           0xF81F
#define Grey_Blue                                                                        0x5458
#define Blue                                                                             0x001F
#define Dark_Blue                                                                        0x01CF
#define Light_Blue                                                                       0x051F
#define Light_Blue_2                                                                     0x7D7C
#define Red                                                                              0xF800
#define Green                                                                            0x07E0
#define Cyan                                                                             0x7FFF
#define Yellow                                                                           0xFFE0
#define Orange                                                                           0xFC08
#define Magenta                                                                          0xF81F

unsigned int exit0;


#define Button1 PORTAbits.RA2 // SELECT
#define Button2 PORTAbits.RA3 // SELECT
#define Button3 PORTAbits.RA4  // ENTER
#define Button4 PORTAbits.RA14 // exit






#include "xc.h"
#include "p32xxxx.h"
#include "SPI.h"
#include "CONFIG.h"
#include "Delay.h"
#include "FONT.h"
 #include "ILI9341.h"
#include "FUNCTIONS.h"
#include "ICONS.h"
#include "SD_CARD.h"
#include "FAT32.h"
#include "BITMAP.h"
#include "VS1011.h"
 #include <sys/attribs.h> 
  #include <stdio.h>

#include "RDA5807M.h"

 
/* To Remap RPn Pins use: "PPSUnLock" (remap your input and/or output pins) "PPSLock" */
#define PPSUnLock {SYSKEY=0x0;SYSKEY=0xAA996655;SYSKEY=0x556699AA;CFGCONbits.IOLOCK=0;} // System UnLocked
#define PPSLock  {CFGCONbits.IOLOCK=1;SYSKEY=0x0;} // System Re-Locked






 
 #define TFT_LED PORTGbits.RG15 //  

unsigned char  buttonState1=1;
unsigned char  previousState1=1;
unsigned char  buttonState2=1;
unsigned char  previousState2=1;
unsigned char  buttonState3=1;
unsigned char  previousState3=1;
unsigned char  buttonState4=1;
unsigned char  previousState4=1;
unsigned char  buttonState5=1;
unsigned char  previousState5=1;


unsigned char play; 
unsigned long File_Size;
unsigned long  Directoryes;
unsigned  long  Address;
unsigned  long  Address0;
unsigned int Number_Of_Files;
unsigned int Number_Of_Files_Indirectory;
unsigned int Number_Of_Folders_Indirectory;
unsigned int x;
unsigned int x2;
unsigned int x3;
unsigned int x4;
unsigned int change;

unsigned int print;
unsigned int print2;
unsigned int select;

unsigned int startx;
unsigned int offset;
unsigned int list_offset;
unsigned int delete_rows;
unsigned int filenumber;

unsigned int increment;
unsigned int i;
unsigned int ii;
unsigned char select_mode;

unsigned char ledstatus;
signed char volume;
unsigned char timer;
unsigned char data;
unsigned char data2;
unsigned char value;
unsigned char txt1[20];

 unsigned char counter;

unsigned int number;
unsigned char buff[10] ;
 
#include "PLAYER.h"




void Initspi ()
{

CS_pin =1;

    SPI2CON = 0;
    SPI2STAT = 0;
    SPI2CON = 0x8120; // re-enable the SPI2 module
    SPI2BRG = 200; // select clock speed
    
    SPI1CON = 0;
    SPI1STAT = 0;
    SPI1CON = 0x8120; // re-enable the SPI2 module
    SPI1BRG = 20; // select clock speed 

}





void InitPorts ()
{

 /*************************************************************************
REMAP INPUTS:
[module name]Rbits.[module name] = 4-bit binary code for [pin name]
**************************************************************************/

SDI2Rbits.SDI2R = 0b0001; // (RPG7 = RG7 input) 

SDI1Rbits.SDI1R = 0b0000;   //SDI1
/*************************************************************************
REMAP OUTPUT OUTPUT PINS TO MODULE:
[pin name]Rbits.[pin name] = 4-bit binary code for [module name]
**************************************************************************/

 INT1R = 0b0000; //Pin F13 = INT1

RPD3Rbits.RPD3R = 0b0101;  //  //SDO1 

RPG8Rbits.RPG8R = 0b0110;  // (0110 = SDO2) to RG8   
 

PPSLock;

    ANSELA = 0;                   // PORTA ANSELA Cleared = Digital
    ANSELB = 0b0000000000000000;  // PORTB ANSELB Cleared = Digital (Set RB15/AN10/CSS10 "frequency-Input" as ANALOG input)

    ANSELG = 0;                   // PORTG ANSELG Cleared = Digital
    TRISA=0XFFFF;
    TRISB=0;
    TRISC=0X0;
    TRISG=0;
    TRISD=0;
    TRISGbits.TRISG7= 1;  //SDI2
    TRISDbits.TRISD2= 1; // SDI6 

    TRISDbits.TRISD0= 1; // SDI6 
    

}

 
 

int main() {
                       
 

         
  Delay_ms(5000);
    
     InitPorts ();  
     Initspi ();
     
    TFT_PORT_init();
  
    TFT_init();
 
    fillScreen2(Black);
        
    SDcard_init();
    SPI2BRG = 2; // select clock speed
     Init_VS1011() ;
    TFT_LED=1;
    Init_FAT32();
    fillScreen2(Black);
     

    SDcard_init(); Init_FAT32();  Open_Root_Directory();
    
    
    
  

    
    
    
    
    
    //Sine_Test();
    
    
    Open_Root_Directory();
    
  
  
    Address= Root_Directory;
  
    Number_Of_Files_Indirectory=Search_File_Indirectory(Root_Directory,buffer,File_Offset) ; 
 
    tostring(Number_Of_Files_Indirectory,buff2); 

    
    

            x=1;
            Delay_ms(500);


            startx=0;
            print=0;
            x3=0;

            exit0=0;

     
    select_mode=2;
    
   RDA5807M_Mute();
     
    
    
    while (1) {
      
           if( select_mode ==1 ){             Mp3_Play ();  }

            if( select_mode ==2 ){             Radio_Play (); }     
                
                  
                
              
               
            if(Button4==0){  
            select_mode++;  if(select_mode>2){select_mode=1;};
            
             if( select_mode ==1 ){  RDA5807M_Mute(); TFT_LED=1;Init_VS1011() ;  Mp3_Play ();  print=0;x3=0; exit0=0; }
                                                                                                        

                                                                                                                   
      
             if( select_mode ==2 ){  Turn_Off_Vs1011 ();fillScreen2(Black);  TFT_LED=1; Radioicon(0,60);  RDA5807M_SetFrequency(1035); PRINT(1035);     }   
     
            
            
            }
          
              
              
              
              
              
              
              
  
       }

         
         
        
        
        
        
    }
    
 