#ifndef BCM2835
#define BCM2835


typedef signed char       int8_t;
typedef signed short      int16_t;
typedef unsigned short      uint16_t;
typedef signed int        int32_t;
typedef unsigned char     uint8_t;
typedef unsigned int       uint32_t;


#define BCM2835_SPI_CLOCK_DIVIDER_512 512
#define BCM2835_SPI_CLOCK_DIVIDER_256 256
#define BCM2835_SPI_CLOCK_DIVIDER_128 128
#define BCM2835_SPI_CLOCK_DIVIDER_64 64
#define BCM2835_SPI_CLOCK_DIVIDER_32 32
#define BCM2835_GPIO_FSEL_OUTP 100
#define BCM2835_GPIO_FSEL_INPT 110
#define HIGH 101
#define LOW  102
#define BCM2835_SPI_BIT_ORDER_MSBFIRST 2
#define BCM2835_SPI_MODE1 3

void bcm2835_gpio_fsel( int CS_pin, int code );
void bcm2835_gpio_write( int CS_pin, int val);
void bcm2835_gpio_fsel( int DRDY_pin, int code );
void bcm2835_gpio_set_pud( int DRDY_pin, int val);
bool bcm2835_init();
bool bcm2835_spi_begin();
void bcm2835_spi_setBitOrder( int code );
void bcm2835_spi_setDataMode( int code );
void bcm2835_spi_setClockDivider( int code );
void bcm2835_i2c_begin();
void bcm2835_i2c_setSlaveAddress(int address);
void bcm2835_i2c_set_baudrate(int baud);
void delayMicroseconds(int seconds);
void bcm2835_delayMicroseconds(int seconds);
int bcm2835_gpio_lev( int pin );
int bcm2835_spi_transfer(int hexcode);


void bcm2835_gpio_fsel( int CS_pin, int code ){}
void bcm2835_gpio_write( int CS_pin, int val){ usleep(50); }
//void bcm2835_gpio_write( int CS_pin, int val){ }
void bcm2835_gpio_set_pud( int DRDY_pin, int val){}
bool bcm2835_init(){ return true; }
bool bcm2835_spi_begin(){ return true;}
void bcm2835_spi_setBitOrder( int code ){}
void bcm2835_spi_setDataMode( int code ){}
void bcm2835_spi_setClockDivider( int code ){}
void bcm2835_i2c_begin(){}
void bcm2835_i2c_setSlaveAddress(int address){}
void bcm2835_i2c_set_baudrate(int baud){}
void delayMicroseconds(int seconds){}
void bcm2835_delayMicroseconds(int seconds){}
int bcm2835_gpio_lev( int pin ){ return 1; }
int bcm2835_spi_transfer(int hexcode){ usleep(50); return 0b00110110;}
//int bcm2835_spi_transfer(int hexcode){ return hexcode;}























#endif
