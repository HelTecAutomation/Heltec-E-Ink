#ifndef __DEPG0213Bx800FxX_BW_H__
#define __DEPG0213Bx800FxX_BW_H__
#include "epdif.h"

//250*122///////////////////////////////////////


#define ALLSCREEN_GRAGHBYTES	4000

/* Display resolution */
// #define EPD_WIDTH       
// #define EPD_HEIGHT      

class DEPG0213Bx800FxX_BW:EpdIf {
    public:
        DEPG0213Bx800FxX_BW();
        ~DEPG0213Bx800FxX_BW();
        void SendCommand(unsigned char command);
        void SendData(unsigned char data);
        void WaitUntilIdle(void);
        void Reset(void);

    public:
        void EPD_Init(void); //Electronic paper initialization
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

        void EPD_Load_Data(unsigned char data);
};


extern DEPG0213Bx800FxX_BW epd213bw;
#endif