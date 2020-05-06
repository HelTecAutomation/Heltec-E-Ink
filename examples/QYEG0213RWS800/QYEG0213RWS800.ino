/**
  *This example is the latest 2.13 black and white red ink screen code.
  *Compared with the previous 2.13 black and white red Tri Color ink screen, the biggest change is that the pixel point is changed from 212x104 to 250x122.
  *When selecting this program, please pay attention to whether the ink screen in your hand is the latest 2.13 black and white red ink screen.
  */

#include "QYEG0213RWS800.h"
#include "picture.h"
void setup() {
    Serial.begin(115200);
    epd213.EPD_HW_Init(); //Electronic paper initialization
    epd213.EPD_ALL_image(gImage_213black,gImage_213red);	//Refresh the picture in full screen
    epd213.EPD_DeepSleep();  //Enter deep sleep	
}
void loop() {

}