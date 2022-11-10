#include "DEPG0420BxS19AFxX_BW.h"

/************************************** init ************************************************/
void DEPG0420BxS19AFxX_BW::EPD_Init(void) {
#if defined( ESP32 )
	SPI.begin(this->clk_pin, MISO,MOSI, this->cs_pin);
#elif defined( ESP8266 )
	SPI.pins(this->clk_pin, MISO, MOSI, this->cs_pin);
	SPI.begin();
#elif defined( CubeCell_Board )//AB01
    SPI.begin(this->cs_pin, this->freq, this->spi_num);
#endif

	if (IfInit() != 0) {
		Serial.print("e-Paper init failed");
		return;
	}
	Reset();
    WaitUntilIdle();
    SendCommand(0x12); // soft reset
    WaitUntilIdle();
	
    SendCommand(0x74); //set analog block control       
     SendData(0x54);
    SendCommand(0x7E); //set digital block control          
     SendData(0x3B);
	
    SendCommand(0x01); //Driver output control      
     SendData(0x2B);
     SendData(0x01);
     SendData(0x00);
	
    SendCommand(0x11); //data entry mode       
     SendData(0x01);
		
    SendCommand(0x44); //set Ram-X address start/end position   
     SendData(0x00);
    SendData(0x31);    //0x31-->(49+1)*8=400
	
    SendCommand(0x45); //set Ram-Y address start/end position          
     SendData(0x2B);   //0x012B-->(299+1)=300
    SendData(0x01);
     SendData(0x00);
    SendData(0x00); 
    SendCommand(0x3C); //set border 
     SendData(0x01);

    SendCommand(0x18); // use the internal temperature sensor
    SendData(0x80);

    SendCommand(0x22);  
    SendData(0xB1); 
    SendCommand(0x20); 
    WaitUntilIdle();	
    Serial.println("e-Paper init OK!");	
}

/****************************** All screen update *******************************************/
void DEPG0420BxS19AFxX_BW::EPD_ALL_image(const unsigned char *datas) {
   	unsigned int i;

    SendCommand(0x24);   //write RAM for black(0)/white (1)

	for (int i = 0; i < ALLSCREEN_BYTES; i++) {
        SendData(pgm_read_byte(&datas[i]));
    }	

   	EPD_Update();		 
}

/********************************* update ***************************************************/
void DEPG0420BxS19AFxX_BW::EPD_Update(void) {      			
    SendCommand(0x22);
    SendData(0xC7);    			
    SendCommand(0x20);
    WaitUntilIdle();
    DelayMs(100);   
}

/********************************** deep sleep **********************************************/
void DEPG0420BxS19AFxX_BW::EPD_DeepSleep(void) {  	
   SendCommand(0x10);
   SendData(0x01);   
   DelayMs(100); 		
}

/********************************* Display All Black ****************************************/
void DEPG0420BxS19AFxX_BW::EPD_WhiteScreen_Black(void) {
    EPD_Load_Data(0x00);
	 
}

/********************************* Display All White ****************************************/
void DEPG0420BxS19AFxX_BW::EPD_WhiteScreen_White(void)
{
    EPD_Load_Data(0xFF);

}

/********************************** Load Data ***********************************************/
void DEPG0420BxS19AFxX_BW::EPD_Load_Data(unsigned char data) {
  uint32_t i,j; 

  SendCommand(0x4E);     
  SendData(0x00);
  SendCommand(0x4F);       
  SendData(0x2B);
  SendData(0x01);
  WaitUntilIdle();
  SendCommand(0x24);   
  for(i=0;i<300;i++)
      {
         for(j=0;j<50;j++)
             {
	 SendData(data);
             }
       }
    EPD_Update();
}

/* DEPG0420BxS19AFxX_BW.cpp END */