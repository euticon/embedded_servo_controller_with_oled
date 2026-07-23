
#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include "device_drivers/timers.h"


#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

#define White 1
#define Black 0

#define SSD1306_ADDR 0x3C
#define SSD1306_CMD 0x00
#define SSD1306_DATA 0x40

typedef struct
{
    const uint8_t width;
    const uint8_t height;
    const uint16_t *const data;
    const uint8_t *const char_width;
} SSD1306_Font_t;

#define SSD1306_INCLUDE_FONT_7x10
#include "ssd1306_fonts.h"

extern uint8_t SSD1306_Buffer[SSD1306_WIDTH*SSD1306_HEIGHT/8];

void i2c_write(uint8_t addr,uint8_t control_byte,uint8_t data);
void ssd1306_init(void);
void ssd1306_cmd(uint8_t cmd);
void ssd1306_data(uint8_t data);


void ssd1306_clear(void);
void ssd1306_updateScreen(void);
void ssd1306_setCursor(uint8_t x,uint8_t y);
void ssd1306_drawPixel(uint8_t x,uint8_t y,uint8_t color);

char ssd1306_writeChar(char ch, SSD1306_Font_t Font, uint8_t color);
char ssd1306_writeString(char *str, SSD1306_Font_t Font, uint8_t color);

const char *SpeedToString(speed_type speed);
const char *DirectionToString(direction_type direction);
void DisplayServoStatus(void);


#endif
