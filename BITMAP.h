


void Open_Bitmap(unsigned long Directory_Entry )
{ 
   unsigned int data;
   unsigned int Buffer_Offset=0;
   unsigned int Offset;
   unsigned int ii;
   unsigned int i; 
   unsigned int increment=0x36; 
   unsigned int color=Red;
   
   unsigned int RED; 
   unsigned int GREEN; 
   unsigned int BLUE;


 Read_Buffer((Directory_Entry),buffer); 
        
for(i=0;i<=240;i++)   
{  
        Page_Address_Set(i);
for(ii=0;ii<=319;ii++)
{       
        Column_Address_Set( ii );   
    
                 
        RED=buffer[increment];
        increment++;
         if(increment>511)
        { Directory_Entry++;Read_Buffer((Directory_Entry),buffer); increment=0; }
        GREEN=buffer[increment];
        increment++;
        if(increment>511)
        { Directory_Entry++;Read_Buffer((Directory_Entry),buffer); increment=0; }
    
        BLUE=buffer[increment];
        increment++;
        
         if(increment>511)
        { Directory_Entry++;Read_Buffer((Directory_Entry),buffer); increment=0; }
 

        RED=((RED&0xF8)>>3);
        GREEN=((GREEN&0xFC)<<3);
        BLUE=((BLUE&0xF8)<<8);

        color=(RED|GREEN|BLUE);

        Write_Data(color);

    
 }
}
     
 
   
   
   
    
 
}

/*

void slideshow(void)
{
unsigned int Number_Of_Files_Indirectory;
  
    Number_Of_Files_Indirectory=Search_File_Indirectory(Root_Directory,0,buffer,File_Offset) ; 
    tostring(Number_Of_Files_Indirectory,buff2); 

    text1 ( buff2,200 ,0,1,Black,White);
    text1 ( "Files Found",240 ,0,1,Black,White);


   tostring((File_Offset[1]),buff2); 
   text1 ( buff2,0 ,0,1,Black,White);
    
    
    tostring2(Number_Of_Files_Indirectory,buff2); 
    
    Address=File_Start_Addres( Root_Directory,x );
    Open_Bitmap( Address);
 
    if(x==Number_Of_Files_Indirectory){x=0;} 
    text1 ( buff2,200 ,0,1,Black,White);
    text1 ( "Files ",100 ,0,1,Black,White);
    
    tostring2(x,buff2); 

    text1 ( buff2,150 ,0,1,Black,White);
 
   Reed_Filename(Root_Directory,x,Filename_Table);
   text1 ( Filename_Table,0 ,0,1,Black,White);
    
    Reed_Long_Filename(Root_Directory,x,Filename_Table);
    
     text1 (Filename_Table,0 ,60,1,Black,White);
     x++;if(x>Number_Of_Files_Indirectory);
    
       Delay_ms(5000);     

}


*/



