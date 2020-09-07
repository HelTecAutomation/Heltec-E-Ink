/*
DEPG0150BxS810FxX_BW is a 1.54 inch black and white screen
Display Resolution 200(H)×200(V) 
*/
#include "DEPG0150BxS810FxX_BW.h"
#include "picture.h"
void setup() {
    Serial.begin(115200);
    epd154bw.EPD_Init(); //Electronic paper initialization
    epd154bw.EPD_ALL_image(gImage_154image_bw);	//Refresh the picture in full screen
    // epd154bw.EPD_DeepSleep();  //Enter deep sleep	

    // epd154bw.EPD_WhiteScreen_Black();
    // delay(1000);
    // epd154bw.EPD_WhiteScreen_White();
}
void loop() {

}