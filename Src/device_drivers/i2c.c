#include "device_drivers/i2c.h"
#include "device_headers/stm32f446xx.h"

void i2c_init(void)
{
    /* Disable I2C */
    I2C1->CR1 &= ~I2C_CR1_PE;

    /* APB1 frequency = 16 MHz */
    I2C1->CR2 = 16;

    /* Standard Mode (100 kHz) */
    I2C1->CCR = 80;

    /* Maximum rise time */
    I2C1->TRISE = 17;

    /* Enable I2C */
    I2C1->CR1 |= I2C_CR1_PE;
}

uint8_t i2c_check_addr(uint8_t addr)
{
    /* Clear AF flag if previously set */
    I2C1->SR1 &= ~I2C_SR1_AF;

    /* Generate START */
    I2C1->CR1 |= I2C_CR1_START;

    /* Wait until START generated */
    while (!(I2C1->SR1 & I2C_SR1_SB));

    /* Send 7-bit address + Write bit */
    I2C1->DR = (addr << 1);

    while (1)
    {
        /* Slave ACKed */
        if (I2C1->SR1 & I2C_SR1_ADDR)
        {
            /* Clear ADDR flag */
            volatile uint32_t temp;
            temp = I2C1->SR1;
            temp = I2C1->SR2;
            (void)temp;

            /* Generate STOP */
            I2C1->CR1 |= I2C_CR1_STOP;

            return 1;
        }

        /* Slave NACKed */
        if (I2C1->SR1 & I2C_SR1_AF)
        {
            /* Clear AF flag */
            I2C1->SR1 &= ~I2C_SR1_AF;

            /* Generate STOP */
            I2C1->CR1 |= I2C_CR1_STOP;

            return 0;
        }
    }
}
