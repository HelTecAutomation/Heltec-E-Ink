/*
DEPG0290BxS75AFxX is a 2.9 inch black and white screen
Display Resolution 128(H)×296(V)
*/
#include "DEPG0290BxS75AFxX_BW.h"
#include "picture.h"
void setup() {
    Serial.begin(115200);
    epd290bw.EPD_Init(); //Electronic paper initialization
    epd290bw.EPD_ALL_image(gImage_290image_bw);	//Refresh the picture in full screen
    // epd290bw.EPD_DeepSleep();  //Enter deep sleep	

    // epd290bw.EPD_WhiteScreen_Black();
    // delay(1000);
    // epd290bw.EPD_WhiteScreen_White();
}
void loop() {

}