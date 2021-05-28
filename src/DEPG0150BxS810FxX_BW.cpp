#include "DEPG0150BxS810FxX_BW.h"

// High Direction
int DEPG0150BxS810FxX_BW::HDirInit(void)
{
#if defined( ESP32 )
	SPI.begin(this->clk_pin, MISO,MOSI, this->cs_pin);
#elif defined( ESP8266 )
	SPI.pins(this->clk_pin, MISO, MOSI, this->cs_pin);
	SPI.begin();
#elif defined( CubeCell_Board )//AB01
  SPI.begin(this->cs_pin, this->freq, this->spi_num);
#endif
	/* this calls the peripheral hardware interface, see epdif */
	if (!this->spiFlag && IfInit() != 0) {
		return -1;
	}
	this->spiFlag = 1;
	/* EPD hardware init start */
	Reset();

	WaitUntilIdle();
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();

	SendCommand(0x01); //Driver output control
	SendData(0xC7);
	SendData(0x00);
	SendData(0x01);

	SendCommand(0x11); //data entry mode
	SendData(0x01);

	SendCommand(0x44); //set Ram-X address start/end position
	SendData(0x00);
	SendData(0x18);    //0x0C-->(18+1)*8=200

	SendCommand(0x45); //set Ram-Y address start/end position
	SendData(0xC7);   //0xC7-->(199+1)=200
	SendData(0x00);
	SendData(0x00);
	SendData(0x00);

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x01);

	SendCommand(0x18);
	SendData(0x80);

	SendCommand(0x22); // //Load Temperature and waveform setting.
	SendData(0XB1);
	SendCommand(0x20);

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;
	SendData(0xC7);
	SendData(0x00);
	WaitUntilIdle();
	/* EPD hardware init end */

	return 0;
}

// Low Direction
int DEPG0150BxS810FxX_BW::LDirInit(void)
{
#if defined( ESP32 )
	SPI.begin(this->clk_pin, MISO,MOSI, this->cs_pin);
#elif defined( ESP8266 )
	SPI.pins(this->clk_pin, MISO, MOSI, this->cs_pin);
	SPI.begin();
#elif defined( CubeCell_Board )//AB01
  SPI.begin(this->cs_pin, this->freq, this->spi_num);
#endif
	/* this calls the peripheral hardware interface, see epdif */
	if (!this->spiFlag && IfInit() != 0) {
		return -1;
	}
	this->spiFlag = 1;
	/* EPD hardware init start */
	Reset();

	WaitUntilIdle();
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();

	SendCommand(0x01); //Driver output control
	SendData(0xC7);
	SendData(0x00);
	SendData(0x00);

	SendCommand(0x11); //data entry mode
	SendData(0x03);

  SendCommand(0x44);
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  SendData((0 >> 3) & 0xFF);
  SendData((200 >> 3) & 0xFF);
  SendCommand(0x45);
  SendData(0 & 0xFF);
  SendData((0 >> 8) & 0xFF);
  SendData(200 & 0xFF);
  SendData((200 >> 8) & 0xFF);

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x01);

	SendCommand(0x18);
	SendData(0x80);

	SendCommand(0x22); // //Load Temperature and waveform setting.
	SendData(0XB1);
	SendCommand(0x20);

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;
	SendData(0xC7);
	SendData(0x00);
	WaitUntilIdle();
	/* EPD hardware init end */

	return 0;
}

void DEPG0150BxS810FxX_BW::Clear(void)
{
	int w, h;
	w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	h = EPD_HEIGHT;
 
	SendCommand(0x24);
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}
	//DISPLAY REFRESH
	DisplayFrame();
}

void DEPG0150BxS810FxX_BW::Display(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24);
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	//DISPLAY REFRESH
	DisplayFrame();
}

void DEPG0150BxS810FxX_BW::DisplayPartBaseImage(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24);
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}

		SendCommand(0x26);
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	//DISPLAY REFRESH
	DisplayFrame();
}

void DEPG0150BxS810FxX_BW::DisplayPartBaseWhiteImage(void)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	SendCommand(0x24);
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}

	SendCommand(0x26);
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}


	//DISPLAY REFRESH
	DisplayFrame();
}


void DEPG0150BxS810FxX_BW::DisplayPart(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24);
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	//DISPLAY REFRESH
	DisplayPartFrame();
}


/**
 *  @brief: private function to specify the memory area for data R/W
 */
void DEPG0150BxS810FxX_BW::SetMemoryArea(int x_start, int y_start, int x_end, int y_end)
{
	SendCommand(0x44);
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	SendData((x_start >> 3) & 0xFF);
	SendData((x_end >> 3) & 0xFF);
	SendCommand(0x45);
	SendData(y_start & 0xFF);
	SendData((y_start >> 8) & 0xFF);
	SendData(y_end & 0xFF);
	SendData((y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void DEPG0150BxS810FxX_BW::SetMemoryPointer(int x, int y)
{
	SendCommand(0x4e);
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	SendData((x >> 3) & 0xFF);
	SendCommand(0x4F);
	SendData(y & 0xFF);
	SendData((y >> 8) & 0xFF);
	WaitUntilIdle();
}


/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void DEPG0150BxS810FxX_BW::DisplayFrame(void)
{
	//DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xF7);
	SendCommand(0x20);
	WaitUntilIdle();
}

void DEPG0150BxS810FxX_BW::DisplayPartFrame(void)
{
	SendCommand(0x22);
	SendData(0xFF);
	SendCommand(0x20);
	WaitUntilIdle();
}


void DEPG0150BxS810FxX_BW::SetFrameMemory(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
)
{
	int x_end;
	int y_end;
	
	DigitalWrite(reset_pin, LOW);                //module reset
	DelayMs(10);
	DigitalWrite(reset_pin, HIGH);
	DelayMs(10);
	SendCommand(0x3c);
	SendData(0x80);

	if (
	        image_buffer == NULL ||
	        x < 0 || image_width < 0 ||
	        y < 0 || image_height < 0
	) {
		return;
	}
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	x &= 0xF8;
	image_width &= 0xF8;
	if (x + image_width >= this->width) {
		x_end = this->width - 1;
	} else {
		x_end = x + image_width - 1;
	}
	if (y + image_height >= this->height) {
		y_end = this->height - 1;
	} else {
		y_end = y + image_height - 1;
	}
	SetMemoryArea(x, y, x_end, y_end);
	SetMemoryPointer(x, y);
	SendCommand(0x24);
	/* send the image data */
	for (int j = 0; j < y_end - y + 1; j++) {
		for (int i = 0; i < (x_end - x + 1) / 8; i++) {
			SendData(image_buffer[i + j * (image_width / 8)]);
		}
	}
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Init() to awaken
 */
void DEPG0150BxS810FxX_BW::Sleep()
{
	SendCommand(0x10); //enter deep sleep
	SendData(0x01);
	DelayMs(200);

	DigitalWrite(reset_pin, LOW);
}

/** DEPG0150BxS810FxX_BW.cpp END **/
