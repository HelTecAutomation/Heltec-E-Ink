#include "DEPG0213Bx800FxX_BW.h"

DEPG0213Bx800FxX_BW::~DEPG0213Bx800FxX_BW() {
};

DEPG0213Bx800FxX_BW::DEPG0213Bx800FxX_BW() {
    reset_pin = RST_PIN;
    dc_pin = DC_PIN;
    cs_pin = CS_PIN;
    busy_pin = BUSY_PIN;
};

/**
 *  @brief: basic function for sending commands
 */
void DEPG0213Bx800FxX_BW::SendCommand(unsigned char command) {
    DigitalWrite(dc_pin, LOW);
    SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void DEPG0213Bx800FxX_BW::SendData(unsigned char data) {
    DigitalWrite(dc_pin, HIGH);
    SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes LOW
 */
void DEPG0213Bx800FxX_BW::WaitUntilIdle(void) {
    while(DigitalRead(busy_pin) == HIGH) {      //LOW: idle, HIGH: busy
        DelayMs(100);
    }
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void DEPG0213Bx800FxX_BW::Reset(void) {
    DigitalWrite(reset_pin, LOW);                //module reset    
    DelayMs(100);
    DigitalWrite(reset_pin, HIGH);
    DelayMs(100);    
}

/************************************** init ************************************************/
void DEPG0213Bx800FxX_BW::EPD_Init(void) {
    /* this calls the peripheral hardware interface, see epdif */
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
	Reset();
	WaitUntilIdle();
    SendCommand(0x12); // soft reset
    WaitUntilIdle();
	
	Serial.println("e-Paper init OK!");	
}

/****************************** All screen update *******************************************/
void DEPG0213Bx800FxX_BW::EPD_ALL_image(const unsigned char *datas) {
   	unsigned int i;

    // SendCommand(0x4E);     
    // SendData(0x00);

    // SendCommand(0x4F);      
    // SendData(0xf9);
    // SendData(0x00);
    // WaitUntilIdle();	
    SendCommand(0x24);   //write RAM for black(0)/white (1)

	for (int i = 0; i < ALLSCREEN_GRAGHBYTES; i++) {
        SendData(pgm_read_byte(&datas[i]));
    }	

   	EPD_Update();		 
}

/********************************* update ***************************************************/
void DEPG0213Bx800FxX_BW::EPD_Update(void) {     			
    SendCommand(0x20);
    WaitUntilIdle();
    // DelayMs(100);   
}

/********************************** deep sleep **********************************************/
void DEPG0213Bx800FxX_BW::EPD_DeepSleep(void) {  	
    SendCommand(0x10); //enter deep sleep
    SendData(0x01); 
    DelayMs(100); 	
}

/********************************* Display All Black ****************************************/
void DEPG0213Bx800FxX_BW::EPD_WhiteScreen_Black(void) {
    EPD_Load_Data(0x00);
}

/********************************* Display All White ****************************************/
void DEPG0213Bx800FxX_BW::EPD_WhiteScreen_White(void) {
    EPD_Load_Data(0xff);
}

/********************************** Load Data ***********************************************/
void DEPG0213Bx800FxX_BW::EPD_Load_Data(unsigned char data) {
   unsigned int i,k;
    SendCommand(0x4E);     
    SendData(0x00);

    SendCommand(0x4F);       
    SendData(0xf9);
    SendData(0x00);

    WaitUntilIdle();
    SendCommand(0x24);   //write RAM for black(0)/white (1)

    for(k=0;k<250;k++) {
        for(i=0;i<16;i++) {
            SendData(data);
        }
    }
    EPD_Update();
}

DEPG0213Bx800FxX_BW epd213bw;

/* DEPG0213Bx800FxX_BW END */