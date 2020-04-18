// WriteSPI(x);

unsigned char buffer[511] ;
unsigned char buff2[15] ;


  
unsigned char send_cmd(unsigned char command,unsigned long address,unsigned char CRC);
void  Read_Buffer(unsigned long sector,unsigned char *buff);
void SDcard_init(void);




#define CS_pin      LATGbits.LATG9

#define GO_IDLE_STATE 0
#define SEND_OP_COND 1
#define SEND_IF_COND 8
#define SEND_CSD 9
#define SEND_CID 10
#define SD_STATUS 13
#define SEND_STATUS 13
#define SET_BLOCKLEN 16
#define READ_SINGLE_BLOCK 17
#define READ_MULT_BLOCK 18
#define WRITE_BLOCK 24
#define SD_SEND_OP_COND 41
#define APP_CMD 55
#define READ_OCR 58
#define CRC_ON_OFF 59 






void  Read_Buffer(unsigned long sector,unsigned char *buff)
{  
    
 unsigned char x;   
unsigned int ii=0;        
unsigned char data=0;    
send_cmd(READ_SINGLE_BLOCK,sector,0xff);

CS_pin =0;  
while(data!=0xFE){
data =ReadSPI();
} 

for(ii=0;ii<=511;ii++)
{  
    buff[ii]=ReadSPI();
}

}

 

   
unsigned char send_cmd(unsigned char command,unsigned long address,unsigned char CRC){
   
        unsigned char response;
        unsigned char data;
         CS_pin =1;
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
 
         CS_pin =0;
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
         WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        WriteSPI(0xff);
        data=(command|0x40);
        
        WriteSPI(data);
        data=((address>>24) & 0xFF);
        WriteSPI(data);
        data=((address>>16) & 0xFF);
        WriteSPI(data);
        data=((address>>8) & 0xFF);
        WriteSPI(data);
        data=((address) & 0xFF);
        WriteSPI(data);
        WriteSPI(CRC);

         WriteSPI(0xff);
         
       response=ReadSPI();
        while(response==0xFF){response=ReadSPI();}

      
        return response;
     
          CS_pin =0;
         
       
 
    } 


void SDcard_init(void){
 
     unsigned char x=0;
     unsigned char i ;
    CS_pin =1;
    // send 80 clocks (10 bytes) to wake up SD card
    // load dummy values into buffer
    for(i= 0; i < 50; i++){
	WriteSPI(0xff);  
    }
   
     
        CS_pin =0;
 
    text1 ("Starting SD card initialization",0 ,0,1,Black,White);
    
    text1 ( "GO_IDLE_STATE",20 ,20,1,Black,White);
    x=send_cmd(GO_IDLE_STATE,0,0x95);;
    
    tohex(x ,buff2);
    text1 ( buff2,200 ,20,1,Black,White);
    
     
    text1 ( "SEND_IF_COND",20 ,40,1,Black,White);
    x=send_cmd(SEND_IF_COND, 0x000001AA,0x87);;
    
    tohex(x ,buff2);
    text1 ( buff2,200 ,40,1,Black,White);
    
    
    
    do{ 
    
    
    text1 ( "APP_CMD",20 ,80,1,Black,White);
    x=send_cmd(APP_CMD,0,0x65);
    
    tohex(x ,buff2);
    text1 ( buff2,200 ,80,1,Black,White);

   
    text1 ( "SD_SEND_OP_COND",20 ,100,1,Black,White);
    x=send_cmd(SD_SEND_OP_COND,0x40000000,0x77);
     
        

        
    tohex(x ,buff2);
    text1 ( buff2,200 ,100,1,Black,White);
     
    }while(x!=0);
    
}
 

