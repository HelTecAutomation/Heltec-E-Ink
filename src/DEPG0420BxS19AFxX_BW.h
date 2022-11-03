#ifndef __DEPG0420BxS19AFxX_BW_H__
#define __DEPG0420BxS19AFxX_BW_H__
#include "EpdBase.h"


#define MAX_LINE_BYTES    50
#define MAX_COLUMN_BYTES  300
#define ALLSCREEN_BYTES   15000

class DEPG0420BxS19AFxX_BW: public EpdBase {
    public:
        DEPG0420BxS19AFxX_BW(uint8_t _rst, uint8_t _dc, uint8_t _cs,  uint8_t _busy, int8_t _clk=-1, uint8_t _spi_num = 0 ,uint32_t _freq = 2000000): \
        EpdBase(_rst, _dc, _cs, _busy, _clk, _spi_num, _freq){}

        ~DEPG0420BxS19AFxX_BW(){};

    public:
        void EPD_Init(void); //Electronic paper initialization
        void EPD_Update(void);
            
        void EPD_WhiteScreen_Black(void);
        void EPD_WhiteScreen_White(void);
        void EPD_DeepSleep(void);
        //Display 

        void EPD_ALL_image(const unsigned char *datas);

    private:
        void EPD_Load_Data(unsigned char data);
};

#endif