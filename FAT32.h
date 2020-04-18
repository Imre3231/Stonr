 






/*
00h	1 bytes	Ordinal field
01h	2 bytes	Unicode Character 1
03h	2 bytes	Unicode Character 2
05h	2 bytes	Unicode Character 3
07h	2 bytes	Unicode Character 4
09h	2 bytes	Unicode Character 5
0Bh	1 bytes	Flag byte
0Ch	1 bytes	Reserved - Always 00h
0Dh	1 bytes	Checksum
0Eh	2 bytes	Unicode Character 6
10h	2 bytes	Unicode Character 7
12h	2 bytes	Unicode Character 8
14h	2 bytes	Unicode Character 9
16h	2 bytes	Unicode Character 10
18h	2 bytes	Unicode Character 11
1Ah	2 bytes	Always 0000h
1Ch	2 bytes	Unicode Character 12
1Eh	2 bytes	Unicode Character 13
*/

 unsigned int Data1; 
unsigned long Data2; 
unsigned int Master_Boot_Record=8192;

unsigned char Filename_Table[50] ;

 
//unsigned char Longfilename_Character[14]={ 0x1E,0x1C,0x1A,0x18,0x16,0x14,0x12,0x10,0x0E,0x09,0x07,0x05,0x03,0x01 } ; 
unsigned char Longfilename_Character[14]={ 0x01,0x03,0x05,0x07,0x09,0x0E,0x10,0x12,0x14,0x16,0x18,0x1C,0x1E } ; 

unsigned char txt_FAT32[17]={0x20,0x4E,0x41,0x4D,0x45,0x20,0x20,0x20,0x20,0x46,0x41,0x54,0x33,0x32,0x20,0x20,0x20} ; 


  
 unsigned int File_Offset[900]; 
 
unsigned int Lineoffset;

unsigned int Bytes_Per_Sector;

unsigned int Sectors_Per_Cluster; 
unsigned int Number_of_FATs;

unsigned long Hidden_Sectors;
unsigned long Sectors_Per_FAT;
unsigned long Root_Cluster_Number; 
unsigned int  Reserved_Sectors;

unsigned long Root_Directory; 
unsigned int Number_Of_Files_Indirectory;

unsigned long Reed_File_Size(unsigned long Directory_Entry, unsigned int Filenumber );
unsigned char Reed_File_Type(unsigned long Directory_Entry, unsigned int Filenumber );



unsigned int Search_File_Indirectory(unsigned long Directory_Entry,unsigned char *buff,unsigned int *buff2);

unsigned char Reed_Long_Filename(unsigned long Directory_Entry, unsigned int Filenumber, char *txtbuff);

unsigned char Reed_Byte(unsigned char offset,unsigned char *buff);
unsigned int  Reed_Word(unsigned char offset,unsigned char *buff);
unsigned long Reed_Dword(unsigned char offset,unsigned char *buff);

void Open_Root_Directory(void);


void Check_MBR_FAT32(unsigned char *buff)
{
    
   unsigned char data=0;
   unsigned int ii=0;   
   Read_Buffer(8192,buff);  
   for(ii=0;ii<15;ii++)
{
   
   if(txt_FAT32[ii]==buff[ii+0x49]){data=1;}else{data=0;}      
   if(data==0){break;};    
   }
   
   if(data==0){text1 ("FAT32 not Found",0 ,60,1,Black,White);    }
   if(data==1){text1 ("FAT32 Found",0 ,60,1,Black,White);    }
 
}

 



void Init_FAT32(void)
{
    
     
     unsigned int Data;
     
    fillScreen2(Black);
    
    text1 ("FAT32 initialization",0 ,0,1,Black,White);

    text1 ("Read sector 0 ",0 ,20,1,Black,White);    
    
     Read_Buffer(0,buffer);
     
     if(buffer[0x1c7]==0x20)
     {
      text1 ("MBR at 8192",0 ,40,1,Black,White);    
     }
 
    Lineoffset=80;
    Check_MBR_FAT32(buffer);
     /**********************************************************/
    Bytes_Per_Sector=Reed_Word(0x0B,buffer);
    text1 ("Bytes_Per_Sector",0 ,Lineoffset,1,Black,White);
    intToStr(Bytes_Per_Sector,buff2,1,4);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
    /**********************************************************/ 
    Sectors_Per_Cluster=Reed_Byte(0x0D,buffer);
    text1 ("Sectors_Per_Cluster",0 ,Lineoffset,1,Black,White);
    intToStr(Sectors_Per_Cluster,buff2,1,4);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
     /**********************************************************/
    Number_of_FATs=Reed_Byte(0x10,buffer);
    text1 ("Number_of_FATs",0 ,Lineoffset,1,Black,White);
    intToStr(Number_of_FATs,buff2,1,4);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
    /**********************************************************/
    
    Hidden_Sectors= Reed_Dword((0x1C),buffer);
    text1 ("Hidden_Sectors",0 ,Lineoffset,1,Black,White);
    intToStr(Hidden_Sectors,buff2,1,12);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
    /**********************************************************/
    Sectors_Per_FAT= Reed_Dword((0x24),buffer);
    text1 ("Sectors_Per_FAT",0 ,Lineoffset,1,Black,White);
    intToStr(Sectors_Per_FAT,buff2,1,12);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;

   /**********************************************************/
    Root_Cluster_Number= Reed_Dword((0x2C),buffer);
    text1 ("Root_Cluster_Number",0 ,Lineoffset,1,Black,White);
    intToStr(Root_Cluster_Number,buff2,1,12);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
  
    /**********************************************************/
    Reserved_Sectors= Reed_Dword((0x0E),buffer);
    text1 ("Reserved_Sectors",0 ,Lineoffset,1,Black,White);
    intToStr(Reserved_Sectors,buff2,1,12);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
    
    
    /**********************************************************/
    Root_Directory=( 24576 );
    text1 ("Root_Directory",0 ,Lineoffset,1,Black,White);
    intToStr(Root_Directory,buff2,1,12);
    text1 (buff2,180 ,Lineoffset,1,Black,White);
    Lineoffset=Lineoffset+20;
    
    
    Open_Root_Directory();
    
}




  unsigned int Search_File_Indirectory(unsigned long Directory_Entry, unsigned char *buff,unsigned int *buff2)
{
  unsigned int ii;
  unsigned long Directory_Entry2;
  unsigned int offset=0;
   unsigned int offset2=0;
  unsigned int counter=0;
  
  Directory_Entry2=Directory_Entry;
  
  if(Directory_Entry==Root_Directory){ buff2[0]=0; counter++;  }
  
  Read_Buffer(Directory_Entry,buffer); 
  
   offset=0;
  Read_Buffer(Directory_Entry2,buffer); 
  while(1)
  {
      offset2=0;
    for(ii=0;ii<16;ii++)
    {
        
        
    if(((buff[((offset2)+0X0B)]==0x10)) & ((buff[(offset2)]!=0xE5)  ) ){   buff2[counter]=offset; counter++; };
    offset=offset+2;   offset2=(offset2+0x20); ; } 
    Directory_Entry++;
    Read_Buffer(Directory_Entry,buffer);
    if((buff[0x00]==0x00)&(buff[0x10]==0x00)){break;};
  }
  
  offset=0;
  Read_Buffer(Directory_Entry2,buffer); 
  
  
    while(1)
  {
      offset2=0;
    for(ii=0;ii<16;ii++)
    {
        
        
    if(((buff[((offset2)+0X0B)]==0x30)) & ((buff[(offset2)]!=0xE5)  ) ){   buff2[counter]=offset; counter++; };
    offset=offset+2;   offset2=(offset2+0x20); ; } 
    Directory_Entry++;
    Read_Buffer(Directory_Entry,buffer);
    if((buff[0x00]==0x00)&(buff[0x10]==0x00)){break;};
    
    
  }
  
    offset=0;
  Read_Buffer(Directory_Entry2,buffer); 
  

    while(1)
  {
      offset2=0;
    for(ii=0;ii<16;ii++)
    {
        
        
    if(((buff[((offset2)+0X0B)]==0x20)) & ((buff[(offset2)]!=0xE5)  ) ){   buff2[counter]=offset; counter++; };
    offset=offset+2;   offset2=(offset2+0x20); ; } 
    Directory_Entry2++;
    Read_Buffer(Directory_Entry2,buffer);
    if((buff[0x00]==0x00)&(buff[0x10]==0x00)){break;};
  }
  

  
      offset=0;
  Read_Buffer(Directory_Entry2,buffer); 
  
  
  
        return counter;
}

  
  
  
  

void Reed_Filename(unsigned long Directory_Entry, unsigned int Filenumber, char *txtbuff)
{
    unsigned int Buffer_Offset;
    unsigned int Offset;
    unsigned int ii;
    Buffer_Offset= (File_Offset[Filenumber]/32); 
    Read_Buffer(((Directory_Entry+Buffer_Offset)),buffer); 
    Offset=(File_Offset[Filenumber]-(Buffer_Offset*32));
    for(ii=0;ii<11;ii++)
    {txtbuff[ii]=buffer[(Offset*0x10)+ii];}
    txtbuff[11]=0x00; // End
 
}


unsigned char Reed_File_Type(unsigned long Directory_Entry, unsigned int Filenumber )
{
    unsigned char Data;
    unsigned int Buffer_Offset;
    unsigned int Offset;
    unsigned int ii;
    Buffer_Offset= (File_Offset[Filenumber]/32); 
    Read_Buffer(((Directory_Entry+Buffer_Offset)),buffer); 
    Offset=(File_Offset[Filenumber]-(Buffer_Offset*32));
    
    
     
    if( buffer[(Offset*0x10)+0x0B]==0x10){Data=0x01 ;}  // Folder type
    if( buffer[(Offset*0x10)+0x0B]==0x30){Data=0x01 ;} 
    if( buffer[(Offset*0x10)+0x0B]==0x20)
    {
       if( buffer[(Offset*0x10)+0x08]==0x4D) {Data=0x02 ;   } 
       if( buffer[(Offset*0x10)+0x08]==0x42) {Data=0x03 ;   } 
    }
       
    
    return Data;
     
 
}



unsigned long Reed_File_Size(unsigned long Directory_Entry, unsigned int Filenumber )
{
   
    unsigned int Buffer_Offset;
    unsigned int Offset;
    unsigned int ii;
    
    
   unsigned long Data;
    
    unsigned long HIGHWORD;
    unsigned long LOWWORD;
    unsigned long HIGHBYTE=0;                       
    unsigned long LOWBYTE=0;
   
    Buffer_Offset= (File_Offset[Filenumber]/32); 
    Read_Buffer(((Directory_Entry+Buffer_Offset)),buffer); 
    Offset=(File_Offset[Filenumber]-(Buffer_Offset*32));
    
    
 
              
  LOWBYTE= buffer[((Offset*0x10)+0x1C)];
  HIGHBYTE= buffer[((Offset*0x10)+0x1D)];
  LOWWORD=((HIGHBYTE<<8)|LOWBYTE);
  
  LOWBYTE= buffer[((Offset*0x10)+0x1E)];
  HIGHBYTE= buffer[((Offset*0x10)+0x1F)];
  HIGHWORD=((HIGHBYTE<<8)|LOWBYTE);
  
  Data=((HIGHWORD<<16)|LOWWORD);
    
    return Data;
     
 
}






unsigned char Reed_Long_Filename(unsigned long Directory_Entry, unsigned int Filenumber, char *txtbuff)
{   
    unsigned char counter=0;
    unsigned char counter2=0;
    unsigned int Buffer_Offset;
    unsigned int Offset;
    unsigned int Offset2;
    unsigned int i;
    unsigned char ii;
    unsigned char Loffset;
    
    Buffer_Offset= (File_Offset[Filenumber]/32); 
    Read_Buffer(((Directory_Entry+Buffer_Offset)),buffer); 
    Offset=(File_Offset[Filenumber]-(Buffer_Offset*32));
    Offset2=((Offset*0x10)-0x20);
   
   if(buffer[(Offset*0x10)-0x20+0x0B]==0x0F)
   { 
       
        
          for(i=0;i<4;i++)
          {
               for(ii=0;ii<13;ii++)
               {  

                 txtbuff[ii+(13*counter)]=buffer[Offset*0x10+(Longfilename_Character[ii])-(0x20*(counter+1))] ;;
                 
                 if(buffer[Offset*0x10+(Longfilename_Character[ii])-(0x20*(counter+1))]==0  ){break ;}
                 
               }
               counter++;

               

          }   
    }
       
}



unsigned long File_Start_Addres(unsigned long Directory_Entry,unsigned int Filenumber )
{
    unsigned long CLUSTER;
    unsigned int Buffer_Offset;
    unsigned int Offset;
    unsigned int ii;

    unsigned long Data;
    
    unsigned long HIGHWORD;
    unsigned long LOWWORD;
    unsigned long HIGHBYTE=0;                       
    unsigned long LOWBYTE=0;
   
    
   Buffer_Offset= (File_Offset[Filenumber]/32);  
   Read_Buffer(((Directory_Entry+Buffer_Offset)),buffer);  
   Offset=(File_Offset[Filenumber]-(Buffer_Offset*32));
   
   
   

  LOWBYTE= buffer[((Offset*0x10)+0x1A)];
  HIGHBYTE= buffer[((Offset*0x10)+0x1B)];
  LOWWORD=((HIGHBYTE<<8)|LOWBYTE);
  
  LOWBYTE= buffer[((Offset*0x10)+0x14)];
  HIGHBYTE= buffer[((Offset*0x10)+0x15)];
  HIGHWORD=((HIGHBYTE<<8)|LOWBYTE);
  
  CLUSTER=((HIGHWORD<<16)|LOWWORD);
  
  if(CLUSTER==0){Data=0;}
  else{ Data=(((CLUSTER-2)*Sectors_Per_Cluster));}
  
  
  
  return Data;
  
}


void Open_Directory(unsigned long Directory_Entry)
{
 Read_Buffer(Directory_Entry, buffer);

}


void Open_Root_Directory(void)
{
 Read_Buffer(Root_Directory, buffer);

}




unsigned int Reed_Word(unsigned char offset,unsigned char *buff)
{
  
    unsigned int Data;
    unsigned int HIGHBYTE=0;                       
    unsigned char LOWBYTE=0;

    LOWBYTE=buff[offset];                       
    HIGHBYTE=buff[(offset+1)];  
    Data=((HIGHBYTE<<8)|LOWBYTE);
    return Data;

}
 
 
 
unsigned char Reed_Byte(unsigned char offset,unsigned char *buff)
{
  
    unsigned char Data;
    Data=buff[offset];
    return Data;

}


unsigned long Reed_Dword(unsigned char offset,unsigned char *buff)
{
    unsigned long Data;
    
    unsigned long HIGHWORD;
    unsigned int LOWWORD;
    unsigned int HIGHBYTE=0;                       
    unsigned int LOWBYTE=0;
   
    
    
    LOWBYTE=buff[offset];                       
    HIGHBYTE=buff[(offset+1)];  
    LOWWORD=((HIGHBYTE<<8)|LOWBYTE);

   
    LOWBYTE=buff[offset+2];                       
    HIGHBYTE=buff[(offset+3)];  
    HIGHWORD=((HIGHBYTE<<8)|LOWBYTE);
    
    Data=((HIGHWORD<<16)|LOWWORD);
   
    return Data;

}
