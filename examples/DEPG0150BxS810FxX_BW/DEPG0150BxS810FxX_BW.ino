/*
DEPG0150BxS810FxX_BW is a 1.54 inch black and white screen
Display Resolution 200(H)×200(V) 
*/
#include "DEPG0150BxS810FxX_BW.h"
#include "picture.h"

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

void setup() {
    Serial.begin(115200);
    epd154bw.EPD_Init(); //Electronic paper initialization
    epd154bw.EPD_ALL_image(gImage_154image_bw);	//Refresh the picture in full screen

    // delay(1000);
    // epd154bw.EPD_WhiteScreen_Black();
    // delay(1000);
    // epd154bw.EPD_WhiteScreen_White();
    epd154bw.EPD_DeepSleep();  //Enter deep sleep	
}
void loop() {

}