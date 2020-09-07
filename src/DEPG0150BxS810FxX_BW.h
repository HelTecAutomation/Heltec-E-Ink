#ifndef __DEPG0150BxS810FxX_BW_H__
#define __DEPG0150BxS810FxX_BW_H__
#include "epdif.h"

/////////////////////////////////////////

#define	 MAX_LINE_BYTES   25
#define  MAX_COLUMN_BYTES 200	
#define  ALLSCREEN_BYTES  5000
/* Display resolution */
// #define EPD_WIDTH       
// #define EPD_HEIGHT      

class DEPG0150BxS810FxX_BW:EpdIf {
    public:
        DEPG0150BxS810FxX_BW();
        ~DEPG0150BxS810FxX_BW();
        void SendCommand(unsigned char command);
        void SendData(unsigned char data);
        void WaitUntilIdle(void);
        void Reset(void);
    public:
        void EPD_Init(void); //Electronic paper initialization
        void EPD_Update(void);
            
        void EPD_DeepSleep(void);
        //Display 

        void EPD_ALL_image(const unsigned char *datas);
        void EPD_WhiteScreen_Black(void);
        void EPD_WhiteScreen_White(void);

    private:
        unsigned int dc_pin;
        unsigned int cs_pin;
        unsigned int reset_pin;
        unsigned int busy_pin;

        void EPD_Load_Data(unsigned char data);

};

extern DEPG0150BxS810FxX_BW epd154bw;

#endif/** DEPG0150BxS810FxX_BW.h END**/