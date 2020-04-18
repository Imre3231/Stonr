 








void select_limit(void)
{
    
 
    if(x>(Number_Of_Files_Indirectory-1)){x=(0);}
    if(x<1){x=1;}
    
  
    
}


 
 
void Open_Mp3(unsigned long Directory_Entry )
{ 
   
   unsigned char data;
   unsigned int Buffer_Offset=0;
   unsigned int Offset=0;
   unsigned int ii;
   unsigned int i;
    unsigned int Size ; 
   unsigned int increment=0x36; 
    
    
    play=0;
    
    
   Size = (File_Size/512);
    
   
                        tostring3(File_Size,buff2);   
                       text1 ( buff2,0,0,1,Black,White); 
                       
     
 MP3_CS = 0;    /* Pull XCS low, now SPI writes go to SCI port     */
  WriteSPI2(0x02);      /* Send SPI Byte, then wait for byte to be sent.   */
  WriteSPI2(0x00);      /* 0x02 was WRITE command, 0x00 is register number */
  WriteSPI2(0x08);      /* This byte goes to MSB                           */
  WriteSPI2(0x20);      /* ..and this is LSB. (0x20=Allow Test Mode)       */
              /* Wait until Atmel MCU signals SPI write complete */
  MP3_CS = 1;  /* Pull XCS high, now SPI writes don't go to SCI port. */



  
exit0=0;
  
Read_Buffer((Directory_Entry),buffer); 
    
    
   while(1){
            
       
             for (ii=0; ii<16; ii++){
       
            while (DREQ == 0){  if(exit0>0){break;} };    
 
            for (i=0; i<32; i++)
            { 
                BSYNC =1;
                BSYNC =0;
               WriteSPI2(buffer[Offset]);  Offset++; 
               BSYNC =1;
               
            }
                 
            
             }
             
             Offset=0;
             
             
         Directory_Entry++;
         Read_Buffer((Directory_Entry),buffer); 
         
          buttonState1=Button3; 
        if(buttonState1 != previousState1){ if (buttonState1==1){ 
            exit0=1;
      
                     } } 
         previousState1 = buttonState1;
          
         if(Button1==0){ x++; exit0=2; }
         if(Button2==0){ x--; exit0=3; }
         
         Size--;
         if(Size<1){x++ ;exit0=2; }
         
         
         if(exit0>0){break;}
         
         
         
      
   }


}

 




void Print_Filelist(void)
{

    
                
    
            if(print==0){          
                      x2=x;
                      x4=x+1;
                       if(x==1){ x3=1; }
                      
                       
                      if(change<x){ x3++;    if(x3>6){ x3=6; ; ;  }     }
                      if(change>x){ x3--;    if(x3<1){x3=1;  ;}   }
                      
                   
                       
                      if (x4<(x3)){x=1;}  else{x=((x4-x3 ));    }
                       
                         

 
                         
                      list_offset=0;
                      
                      fillScreen2(Black);
                      for(i=0;i<=5;i++){
        
                        
                       select_limit();     
                        
                       list_offset++;    
                         
                       tostring(Number_Of_Files_Indirectory,buff2);   
                       text1 ( buff2,50 ,230,1,Black,White); 
                      
                       tostring(x,buff2); 
                       text1 ( buff2,200 ,230,1,Black,White); 

                         tostring(x,buff2); 
                         text1 ( buff2,200 ,230,1,Black,White); 

                       data2= Reed_File_Type(Address,(x));
                       if(data2==0x01){ Foldericon(0,list_offset*30);}
                       if(data2==0x02){ Mp3icon(0,list_offset*30);}
                       if(data2==0x03){ BMPicon(0,list_offset*30);}
                       
                       Reed_Filename(Address,(x),Filename_Table);
                       Reed_Long_Filename(Address,(x),Filename_Table);

                       if((x3==(i+1) )){text0 (Filename_Table,60 ,10+(list_offset*30),1,White,Black,250);  }else{ text0 (Filename_Table,60 ,10+(list_offset*30),1,Black,White,250); }
                         
                       
                       
                       x++;
                       if((list_offset)>((Number_Of_Files_Indirectory-(2))) ){break; }
 
                   
                       }
                
                
                        

                       
                      
            
                        x=x2;
                        change=x;
                        print=1;

        }


}






void Play_bitmap(void){
          
              data2= Reed_File_Type((Address),(x));           
              if(data2==0x02){
              
              Address0=Root_Directory+  File_Start_Addres(Address,0 );
              Address= Root_Directory+ File_Start_Addres(Address,x );
              Open_Bitmap(Address);
              
              fillScreen2(Black);
              Address=Address0;
              Number_Of_Files_Indirectory=Search_File_Indirectory(Address,buffer,File_Offset) ; 
              }
}



void Play_MP3(void)
{

          if(data2!=0x02){play=1; print=0;  };  
          if(data2==0x02){
              
              Address0=Root_Directory+  File_Start_Addres(Address,0 );
              Address= Root_Directory+ File_Start_Addres(Address,x );
              
              
              
             Open_Mp3(Address); 
              
              
              fillScreen2(Black);
              Address=Address0;
              Number_Of_Files_Indirectory=Search_File_Indirectory(Address0,buffer,File_Offset) ; 
              print=0;
              
          }
         

}


void Enter_Button(void)
{

        buttonState3=Button3; 
        if(buttonState3 != previousState3){ if (buttonState3==1){ 
   
         
          data2= Reed_File_Type((Address),(x));   
            
         if(data2==0x01){
            
         Address= Root_Directory+ File_Start_Addres(Address,x );
         
          
         Number_Of_Files_Indirectory=Search_File_Indirectory(Address,buffer,File_Offset) ; 
         x=1;
            
                    }
         
         
          if(data2==0x02){
              
              Address0=Root_Directory+  File_Start_Addres(Address,0 );
              Address= Root_Directory+ File_Start_Addres(Address,x );
              
              
              
             Open_Mp3(Address); 
              
              
              fillScreen2(Black);
              Address=Address0;
              Number_Of_Files_Indirectory=Search_File_Indirectory(Address,buffer,File_Offset) ; 
              print=0;
              
          }
         
          
          
                   
          if(data2==0x03){
              
              Address0=Root_Directory+  File_Start_Addres(Address,0 );
              Address= Root_Directory+ File_Start_Addres(Address,x );
              
              
              
             Open_Bitmap(Address); 
              Delay_ms(5000);
              
              fillScreen2(Black);
              Address=Address0;
              Number_Of_Files_Indirectory=Search_File_Indirectory(Address,buffer,File_Offset) ; 
              print=0;
              
          }
         
         
         
         
         
         print=0;
 
                    } } 
         previousState3 = buttonState3;

}



void Buttons2(void)
{

                if(Button1==0){value++; if(value>5) {value=10;    x++;  print=0; }  }  ; 
                

                if(Button2==0){value++; if(value>5) {value=10;    x--;  print=0; }  }   ; 

                if((Button1==1)&(Button2==1)){value=0;   }; 


}

void Buttons(void)
{

     buttonState1=Button1; 
        if(buttonState1 != previousState1){ if (buttonState1==1){ 

            x++;     
            print=0;
                    } } 
         previousState1 = buttonState1;
         
         
              
        buttonState2=Button2; 
        if(buttonState2 != previousState2){ if (buttonState2==1){ 

            x--;    
            print=0;    
                    } } 
         previousState2 = buttonState2;


}




void Mp3_Play (void)
{


    
     
        if(exit0==0){   Print_Filelist();  }
        if(print==0){  Print_Filelist();  print=1; }     

        
         
           select_limit();
        data2= Reed_File_Type((Address),(x)); 
        if(exit0==2){ select_limit(); 
        File_Size=Reed_File_Size(Address,x);  print=0;
        if(data2==0x02){ exit0=0;  Play_MP3();   }     }
          
        if(exit0==3){ select_limit(); 
        File_Size= Reed_File_Size(Address,x);  print=0;      
        if(data2==0x02){ exit0=0; Play_MP3();   };   }
   
        
                
        Enter_Button();
        Buttons();
 
    
    


}






void POWER_OFF() 
{
 
    if( Button4==0)
            {   
        
        
                  RDA5807M_Mute();
                Turn_Off_Vs1011 ();
                 exit0=1;
                 
               
    
            } 
                    
      


}






 