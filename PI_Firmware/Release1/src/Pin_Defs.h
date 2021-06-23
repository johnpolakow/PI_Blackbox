#ifndef PIN_DEFINITIONS
#define PIN_DEFINITIONS

// Pin Numbering
/*
Rasperry Pi Physical Pin Numbering w/ bcm2835 library pin Numbering
            BCM2835           Raspberry Pi
Function     pin#             physical pin#
SDA1          2                   3       PI_SDA
SCL1          3                   5       PI_SCL
GPCLK0        4                   7       BUF_EN_2
GPCLK1        5                   29      MAX31856_DRDY1
GPCLK2        6                   31      SW_CTRL_100uA
SPI0_CE1_N    7                   26      MAX31856_CS3
SPI0_CE0_N    8                   24      MAX31856_CS2
SPI0_MISO     9                   21      ADS1256_MISO
SPI0_MOSI     10                  19      ADS1256 MOSI
SPI0_SCLK     11                  23      ADS1256_SCLK
PWM0          12                  32      RELAY_RESET
PWM1          13                  33      ADS1256_CS_1
TXD0          14                  8       CCC_UART_TX
RXD0          15                  10      CCC_UART_RX
SPI1_CE2      16                  36      MAX31856_DRDY2
SPI1_CE1      17                  11      ADS1256_DRDY
PCM_CLK       18                  12      ADS1256_RESET
SPI1_MISO     19                  35      MISO_SPI1
SPI1_MOSI     20                  38      MOSI_SPI1
SPI1_SCLK     21                  40      SCLK_SPI1
SD0_CLK       22                  15      ADS1256_CS_0
SD0_CMD       23                  16      DAC8552_CS
SD0_DAT0      24                  18      BUF_EN_1
SD0_DAT1      25                  22      MAX31856_CS1
SD0_DAT2      26                  37      MAX31856_DRDY3
SD0_DAT3      27                  13      BUF_EN_0
              01                  28      RELAY_SET
              00                  27      ADS1256_DRDY2
*/
#define BUS_SPEED_100KHZ  100000
#define BUS_SPEED_300KHZ  300000
#define BUS_SPEED_400KHZ  400000

#define DS3231_ADDRESS      0x68
#define ADT7410_I2C_ADDR    0x48

#define ADS1256_DRDY_0    17        // physical pin 11
#define ADS1256_DRDY_1     0        // physical pin 27
#define ADS1256_RESET     18        // physical pin 12

#define ADS1256_CS_0      22        // Physical pin 15
#define ADS1256_CS_1      13        // physical pin 33

//#define	DAC8552_CS	    RPI_GPIO_P1_16	// Physical pin 16
#define	DAC8552_CS	      23	      // Physical pin 16

#define MAX31856_CS_1     25        // physical pin 25
#define MAX31856_CS_2     8         // physical pin 24
#define MAX31856_CS_3     7         // physical pin 26
#define MAX31856_DRDY_1   5         // physcial pin 29
#define MAX31856_DRDY_2   16        // physical pin 36
#define MAX31856_DRDY_3   26        // physical pin 37

#define BUFFER_EN_1       24
#define BUFFER_EN_2       4         // physical pin 7
#define BUFFER_EN_0       27        // physical pin 13

#define PI_MOSI_0         10        // physical pin 19
#define PI_MISO_0         9         // physical pin 21
#define PI_SCLK_0         11        // physical pin 23

#define PI_MOSI_1         20        // physical pin 38
#define PI_MISO_1         19        // physical pin 35
#define PI_SCLK_1         21        // physical pin 40

#define RELAY_RESET       12        // physical pin 32
#define RELAY_SET         1         // physical pin 28
#define SW_CTRL_100uA     6         // physical pin 31
#define PI_UART_TX        14        // physical pin 8
#define PI_UART_RX        15        // physical pin 10






typedef struct ADS1256
{
    int CS_pin;
    int DRDY_pin;
    int RESET_pin;
		int BUF_EN_pin;
} ADC;

ADC ADC0;
ADC ADC1;

int CURRENT_SOURCE_SELECT = 0;

bool RELAY_is_ON = false;
const int NUM_MEAS_SAMPLES = 3;







#endif
