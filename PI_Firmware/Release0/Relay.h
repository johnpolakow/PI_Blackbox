#include <bcm2835.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


bool DEBUG = false;

static const int ONE_MILLISECOND = 1000; // 1ms == 1000 microseconds


#define RELAY_RESET				12			// physical pin 32
#define RELAY_SET					1		// physical pin 28
#define SW_CTRL_100UA			6		 // physical pin 28

int CURRENT_SOURCE_SELECT = 0;


#define PULSE_ON	60*ONE_MILLISECOND

void Relay_ON();
void Relay_OFF();
void Toggle_Current_Source();

void ADS1256_Init(void)
{
  if (!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you running as root??\n");
    return;
  }
  if (!bcm2835_spi_begin())
  {
    printf("bcm2835_i2c_begin failed. Are you running as root??\n");
    return;
  }

	bcm2835_gpio_fsel(RELAY_RESET, BCM2835_GPIO_FSEL_OUTP);			   // Declare Reset as output pin
	bcm2835_gpio_write(RELAY_RESET, LOW);

	bcm2835_gpio_fsel(RELAY_SET, BCM2835_GPIO_FSEL_OUTP);			     // Declare set as output pin
	bcm2835_gpio_write(RELAY_SET, LOW);

  bcm2835_gpio_fsel(SW_CTRL_100UA, BCM2835_GPIO_FSEL_OUTP);			// Set software control of REF100 as output pin
  bcm2835_gpio_write(SW_CTRL_100UA, LOW);


  printf("\nRESET PIN:\t%d\n", RELAY_RESET);
  printf("SET PIN:\t%d\n", RELAY_SET);
}

void  DelayMicroseconds(uint64_t micros)
{
	bcm2835_delayMicroseconds (micros);
}

char Get_Input_Method_From_Serial()
{
    printf("\nEnter:\n\t'n' for relay on\t\t'f' for relay off\t\t't' toggle current source");
    printf("\n>> ");

    int ascii;
    char ch;
    int valid_selection = 0;

    while(!valid_selection)
    {
	         ch = getchar();
            if( ch == 'n' || ch == 'f' || ch == 't')
            {
		printf("received: %c\n", ch);
                 valid_selection = 1;
                 break;
            }
    }
    return ch;
}





void Relay_ON()
{
	printf("--RELAY ON--\n");
	bcm2835_gpio_write(RELAY_RESET, LOW); 		// verifies other latching coil isnt being driven
  delayMicroseconds(100);
	printf("\tRELAY SET HIGH [pin 28]");
	bcm2835_gpio_write(RELAY_SET, HIGH);
  printf("changed pin %d to HI\n", RELAY_SET);
	printf("\t ....\n");
	delayMicroseconds(PULSE_ON);
	bcm2835_gpio_write(RELAY_SET, LOW);
	printf("\t[pin 28 HI, pin 32 LOW].... relay should be on\n");
}

void Relay_OFF()
{
	printf("--RELAY OFF--\n");
  delayMicroseconds(10);
	bcm2835_gpio_write(RELAY_SET, LOW); 		// verifies other latching coil isnt being driven
  delayMicroseconds(100);
	printf("\tRELAY RESET HIGH [pin 32]");
	bcm2835_gpio_write(RELAY_RESET, HIGH);
  printf("changed pin %d to HI\n", RELAY_RESET);
	delayMicroseconds(PULSE_ON);
	bcm2835_gpio_write(RELAY_RESET, LOW);
	printf("\t[pin 28 LOW, pin 32 HI]\n");
}

void Toggle_Current_Source()
{
	printf("--Toggle_Current_Source--\n");
  delayMicroseconds(10);

  ++CURRENT_SOURCE_SELECT;
  if(CURRENT_SOURCE_SELECT > 1) CURRENT_SOURCE_SELECT = 0;

  if(CURRENT_SOURCE_SELECT) bcm2835_gpio_write(SW_CTRL_100UA, HIGH);

  else bcm2835_gpio_write(SW_CTRL_100UA, LOW);

  printf("\tchanged pin %d to %d\n", SW_CTRL_100UA, CURRENT_SOURCE_SELECT);
}


void main()
{
  int32_t adc[8];
	int32_t volt[8];
	uint8_t i;
	uint8_t buf[3];


  delayMicroseconds(ONE_MILLISECOND);
  ADS1256_Init();
  delayMicroseconds(50);

/*
	bcm2835_gpio_write(RELAY_RESET, HIGH);
	delayMicroseconds(1000*ONE_MILLISECOND);
	bcm2835_gpio_write(RELAY_RESET, LOW);

	delayMicroseconds(500*ONE_MILLISECOND);
	bcm2835_gpio_write(RELAY_SET, HIGH);
	delayMicroseconds(1000*ONE_MILLISECOND);
	bcm2835_gpio_write(RELAY_SET, LOW);
  */

  //printf( "\033[0m\033[2J\033[H");  // clears the terminal and brings cursor to first line
  printf("\n");

  printf("-------------------------------------------------------------------------------------------------\n");

  while(1)
  {
			  char selection = Get_Input_Method_From_Serial();
        if(selection == 'n')
        {
            Relay_ON();
        }
        if(selection == 'f')
        {
          Relay_OFF();
        }
        if(selection == 't')
        {
          Toggle_Current_Source();
        }
			  DelayMicroseconds(1e4);
  }
  bcm2835_close();
}
