

#ifndef _ADT7410_
#define _ADT7410_


#include <bcm2835.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

#include "Pin_Defs.h"
#include "ADS1256.h"


/* I2C registers in ADT74x0 */
#define ADT7410_T_MSB       0x00
#define ADT7410_T_LSB       0x01
#define ADT7410_STATUS      0x02
#define ADT7410_CONFIG      0x03
#define ADT7410_IDREG       0x0b
#define ADT7410_RESET       0x2f

#define ADT7410_STATUS_GOOD  0



static int ADT7410_Init();
static int read_ADT7410(const uint8_t addr, double *temp);
static double Get_ADT7410_Temp();


static void Read_PCB_Temp()
{
    pcb_temperature.value_sum += Get_ADT7410_Temp();
    ++pcb_temperature.num_samples;
}

static double Get_ADT7410_Temp()
{
    double cur_temp;
    read_ADT7410(ADT7410_I2C_ADDR, &cur_temp);
    return cur_temp;
}

// Return 0 if OK, -ve to show error
static int ADT7410_Init()
{
    int stat;
    uint8_t buff[4];

    bcm2835_i2c_setSlaveAddress(ADT7410_I2C_ADDR);

    bcm2835_delay(500);    // give chip 100 ms to stabilize

    buff[0] = ADT7410_RESET;
    if ((stat = bcm2835_i2c_write((char *)buff, 1)) != 0)   // send reset
        return -(0x10 + stat);

    bcm2835_delay(1); // Device needs 200us after reset, give it 1ms

    buff[0] = ADT7410_CONFIG;
    buff[1] = 0x80;    // 16bit cts conversions

    if ((stat = bcm2835_i2c_write((char *)buff, 2)) != 0)   // write config to ADT7410
        return -(0x20 + stat);

    char reg = ADT7410_IDREG;
    if ((stat = bcm2835_i2c_read_register_rs(&reg, (char *)buff, 1)) != 0)
        return -(0x30 + stat);

    if ((buff[0] & 0xf8) != 0xc8)
        return -0x3f;

    return 0;
}  

// Return 0 if OK, -ve to show error
// Set *temp to be the temperature in Celsius
static int read_ADT7410(const uint8_t addr, double *temp)
{
  int stat;
  uint8_t buff[4];

  bcm2835_i2c_setSlaveAddress(addr);
  
  char reg = ADT7410_T_MSB;
  if ((stat = bcm2835_i2c_read_register_rs(&reg, (char *)buff, 2)) != 0)
    return -(0x40 + stat);

  // ADT74x0 puts MSB first so flip order
  int16_t hi = buff[0];
  int16_t lo = buff[1];

  int16_t t128 = hi << 8 | lo;

  *temp = t128 / 128.0;

  return 0;
}

#endif