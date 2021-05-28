/*
DEPG0150BxS810FxX_BW is a 1.54 inch black and white screen
Display Resolution 200(H)×200(V) 
*/
#include "DEPG0150BxS810FxX_BW.h"
#include "picture.h"
#include "e_ink_display.h"

#define UNDEFINED -1
#ifdef CubeCell_Board //AB01
	#define FREQUENCY 2000000

	DEPG0150BxS810FxX_BW epd154bw(GPIO1, GPIO2, GPIO3, GPIO5, UNDEFINED, SPI_NUM_0, FREQUENCY);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin, spi_num, frequency
#elif defined( ESP32 )
	#define RST_PIN         16
	#define DC_PIN          22
	#define CS_PIN          18
	#define BUSY_PIN        23
	#define CLK_PIN         5

	DEPG0150BxS810FxX_BW epd154bw(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
#elif defined( ESP8266 )
	#define RST_PIN         16
	#define DC_PIN          4
	#define CS_PIN          15
	#define BUSY_PIN        5
	#define CLK_PIN         14

	DEPG0150BxS810FxX_BW epd154bw(RST_PIN, DC_PIN, CS_PIN, BUSY_PIN, CLK_PIN);//reset_pin, dc_pin, cs_pin, busy_pin, clk_pin
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
	// put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("e-Paper init and clear");
	epd154bw.LDirInit();
	epd154bw.Clear();
	pt.SetWidth(200);
	pt.SetHeight(24);

	Serial.println("e-Paper Paint");
	pt.Clear(COLORED);
	pt.DrawStringAt(30, 4, "E-ink - 1.54!", &Font16, UNCOLORED);

	epd154bw.SetFrameMemory(pt.GetImage(), 0, 10, pt.GetWidth(), pt.GetHeight());

	pt.Clear(UNCOLORED);
	pt.DrawStringAt(30, 4, "e-Paper Demo", &Font16, COLORED);
	epd154bw.SetFrameMemory(pt.GetImage(), 0, 30, pt.GetWidth(), pt.GetHeight());

	pt.SetWidth(64);
	pt.SetHeight(64);

	pt.Clear(UNCOLORED);
	pt.DrawRectangle(0, 0, 40, 50, COLORED);
	pt.DrawLine(0, 0, 40, 50, COLORED);
	pt.DrawLine(40, 0, 0, 50, COLORED);
	epd154bw.SetFrameMemory(pt.GetImage(), 16, 60, pt.GetWidth(), pt.GetHeight());

	pt.Clear(UNCOLORED);
	pt.DrawCircle(32, 32, 30, COLORED);
	epd154bw.SetFrameMemory(pt.GetImage(), 120, 60, pt.GetWidth(), pt.GetHeight());

	pt.Clear(UNCOLORED);
	pt.DrawFilledRectangle(0, 0, 40, 50, COLORED);
	epd154bw.SetFrameMemory(pt.GetImage(), 16, 130, pt.GetWidth(), pt.GetHeight());

	pt.Clear(UNCOLORED);
	pt.DrawFilledCircle(32, 32, 30, COLORED);
	epd154bw.SetFrameMemory(pt.GetImage(), 120, 130, pt.GetWidth(), pt.GetHeight());
	epd154bw.DisplayFrame();
	delay(2000);

	Serial.println("e-Paper show pic");
	epd154bw.HDirInit();
	epd154bw.Display(gImage_154image_bw);

	//Part display
	epd154bw.HDirInit();
	epd154bw.DisplayPartBaseImage(gImage_154image_bw);

  Serial.println("e-Paper print number");
	pt.SetWidth(50);
	pt.SetHeight(60);
	pt.Clear(UNCOLORED);

	char i = 0;
	char str[10][10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	for (i = 0; i < 10; i++) {
		pt.Clear(UNCOLORED);
		pt.DrawStringAt(10, 10, str[i], &Font24, COLORED);
		epd154bw.SetFrameMemory(pt.GetImage(), 80, 70, pt.GetWidth(), pt.GetHeight());
		epd154bw.DisplayPartFrame();
		delay(100);
	}

	Serial.println("e-Paper clear and goto sleep");
	epd154bw.HDirInit();
	epd154bw.Clear();
	epd154bw.Sleep();
}
void loop() {

}
