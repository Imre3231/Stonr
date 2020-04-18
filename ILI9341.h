


#define TFT_RS_pin      LATCbits.LATC3      //
#define TFT_WR_pin      LATCbits.LATC4      //
#define TFT_RD_pin      LATCbits.LATC2      //
//  #define TFT_CS_pin      LATCbits.LATC2       //   
#define TFT_RST_pin     LATCbits.LATC1       //

#define TFT_data_out_port LATB

#define TFT_DISP_HEIGHT 239
#define TFT_DISP_WIDTH  319
 




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

#define TRUE                                                                             1
#define FALSE                                                                            0

#define YES                                                                              1
#define NO                                                                               0

 

#define HIGH                                                                             1
#define LOW                                                                              0

#define DAT                                                                              1
#define CMD                                                                              0

#define SQUARE                                                                           0
#define ROUND                                                                            1

#define ILI9341_NOP                                                                      0x00
#define ILI9341_RESET                                                                    0x01
#define ILI9341_READ_DISPLAY_IDENTIFICATION_INFORMATION                                  0x04
#define ILI9341_READ_DISPLAY_STATUS                                                      0x09
#define ILI9341_READ_DISPLAY_POWER_MODE                                                  0x0A
#define ILI9341_READ_DISPLAY_MADCTL                                                      0x0B
#define ILI9341_READ_DISPLAY_PIXEL_FORMAT                                                0x0C
#define ILI9341_READ_DISPLAY_IMAGE_FORMAT                                                0x0D
#define ILI9341_READ_DISPLAY_SIGNAL_MODE                                                 0x0E
#define ILI9341_READ_DISPLAY_SELF_DIAGNOSTIC_RESULT                                      0x0F
#define ILI9341_ENTER_SLEEP_MODE                                                         0x10
#define ILI9341_SLEEP_OUT                                                                0x11
#define ILI9341_PARTIAL_MODE_ON                                                          0x12
#define ILI9341_NORMAL_DISPLAY_MODE_ON                                                   0x13
#define ILI9341_DISPLAY_INVERSION_OFF                                                    0x20
#define ILI9341_DISPLAY_INVERSION_ON                                                     0x21
#define ILI9341_GAMMA                                                                    0x26
#define ILI9341_DISPLAY_OFF                                                              0x28
#define ILI9341_DISPLAY_ON                                                               0x29
#define ILI9341_COLUMN_ADDR                                                              0x2A
#define ILI9341_PAGE_ADDR                                                                0x2B
#define ILI9341_GRAM                                                                     0x2C
#define ILI9341_COLOR_SET                                                                0x2D
#define ILI9341_MEMORY_READ                                                              0x2E
#define ILI9341_PARTIAL_AREA                                                             0x30
#define ILI9341_VERTICAL_SCROLLING_DEFINITION                                            0x33
#define ILI9341_TEARING_EFFECT_LINE_OFF                                                  0x34
#define ILI9341_TEARING_EFFECT_LINE_ON                                                   0x35
#define ILI9341_MAC                                                                      0x36
#define ILI9341_VERTICAL_SCROLLING_START_ADDRESS                                         0x37
#define ILI9341_IDLE_MODE_OFF                                                            0x38
#define ILI9341_IDLE_MODE_ON                                                             0x39
#define ILI9341_PIXEL_FORMAT                                                             0x3A
#define ILI9341_WMC                                                                      0x3C
#define ILI9341_RMC                                                                      0x3E
#define ILI9341_SET_TEAR_SCANLINE                                                        0x44
#define ILI9341_WDB                                                                      0x51
#define ILI9341_READ_DISPLAY_BRIGHTNESS                                                  0x52
#define ILI9341_WCD                                                                      0x53
#define ILI9341_READ_CTRL_DISPLAY                                                        0x54
#define ILI9341_WCABC                                                                    0x55
#define ILI9341_RCABC                                                                    0x56
#define ILI9341_WCABCMB                                                                  0x5E
#define ILI9341_RCABCMB                                                                  0x5F
#define ILI9341_RGB_INTERFACE                                                            0xB0
#define ILI9341_FRC                                                                      0xB1
#define ILI9341_FRAME_CTRL_NM                                                            0xB2
#define ILI9341_FRAME_CTRL_IM                                                            0xB3
#define ILI9341_FRAME_CTRL_PM                                                            0xB4
#define ILI9341_BPC                                                                      0xB5
#define ILI9341_DFC                                                                      0xB6
#define ILI9341_ENTRY_MODE_SET                                                           0xB7
#define ILI9341_BACKLIGHT_CONTROL_1                                                      0xB8
#define ILI9341_BACKLIGHT_CONTROL_2                                                      0xB9
#define ILI9341_BACKLIGHT_CONTROL_3                                                      0xBA
#define ILI9341_BACKLIGHT_CONTROL_4                                                      0xBB
#define ILI9341_BACKLIGHT_CONTROL_5                                                      0xBC
#define ILI9341_BACKLIGHT_CONTROL_6                                                      0xBD
#define ILI9341_BACKLIGHT_CONTROL_7                                                      0xBE
#define ILI9341_BACKLIGHT_CONTROL_8                                                      0xBF
#define ILI9341_POWER1                                                                   0xC0
#define ILI9341_POWER2                                                                   0xC1
#define ILI9341_VCOM1                                                                    0xC5
#define ILI9341_VCOM2                                                                    0xC7
#define ILI9341_POWERA                                                                   0xCB
#define ILI9341_POWERB                                                                   0xCF
#define ILI9341_READ_ID1                                                                 0xDA
#define ILI9341_READ_ID2                                                                 0xDB
#define ILI9341_READ_ID3                                                                 0xDC
#define ILI9341_PGAMMA                                                                   0xE0
#define ILI9341_NGAMMA                                                                   0xE1
#define ILI9341_DTCA                                                                     0xE8
#define ILI9341_DTCB                                                                     0xEA
#define ILI9341_POWER_SEQ                                                                0xED
#define ILI9341_3GAMMA_EN                                                                0xF2
#define ILI9341_INTERFACE                                                                0xF6
#define ILI9341_PRC                                                                      0xF7

#define PORTRAIT_1                                                                       1
#define PORTRAIT_2                                                                       2
#define LANDSCAPE_1                                                                      3
#define LANDSCAPE_2                                                                      4

#define X_max                                                                            240
#define Y_max                                                                            320

#define pixels                                                                           (X_max * Y_max)


unsigned int MAX_X = X_max;
unsigned int MAX_Y = Y_max;





void TFT_init();
void TFT_PORT_init();
void TFT_reset();
void Draw_Pixel(unsigned int X, unsigned int Y,unsigned int COLOR);
void Write_Data(unsigned int num );
void Write_Data2(unsigned int data );
void Write_Command(unsigned int command);
void Column_Address_Set(unsigned int StartX);
void Page_Address_Set(unsigned int StartY);
void SetCurPos(unsigned int X, unsigned int Y);
void FillScreen( unsigned int color);




void TFT_PORT_init()
{
    TRISB=0x0000; 
    TRISD=0x0000;
    PORTB=0xFFFF;
    PORTD=0xFFFF;
    Delay_ms(10);
}


void TFT_reset()
{
    TFT_RST_pin = 1;
    Delay_ms(500);
    TFT_RST_pin = 0;
    Delay_ms(500);
    TFT_RST_pin = 1;
    Delay_ms(500);
}


void TFT_init()
{
    TFT_PORT_init();
    TFT_reset();
    TFT_RD_pin = 1;  
   
    Delay_ms(500);
 //-----------------------------------------------------------------------------
    //************* Start Initial Sequence **********//
Write_Command(0x0028);//display OFF

Write_Command(0x0011);
Write_Data(0x0000);//exit SLEEP mode

Write_Command(0x00CB);//Power Control A
Write_Data(0x0039);//always 0x39
Write_Data(0x002C);//always 0x2C
Write_Data(0x0000);//always 0x00
Write_Data(0x0034);//Vcore = 1.6V
Write_Data(0x0002);//DDVDH = 5.6V

Write_Command(0x00CF);//Power Control B
Write_Data(0x0000);//always 0x00
Write_Data(0x0081);//PCEQ off
Write_Data(0x0030);//ESD protection

Write_Command(0x00E8);//Driver timing control A
Write_Data(0x0085);//non-overlap
Write_Data(0x0001);//EQ timing
Write_Data(0x0079);//Pre-charge timing

Write_Command(0x00EA);//Driver timing control B
Write_Data(0x0000);//Gate driver timing
Write_Data(0x0000);//always 0x00

Write_Command(0x00ED);//Power-On sequence control
Write_Data(0x0064);//soft start
Write_Data(0x0003);//power on sequence
Write_Data(0x0012);//power on sequence
Write_Data(0x0081);//DDVDH enhance on

Write_Command(0x00F7);//Pump ratio control
Write_Data(0x0020);//DDVDH=2xVCI
										  
Write_Command(0x00C0);//power control 1
Write_Data(0x0026);

Write_Command(0x00C1);//power control 2
Write_Data(0x0011);

Write_Command(0x00C5);//VCOM control 1
Write_Data(0x0035);
Write_Data(0x003E);

Write_Command(0x00C7);//VCOM control 2
Write_Data(0x00BE);

Write_Command(0x0036);//memory access control = BGR
Write_Data(0x0028);
/*
Write_Data(0x0058);
Write_Data(0x0088);
Write_Data(0x0028);
Write_Data(0x00E8);
*/

Write_Command(0x00B1);//frame rate control
Write_Data(0x0000);
Write_Data(0x0010);

Write_Command(0x00B6);//display function control
Write_Data(0x000A);
Write_Data(0x00A2);

Write_Command(0x003A);//pixel format = 16 bit per pixel
Write_Data(0x0055);

Write_Command(0x00F2);//3G Gamma control
Write_Data(0x0002);//off

Write_Command(0x0026);//Gamma curve 3
Write_Data(0x0001);

/*
TFT_24S_Write_Command(0x00E0);TFT_24S_Write_Data(0x001F);//positive gamma correction
							  TFT_24S_Write_Data(0x001B);
							  TFT_24S_Write_Data(0x0018);
							  TFT_24S_Write_Data(0x000B);
							  TFT_24S_Write_Data(0x000F);
							  TFT_24S_Write_Data(0x0009);
							  TFT_24S_Write_Data(0x0046);
							  TFT_24S_Write_Data(0x00B5);
							  TFT_24S_Write_Data(0x0037);
							  TFT_24S_Write_Data(0x000A);
							  TFT_24S_Write_Data(0x000C);
							  TFT_24S_Write_Data(0x0007);
							  TFT_24S_Write_Data(0x0007);
							  TFT_24S_Write_Data(0x0005);
							  TFT_24S_Write_Data(0x0000);
TFT_24S_Write_Command(0x00E1);TFT_24S_Write_Data(0x0000);//negative gamma correction
							  TFT_24S_Write_Data(0x0024);
							  TFT_24S_Write_Data(0x0027);
							  TFT_24S_Write_Data(0x0004);
							  TFT_24S_Write_Data(0x0010);
							  TFT_24S_Write_Data(0x0006);
							  TFT_24S_Write_Data(0x0039);
							  TFT_24S_Write_Data(0x0074);
							  TFT_24S_Write_Data(0x0048);
							  TFT_24S_Write_Data(0x0005);
							  TFT_24S_Write_Data(0x0013);
							  TFT_24S_Write_Data(0x0038);
							  TFT_24S_Write_Data(0x0038);
							  TFT_24S_Write_Data(0x003A);
							  TFT_24S_Write_Data(0x001F);
*/

   Write_Command(0x11); //Exit Sleep
   Delay_ms(80);
   Write_Command(0x29); //display on
   
        Write_Command(0x002a);              // FIRST CURSOR POSITON SETUP 
        Write_Data2(0x0000);
        Write_Data2(0x013f);
        Write_Command(0x002b);
        Write_Data2(0x0000);
        Write_Data2(0x00EF);
        Write_Command(0x002c);
}

//-----------------------------------------------------------------------------
 void FillScreen( unsigned int color)
{
     int j;
   int i;
  for(i=0;i<=239;i++)          //i->240
  {
     
     Page_Address_Set(i);

            for(j=0;j<=319;j++)        //j->320
            {
              Column_Address_Set(j);
              Write_Data(color);
            }

   
  }
   
   
}
 
 
    void fillBOX(unsigned int color)
{
     
    unsigned int i;
    unsigned int ii;                                                  
    TFT_RS_pin=1;
   
    
    for(ii=0; ii<160; ii++)
    {     
    Column_Address_Set(0);
    Page_Address_Set(ii);
    Write_Command(0x002c);     
      
        for(i=0; i<160; i++)
       {
         Write_Data(color);

        }
     }
  
}
                       

 void fillScreen2(unsigned int color)
{
     
     unsigned int i;
     
    Column_Address_Set(0);
    Page_Address_Set(0);
    Write_Command(0x002c);   
    TFT_RS_pin=1;
   
    for(i=0; i<38400; i++)
    {
        Write_Data(color);
        Write_Data(color);     
    }
   
}
 

 
 
void test_01(void)
{

    fillScreen2(Black);
    fillScreen2(Blue);
    fillScreen2(Red);
    fillScreen2(Green);
    fillScreen2(Cyan);
    fillScreen2(Yellow);
    fillScreen2(Orange);
    fillScreen2(White);
    fillScreen2(Magenta);
}


void Draw_Pixel(unsigned int X, unsigned int Y,unsigned int COLOR)
{
       SetCurPos(X,Y);
       Write_Data(COLOR);
}

void SetCurPos(unsigned int StartX, unsigned int StartY)
{
    
        Write_Command(0x002a);
        Write_Data2(StartX);
        Write_Data2(0x013f);
        Write_Command(0x002B);
        Write_Data2(StartY);
        Write_Data2(0x00EF);
        Write_Command(0x002c); 
        
 }




void Column_Address_Set(unsigned int StartX)  //Command 2AH 
{
        Write_Command(0x002a);
        Write_Data2(StartX);
        Write_Command(0x002c);                // MEMORY WRITE
}


void Page_Address_Set(unsigned int StartY)    //Command 2BH 
{
        Write_Command(0x002B);
        Write_Data2(StartY);
        Write_Command(0x002c);               // MEMORY WRITE
}


void Write_Command(unsigned int command)
{
    TFT_RS_pin = 0;
    TFT_data_out_port = command;
    TFT_WR_pin = 0;       
   
    TFT_WR_pin = 1;  
     
}


void Write_Data(unsigned int data )
{
    TFT_RS_pin = 1;
    TFT_data_out_port = data;
    TFT_WR_pin = 0;  
    
    TFT_WR_pin = 1;
     
}


void Write_Data2(unsigned int data )
{
	TFT_RS_pin = 1;
    TFT_data_out_port = ((data>>8)& 0x00ff);
    TFT_WR_pin = 0;
    TFT_WR_pin = 1;
    TFT_data_out_port = ((data)& 0x00ff);
    TFT_WR_pin = 0;
    TFT_WR_pin = 1;
     
}

/*
      GLCD_FONT2 (xx,100 ,100,Black,Red,0,Consolas52x67);
     Delay_ms(500);
     xx++;
     if(xx>9){xx=0;};
 */
