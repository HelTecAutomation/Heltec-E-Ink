#ifndef __DEPG0290BxS75AFxX_BW_H__
#define __DEPG0290BxS75AFxX_BW_H__
#include "epdif.h"

//250*122///////////////////////////////////////


#define ALLSCREEN_GRAGHBYTES	4736

/* Display resolution */
// #define EPD_WIDTH       
// #define EPD_HEIGHT      

class DEPG0290BxS75AFxX:EpdIf {
    public:
        DEPG0290BxS75AFxX(uint8_t _rst, uint8_t _dc, uint8_t _cs,  uint8_t _busy, int8_t _clk=-1, uint8_t _spi_num = 0 ,uint32_t _freq = 2000000) {
            this->dc_pin = _dc;
            this->cs_pin = _cs;
            this->reset_pin = _rst;
            this->busy_pin = _busy;
            this->freq = _freq;
            this->spi_num = _spi_num;
            this->clk_pin = _clk;
        }
        ~DEPG0290BxS75AFxX();
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
        uint8_t     dc_pin;
        uint8_t     cs_pin;
        uint8_t     reset_pin;
        uint8_t     busy_pin;
        uint32_t    freq;
        uint8_t     spi_num;
        uint8_t     clk_pin;

        void EPD_Load_Data(unsigned char data);
};

#endif