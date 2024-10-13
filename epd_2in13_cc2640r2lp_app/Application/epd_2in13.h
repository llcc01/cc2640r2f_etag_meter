#ifndef __EPD_2IN13__
#define __EPD_2IN13__

#include <stdint.h>

#define EPD_WIDTH 250
#define EPD_HEIGHT 128
#define EPD_PAD_LEFT 46
#define EPD_PAD_TOP 8

void EPD_2IN13_Lut(const unsigned char *lut);
void EPD_2IN13_Lut_ById(int id);
void EPD_2IN13_SoftReset();
int8_t EPD_2IN13_ReadTemp();
void EPD_2IN13_LoadImage(uint8_t *image, int size, uint8_t cmd);
void EPD_2IN13_BWR(int width, int height, int left, int top);
void EPD_2IN13_WriteRam(uint8_t *image, int width, int height, int left, int top, uint8_t is_red);
void EPD_2IN13_Display(uint8_t reg);
void EPD_2IN13_Sleep(void);
void EPD_2IN13_Clear(void);
void EPD_SSD_Update_Clock(void);
void EPD_2IN13_Update_Image();
int EPD_SSD_Update(void);
void EPD_SSD_Init(void);

#endif
