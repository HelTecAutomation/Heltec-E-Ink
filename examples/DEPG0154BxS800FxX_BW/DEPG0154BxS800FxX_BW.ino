/*
DEPG0150BxS810FxX_BW is a 1.54 inch black and white screen
Display Resolution 200(H)×200(V) 
*/
#include "DEPG0154BxS800FxX_BW.h"
#include "picture.h"
#include "e_ink_display.h"

#define UNDEFINED -1
#ifdef CubeCell_Board //AB01
	#define FREQUENCY 2000000

	DEPG0154BxS800FxX_BW epd154bw(GPIO1, GPIO2, GPIO3, GPIO5, UNDEFINED, SPI_NUM_0, FREQUENCY);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin, spi_num, frequency
#elif defined( ESP32 )
	#define RST_PIN         16
	#define DC_PIN          22
	#define CS_PIN          18
	#define BUSY_PIN        23
	#define CLK_PIN         5

	DEPG0154BxS800FxX_BW epd154bw(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#elif defined( ESP8266 )
	#define RST_PIN         16
	#define DC_PIN          4
	#define CS_PIN          15
	#define BUSY_PIN        5
	#define CLK_PIN         14

	DEPG0154BxS800FxX_BW epd154bw(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#elif defined ( AVR )
	#define RST_PIN         8
	#define DC_PIN          9
	#define CS_PIN          10
	#define BUSY_PIN        7
#endif

unsigned char img[1024];
Paint pt(img, 0, 0);

unsigned long time_start_ms;
unsigned long time_now_s;
#define COLORED     0
#define UNCOLORED   1


void setup() {
	Serial.begin(115200);
	epd154bw.EPD_Init(); //Electronic paper initialization
    delay(100);
	epd154bw.EPD_ALL_image(gImage_152);	//Refresh the picture in full screen
	delay(5000);
  epd154bw.Clear();
  
  pt.SetWidth(152);
  pt.SetHeight(24);
  
  Serial.println("e-Paper Paint");
  pt.Clear(COLORED);
  pt.DrawStringAt(10, 4, "E-ink - 1.54!", &Font16, UNCOLORED);
  epd154bw.SetFrameMemory(pt.GetImage(), 0, 10, pt.GetWidth(), pt.GetHeight());
  delay(100);
  
  pt.Clear(UNCOLORED);
  pt.DrawStringAt(10, 4, "e-Paper Demo", &Font16, COLORED);
  epd154bw.SetFrameMemory(pt.GetImage(), 0, 30, pt.GetWidth(), pt.GetHeight());
	delay(100);

	pt.SetWidth(64);
	pt.SetHeight(64);

	pt.Clear(UNCOLORED);
	pt.DrawRectangle(0, 0, 40, 50, COLORED);
	pt.DrawLine(0, 0, 40, 50, COLORED);
	pt.DrawLine(40, 0, 0, 50, COLORED);
	epd154bw.SetFrameMemory(pt.GetImage(), 16, 60, pt.GetWidth(), pt.GetHeight());
	delay(100);

	epd154bw.HalLcd_Partial_Update();
	delay(2000);

}
void loop() {

}