/*This Code applicable to e-ink(1.54/2.13/2.90) driven by HelTec AutoMation WiFi_Kit_Series Development Board.
  Simple e-ink Display example
  1.54-BLACK AND WHITE SCREEN(With a BLUE label.)--200 x 200 IMAGE_DATA 1,2
  2.13-BLACK , WHITE AND RED SCREEN--104 x 212 IMAGE_RED IMAGE_BLACK
  2.90-BLACK AND WHITE SCREEN--128 x 296 IMAGE 1,2,3,4,5
  AND SO ON.
  Please put the modeled array in the "imagedata.h" and "imagedata.cpp" files
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

/* Please select the size of the corresponding screen at "Epd Inch" on the tool menu bar of Arduino */

void setup() 
{
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  epd.Init(lut_full_update);
//#ifndef USE_583_BWY || USE_583_BWR
  Display_clear(); /* If you are using a 5.83-inch trichromatic screen, shield it */
//#endif
#if defined ( USE_154_BW_BLUE )
  Display_picture(IMAGE_DATA2);
  Display_clear();
  Display_picture(IMAGE_DATA);
  Display_clear();
  Display_picture(IMAGE_DATA1);
//  Display_String(30,170,20,8,"E-INK-1.54",&Font20,30,15);
#elif defined ( USE_154_BW_GREEN )
  Display_picture(IMAGE_154_BW);
#elif defined ( USE_154_BWY )
  Display_picture(IMAGE_154_BWY_2_BLACK,IMAGE_154_BWY_2_RED);
#elif defined ( USE_154_BWR_152 )
  Display_picture(IMAGE_154_BWR_2_BLACK,IMAGE_154_BWR_2_RED);
#elif defined ( USE_213_BW )
  Display_picture(IMAGE_213_BW_1);
#elif defined ( USE_213_BWR )
  Display_picture(IMAGE_BLACK,IMAGE_RED);
#elif defined ( USE_213_BWY )
  Display_picture(IMAGE_213_BWY_BLACK,IMAGE_213_BWY_RED);
#elif defined(USE_213_BWRou)
  Display_picture(IMAGE_213_BW_1);
#elif defined ( USE_260_BW )
  Display_picture(IMAGE_260_BW_BLACK,IMAGE_260_BW_RED);
#elif defined ( USE_260_BWR )
  Display_picture(IMAGE_260_BWR_BLACK,IMAGE_260_BWR_RED);
#elif defined ( USE_270_BW )
  Display_picture(IMAGE_270_BW_BLACK);
#elif defined ( USE_270_BWR )
  Display_picture(IMAGE_270_BWR_2_BLACK,IMAGE_270_BWR_2_RED);
#elif defined ( USE_290_BW )
  Display_picture(IMAGE2);
  Display_clear();
  Display_picture(IMAGE1);
  Display_clear();
  Display_picture(IMAGE);
//  Display_String(24,128,10,8,"E-INK-2.90",&Font16,50,90);
#elif defined ( USE_290_BWR )
  Display_picture(IMAGE_290_BWR_BLACK,IMAGE_290_BWR_RED);
#elif defined ( USE_290_BWY )
  Display_picture(IMAGE_290_BWY_BLACK,IMAGE_290_BWY_RED);
#elif defined ( USE_290_BWRou )
  Display_picture(IMAGE_290_BWRou);
#elif defined ( USE_420_BWR )
  Display_picture(IMAGE_420_BWR_BLACK,IMAGE_420_BWR_RED);
#elif defined ( USE_420_BWY )
  Display_picture(IMAGE_420_BWY_1_BLACK,IMAGE_420_BWY_1_RED);
#elif defined ( USE_420_BW )
  Display_picture(IMAGE_420_BW_1);
#elif defined ( USE_583_BWR )
  Display_picture( IMAGE_583_BWR );
#elif defined ( USE_583_BW )
  Display_picture( IMAGE_583_BW_1 );
#elif defined ( USE_583_BWY )
  Display_picture( IMAGE_583_BWY );
#elif defined ( USE_750_BWR )
  Display_picture( IMAGE_750_BWR );
#elif defined ( USE_750_BWY )
  Display_picture( IMAGE_750_BWY );
#elif defined ( USE_750_BW )
  Display_picture( IMAGE_750_BW );
#endif
}

void loop() 
{
    
}

void Display_clear()
{
#if ORDINARY_SCREEN
	epd.ClearFrame();
  //epd.DisplayFrame();
  
#elif SPECIAL_SCREEN
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
#if defined (USE_290_BW)
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
#endif
  delay(2000);
  
#endif
}

#if TWO_PARAMETER
void Display_picture(const unsigned char* IMAGE_BLACK,const unsigned char* IMAGE_RED)
{
  epd.DisplayFrame(IMAGE_BLACK, IMAGE_RED);
}

#elif  ONLY_A_PARAMETER
void Display_picture(const unsigned char* IMAGE_BLACK)
{
  epd.DisplayFrame(IMAGE_BLACK);
}

#elif SPECIAL_SCREEN
void Display_picture(const unsigned char* IMAGE_BUFFER)
{
  epd.SetFrameMemory(IMAGE_BUFFER);
  epd.DisplayFrame();
  epd.SetFrameMemory(IMAGE_BUFFER);
  epd.DisplayFrame();
  delay(2000);
}
#endif

/**
	Width,Heigh displays the fast read and height of the area.
	The starting position of the character in the display area of the TextX,TextY.
	Text is the display content.
	Font is the display font: font8, font12, font16, font20, font24.
	The starting position of the areaX,areaY display area relative to the screen is (0,0) in the upper right corner.
 * */

void Display_String(int width, int Heigh, int TextX, int TextY, const char* text, sFONT* font, int areaX,int aeraY )
{
  paint.Clear(COLORED);
  paint.SetWidth(width); /* Set the size of the area */
  paint.SetHeight(Heigh);
  paint.SetRotate(ROTATE_270); /* rotate the direction of the text */
  paint.DrawStringAt(TextX, TextY, text, font, UNCOLORED);

#if defined(USE_213_BWR) 
  //epd.SetPartialWindowBlack(paint.GetImage(), areaX, aeraY, paint.GetWidth(), paint.GetHeight());
  epd.SetPartialWindowRed(paint.GetImage(), areaX, aeraY, paint.GetWidth(), paint.GetHeight());

#elif defined(USE_154_BW_BLUE) || defined(USE_290_BW)
  epd.SetFrameMemory(paint.GetImage(), areaX,aeraY, paint.GetWidth(), paint.GetHeight());

#endif
  epd.DisplayFrame();
  delay(1000);
}
