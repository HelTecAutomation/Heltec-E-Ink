/*
DEPG0213Bx800FxX_BW is a 2.13 inch black and white screen
Display Resolution 122(H)×250(V) 
*/
#include "DEPG0213Bx800FxX_BW.h"
#include "picture.h"
void setup() {
    Serial.begin(115200);
    epd213bw.EPD_Init(); //Electronic paper initialization
    epd213bw.EPD_ALL_image(gImage_213image_bw);	//Refresh the picture in full screen
    // epd213bw.EPD_DeepSleep();  //Enter deep sleep

    // epd213bw.EPD_WhiteScreen_Black();
    // delay(1000);
    // epd213bw.EPD_WhiteScreen_White();	
}
void loop() {

}