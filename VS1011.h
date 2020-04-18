



 

// Smart MP3 board connections
 
#define MP3_CS          PORTDbits.RD12 //  XCS ------Chip_select
#define MP3_RST         PORTDbits.RD13 //  XRESET----Hardware_Reset 
#define DREQ            PORTDbits.RD4 //  DREQ------Data_Request 
#define BSYNC           PORTDbits.RD5 //  BSYNC-----SDI data is synchronized with a rising edge of BSYNC.
 
  


void MP3_SDI_Write(char data_) {

  MP3_CS = 1;
  BSYNC  = 0;

  while (DREQ == 0);             // wait until DREQ becomes 1, see MP3 codec datasheet, Serial Protocol for SCI

  WriteSPI2(data_);
  BSYNC  = 1;
}




void MP3_SCI_Write(char address, unsigned int data_in) { // Writes one word to MP3 SCI
    
    
   unsigned char HIGHBYTE=0;                       
   unsigned char LOWBYTE=0; 
   
   LOWBYTE=(data_in&0xFF);
   HIGHBYTE=((data_in>>8)&0xFF);
    
  MP3_CS = 0;                             // select MP3 SCI
  WriteSPI2(0x02); WriteSPI2(address);  // send WRITE command, send address
  WriteSPI2(HIGHBYTE); WriteSPI2(LOWBYTE); // Send High byte, send Low byte
  MP3_CS = 1;                             // deselect MP3 SCI
   while (DREQ == 0);                      // wait until DREQ becomes 1
}
// Reads words_count words from MP3 SCI
void MP3_SCI_Read(char start_address, char words_count, unsigned int *data_buffer) {
  unsigned int temp;
  MP3_CS = 0;                             // select MP3 SCI
  WriteSPI2(0x03);                       // send READ command
  WriteSPI2(start_address);
  while (words_count--) {                 // read words_count words byte per byte
    temp = ReadSPI2();
    temp <<= 8;
    temp += ReadSPI2();
    *(data_buffer++) = temp;
  }
  MP3_CS = 1;                             // deselect MP3 SCI
   while (DREQ == 0);                      // wait until DREQ becomes 1
}
 
void Set_Clock(unsigned int clock_khz, char doubler) {   // Set clock
  clock_khz /= 2;                                  // calculate value
  if (doubler) clock_khz |= 0x8000;
  MP3_SCI_Write(0x03, clock_khz);                  // Write value to CLOCKF register
  Delay_ms(2);
  
   
}


  


void Init_VS1011() {
    
    
    unsigned int i;
    
 // Set_Clock(25000,0);                             
 // Set clock to 25MHz, do not use clock doubler
  TRISDbits.TRISD12  =0 ; //  XCS ------Chip_select cofigure pin as output
  TRISDbits.TRISD13  =0 ; //  XRESET----Hardware_Reset   MP3_RST pin, cofigure pin as output      
  TRISDbits.TRISD4  =1 ; //  DREQ------Data_Request     // Configure DREQ as input    
  TRISDbits.TRISD5  =0 ; //  BSYNC-----SDI data is synchronized with a rising edge of BSYNC, cofigure pin as output
  
 
          
  
  MP3_CS = 1;              // Deselect MP3_CS, 
  
                                               // Configure DREQ as input
  BSYNC = 0;               // Clear BSYNC, cofigure pin as output
  
  
  
  
  

  
  
   Delay_ms(2000);
   MP3_RST = 0;  
   Delay_ms(2000);
   MP3_RST = 1; 
  
  
  Delay_ms(20); 
    
  Set_Clock(25000,0);// Software Reset
  
    Delay_ms(20);  
  MP3_SCI_Write(0x00,0x0204);                      // Set SM_RESET bit and SM_BITORD bit(bitorder is LSB first)
                                    // Required, see MP3 codec datasheet -> Software Reset
  while (DREQ == 0);                               // wait until DREQ becomes 1
  for (i=0; i<2048; i++) MP3_SDI_Write(0);         // feed 2048 zeros to the MP3 SDI bus
  
  MP3_SCI_Write(0x0B, 0);  
  
  
}


void Soft_Reset() { 
    
   unsigned int i; 
 // Set_Clock(25000,0);// Software Reset
    
  MP3_SCI_Write(0x00,0x0204);                      // Set SM_RESET bit and SM_BITORD bit(bitorder is LSB first)
  Delay_ms(2);                                     // Required, see MP3 codec datasheet -> Software Reset
  while (DREQ == 0);                               // wait until DREQ becomes 1
  for (i=0; i<2048; i++) MP3_SDI_Write(0);         // feed 2048 zeros to the MP3 SDI bus
}





void Sine_Test(void)
{
 
 
                       
  
   Delay_ms(100);            /* 100 ms delay */

  /* VS10xx Application Notes, chapter 4.8 ---------------------------------*/
  /* As an example, let's write value 0x0820 to register 00 byte by byte    */
  MP3_CS = 0;    /* Pull XCS low, now SPI writes go to SCI port     */
  WriteSPI2(0x02);      /* Send SPI Byte, then wait for byte to be sent.   */
  WriteSPI2(0x00);      /* 0x02 was WRITE command, 0x00 is register number */
  WriteSPI2(0x08);      /* This byte goes to MSB                           */
  WriteSPI2(0x20);      /* ..and this is LSB. (0x20=Allow Test Mode)       */
              /* Wait until Atmel MCU signals SPI write complete */
  MP3_CS = 1;  /* Pull XCS high, now SPI writes don't go to SCI port. */

 while (DREQ == 0);       /* Wait for DREQ = 1                               */
    ; 			 /* Do nothing while waiting for DREQ = 1           */

  /* Send a Sine Test Header to Data port                                   */
          /* pull XDCS low, now SPI writes go to SDI port    */
  BSYNC = 0; 
  WriteSPI2(0x53);      /* - This is a special VLSI Solution test header - */
  WriteSPI2(0xef);      /* - that starts a sine sound. It's good for     - */
  WriteSPI2(0x6e);      /* - testing your code and the chip. */
  WriteSPI2(0x44);      
  WriteSPI2(0x00);      
  WriteSPI2(0x00);
  WriteSPI2(0x00);
  WriteSPI2(0x00);
   BSYNC = 1;
  
  
  Delay_ms (500);           /* 500 ms delay */
 
 MP3_CS = 0;    /* Pull XCS low, now SPI writes go to SCI port     */
  WriteSPI2(0x02);      /* Send SPI Byte, then wait for byte to be sent.   */
  WriteSPI2(0x0B);      /* 0x02 was WRITE command, 0x00 is register number */
  WriteSPI2(0x00);      /* This byte goes to MSB                           */
  WriteSPI2(0x00);      /* ..and this is LSB. (0x20=Allow Test Mode)       */
              /* Wait until Atmel MCU signals SPI write complete */
  MP3_CS = 1;  /* Pull XCS high, now SPI writes don't go to SCI port. */
  
        
          
} 
 



void Set_Volume (unsigned char volume)

{
    
unsigned int data=0;
data=volume;

data=((data<<8)|volume);
    
 MP3_SCI_Write(0x0B,data);   
    
}

    


void Turn_Off_Vs1011 (void)

{
    
 MP3_RST = 0;
    
    
    
}

    