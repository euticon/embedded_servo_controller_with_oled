
#include "device_drivers/ssd1306_new.h"
#include "device_drivers/i2c.h"
#include "device_drivers/timers.h"
#include <string.h>
#include <stdio.h>

uint8_t SSD1306_Buffer[SSD1306_WIDTH*SSD1306_HEIGHT/8];

static uint8_t cursorX;
static uint8_t cursorY;


void i2c_write(uint8_t addr,uint8_t control_byte,uint8_t data)
{
	    /* Generate START condition */
	    I2C1->CR1 |= I2C_CR1_START;

	    /* Wait until START condition generated */
	    while (!(I2C1->SR1 & I2C_SR1_SB));

	    /* Send slave address + Write bit */
	    I2C1->DR = addr << 1;

	    /* Wait for address acknowledge */
	    while (!(I2C1->SR1 & I2C_SR1_ADDR));

	    /* Clear ADDR flag */
	    volatile uint32_t temp;
	    temp = I2C1->SR1;
	    temp = I2C1->SR2;
	    (void)temp;

	    /* Wait until transmit register empty */
	    while (!(I2C1->SR1 & I2C_SR1_TXE));

	    /* Send control byte */
	    I2C1->DR = control_byte;

	    /* Wait until transmit register empty */
	    while (!(I2C1->SR1 & I2C_SR1_TXE));

	    /* Send data byte */
	    I2C1->DR = data;

	    /* Wait until both bytes transmitted */
	    while (!(I2C1->SR1 & I2C_SR1_BTF));

	    /* Generate STOP condition */
	    I2C1->CR1 |= I2C_CR1_STOP;

}
void ssd1306_cmd(uint8_t cmd)
{
	i2c_write(SSD1306_ADDR,SSD1306_CMD,cmd);
}

void ssd1306_data(uint8_t data)
{
	i2c_write(SSD1306_ADDR,SSD1306_DATA,data);
}

void ssd1306_init(void)
{
	/* Turn display off during configuration */
			ssd1306_cmd(0xAE);

		    /* Set memory addressing mode */
		    ssd1306_cmd(0x20);

		    /* Use horizontal addressing mode */
		    ssd1306_cmd(0x00);

		    /* Remap display columns */
		    ssd1306_cmd(0xA1);

		    /* Set COM output scan direction */
		    ssd1306_cmd(0xC8);

		    /* Set display contrast */
		    ssd1306_cmd(0x81);

		    /* Set contrast value */
		    ssd1306_cmd(0x7F);

		    /* Set normal (non-inverted) display mode */
		    ssd1306_cmd(0xA6);

		    /* Set multiplex ratio */
		    ssd1306_cmd(0xA8);

		    /* Configure multiplex value for 64 rows */
		    ssd1306_cmd(0x3F);

		    /* Set display offset */
		    ssd1306_cmd(0xD3);

		    /* No display offset */
		    ssd1306_cmd(0x00);

		    /* Set display clock divide ratio */
		    ssd1306_cmd(0xD5);

		    /* Set recommended clock setting */
		    ssd1306_cmd(0x80);

		    /* Enable charge pump regulator */
		    ssd1306_cmd(0x8D);

		    /* Use internal charge pump */
		    ssd1306_cmd(0x14);

		    /* Turn display on */
		    ssd1306_cmd(0xAF);
}

/******************************************************/

void ssd1306_setCursor(uint8_t x,uint8_t y)
{
    cursorX=x;
    cursorY=y;
}

void ssd1306_clear(void)
{
    memset(SSD1306_Buffer,0,sizeof(SSD1306_Buffer));
}

void ssd1306_drawPixel(uint8_t x,uint8_t y,uint8_t color)
{
    if(x>=SSD1306_WIDTH || y>=SSD1306_HEIGHT) return;

    if(color)
        SSD1306_Buffer[x+(y/8)*SSD1306_WIDTH]|=(1<<(y%8));
    else
        SSD1306_Buffer[x+(y/8)*SSD1306_WIDTH]&=~(1<<(y%8));
}

void ssd1306_updateScreen(void)
{
    for(uint8_t page=0;page<8;page++)
    {
        ssd1306_cmd(0xB0+page);
        ssd1306_cmd(0x00);
        ssd1306_cmd(0x10);

        for(uint8_t col=0;col<128;col++)
        {
            ssd1306_data(SSD1306_Buffer[page*128+col]);
        }
    }
}

char ssd1306_writeChar(char ch, SSD1306_Font_t Font, uint8_t color)
{
    uint32_t i,b,j;

    if(ch<32 || ch>126)
        return 0;

    if((SSD1306_WIDTH<(cursorX+Font.width))||
       (SSD1306_HEIGHT<(cursorY+Font.height)))
        return 0;

    for(i=0;i<Font.height;i++)
    {
        b=Font.data[(ch-32)*Font.height+i];

        for(j=0;j<Font.width;j++)
        {
            if((b<<j)&0x8000)
                ssd1306_drawPixel(cursorX+j,cursorY+i,color);
            else
                ssd1306_drawPixel(cursorX+j,cursorY+i,!color);
        }
    }

    cursorX+=Font.width;

    return ch;
}

char ssd1306_writeString(char *str, SSD1306_Font_t Font, uint8_t color)
{
    while(*str)
    {
        if(ssd1306_writeChar(*str,Font,color)!=*str)
            return *str;

        str++;
    }

    return *str;
}
const char *SpeedToString(speed_type speed)
{
    switch(speed)
    {
        case stop:   return "STOP";
        case slow:   return "SLOW";
        case medium: return "MEDIUM";
        case fast:   return "FAST";
        default:     return "UNKNOWN";
    }
}

const char *DirectionToString(direction_type direction)
{
    switch(direction)
    {
        case CW:  return "CW";
        case ACW: return "CCW";
        default:  return "UNKNOWN";
    }
}

void DisplayServoStatus(void)
{


	char line1[20];
    char line2[20];

    sprintf(line1, "Speed: %s", SpeedToString(current_speed));
    sprintf(line2, "Dir: %s", DirectionToString(current_direction));

    ssd1306_clear();

    ssd1306_setCursor(0, 0);
    ssd1306_writeString(line1, Font_7x10, White);

    ssd1306_setCursor(0, 15);
    ssd1306_writeString(line2, Font_7x10, White);

    ssd1306_updateScreen();
}
