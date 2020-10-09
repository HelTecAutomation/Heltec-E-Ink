#include "DEPG0150BxS810FxX_BW.h"

/******************************* init ***************************************************/

void DEPG0150BxS810FxX_BW::EPD_Init(void) {
/* this calls the peripheral hardware interface, see epdif */
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
  WaitUntilIdle();//读busy信号
  SendCommand(0x12); // 软件复位    soft  reset
  WaitUntilIdle();
  
  Serial.println("e-Paper init OK!");	
}


/********************************* update ************************************************/
void DEPG0150BxS810FxX_BW::EPD_Update(void) {     			
  SendCommand(0x20);
  WaitUntilIdle();
}

/*********************************** deep sleep ******************************************/
void DEPG0150BxS810FxX_BW::EPD_DeepSleep(void) {
  SendCommand(0x10);
  SendData(0x01);   
  DelayMs(100); 
}

/******************************** EPD_ALL_image ******************************************/
void DEPG0150BxS810FxX_BW::EPD_ALL_image(const unsigned char *datas) {

  SendCommand(0x24);   //write RAM for black(0)/white (1)

  for (int i = 0; i < ALLSCREEN_BYTES; i++) {
    SendData(pgm_read_byte(&datas[i]));
  }	

  EPD_Update();
}

/********************************** All black *********************************************/
void DEPG0150BxS810FxX_BW::EPD_WhiteScreen_Black(void) {
  EPD_Load_Data(0x00);
}

/********************************** All white *********************************************/
void DEPG0150BxS810FxX_BW::EPD_WhiteScreen_White(void) {
  EPD_Load_Data(0xff);
}

/********************************** Load Data *********************************************/
void DEPG0150BxS810FxX_BW::EPD_Load_Data(unsigned char data) {
  SendCommand(0x24);   //write RAM for black(0)/white (1)

  for (int i = 0; i < ALLSCREEN_BYTES; i++) {
    SendData(data);
  }	

  EPD_Update();
}

/** DEPG0150BxS810FxX_BW.cpp END **/
