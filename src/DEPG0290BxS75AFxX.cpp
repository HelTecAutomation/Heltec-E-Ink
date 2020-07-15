#include "DEPG0290BxS75AFxX.h"

DEPG0290BxS75AFxX::~DEPG0290BxS75AFxX() {
};

DEPG0290BxS75AFxX::DEPG0290BxS75AFxX() {
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
    width = EPD_WIDTH;
    height = EPD_HEIGHT;
};

/**
 *  @brief: basic function for sending commands
 */
void DEPG0290BxS75AFxX::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void DEPG0290BxS75AFxX::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes LOW
 */
void DEPG0290BxS75AFxX::WaitUntilIdle(void) {
    while(DigitalRead(busy_pin) == HIGH) {      //LOW: idle, HIGH: busy
        DelayMs(100);
    }      
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void DEPG0290BxS75AFxX::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(100);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(100);    
}

/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void DEPG0290BxS75AFxX::EPD_HW_Init(void)
{
		 /* this calls the peripheral hardware interface, see epdif */
	//Serial.begin(115200);
#if defined( ESP32 )
	SPI.begin(CLK_PIN,MISO,SDI_PIN,CS_PIN);

#elif defined( ESP8266 )
	SPI.pins(CLK_PIN,MISO,SDI_PIN,CS_PIN);
	SPI.begin();
#endif
	if (IfInit() != 0) {
		Serial.print("e-Paper init failed");
		return;
	}
	// Reset();
	WaitUntilIdle();
    SendCommand(0x12); // soft reset
    WaitUntilIdle();
	
    SendCommand(0x74); //set analog block control       
     SendData(0x54);
    SendCommand(0x7E); //set digital block control          
     SendData(0x3B);
	
    SendCommand(0x01); //Driver output control      
     SendData(0x27);
     SendData(0x01);
     SendData(0x00);
	
    SendCommand(0x11); //data entry mode       
     SendData(0x01);
		
    SendCommand(0x44); //set Ram-X address start/end position   
     SendData(0x00);
    SendData(0x0F);    //0x0F-->(15+1)*8=128
	
    SendCommand(0x45); //set Ram-Y address start/end position          
     SendData(0x27);   //0x0127-->(295+1)=296
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

    SendCommand(0x4E);     
    SendData(0x00);
    SendCommand(0x4F);       
    SendData(0x27);
    SendData(0x01);
	WaitUntilIdle();
	Serial.println("e-Paper init OK!");	
}
//////////////////////////////All screen update////////////////////////////////////////////
void DEPG0290BxS75AFxX::EPD_ALL_image(const unsigned char *datas)
{
   	unsigned int i;

    SendCommand(0x24);   //write RAM for black(0)/white (1)

	for (int i = 0; i < ALLSCREEN_GRAGHBYTES; i++) {
        SendData(pgm_read_byte(&datas[i]));
    }	

   	EPD_Update();		 
}



/////////////////////////////////////////////////////////////////////////////////////////
void DEPG0290BxS75AFxX::EPD_Update(void)
{   
    SendCommand(0x21);
    SendData(0x40); 

    SendCommand(0x22);
    SendData(0xC7);    			
    SendCommand(0x20);
    WaitUntilIdle();
    DelayMs(100);   
}



void DEPG0290BxS75AFxX::EPD_DeepSleep(void)
{  	
  SendCommand(0x10); //enter deep sleep
  SendData(0x01); 
}


void DEPG0290BxS75AFxX::EPD_WhiteScreen_Black(void)
{
   unsigned int i,k;
    SendCommand(0x24);   //write RAM for black(0)/white (1)
	for(k=0;k<296;k++)
  {
		for(i=0;i<16;i++)
		{
			SendData(0x00);
			}
  }
	
		EPD_Update();
}




void DEPG0290BxS75AFxX::EPD_WhiteScreen_White(void)
{
   unsigned int i,k;
    SendCommand(0x24);   //write RAM for black(0)/white (1)
	for(k=0;k<296;k++)
  {
		for(i=0;i<16;i++)
		{
			SendData(0xff);
			}
  }
	
	EPD_Update();
}


//////////////////////////////////////////////////////////////////////////////////////
DEPG0290BxS75AFxX epd296;