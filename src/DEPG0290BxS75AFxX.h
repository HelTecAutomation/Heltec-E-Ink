#ifndef __EPD_213_H__
#define __EPD_213_H__
#include "epdif.h"

//250*122///////////////////////////////////////


#define ALLSCREEN_GRAGHBYTES	4736

/* Display resolution */
#define EPD_WIDTH       128
#define EPD_HEIGHT      296

class DEPG0290BxS75AFxX:EpdIf {
    public:
        DEPG0290BxS75AFxX();
        ~DEPG0290BxS75AFxX();
        void SendCommand(unsigned char command);
        void SendData(unsigned char data);
        void WaitUntilIdle(void);
        void Reset(void);
    public:
        void EPD_HW_Init(void); //Electronic paper initialization
        void EPD_Update(void);
            
        void EPD_WhiteScreen_Black(void);
        void EPD_WhiteScreen_White(void);
        void EPD_DeepSleep(void);
        //Display 

        void EPD_ALL_image(const unsigned char *datas);

    private:
        unsigned int dc_pin;
        unsigned int cs_pin;
        unsigned int reset_pin;
        unsigned int busy_pin;
        unsigned int height;
        unsigned int width;
};


extern DEPG0290BxS75AFxX epd296;
#endif