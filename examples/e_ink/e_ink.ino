/*
  This is a simple example show the e-ink
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  www.heltec.cn
  */
#include <SPI.h>
#include "e-ink.h"
#include "e-ink-display.h"
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1


#if defined( USE_154 )
unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8
Epd epd;

void setup() {

  Serial.begin(9600);
  #if defined( ESP32 )
  SPI.begin(SCK,MISO,MOSI,SS);

  #elif defined( ESP8266 )
  SPI.pins(SCK,MISO,MOSI,SS);
  SPI.begin();
  #endif
  if (epd.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  delay(1000);


  paint.SetWidth(30);
  paint.SetHeight(196);
  paint.SetRotate(ROTATE_270);
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(40, 10, "Hello world!", &Font16, COLORED);
  epd.SetFrameMemory(paint.GetImage(),70, 5, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  delay(1000);

  epd.SetFrameMemory(IMAGE_DATA2);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_DATA2);
  epd.DisplayFrame();
  delay(2000);

  epd.SetFrameMemory(IMAGE_DATA);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_DATA);
  epd.DisplayFrame();
  delay(2000);

  epd.SetFrameMemory(IMAGE_DATA1);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_DATA1);
  epd.DisplayFrame();
  delay(2000);

  epd.SetFrameMemory(IMAGE_DATA1);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_DATA1);
  epd.DisplayFrame();


    if (epd.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }


}

void loop()
{
  //paint.SetWidth(30);           /*设置区域的大小*/
  //paint.SetHeight(170);
  //paint.SetRotate(ROTATE_270); /*旋转文字的方向*/

  //paint.Clear(COLORED);          /*将区域显示为黑色*/
  //paint.DrawStringAt(20,8, "E-INK-1.54", &Font20, UNCOLORED);
 // epd.SetFrameMemory(paint.GetImage(), 30, 15, paint.GetWidth(), paint.GetHeight());     /*设置区域的位置*/
  //epd.DisplayFrame();
  //delay(1000);

}

#elif defined( USE_213 )

  Epd epd;
void setup() {
  Serial.begin(9600);
  #if defined( USE_ESP32 )
  SPI.begin(SCK,MISO,MOSI,SS);
  #elif defined( USE_ESP8266 )
  SPI.pins(SCK,MISO,MOSI,SS);
  SPI.begin();
  #endif
  if (epd.Init() != 0) {
    Serial.print("e-Paper init failed");
    return;
  }

   epd.ClearFrame();
   epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);

/*
  paint.Clear(COLORED);
  paint.DrawStringAt(8, 2, "Hello world", &Font12, UNCOLORED);
  epd.SetPartialWindowRed(paint.GetImage(), 0, 24, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
*/
}

void loop() {
  // put your main code here, to run repeatedly:
}

#elif defined( USE_290 )

unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8
Epd epd;

void setup() {
  Serial.begin(9600);
  #if defined( USE_ESP32 )
  SPI.begin(SCK,MISO,MOSI,SS);
  #elif defined( USE_ESP8266 )
  SPI.pins(SCK,MISO,MOSI,SS);
  SPI.begin();
  #endif
   if (epd.Init(lut_full_update) != 0)
  {
      Serial.print("e-Paper init failed");
      return;
  }
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  delay(2000);

  epd.SetFrameMemory(IMAGE);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE);
  epd.DisplayFrame();
  delay(1000);

      if (epd.Init(lut_partial_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }
}

void loop() {




 //paint.SetWidth(24);   /*设置区域的大小*/
 // paint.SetHeight(128);
  //paint.SetRotate(ROTATE_270);   /*旋转文字的方向*/
 // paint.Clear(COLORED);          /*将区域显示为黑色*/
 // paint.DrawStringAt(10,8, "E-INK-2.90", &Font16, UNCOLORED);     /*设置文字的位置*/
  //epd.SetFrameMemory(paint.GetImage(), 50,90, paint.GetWidth(), paint.GetHeight());    /*设置区域的位置*/
 // epd.DisplayFrame();
 // delay(1000);
}
#endif
