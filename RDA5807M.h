unsigned int count=0;
unsigned int freq=1035;










#define SDA_TRIS  TRISGbits.TRISG0
#define SCL_TRIS  TRISGbits.TRISG1
#define SDA       PORTGbits.RG0
#define SCL       PORTGbits.RG1

#define ACK       0x00
#define NACK      0x80



#define BYTE      unsigned char
#define WORD      unsigned int
#define DWORD      unsigned long 


void IdleI2C(void)
{
 
 
 Nop();
    
    
}




//....................................................................
// This function generates an I2C Start Condition
//....................................................................
void StartI2C(void)
{
unsigned int i;

SDA_TRIS = 1;                   // ensure SDA & SCL are high
SCL = 1;
SDA_TRIS = 0;                   // SDA = output
SDA = 0;                        // pull SDA low
for (i=0;i<2;i++) Delay_ms(5);
SCL = 0;                        // pull SCL low
}


//....................................................................
// This function generates an I2C Stop Condition
//....................................................................
void StopI2C(void)
{
unsigned int i;

SCL = 0;                        // ensure SCL is low
SDA_TRIS = 0;                   // SDA = output
SDA = 0;                        // SDA low
for (i=0;i<3;i++) Delay_ms(5);
SCL = 1;                        // pull SCL high
SDA_TRIS = 1;                   // allow SDA to be pulled high
for (i=0;i<3;i++) Delay_ms(5);
SCL=0;                          // ensure SCL is low
}


//....................................................................
// Outputs a bit to the I2C bus
//....................................................................
void bit_out(unsigned char data)
{
unsigned int i;

SCL = 0;                        // ensure SCL is low
SDA_TRIS=0;                     // configure SDA as an output
SDA= (data>>7);                 // output the MSB
for (i=0;i<2;i++) Delay_ms(5);
SCL = 1;                        // pull SCL high to clock bit
for (i=0;i<3;i++) Delay_ms(5);
SCL = 0;                        // pull SCL low for next bit
}


//....................................................................
// Inputs a bit from the I2C bus
//....................................................................
void bit_in(unsigned char *data)
{
unsigned int i;

SCL = 0;                        // ensure SCL is low
SDA_TRIS = 1;                   // configure SDA as an input
SCL = 1;                        // bring SCL high to begin transfer
for (i=0;i<3;i++) Delay_ms(5);
*data |= SDA;                   // input the received bit
SCL = 0;                        // bring SCL low again.
}


//....................................................................
// Writes a byte to the I2C bus
//....................................................................
unsigned char WriteI2C(unsigned char data)
{
unsigned char i;                // loop counter
unsigned char ack;              // ACK bit

ack = 0;
for (i = 0; i < 8; i++)         // loop through each bit
    {
    bit_out(data);              // output bit
    data = data << 1;           // shift left for next bit
    }

bit_in(&ack);                   // input ACK bit
return ack;
}


//....................................................................
// Reads a byte from the I2C bus
//....................................................................
unsigned char ReadI2C( )
{
unsigned char i;                // loop counter
unsigned char ret=0;            // return value

for (i = 0; i < 8; i++)         // loop through each bit
    {
    ret = ret << 1;             // shift left for next bit
    bit_in(&ret);               // input bit
    }

 
return ret;
}


//.............................................................................
//          Polls the bus for ACK from device
//.............................................................................
void AckI2C ( )
{
unsigned char result=1;

while(result)
	{
	StartI2C();            // generate Restart condition
	result=WriteI2C(0xff ); // send control byte (WRITE command)
        }

StopI2C();                     // generate Stop condition
}



 
void RDA5807M_SetFrequency(unsigned int freq)
   
{
    
  unsigned long   frequency; 
  unsigned long   frequencyB; 
  unsigned long    frequencyH; 
  unsigned long    frequencyL; 
    
 frequency=freq*100000; //starting frequency
frequencyB=(4*(frequency+225000))/32768; //calculating PLL word
frequencyH=frequencyB>>8;
frequencyL=frequencyB&0XFF;

TRISD=0;
PORTD=0xfffff;
TRISDbits.TRISD0= 1; // SDI6 

StartI2C();
WriteI2C(0xC0); //adres om te schrijven
WriteI2C(0);
WriteI2C(0);
WriteI2C(0xB0);
WriteI2C(0b00010000);
WriteI2C(0x00);
StopI2C(); 




StartI2C();
WriteI2C(0xC0); //adres om te schrijven
WriteI2C(frequencyH);
WriteI2C(frequencyL);
WriteI2C(0xB0);
WriteI2C(0b00010000);
WriteI2C(0x00);
StopI2C(); 


}

 

 
void RDA5807M_Mute( )
   
{
    

StartI2C();
WriteI2C(0xC0); //adres om te schrijven
WriteI2C(0x00);
WriteI2C(0X00);
WriteI2C(0xB0);
WriteI2C(0b01010000);
WriteI2C(0x00);
StopI2C(); 


}
 



void PRINT( unsigned long  Number)
{
    
       unsigned char buf1[8];
     
            
            Number=(Number)*10;
            
            buf1[0]=((Number/10000)%10)+48;
            buf1[1]=((Number/1000)%10)+48;
            buf1[2]=((Number/100)%10)+48 ;
            buf1[3]=(46);
            buf1[4]=((Number/10)%10)+48;
            buf1[5]=((Number/1)%10)+48; 
            buf1[6]=0;
            
            text2 (buf1,20 ,10,1,Black,White);
            text2 ("Mhz",180 ,10,1,Black,White);
        
        
            

}



 

void  Radio_Play(void)
 {
     
    
    if ( Button1==0)
      { freq++; count++;if(count>30)count=30; 
      if(freq>(112*10)){freq=(112*10); }
      RDA5807M_SetFrequency( freq);  PRINT( freq);  }
          
      
      if ( Button2==0)
      { freq-- ; count++;if(count>30)count=30;  
      if(freq< (80*10)){freq= (80*10); }
       RDA5807M_SetFrequency( freq);    PRINT( freq);  }  
           
      if((Button1 ==1)&(Button2==1 )){ count=0; }
     
      
     if(count<15){Delay_ms(50);}
     if(count>15){ if(count>25){Delay_ms(10); } else {Delay_ms(20);}} 

    
    
    
     
 }