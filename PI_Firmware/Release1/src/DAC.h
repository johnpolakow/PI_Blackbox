#ifndef DAC_H
#define DAC_H


#include <math.h>
#include <bcm2835.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include <errno.h>
#include "Pin_Defs.h"
#include "Read_Metrics.h"
#include "DAC_COUNT_LUT.h"

#define ONE_MILLISECOND 1000

static const uint8_t channel_A = 0x30;    // primary DAC channel, used to set heat load current
static const uint8_t channel_B = 0x34;    // auxiliary DAC channel, currently brought out to a test point
static const float VREF = 5.0;

static const float DAC_V_FULL_SCALE = 5.0455;		// REQUIRE MEASUREMENT
static const float DAC_V_OFFSET = .00146;			  // REQUIRE MEASUREMENT

static const int DAC_MAX_COUNT = 65536; // 2^16
double IDEAL_VOLT_QUANTA;
double ACTUAL_VOLT_QUANTA;

void DAC_Start();
void DAC_CS_HIGH();
void DAC_CS_LOW();
void DAC_Set_Count(uint8_t channel, uint16_t Counts);
uint16_t Load_milliAmps_to_Counts(double target_milliAmps);
uint16_t Load_milliWatts_to_DAC_Counts( double target_milliWatts );

void DAC_Start()
{
    IDEAL_VOLT_QUANTA = VREF/((const double)DAC_MAX_COUNT);
    ACTUAL_VOLT_QUANTA = (DAC_V_FULL_SCALE-DAC_V_OFFSET)/((const double)DAC_MAX_COUNT);
}

void DAC_CS_HIGH()
{
    delayMicroseconds(1);
    bcm2835_gpio_write(DAC8552_CS,HIGH);
}

void DAC_CS_LOW()
{
  bcm2835_gpio_write(DAC8552_CS,LOW);
  delayMicroseconds(2);
  bcm2835_gpio_write(BUFFER_EN_1,LOW);
}

// Set DAC output voltage to value according to "Counts"
// channel refers to channel_A or channel_B. channel_A is used on PI_DAQ
void DAC_Set_Count(uint8_t channel, uint16_t Counts)
{
	uint8_t byte[3];	// container for bytes to send
	byte[0] = channel;	// first byte is the DAC channel to set (A or B)
	byte[1] = (Counts>>8);	// send MSB byte first by shifting to right 8 bits, and storing result in 8 bit variable
	byte[2] = (Counts&0x00FF); // sending LSB by AND-ing counts with 0x00FF, which clears the MSB, then store result in 8 bit variable


  pthread_mutex_lock (&SPI_BUS_LOCK);         // get mutex
      DAC_CS_LOW() ;
      delayMicroseconds(2);
        bcm2835_spi_transfer(byte[0]);
        delayMicroseconds(10);
        bcm2835_spi_transfer(byte[1]);
        delayMicroseconds(10);
        bcm2835_spi_transfer(byte[2]);
        delayMicroseconds(2);
        DAC_CS_HIGH() ;
        delayMicroseconds(5);
  pthread_mutex_unlock (&SPI_BUS_LOCK);         // release mutex
}

// Convert desired load current to a count value for programming the DAC
uint16_t Load_milliAmps_to_Counts(double target_milliAmps)
{
    int index_lower_bound=0, index_upper_bound=1;
    float mA_lower_bound, mA_upper_bound;

    uint16_t interpolated_count, count_lower_bound, count_upper_bound;


    index_upper_bound = Find_Index_Upper_Bound(target_milliAmps, DAC_COUNT_LUT, ARRAY_SIZE(DAC_COUNT_LUT));
    index_lower_bound = index_upper_bound-1;

    count_lower_bound = DAC_COUNT_LUT[index_lower_bound][DAC_COUNT]; // ADC returned value
    count_upper_bound = DAC_COUNT_LUT[index_upper_bound][DAC_COUNT];  // count value programmed to the DAC which produced the known upper bound mA value

    mA_lower_bound = DAC_COUNT_LUT[index_lower_bound][MILLIAMP_MEAS];  // actual measured value
    mA_upper_bound= DAC_COUNT_LUT[index_upper_bound][MILLIAMP_MEAS]; // lower voltage

    float local_slope = (mA_upper_bound - mA_lower_bound)/(float)(count_upper_bound - count_lower_bound);   // "m" in y = mx + b
    float offset_milliamps = DAC_COUNT_LUT[index_lower_bound][MILLIAMP_MEAS]; // "b" in y = mx + b

    interpolated_count  = (int)( (target_milliAmps - offset_milliamps) / local_slope ); // x (count) = ( y - b ) / m

    return interpolated_count;
}

// Convert milliWatts disipation across a 200R resistor to DAC counts
uint16_t Load_milliWatts_to_DAC_Counts( double target_milliWatts )
{
    // watts = milliwatts / 1000
    // watts = (i_amps^2)*R      R = 200
    // watts = (i_amps^2)*200
    // i_amps^2 = watts/200
    // i_amps = sqrt( watts / 200 )
    // i_milliAmps = 1000 * sqrt( watts / 200 )

    double target_Watts = target_milliWatts / 1000.0;
    double i_amps = sqrt( target_Watts / 200 );
    double i_milliAmps = 1000 * i_amps;
    //printf("set_mA: %f\n", i_milliAmps);
    uint16_t DAC_counts = Load_milliAmps_to_Counts( i_milliAmps );

    return DAC_counts;
}

#endif
