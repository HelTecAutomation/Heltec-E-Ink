#ifndef __DEPG0150BxS810FxX_BW_H__
#define __DEPG0150BxS810FxX_BW_H__
#include "EpdBase.h"

/////////////////////////////////////////

#define	 MAX_LINE_BYTES   25
#define  MAX_COLUMN_BYTES 200	
#define  ALLSCREEN_BYTES  5000
/* Display resolution */
// #define EPD_WIDTH       
// #define EPD_HEIGHT      

class DEPG0150BxS810FxX_BW:public EpdBase {
    public:
        DEPG0150BxS810FxX_BW(uint8_t _rst, uint8_t _dc, uint8_t _cs,  uint8_t _busy, int8_t _clk=-1, uint8_t _spi_num = 0 ,uint32_t _freq = 2000000): \
        EpdBase(_rst, _dc, _cs, _busy, _clk, _spi_num, _freq){}

        ~DEPG0150BxS810FxX_BW(){}

    public:
        void EPD_Init(void); //Electronic paper initialization
        void EPD_Update(void);  
        void EPD_DeepSleep(void);
        //Display 
        void EPD_ALL_image(const unsigned char *datas);
        void EPD_WhiteScreen_Black(void);
        void EPD_WhiteScreen_White(void);

    private:
        void EPD_Load_Data(unsigned char data);

};

#endif/** DEPG0150BxS810FxX_BW.h END**/