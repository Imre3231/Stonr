
#include <xc.h>

void Delay_ms(int x)
{
    int  i;
   int  j;
   for(i=0;i<x;i++)
      {
       for(j=0;j<200;j++)
       {
           Nop();/**Some delay***/   
            Nop();/**Some delay***/   
       }      
      
      }
}

void Delay_us(int x)
{
    int  i;
   int  j;
   for(i=0;i<x;i++)
      {
      
           Nop();/**Some delay***/   
            Nop();/**Some delay***/   
           
      
      }
}

