#ifndef __DEPG0150BxS810FxX_BW_H__
#define __DEPG0150BxS810FxX_BW_H__
#include "EpdBase.h"

/////////////////////////////////////////

#define	 MAX_LINE_BYTES   25
#define  MAX_COLUMN_BYTES 200	
#define  ALLSCREEN_BYTES  5000

/* Display resolution */
#define EPD_WIDTH       200
#define EPD_HEIGHT      200


class DEPG0150BxS810FxX_BW:public EpdBase {
	public:
		DEPG0150BxS810FxX_BW(uint8_t _rst, uint8_t _dc, uint8_t _cs,  uint8_t _busy, int8_t _clk=-1, uint8_t _spi_num = 0 ,uint32_t _freq = 2000000): \
		EpdBase(_rst, _dc, _cs, _busy, _clk, _spi_num, _freq){}

		~DEPG0150BxS810FxX_BW(){}
		int LDirInit(void);
		int HDirInit(void);
		void Clear(void);
		void Display(const unsigned char* frame_buffer);
		void DisplayPartBaseImage(const unsigned char* frame_buffer);
		void DisplayPartBaseWhiteImage(void);
		void DisplayPart(const unsigned char* frame_buffer);
		void SetFrameMemory(
						const unsigned char* image_buffer,
						int x,
						int y,
						int image_width,
						int image_height
		);
		void DisplayFrame(void);
		void DisplayPartFrame(void);

		void Sleep(void);

	private:
		unsigned int spiFlag = 0;
		unsigned long width = EPD_WIDTH;
		unsigned long height = EPD_HEIGHT;
		void SetMemoryArea(int x_start, int y_start, int x_end, int y_end);
		void SetMemoryPointer(int x, int y);

};

#endif/** DEPG0150BxS810FxX_BW.h END**/