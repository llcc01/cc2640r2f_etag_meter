#ifndef __EPD_2IN13__
#define __EPD_2IN13__

static void EPD_2IN13_Lut(const unsigned char *lut);
static void EPD_2IN13_Lut_ById(int id);
static void EPD_2IN13_SoftReset();
static int8_t EPD_2IN13_ReadTemp();
static void EPD_2IN13_LoadImage(uint8_t *image, int size, uint8_t cmd);
static void EPD_2IN13_BWR(int width, int height, int left, int top);
static void EPD_2IN13_WriteRam(uint8_t *image, int width, int height, int left, int top, uint8_t is_red);
static void EPD_2IN13_Display(uint8_t reg);
static void EPD_2IN13_Sleep(void);
static void EPD_2IN13_Clear(void);
static void EPD_SSD_Update_Clock(void);
static void EPD_2IN13_Update_Image();
static int EPD_SSD_Update(void);
static void EPD_SSD_Init(void);

#endif
