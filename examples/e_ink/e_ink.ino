/*This Code applicable to e-ink(1.54/2.13/2.90) driven by HelTec AutoMation WiFi_Kit_Series Development Board.
  Simple e-ink Display example
  1.54--200 x 200 IMAGE_DATA 1,2
  2.13--104 x 212 IMAGE_RED IMAGE_BLACK
  2.90--128 x 296 IMAGE 1,2,3,4,5
*/ 

#include <SPI.h>
#include "e_ink.h"
#include "e_ink_display.h"
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1

unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8
Epd epd;

/*Please select screen size in <e-ink.h>*/

void setup() 
{
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
 epd.Init(lut_full_update);
 Display_clear();
#if defined(USE_154)
  Display_picture(IMAGE_DATA2);
  Display_clear();
  Display_picture(IMAGE_DATA);
  Display_clear();
  Display_picture(IMAGE_DATA1);
  Display_String(30,170,20,8,"E-INK-1.54",&Font20,30,15);
#elif defined(USE_213)
  Display_Color_picture(IMAGE_BLACK,IMAGE_RED);
#elif defined(USE_290)
  Display_picture(IMAGE2);
  Display_clear();
  Display_picture(IMAGE1);
  Display_clear();
  Display_picture(IMAGE);
  Display_String(24,128,10,8,"E-INK-2.90",&Font16,50,90);
#endif
}

void loop() 
{
    
}

void Display_clear()
{
#if defined(USE_213)
  epd.ClearFrame();
  //epd.DisplayFrame();
#elif defined(USE_154) || defined(USE_290)
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  delay(2000);
#endif
}

#if defined(USE_213)
void Display_Color_picture(const unsigned char* IMAGE_BLACK,const unsigned char* IMAGE_RED)
{
  epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
}
#elif defined(USE_154) || defined(USE_290)
void Display_picture(const unsigned char* IMAGE_BUFFER)
{
  epd.SetFrameMemory(IMAGE_BUFFER);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_BUFFER);
  epd.DisplayFrame();
  delay(2000);
}
#endif

/*width,Heigh显示区域的快读和高度
  TextX,TextY在显示区域中字符的起始位置
  text为显示内容
  font为显示字体：font8、font12、font16、font20、font24
  areaX,areaY显示区域相对于屏的起始位置，右上角为（0，0）
*/
void Display_String(int width, int Heigh, int TextX, int TextY, const char* text, sFONT* font, int areaX,int aeraY )
{
  paint.Clear(COLORED);
  paint.SetWidth(width);   /*设置区域的大小*/
  paint.SetHeight(Heigh);
  paint.SetRotate(ROTATE_270);   /*旋转文字的方向*/
  paint.DrawStringAt(TextX, TextY, text, font, UNCOLORED);

#if defined(USE_213)
  //epd.SetPartialWindowBlack(paint.GetImage(), areaX, aeraY, paint.GetWidth(), paint.GetHeight());
  epd.SetPartialWindowRed(paint.GetImage(), areaX, aeraY, paint.GetWidth(), paint.GetHeight());
#elif defined(USE_154) || defined(USE_290)
  epd.SetFrameMemory(paint.GetImage(), areaX,aeraY, paint.GetWidth(), paint.GetHeight());
#endif
  epd.DisplayFrame();
  delay(1000);
}
