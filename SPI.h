 
unsigned char WriteSPI( unsigned char data);
unsigned char WriteSPI6( unsigned char data);




unsigned char WriteSPI( unsigned char data)
{
SPI2BUF=data; // write to buffer for TX
while( !SPI2STATbits.SPIRBF); // wait transfer complete
return SPI2BUF; // read the received value
}// writeSPI



unsigned char ReadSPI(void)
{
    unsigned char data;
    data= WriteSPI(0xff);
    return data;
   
}



unsigned char WriteSPI2( unsigned char data)
{
SPI1BUF=data; // write to buffer for TX
while( !SPI1STATbits.SPIRBF); // wait transfer complete
return SPI1BUF; // read the received value
}// writeSPI




unsigned char ReadSPI2(void)
{
    unsigned char data;
    data= WriteSPI2(0xff);
    return data;
   
}