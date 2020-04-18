
 

 



unsigned char CHARACTER_WIDTH(unsigned int character,const unsigned short *FONT);
/*
void number_print(unsigned char *buffer,unsigned int x,unsigned int y )
{
    unsigned char count=0;
    while(*buffer)              // Write data to LCD up to null
    {
       
        GLCD_FONT2((*buffer-47),(x+(55*count)) ,y ,Black,White,0,Tahoma47x78);      // Write character to LCD
        
        
        buffer++;  // Increment buffer 
        count++;
    }
}
*/
void Draw_Filled_Rectangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2,  unsigned int color);
void slideshow(void);
unsigned int CHARACTER_POSITON;

unsigned char CHARACTER_WIDTH(unsigned int character,const unsigned short *FONT)
{
    
    unsigned char    CHARACTER_W;    
    CHARACTER_W = FONT[(8+(character*4))];
    if(character==0){CHARACTER_W = FONT[(8+(4*4))]; };
    return CHARACTER_W;

}








 void GLCD_FONT2 (unsigned int character,unsigned int x,unsigned int y,unsigned int color1,unsigned int color2,unsigned int space,const unsigned short *FONT)
{
    unsigned int    counter;
    unsigned int    i;
    unsigned int    ii;
    unsigned int    xx;
    unsigned int    STARTINGPOINT;
    unsigned int    CHARACTER_HEIGHT;
    unsigned int    CHARACTER_WIDTH;
    unsigned int    DATA;
    unsigned int    VERTICAL;
    unsigned int    HORIZONTAL;
    unsigned int    HORIZONTAL_COUNTER;
    unsigned int    VERTICAL_COUNTER;
    unsigned int    LOWBYTE;
    unsigned int    HIGHBYTE;
    unsigned int    LOW1;
    unsigned int    HIGH1;
    unsigned int    BYTEWIDTH; 
    
    LOW1=0;
    HIGH1=0;
    CHARACTER_HEIGHT = FONT[6];
    CHARACTER_WIDTH = FONT[(8+(character*4))];
    BYTEWIDTH=((CHARACTER_WIDTH/8));
    if((CHARACTER_WIDTH%8)!=0){BYTEWIDTH++; };
    
    LOWBYTE= FONT[(9+(character*4))];
    HIGHBYTE= FONT[(10+(character*4))];
    HIGH1=((HIGHBYTE<<8)&0xFF00);
    LOW1=((LOWBYTE&0x00FF));
    HORIZONTAL_COUNTER = CHARACTER_WIDTH ;
    VERTICAL_COUNTER = CHARACTER_HEIGHT ;
    STARTINGPOINT= ((LOW1)|(HIGH1));
    
        
    VERTICAL=0;
    HORIZONTAL=0;
    counter=0;      
    DATA = FONT[(STARTINGPOINT)];           
      for(xx=0;xx<CHARACTER_HEIGHT;xx++) 
        {   counter=0;
            for(ii=0;ii<BYTEWIDTH;ii++) 
            {                               
                for(i=0;i<8;i++)          
                {
                    Column_Address_Set(( 320-(counter+x)));
                    if(((DATA>>(i))&0x01)==0){ Write_Data(color1); }
                    if(((DATA>>(i))&0x01)==1){ Write_Data(color2); }                           
                            VERTICAL++;
                            counter++;
                }
                    STARTINGPOINT++;
                    DATA = FONT[(STARTINGPOINT)];
            }                                  
                    Page_Address_Set(HORIZONTAL+y),    
                    HORIZONTAL++; VERTICAL=0; 
                    for(i=0;i<space;i++) { Draw_Pixel( (320-((counter+x)+i)),(HORIZONTAL+y),color1);  }; //CLEAR END                           
        }   
        
    
   }    

                 
                        
 
 
 
 
 
 

 void text1 (unsigned char *buffer,unsigned int x,unsigned int y,unsigned int spaceing ,unsigned int color1,unsigned int color2)
{
    unsigned char WIDTH; 
    unsigned char count=0;
    CHARACTER_POSITON=0;
    while(*buffer)              // Write data to LCD up to null
    {
        
         
        GLCD_FONT2((*buffer-32),(((CHARACTER_POSITON))+x) ,y,color1,color2,1,Times_New_Roman16x16);      // Write character to LCD
        
         WIDTH = CHARACTER_WIDTH((*buffer-32),Times_New_Roman16x16);       
         CHARACTER_POSITON=CHARACTER_POSITON+WIDTH+spaceing;
        buffer++;  // Increment buffer 
        count++;
    }
    
    
}



 void text0 (unsigned char *buffer,unsigned int x,unsigned int y,unsigned char spaceing,unsigned int color1,unsigned int color2,unsigned int limit)
{
    unsigned char WIDTH; 
    unsigned char count=0;
    CHARACTER_POSITON=0;
    
    
    
    while(*buffer)              // Write data to LCD up to null
    {
        
         
        GLCD_FONT2((*buffer-32),(((CHARACTER_POSITON))+x) ,y,color1,color2,1,Times_New_Roman16x16);      // Write character to LCD
        
         WIDTH = CHARACTER_WIDTH((*buffer-32),Times_New_Roman16x16);       
         CHARACTER_POSITON=CHARACTER_POSITON+WIDTH+spaceing;
        buffer++;  // Increment buffer 
        count++;
        
       if( (CHARACTER_POSITON+x) >limit){break;}
 
    }
 }
 
 

 void text2 (unsigned char *buffer,unsigned int x,unsigned int y,unsigned int spaceing ,unsigned int color1,unsigned int color2)
{
    unsigned char WIDTH; 
    unsigned char count=0;
    CHARACTER_POSITON=0;
    while(*buffer)              // Write data to LCD up to null
    {
        
         
        GLCD_FONT2((*buffer-32),(((CHARACTER_POSITON))+x) ,y,color1,color2,1,Tahoma44x50);      // Write character to LCD
        
         WIDTH = CHARACTER_WIDTH((*buffer-32),Tahoma44x50);       
         CHARACTER_POSITON=CHARACTER_POSITON+WIDTH+spaceing;
        buffer++;  // Increment buffer 
        count++;
    }
    
    
}

 
 
 
 


void intToStr(unsigned long value, char *str, char leading_zero, char digits)
{
    static long powers[9] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    char temp_digit,digit_cnt=10,first_non_zero=1;
 
    while (digit_cnt!=1)  // initially this value is 10 so the loop is executed 9 times
    {
        temp_digit = 48;  // ASCII 0
        while (value >= powers[digit_cnt-2])  // while number bigger than power value
        {
            value -= powers[digit_cnt-2];       // subtract the power value
            temp_digit++;                       // and increase variable
        }
        if (digit_cnt<=digits) *str++ = temp_digit; // only store requested number of digits  
 
        digit_cnt--;   // used as a counter to detect when we have reached the last char of the array
    }
    *str = (char) value+48; // assign the last character
 
    if (leading_zero==0)   // if parameter is set for no leading zeros
    {   str-=digits;    // go to the first char of the array
        while(first_non_zero==1)    // if the first digit of the number is not found
        {   str++;  // move to next array character
            if (*str=='0') *str=32;      // if digit value is ADCII 0 then replace with space (user selectable)
            else first_non_zero=0;      // else set the flag that the first digit of the number was found
 
        }
    }
}

 










void tohex(unsigned char in,  char * out)
{
  
    const char * hex = "0123456789ABCDEF";
    char * pout = out;
    
    
        
        pout[0] = hex[(in>>4) & 0xF];
        pout[1] = hex[ in     & 0xF];
       
        pout[2] = 0;
   
}



void tostring(unsigned int Number ,  char * out)
{
    
   
    char * pout = out;
    
        pout[2] =((Number/1)%10)+48;
        pout[1] = ((Number/10)%10)+48;;
        pout[0] = ((Number/100)%10)+48;;
        pout[3] = 0;
   
}

void tostring2(unsigned int Number ,  char * out)
{
    
 
        char * pout = out;
        pout[4] = ((Number/1)%10)+48;
        pout[3] = ((Number/10)%10)+48;
        pout[2] = ((Number/100)%10)+48;
        pout[1] = ((Number/1000)%10)+48;;
        pout[0] = ((Number/10000)%10)+48;;
        pout[5] = 0;
   
}



void tostring3(unsigned long Number ,  char * out)
{
    
 
        char * pout = out;
        pout[9] = ((Number/1)%10)+48;
        pout[8] = ((Number/10)%10)+48;
        pout[7] = ((Number/100)%10)+48;
        pout[6] = ((Number/1000)%10)+48;
        pout[5] = ((Number/10000)%10)+48;
        pout[4] = ((Number/100000)%10)+48;
        pout[3] = ((Number/1000000)%10)+48;
        pout[2] = ((Number/10000000)%10)+48;
        pout[1] = ((Number/100000000)%10)+48;
        pout[0] = ((Number/1000000000)%10)+48;
        
        pout[10] = 0;
   
}


