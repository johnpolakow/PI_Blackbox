
#include "Pin_Defs.h"

#ifndef _INIT_BCM2835
#define _INIT_BCM2835


//#include <bcm2835.h>
#include <bcm2835.h>

const int CLOCK_DIVIDER = BCM2835_SPI_CLOCK_DIVIDER_128;

bool Init_BCM2835_Library();
void Initialize_ADS1256_GPIO_pins();
void Initialize_MAX31856_GPIO_pins();
void Initialize_Relay_GPIO_pins();

void Initialize_ADS1256_GPIO_pins()
{
    // buf en0 = original adc
    // buf en1 = new adc on spi0
    // buf en2 == new adc on spi1

  // PIN CONFIGURATION FOR ADC0
    bcm2835_gpio_fsel( ADC0.CS_pin, BCM2835_GPIO_FSEL_OUTP );				// declare Chip Select as output pin
    bcm2835_gpio_write( ADC0.CS_pin, HIGH );												// Write Chip Select High (it is active low)

    bcm2835_gpio_fsel( ADC0.DRDY_pin, BCM2835_GPIO_FSEL_INPT );			// declare data ready on ADC0 as input pin
    bcm2835_gpio_set_pud( ADC0.DRDY_pin, HIGH );										// select pullup on DRDY pin (it is active low, controlled by ADC)

    bcm2835_gpio_fsel( ADC0.BUF_EN_pin, BCM2835_GPIO_FSEL_OUTP );			// declare buffer enable as output pin
    bcm2835_gpio_write( ADC0.BUF_EN_pin, HIGH );											// Write buffer enable high (it is active low)

  // PIN CONFIGURATION FOR ADC1
    bcm2835_gpio_fsel( ADC1.CS_pin, BCM2835_GPIO_FSEL_OUTP );				// Set Chip Select as output pin
    bcm2835_gpio_write( ADC1.CS_pin, HIGH );												// Write Chip Select High (it is active low)

    bcm2835_gpio_fsel( ADC1.DRDY_pin, BCM2835_GPIO_FSEL_INPT );			// declare data ready on ADC1 as input pin
    bcm2835_gpio_set_pud( ADC1.DRDY_pin, HIGH );										// select pullup on DRDY pin (it is active low, controlled by ADC)

    bcm2835_gpio_fsel( ADC1.BUF_EN_pin, BCM2835_GPIO_FSEL_OUTP );			// declare Chip Select as output pin
    bcm2835_gpio_write( ADC1.BUF_EN_pin, HIGH );											// Write buffer enable high (it is active low)

  // RESET PIN RESETS BOTH ADCs
    bcm2835_gpio_fsel(ADS1256_RESET, BCM2835_GPIO_FSEL_OUTP);				// Set Reset as output pin (single pin resets both ADCs)
    bcm2835_gpio_write(ADS1256_RESET, HIGH);												// Write Reset High (low == stay in reset)
}

void Initialize_MAX31856_GPIO_pins()
{
    bcm2835_gpio_fsel(MAX31856_CS_1, BCM2835_GPIO_FSEL_OUTP);		// Set Chip Select as output pin
    bcm2835_gpio_fsel(MAX31856_CS_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(MAX31856_CS_3, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_fsel(BUFFER_EN_1, BCM2835_GPIO_FSEL_OUTP);		// Set Buf enable as output pin
    bcm2835_gpio_set_pud(BUFFER_EN_1, HIGH);

    bcm2835_gpio_write(MAX31856_CS_1, HIGH);											// Write Chip Select High
    bcm2835_gpio_write(MAX31856_CS_2, HIGH);
    bcm2835_gpio_write(MAX31856_CS_3, HIGH);

    bcm2835_gpio_fsel(MAX31856_DRDY_1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(MAX31856_DRDY_2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_fsel(MAX31856_DRDY_3, BCM2835_GPIO_FSEL_INPT);

    bcm2835_gpio_set_pud(MAX31856_DRDY_1, HIGH);											// Write DRDY High
    bcm2835_gpio_set_pud(MAX31856_DRDY_2, HIGH);
    bcm2835_gpio_set_pud(MAX31856_DRDY_3, HIGH);
}

void Initialize_Relay_GPIO_pins()
{
    	bcm2835_gpio_fsel(RELAY_SET, BCM2835_GPIO_FSEL_OUTP);			   // Declare set as output pin
    	bcm2835_gpio_write(RELAY_SET, LOW);

    	bcm2835_gpio_fsel(RELAY_RESET, BCM2835_GPIO_FSEL_OUTP);			     // Declare reset as output pin
    	bcm2835_gpio_write(RELAY_RESET, LOW);

      bcm2835_gpio_fsel(SW_CTRL_100uA, BCM2835_GPIO_FSEL_OUTP);			// Set software control of REF100 as output pin
      bcm2835_gpio_write(SW_CTRL_100uA, LOW);
}

void Initialize_DAC_GPIO_pins()
{
    bcm2835_gpio_fsel(DAC8552_CS, BCM2835_GPIO_FSEL_OUTP);		// declare chip select pin as an output
    bcm2835_gpio_write(DAC8552_CS, HIGH); 				            // write chip select high (should always be high unless sending data)

    bcm2835_gpio_fsel(BUFFER_EN_1, BCM2835_GPIO_FSEL_OUTP);		// declare buffer enable pin as an output
    bcm2835_gpio_write(BUFFER_EN_1, HIGH); 				            // write chip select high (should always be high unless sending data)
}

bool Init_BCM2835_Library()
{
    if (!bcm2835_init())
    {
        printf("bcm2835_init failed. Are you running as root?? ...use sudo \n");
        return false;
    }
    if (!bcm2835_spi_begin())
    {
        printf("bcm2835 spi begin failed. Are you running as root?? ...use sudo\n");
        return false;
    }

    bcm2835_spi_setBitOrder( BCM2835_SPI_BIT_ORDER_MSBFIRST );
    bcm2835_spi_setDataMode( BCM2835_SPI_MODE1 );
    bcm2835_spi_setClockDivider( CLOCK_DIVIDER );

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(DS3231_ADDRESS);
    bcm2835_i2c_set_baudrate(10000);

    Initialize_ADS1256_GPIO_pins();
    Initialize_MAX31856_GPIO_pins();
    Initialize_Relay_GPIO_pins();
    Initialize_DAC_GPIO_pins();

    return true;
}

#endif
