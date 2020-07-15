/*
DEPG0290BxS75AFxX is a 2.9 inch black and white screen
*/
#include "DEPG0290BxS75AFxX.h"
#include "picture.h"
void setup() {
    Serial.begin(115200);
    epd296.EPD_HW_Init(); //Electronic paper initialization
    epd296.EPD_ALL_image(gImage_290black);	//Refresh the picture in full screen
    epd296.EPD_DeepSleep();  //Enter deep sleep	
}
void loop() {

}