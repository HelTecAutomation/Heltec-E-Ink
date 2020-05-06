#ifndef __EPD_213_H__
#define __EPD_213_H__
#include "epdif.h"

//250*122///////////////////////////////////////


#define ALLSCREEN_GRAGHBYTES	4000

#define MONO 1                  
#define RED  2                  

/* Display resolution */
#define EPD_WIDTH       122
#define EPD_HEIGHT      250

class QYEG0213RWS800:EpdIf {
    public:
        QYEG0213RWS800();
        ~QYEG0213RWS800();
        void SendCommand(unsigned char command);
        void SendData(unsigned char data);
        void WaitUntilIdle(void);
        void Reset(void);
    public:
        void EpaperIO_Init(void);
        void Epaper_READBUSY(void);


        void EPD_HW_Init(void); //Electronic paper initialization
        void EPD_Update(void);
            
        void EPD_WhiteScreen_Red(void);
        void EPD_WhiteScreen_Black(void);
        void EPD_WhiteScreen_White(void);
        void EPD_DeepSleep(void);
        //Display 

        void EPD_ALL_image(const unsigned char *datas1,const unsigned char *datas2);
        void EPD_Dis_Part(unsigned int x_start,unsigned int y_start,const unsigned char * datas,const unsigned char color_mode,unsigned int PART_COLUMN,unsigned int PART_LINE);
        void EPD_Dis_Part_mult(unsigned int x_startA,unsigned int y_startA,const unsigned char * datasA1,const unsigned char * datasA2,
                                unsigned int x_startB,unsigned int y_startB,const unsigned char * datasB1,const unsigned char * datasB2,
                                                    unsigned int PART_COLUMN,unsigned int PART_LINE);
    private:
        unsigned int dc_pin;
        unsigned int cs_pin;
        unsigned int reset_pin;
        unsigned int busy_pin;
        unsigned int height;
        unsigned int width;
};


extern QYEG0213RWS800 epd213;
#endif