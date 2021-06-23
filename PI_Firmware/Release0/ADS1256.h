#ifndef ADS1256_H
#define ADS1256_H

#include <bcm2835.h>
#include <stdio.h>
#include <pthread.h>
#include "Pin_Defs.h"
#include "Macros.h"

#include "Interpolate_LUT.h"
#include "Cal/COOLER_V_LUT.h"
#include "Cal/LOAD_mA_LUT.h"
#include "Cal/LOAD_V_LUT.h"
#include "Cal/COOLER_mA_LUT.h"
#include "colors.h"
//#include "MAX31856.h"

extern float get_Corrected_Value(float raw_value, float LUT[][2], int LUT_numElements); // defined in "Interpolate_LUT.h"
extern pthread_mutex_t SPI_BUS_LOCK;   // SPI_BUS_LOCK declared in "Thread_Defs.h"

// Alleged bus speeds for different clock dividers
// core clock: ~400 Mhz on PI3
// clock is divided by clock divider to calculate SPI speed
// rise time for HC125 is ~6.5 ns
/*
div     clock
---------------
8       31.2 MHz
16      15.6 MHz
32      7.8 MHz
64      3.9 MHz
128     1.92 Mhz
256     1 Mhz
*/

const static double LOAD_SHUNT_OHMS = 0.390;

/////////////////////
// these constants used for printing formatted debug messages to console
#define TXRX_TABS 6
#define SECONDARY_FUNCTION_TABS 4
int NUM_TABS = 3;
////////////////////

// Look up tables for correcting measurements after calibration
extern float COOLER_V_LUT[][2];       //   defined in "/Cal/COOLER_V_LUT.h"
extern float LOAD_mA_LUT[][2];          //  defined in "/Cal/LOAD_mA_LUT.h"
extern float LOAD_V_LUT[][2];           // defined in "/Cal/LOAD_V_LUT.h"
extern double ADC0_DCI_LUT[][2];        // defined in "/Cal/ADC0_DCI_LUT.h"
extern double ADC1_DCI_LUT[][2];        // defined in "/Cal/ADC1_DCI_LUT.h"

// analog input binary codes for ADS1256 MUX register
static const uint8_t AIN0  = 0b0000;
static const uint8_t AIN1  = 0b0001;
static const uint8_t AIN2  = 0b0010;
static const uint8_t AIN3  = 0b0011;
static const uint8_t AIN4  = 0b0100;
static const uint8_t AIN5  = 0b0101;
static const uint8_t AIN6  = 0b0110;
static const uint8_t AIN7  = 0b0111;

// constants that define a measurement between two inputs. Format is  [ positive_pin | negative_pin ]
const uint8_t ADC0_COOLER_AMPS  = ( 0b0000 << 4) | 0b0001;    /* AIN0 AIN1 */
const uint8_t ADC0_COOLER_VOLTS = ( 0b0010 << 4) | 0b0011;    /* AIN2 AIN3 */
const uint8_t ADC0_TEMP_DIODE   = (0b0100 << 4)  | 0b0101;    /* AIN4 AIN5 */
const uint8_t ADC0_HEAT_LOAD_V  = (0b0111 << 4)  | 0b0000;    /* AIN7 AINCOM */

const uint8_t ADC1_COOLER_AMPS  = ( 0b0000 << 4) | 0b0001;    /* AIN0 AIN1 */
const uint8_t ADC1_TEMP_DIODE   = ( 0b0010 << 4) | 0b0011;    /* AIN2 AIN3 */
const uint8_t ADC1_HEAT_LOAD_I  = ( 0b0100 << 4) | 0b0101;
const uint8_t ADC1_HEAT_LOAD_V  = ( 0b0110 << 4) | 0b0111;

// structure that encapsulates readings from a measurement
struct metric
{
    long count_sum;
		int num_samples;
    int average_count;
    double average_value;
    double raw_average_value;
};

typedef struct metric Metric_Track;
// Instances of metric struct for each measurement
Metric_Track ADC0_Cooler_Volts;
Metric_Track ADC0_Cooler_Amps;
Metric_Track ADC1_Cooler_Amps;
Metric_Track ADC0_Temp_Diode_Volts;
Metric_Track ADC1_Temp_Diode_Volts;
Metric_Track ADC0_Heat_Load_Volts;
Metric_Track ADC0_Heat_Load_milliAmps;
Metric_Track ADC1_Heat_Load_Volts;
Metric_Track ADC1_Heat_Load_milliAmps;

/*
format of ADS1256 object, defined in "Struct_Defs.h"
There are two ADS1256 ADC chips on the Pi board. This structure
encapsulates the important pin numbers for interfacing with
each ADC. The BUF_EN pin is enable for the SPI buffer, which send_buffers
the MISO, MOSI, and SCLK data lines.

typedef struct ADS1256
{
    int CS_pin;
    int DRDY_pin;
    int RESET_pin;
		int BUF_EN_pin;
} ADC;

ADC ADC0;
ADC ADC1;

*/

/* gain channels */
typedef enum
{
	ADS1256_GAIN_1			= (0),	/* GAIN     1 */
	ADS1256_GAIN_2			= (1),	/* GAIN     2 */
	ADS1256_GAIN_4			= (2),	/* GAIN     4 */
	ADS1256_GAIN_8			= (3),	/* GAIN     8 */
	ADS1256_GAIN_16			= (4),	/* GAIN    16 */
	ADS1256_GAIN_32			= (5),	/* GAIN    32 */
	ADS1256_GAIN_64			= (6),	/* GAIN    64 */
}ADS1256_GAIN_ENUM;

typedef enum
{
	DRATE_30000SPS 	= (0b11110000), //30,000 SPS (default)
	DRATE_15000SPS	= (0b11100000), //15,000 SPS
	DRATE_7500SPS	= (0b11010000), //7,500 SPS
	DRATE_3750SPS	= (0b11000000), //3,750 SPS
	DRATE_2000SPS	= (0b10110000), //2,000 SPS
	DRATE_1000SPS	= (0b10100001), //1,000 SPS
	DRATE_500SPS	= (0b10010010), //500 SPS
	DRATE_100SPS	= (0b10000010), //100 SPS
	DRATE_60SPS	= (0b01110010), //60 SPS
	DRATE_50SPS	= (0b01100011), //50 SPS
	DRATE_30SPS	= (0b01010011), //30 SPS
	DRATE_25SPS	= (0b01000011), //25 SPS
	DRATE_15SPS	= (0b00110011), //15 SPS
	DRATE_10SPS	= (0b00100011), //10 SPS
	DRATE_5SPS	= (0b00010011), //5 SPS
	DRATE_2_5SPS	= (0b00000011), //2.5 SPS
}ADS1256_DRATE_ENUM;

/* REGISTER ADDRESS DEFINITIONS --- ADS1256 datasheet Page 30----- */
enum
{
	/*Register address (in hex), in comments is each register's default value on startup */
	REG_STATUS = 0x0,	// 0x00
	REG_MUX    = 0x1, // 0x01
	REG_ADCON  = 0x2, // 0x20
	REG_DRATE  = 0x3, // 0xF0
	REG_GPIO   = 0x4, // E0H
	REG_OFC0   = 0x5, // xxH
	REG_OFC1   = 0x6, // xxH
	REG_OFC2   = 0x7, // xxH
	REG_FSC0   = 0x8, // xxH
	REG_FSC1   = 0x9, // xxH
	REG_FSC2   = 0xA, // xxH
};

/* Command definitions --- ADS1256 datasheet Page 34 */
enum
{
	CMD_WAKEUP                 = 0x00,	// Completes SYNC and Exits Standby Mode 0000  0000 (00h)
	CMD_READ_DATA              = 0x01, // Read Data 0000  0001 (01h)
	CMD_READ_DATA_CONTINOUSLY  = 0x03, // Read Data Continuously 0000 0011 (03h)
	CMD_SEND_DATA_CONTINOUSLY  = 0x0F, // Stop Read Data Continuously 0000   1111 (0Fh)
	CMD_READ_REG               = 0x10, // Read from REG 0001 | rrrr (0x1 | reg_addr)
	CMD_WRITE_REG              = 0x50, // Write to REG 0101 | rrrr (0x50 | reg_addr)
	CMD_SELF_CAL               = 0xF0, // Offset and Gain Self-Calibration 1111    0000 (F0h)
	CMD_SELF_OFFSET_CAL        = 0xF1, // Offset Self-Calibration 1111    0001 (F1h)
	CMD_SELF_GAIN_CAL          = 0xF2, // Gain Self-Calibration 1111    0010 (F2h)
	CMD_SYSTEM_OFFSET_CAL      = 0xF3, // System Offset Calibration 1111   0011 (F3h)
	CMD_SYSTEM_GAIN_CAL        = 0xF4, // System Gain Calibration 1111    0100 (F4h)
	CMD_SYNC                   = 0xFC, // Synchronize the A/D Conversion 1111   1100 (FCh)
	CMD_STANDBY                = 0xFD, // Begin Standby Mode 1111   1101 (FDh)
	CMD_RESET                  = 0xFE, // Reset to Power-Up Values 1111   1110 (FEh)
};

#define   NOP       0xFF  //No operation
const double V_FULL_SCALE = 5.0;    // reference voltage
const int TOTAL_COUNTS = 8388608;   // 2^23, this is for (+) voltages, same # of counts for (-) voltages
double VOLTS_PER_COUNT;


//
//  FUNCTION DECLARATIONS
//
void 				CS_LOW( ADC* ADC_chip );
void 				CS_HIGH( ADC* ADC_chip );
bool 				DRDY_IS_LOW(ADC* ADC_chip);
void        ADC0_Read_Cooler_Volts();
void        ADC0_Read_Cooler_Amps();
void        ADC0_Read_Temp_Diode();
void        ADC1_Read_Temp_Diode();
void        ADC0_Set_MUX_Cooler_Volts();
void        ADC0_Set_MUX_Cooler_Amps();
void        ADC0_Set_MUX_Temp_Diode();
void        ADC1_Set_MUX_Temp_Diode();
void        ADC1_Set_MUX_Cooler_Amps();
void        ADC1_Read_Cooler_Amps();
void        ADC1_Set_MUX_Heat_Load_I();
void        ADC0_Throw_Away_Reading();
void        ADC1_Throw_Away_Reading();
static void ADS1256_DelayDATA(void);
void 				ADS1256_Init(void);
static void ADS1256_Sync_LCK(ADC* ADC_chip);
static void ADS1256_WaitDRDY ( ADC* ADC_chip );
void 				ADS1256_Calibrate_Gain_and_Offset(ADC* ADC_chip);
double 			ADS1256_Counts_to_Volts(int adc_counts);

void 				Wait_Enter();
void        Print_Tabs(int num_to_print);
void        Calc_Measurement_Averages();
double      Cooler_Counts_to_Volts( int counts );
double      ADC0_Cooler_Counts_to_Amps( int counts);
double      ADC1_Cooler_Counts_to_Amps( int counts);
double      Temp_Diode_Counts_to_Volts( int counts);
double      Heat_Load_Counts_to_milliAmps( int counts );
double      Heat_Load_Counts_to_Volts( int counts );
void        Read_Default_Regs(ADC* ADC_chip);


// these functions contain mutex lock on SPI bus
static uint8_t ADS1256_ReadByte( void );
static uint8_t ADS1256_ReadReg_LCK(ADC* ADC_chip, uint8_t _RegID);
static int32_t ADS1256_ReadData_LCK( ADC* ADC_chip );
static void ADS1256_Throw_Away_Reading_LCK( ADC* ADC_chip );
void 				ADS1256_Config_LCK(ADC* ADC_chip, ADS1256_GAIN_ENUM _gain, ADS1256_DRATE_ENUM _drate);
static void ADS1256_WriteReg_LCK(ADC* ADC_chip, uint8_t RegID, uint8_t RegValue);
void 				ADS1256_Send_Cmd_LCK(ADC* ADC_chip, uint8_t cmd);
static void ADS1256_Hard_Reset_LCK(void);
static void ADS1256_Write_Byte(uint8_t data);

void ADC1_Read_Temp_Diode()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tREAD ADC1 TEMP DIODE  " COLOR_RESET);

  ADS1256_WaitDRDY( &ADC1 );
  ADS1256_Sync_LCK( &ADC1 );
  delayMicroseconds(2);
  int32_t count = ADS1256_ReadData_LCK( &ADC1 );
  ADC1_Temp_Diode_Volts.count_sum += count;
  if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "%2.3f\n" COLOR_RESET, Cooler_Counts_to_Volts( count) );
  if( (count < 0) && PRINT_DEBUG_MUX )
  {
        printf(COLOR_LIGHT_MAGENTA "TD negative number\n" COLOR_RESET);
        uint8_t mux = ADS1256_ReadReg_LCK(&ADC0, REG_MUX);
        printf("mux reg value: 0x%02X\n", mux);

  }
  ++ADC1_Temp_Diode_Volts.num_samples;
}

void ADC1_Set_MUX_Temp_Diode()
{
    delayMicroseconds(2);
    ADS1256_WriteReg_LCK( &ADC1, REG_MUX, ADC1_TEMP_DIODE);
    delayMicroseconds(2);
    ADS1256_Sync_LCK( &ADC1 );
    delayMicroseconds(5);
}

void ADC0_Throw_Away_Reading()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tADC0 THROW AWAY READING\n" COLOR_RESET);
    ADS1256_Throw_Away_Reading_LCK( &ADC0);
}

void ADC1_Throw_Away_Reading()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tADC1 THROW AWAY READING\n" COLOR_RESET);
    ADS1256_Throw_Away_Reading_LCK( &ADC1);
}

void ADC0_Read_Cooler_Volts()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\n\tREAD ADC0 COOLER VOLTS\t" COLOR_RESET);
    ADS1256_WaitDRDY( &ADC0 );
    ADS1256_Sync_LCK( &ADC0 );
    delayMicroseconds(2);
    int32_t count = ADS1256_ReadData_LCK( &ADC0 );
    ADC0_Cooler_Volts.count_sum += count;
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "%2.3f\n" COLOR_RESET, Cooler_Counts_to_Volts( count) );
    if( (count < 0) && PRINT_DEBUG_MUX )
    {
        printf(COLOR_LIGHT_MAGENTA "CV- negative number\n" COLOR_RESET);
        uint8_t mux = ADS1256_ReadReg_LCK(&ADC0, REG_MUX);
        printf("mux reg value: 0x%02X\n", mux);

    }
    ++ADC0_Cooler_Volts.num_samples;
}

void ADC0_Read_Cooler_Amps()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tREAD ADC0 COOLER AMPS\n" COLOR_RESET);
    ADS1256_WaitDRDY( &ADC0 );
    ADS1256_Sync_LCK( &ADC0 );
    delayMicroseconds(2);

    int32_t count = ADS1256_ReadData_LCK( &ADC0 );
    ADC0_Cooler_Amps.count_sum += count;
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "%2.3f\n" COLOR_RESET, Cooler_Counts_to_Volts( count) );
    if( (count < 0) && PRINT_DEBUG_MUX )
    {
        printf(COLOR_LIGHT_MAGENTA "CA - negative number\n" COLOR_RESET);
        uint8_t mux = ADS1256_ReadReg_LCK(&ADC0, REG_MUX);
        printf("mux reg value: 0x%02X\n", mux);
    }
    ++ADC0_Cooler_Amps.num_samples;
}

void ADC0_Read_Temp_Diode()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tREAD ADC0 TEMP DIODE  " COLOR_RESET);

  ADS1256_WaitDRDY( &ADC0 );
  ADS1256_Sync_LCK( &ADC0 );
  delayMicroseconds(2);
  int32_t count = ADS1256_ReadData_LCK( &ADC0 );
  ADC0_Temp_Diode_Volts.count_sum += count;
  if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "%2.3f\n" COLOR_RESET, Cooler_Counts_to_Volts( count) );
  if( (count < 0) && PRINT_DEBUG_MUX )
  {
        printf(COLOR_LIGHT_MAGENTA "TD negative number\n" COLOR_RESET);
        uint8_t mux = ADS1256_ReadReg_LCK(&ADC0, REG_MUX);
        printf("mux reg value: 0x%02X\n", mux);

  }
  ++ADC0_Temp_Diode_Volts.num_samples;
}

void ADC0_Set_MUX_Cooler_Volts()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BOLD_YELLOW "CHANGE MUX0 COOLER VOLTS\n" COLOR_RESET);
  delayMicroseconds(2);
  ADS1256_WriteReg_LCK( &ADC0, REG_MUX, ADC0_COOLER_VOLTS);
    delayMicroseconds(2);
  ADS1256_Sync_LCK( &ADC0 );
  delayMicroseconds(5);
  if( WAIT_MUX_CHANGE ) Wait_Enter();
}

void ADC0_Set_MUX_Cooler_Amps()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BOLD_YELLOW "CHANGE MUX0 COOLER AMPS\n" COLOR_RESET);
    delayMicroseconds(2);
  ADS1256_WriteReg_LCK( &ADC0, REG_MUX, ADC0_COOLER_AMPS);
    delayMicroseconds(2);
  ADS1256_Sync_LCK( &ADC0 );
  delayMicroseconds(5);
  if( WAIT_MUX_CHANGE ) Wait_Enter();
}

void ADC0_Set_MUX_Temp_Diode()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BOLD_YELLOW "CHANGE MUX0 TEMP DIODE\n" COLOR_RESET);
    delayMicroseconds(2);
  ADS1256_WriteReg_LCK( &ADC0, REG_MUX, ADC0_TEMP_DIODE);
    delayMicroseconds(2);
  ADS1256_Sync_LCK( &ADC0 );
  delayMicroseconds(5);
  if( WAIT_MUX_CHANGE ) Wait_Enter();
}

void ADC1_Set_MUX_Cooler_Amps()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BOLD_YELLOW "CHANGE MUX1 COOLER AMPS\n" COLOR_RESET);
    delayMicroseconds(2);
  ADS1256_WriteReg_LCK( &ADC1, REG_MUX, ADC1_COOLER_AMPS);
    delayMicroseconds(2);
  ADS1256_Sync_LCK( &ADC1 );
  delayMicroseconds(5);
  if( WAIT_MUX_CHANGE ) Wait_Enter();
}

void ADC1_Set_MUX_Heat_Load_V()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BOLD_YELLOW "CHANGE MUX1 HEAT LOAD MILLIAMPS\n" COLOR_RESET);
    delayMicroseconds(2);
  ADS1256_WriteReg_LCK( &ADC1, REG_MUX, ADC1_HEAT_LOAD_V);
    delayMicroseconds(2);
  ADS1256_Sync_LCK( &ADC1 );
  delayMicroseconds(5);
  if( WAIT_MUX_CHANGE ) Wait_Enter();
}

void ADC1_Set_MUX_Heat_Load_I()
{
  if( PRINT_DEBUG_MUX ) printf(COLOR_BOLD_YELLOW "CHANGE MUX1 HEAT LOAD MILLIAMPS\n" COLOR_RESET);
    delayMicroseconds(2);
  ADS1256_WriteReg_LCK( &ADC1, REG_MUX, ADC1_HEAT_LOAD_I);
    delayMicroseconds(2);
  ADS1256_Sync_LCK( &ADC1 );
  delayMicroseconds(5);
  if( WAIT_MUX_CHANGE ) Wait_Enter();
}

void ADC1_Read_Cooler_Amps()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tREAD ADC1 COOLER AMPS  " COLOR_RESET);
    ADS1256_WaitDRDY( &ADC1 );
    ADS1256_Sync_LCK( &ADC1 );
    int count = ADS1256_ReadData_LCK( &ADC1 );
    ADC1_Cooler_Amps.count_sum += count;
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "%2.3f\n" COLOR_RESET, ADS1256_Counts_to_Volts( count) );
    ++ADC1_Cooler_Amps.num_samples;
}

void ADC1_Read_Heat_Load_V()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tREAD ADC1 HEAT LOAD V\n" COLOR_RESET);
    ADS1256_WaitDRDY( &ADC1 );
    ADS1256_Sync_LCK( &ADC1 );
    ADC1_Heat_Load_Volts.count_sum += ADS1256_ReadData_LCK( &ADC1 );
    ++ADC1_Heat_Load_Volts.num_samples;
}

void ADC1_Read_Heat_Load_I()
{
    if( PRINT_DEBUG_MUX ) printf(COLOR_BRIGHT_YELLOW "\tREAD ADC1 HEAT LOAD V\n" COLOR_RESET);
    ADS1256_WaitDRDY( &ADC1 );
    ADS1256_Sync_LCK( &ADC1 );
    ADC1_Heat_Load_milliAmps.count_sum += ADS1256_ReadData_LCK( &ADC1 );
    ++ADC1_Heat_Load_milliAmps.num_samples;
}

void Calc_Measurement_Averages()
{
    if( ADC0_Cooler_Volts.num_samples > 0)
    {
        ADC0_Cooler_Volts.average_count  = ADC0_Cooler_Volts.count_sum / ADC0_Cooler_Volts.num_samples;
        ADC0_Cooler_Volts.raw_average_value = Cooler_Counts_to_Volts( ADC0_Cooler_Volts.average_count );
        ADC0_Cooler_Volts.average_value = get_Corrected_Value( ADC0_Cooler_Volts.raw_average_value, COOLER_V_LUT, ARRAY_SIZE(COOLER_V_LUT));
    }
    else
        ADC0_Cooler_Volts.average_value = 0;


    if( ADC0_Cooler_Amps.num_samples > 0)
    {
        ADC0_Cooler_Amps.average_count  = ADC0_Cooler_Amps.count_sum / ADC0_Cooler_Amps.num_samples;
        ADC0_Cooler_Amps.raw_average_value  = ADC0_Cooler_Counts_to_Amps( ADC0_Cooler_Amps.average_count );
        ADC0_Cooler_Amps.average_value  = get_Corrected_Value( ADC0_Cooler_Amps.raw_average_value, COOLER_mA_LUT, ARRAY_SIZE(COOLER_mA_LUT) );
    }
    else
        ADC0_Cooler_Amps.average_value = 0;


    if( ADC1_Cooler_Amps.num_samples > 0)
    {
        ADC1_Cooler_Amps.average_count  = ADC1_Cooler_Amps.count_sum / ADC1_Cooler_Amps.num_samples;
        ADC1_Cooler_Amps.raw_average_value  = ADC0_Cooler_Counts_to_Amps( ADC1_Cooler_Amps.average_count );
        ADC1_Cooler_Amps.average_value  = get_Corrected_Value( ADC1_Cooler_Amps.raw_average_value, COOLER_mA_LUT, ARRAY_SIZE(COOLER_mA_LUT) );
    }
    else
        ADC1_Cooler_Amps.average_value = 0;

    if( ADC0_Temp_Diode_Volts.num_samples > 0)
    {
        ADC0_Temp_Diode_Volts.average_count = ADC0_Temp_Diode_Volts.count_sum / ADC0_Temp_Diode_Volts.num_samples;
        ADC0_Temp_Diode_Volts.average_value = Temp_Diode_Counts_to_Volts( ADC0_Temp_Diode_Volts.average_count );
    }
    else
        ADC0_Temp_Diode_Volts.average_value = 0;

    if( ADC1_Temp_Diode_Volts.num_samples > 0)
    {
        ADC1_Temp_Diode_Volts.average_count = ADC1_Temp_Diode_Volts.count_sum / ADC1_Temp_Diode_Volts.num_samples;
        ADC1_Temp_Diode_Volts.average_value = Temp_Diode_Counts_to_Volts( ADC1_Temp_Diode_Volts.average_count );
    }
    else
        ADC1_Temp_Diode_Volts.average_value = 0;

    if( ADC1_Heat_Load_Volts.num_samples > 0)
    {
        ADC1_Heat_Load_Volts.average_count  = ADC1_Heat_Load_Volts.count_sum / ADC1_Heat_Load_Volts.num_samples ;     // Average count from samples spanning 1 second
        ADC1_Heat_Load_Volts.raw_average_value  = Heat_Load_Counts_to_Volts( ADC1_Heat_Load_Volts.average_count );
        ADC1_Heat_Load_Volts.average_value      = get_Corrected_Value( ADC1_Heat_Load_Volts.raw_average_value, LOAD_V_LUT, ARRAY_SIZE(LOAD_V_LUT));
    }
    else
        ADC1_Heat_Load_Volts.average_value = 0;

    if( ADC1_Heat_Load_milliAmps.num_samples > 0)
    {
        ADC1_Heat_Load_milliAmps.average_count = ADC1_Heat_Load_milliAmps.count_sum / ADC1_Heat_Load_milliAmps.num_samples;
        ADC1_Heat_Load_milliAmps.raw_average_value = Heat_Load_Counts_to_milliAmps( ADC1_Heat_Load_milliAmps.average_count  );
        ADC1_Heat_Load_milliAmps.average_value = get_Corrected_Value( ADC1_Heat_Load_milliAmps.raw_average_value, LOAD_mA_LUT, ARRAY_SIZE(LOAD_mA_LUT));
    }
    else
        ADC1_Heat_Load_milliAmps.average_count = 0;
}

double Cooler_Counts_to_Volts( int counts )
{
    double cooler_divided_voltage = ADS1256_Counts_to_Volts( counts );
    return 4.0 * cooler_divided_voltage;
}

double Heat_Load_Counts_to_milliAmps( int counts )
{
    double V_shunt_amplified = ADS1256_Counts_to_Volts( counts );
    double V_shunt = V_shunt_amplified / 60.0;             // Current sense amplifier has gain of 60
    double i_Amps = V_shunt / LOAD_SHUNT_OHMS;             // sense resistor in ohms, defined in top of this file
    return i_Amps * 1000;                                  // convert amps to milliamps
}

double Heat_Load_Counts_to_Volts( int counts )
{
    return  8.0 * ADS1256_Counts_to_Volts( counts );   // the multiply by 8 is due to an onboard voltage divider network
}

double ADC0_Cooler_Counts_to_Amps( int counts)
{
    //printf("ADC0_CoolA Voltage: %f\n", ADS1256_Counts_to_Volts(counts) );
    return 0.3013*ADS1256_Counts_to_Volts(counts);
}

double ADC1_Cooler_Counts_to_Amps( int counts)
{
    //printf("ADC1_CoolA Voltage: %f\n", ADS1256_Counts_to_Volts(counts) );
    return 0.3013*ADS1256_Counts_to_Volts(counts);
}

double Temp_Diode_Counts_to_Volts( int counts)
{
    return ADS1256_Counts_to_Volts(counts);
}

double ADS1256_Counts_to_Volts(int32_t adc_counts)
{
		double volts = adc_counts * VOLTS_PER_COUNT;
		return volts;
}

void Read_Default_Regs(ADC* ADC_chip)
{
    if(PRINT_DEBUG) printf(COLOR_BRIGHT_GREEN " ADS1256 DEFAULT REG VALUES\n" COLOR_RESET);
    uint8_t Read_Back_Val=0;
    if(PRINT_DEBUG) printf("  STATUS REG:\r");
    Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_STATUS );
    if(PRINT_DEBUG) printf("\t\t0x%02X\n", Read_Back_Val);

    if(PRINT_DEBUG) printf("  MUX REG:\r");
    Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_MUX);
    if(PRINT_DEBUG) printf("\t\t0x%02X\n", Read_Back_Val);

    if(PRINT_DEBUG) printf("  ADCON REG:\r");
    Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_ADCON);
    if(PRINT_DEBUG) printf("\t\t0x%02X\n", Read_Back_Val);

    if(PRINT_DEBUG) printf("  DRATE REG:\r");
    Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_DRATE);
    if(PRINT_DEBUG) printf("\t\t0x%02X\n\n", Read_Back_Val);
}

static void ADS1256_Sync_LCK(ADC* ADC_chip)
{
  pthread_mutex_lock (&SPI_BUS_LOCK);
	   CS_LOW( ADC_chip );
	   bcm2835_delayMicroseconds(5);

     if( PRINT_DEBUG )
     {
        printf("\t\t\t\tSYNC\r");
        Print_Tabs(TXRX_TABS);
        printf("[ TX: %02X ]\n", CMD_SYNC);
     }

	   bcm2835_spi_transfer(CMD_SYNC);
	   bcm2835_delayMicroseconds(5);

     if( PRINT_DEBUG )
     {
        printf("\t\t\t\tWAKEUP\r");
        Print_Tabs(TXRX_TABS);
        printf("[ TX: %02X ]\n", CMD_WAKEUP);
     }

	   bcm2835_spi_transfer(CMD_WAKEUP);
     bcm2835_delayMicroseconds(5);
	   CS_HIGH( ADC_chip );
  pthread_mutex_unlock (&SPI_BUS_LOCK);
}

void CS_LOW( ADC* ADC_chip )
{
    bcm2835_delayMicroseconds(2);
    bcm2835_gpio_write( ADC_chip->BUF_EN_pin, LOW);     // write buffer low to enable the buffer
		bcm2835_gpio_write( ADC_chip->CS_pin, LOW);     		// write chip select low to start a transfer
    delayMicroseconds(2);
}

void CS_HIGH( ADC* ADC_chip )
{
		bcm2835_gpio_write( ADC_chip->CS_pin, HIGH);     			// write chip select high to end the transfer
		bcm2835_gpio_write( ADC_chip->BUF_EN_pin, HIGH);     	// write buffer high to disable the buffer
}

bool DRDY_IS_LOW(ADC* ADC_chip)
{
		return (bcm2835_gpio_lev( ADC_chip->DRDY_pin )==0);		// sample DRDY pin and return whether it is LOW
}

void ADS1256_Init(void)
{
    // buf en0 = original adc
    // buf en1 = new adc on spi0
    // buf en2 == new adc on spi1

	  ADS1256_Hard_Reset_LCK();
		delayMicroseconds(100*ONE_MILLISECOND);
    ADS1256_WaitDRDY( &ADC0 );
		ADS1256_Calibrate_Gain_and_Offset( &ADC0 );
		delayMicroseconds(100*ONE_MILLISECOND);
    ADS1256_WaitDRDY( &ADC1 );
		ADS1256_Calibrate_Gain_and_Offset( &ADC1 );
		delayMicroseconds(100*ONE_MILLISECOND);

    double VOLT_QUANTA = V_FULL_SCALE / TOTAL_COUNTS;  // 1 LSB
		VOLTS_PER_COUNT = VOLT_QUANTA;
}

void ADS1256_Calibrate_Gain_and_Offset(ADC* ADC_chip)
{
	delayMicroseconds( ONE_MILLISECOND );
  if(PRINT_DEBUG) printf("\n\tCAL Gain&Offset->\t");
	ADS1256_Send_Cmd_LCK( ADC_chip, CMD_SELF_CAL );
	while( !DRDY_IS_LOW( ADC_chip ) ){}
}

// resets both ADS1256 chips
static void ADS1256_Hard_Reset_LCK()
{
  if(PRINT_DEBUG){ printf(COLOR_BRIGHT_GREEN "\tHARD RESET .....\n" COLOR_RESET ); }
  pthread_mutex_lock (&SPI_BUS_LOCK);
      bcm2835_gpio_write(ADS1256_RESET,LOW); //perform hardware reset
      delayMicroseconds(20); // LOW at least 4 clock cycles of onboard clock. 10 microseconds is enough
      bcm2835_gpio_write(ADS1256_RESET,HIGH);
      delayMicroseconds(10);
  pthread_mutex_unlock (&SPI_BUS_LOCK);
}

// Configure Gain and Data Rate
void ADS1256_Config_LCK(ADC* ADC_chip, ADS1256_GAIN_ENUM gain, ADS1256_DRATE_ENUM drate)
{
    char ADC_string[6];

    memset(ADC_string,0,sizeof(ADC_string));
    ADC_string[0] = '\0';
    if(ADC_chip->CS_pin == ADS1256_CS_1)
    {
        strcpy(ADC_string, "ADC1");
        ADC_string[ strlen(ADC_string) ] ='\0';
        ADC_string[4] = '\0';
    }
    if(ADC_chip->CS_pin == ADS1256_CS_0)
    {
        strcpy(ADC_string, "ADC0");
        ADC_string[ strlen(ADC_string) ] ='\0';
        ADC_string[4] = '\0';
    }

	if(PRINT_DEBUG) printf(COLOR_BRIGHT_GREEN "\n\n------ADS1256_CONFIG------\n" COLOR_RESET );
	delayMicroseconds(10);
	if(PRINT_DEBUG){ printf("\n"); }
	if(PRINT_DEBUG) printf("Set DRATE: %s\t== 0x%02X\n", ADC_string, drate);

	ADS1256_WriteReg_LCK( ADC_chip, REG_DRATE, drate );
  delayMicroseconds(10);

		uint8_t buf[4];		/* ads1256 register configuration parameters */
		// buf[0] = STATUS register parameters
		// buf[1] = Mux Register parameters
		// buf[2] = ADCON register parameters
		// buf[3] = Data Rate parameters

		/*Status register define
			Bits 7-4 ID3, ID2, ID1, ID0  Factory Programmed Identification Bits (Read Only)

			Bit 3 ORDER: Data Output Bit Order
				0 = Most Significant Bit First (default)
				1 = Least Significant Bit First
			Input data  is always shifted in most significant byte and bit first. Output data is always shifted out most significant
			byte first. The ORDER bit only controls the bit order of the output data within the byte.

			Bit 2 ACAL : Auto-Calibration
				0 = Auto-Calibration Disabled (default)
				1 = Auto-Calibration Enabled
			When Auto-Calibration is enabled, self-calibration begins at the completion of the WREG command that changes
			the PGA (bits 0-2 of ADCON register), DR (bits 7-0 in the DRATE register) or BUFEN (bit 1 in the STATUS register)
			values.

			Bit 1 BUFEN: Analog Input Buffer Enable
				0 = Buffer Disabled (default)
				1 = Buffer Enabled

			Bit 0 DRDY :  Data Ready (Read Only)
				This bit duplicates the state of the DRDY pin.

			ACAL=1  enable  calibration
		*/
		//buf[0] = (0 << 3) | (1 << 2) | (1 << 1);	//	enable the internal buffer
    //buf[0] = (0 << 3) | (1 << 2) | (0 << 1);  // 	The internal buffer is prohibited
		buf[0] = 0b0000 | 0b0100 | 0b0010;  // sets buffer on, autocal enabled, MSB first

    //printf("set status reg: 0x%02X\n", (0 << 3) | (1 << 2) | (1 << 1) );
    //ADS1256_WriteReg_LCK(ADC_chip, REG_STATUS, buf[0]);   //0b0110

		buf[1] = 0x01; // Mux register, setting positive input to AIN0, negative input to AIN1

		/*	ADCON: A/D Control Register (Address 02h)
			Bit 7 Reserved, always 0 (Read Only)
			Bits 6-5 CLK1, CLK0 : D0/CLKOUT Clock Out Rate Setting
				00 = Clock Out OFF
				01 = Clock Out Frequency = fCLKIN (default)
				10 = Clock Out Frequency = fCLKIN/2
				11 = Clock Out Frequency = fCLKIN/4
				When not using CLKOUT, it is recommended that it be turned off. These bits can only be reset using the RESET pin.

			Bits 4-3 SDCS1, SCDS0: Sensor Detect,  Current Sources
				00 = Sensor Detect OFF (default)
				01 = Sensor Detect Current = 0.5 A
				10 = Sensor Detect Current = 2 A
				11 = Sensor Detect Current = 10 A
				The Sensor Detect Current Sources can be activated to verify  the integrity of an external sensor supplying a signal to the
				ADS1255/6. A shorted sensor produces a very small signal while an open-circuit sensor produces a very large signal.

			Bits 2-0 PGA2, PGA1, PGA0: Programmable Gain Amplifier Setting
				000 = 1 (default)
				001 = 2
				010 = 4
				011 = 8
				100 = 16
				101 = 32
				110 = 64
				111 = 64
		*/
		buf[2] = (0 << 5) | (0 << 3) | ( gain << 0); // sets clock out off, sensor detect off, no gain from PGA
		buf[3] = drate;	// DRATE_15SPS;


	  if(PRINT_DEBUG)printf(COLOR_BROWN "Setting Parameters for 4 registers:\n\n" COLOR_RESET);

		if(PRINT_DEBUG)printf("    STATUS REG ID: 0x%02X\tVAL: 0x%02X\n", REG_STATUS, buf[0]);
    ADS1256_WaitDRDY( ADC_chip ); // Wait until a conversion has completed before sending data
    ADS1256_WriteReg_LCK( ADC_chip, REG_STATUS, buf[0] );
    ADS1256_WaitDRDY( ADC_chip ); // Wait until a conversion has completed before sending data
		bcm2835_delayMicroseconds(5);						// 0x00 is status register

		if(PRINT_DEBUG)printf("    MUX REG ID: 0x%02X\tVAL: 0x%02X\n", REG_MUX, buf[1]);
    ADS1256_WriteReg_LCK( ADC_chip, REG_MUX, buf[1] );
    ADS1256_WaitDRDY( ADC_chip ); // Wait until a conversion has completed before sending data
		bcm2835_delayMicroseconds(5);						// 0x01 is MUX register

		if(PRINT_DEBUG)printf("    ADCON REG ID: 0x%02X\tVAL: 0x%02X\n", REG_ADCON, buf[2]);
    ADS1256_WriteReg_LCK( ADC_chip, REG_ADCON, buf[2] );
    ADS1256_WaitDRDY( ADC_chip ); // Wait until a conversion has completed before sending data
		bcm2835_delayMicroseconds(5);						// 0x02 is ADCON register

		if(PRINT_DEBUG)printf("    DRATE REG ID: 0x%02X\tVAL: 0x%02X\n", REG_DRATE, buf[3]);
    ADS1256_WriteReg_LCK( ADC_chip, REG_DRATE, buf[3] );
    ADS1256_WaitDRDY( ADC_chip ); // Wait until a conversion has completed before sending data
		bcm2835_delayMicroseconds(5);						// 0x02 is ADCON register


		if(PRINT_DEBUG)
		{
			printf(COLOR_BRIGHT_GREEN " REGISTER READBACK\n" COLOR_RESET);
			uint8_t Read_Back_Val=0;
      printf("\tSTATUS REG:\r");
			Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_STATUS );
      printf("\n\n");

      printf("\tMUX REG:\r");
			Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_MUX);
      printf("\n\n");

      printf("\tADCON REG:\r");
			Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_ADCON);
      printf("\n\n");

      printf("\tDRATE REG:\r");
      Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, REG_DRATE);
      printf("-----------------------------------------------------------------------\n\n");
      if(WAIT_ENTER) Wait_Enter();
		}
	bcm2835_delayMicroseconds(10);
}

static void ADS1256_DelayDATA(void)
{
	/*
		Delay from last SCLK edge for clocking data DIN to first SCLK rising edge for clocking data DOUT:
		min time = 50*master_clock_period
    master_clock_period determined from oscillator freq. (7.68 Mhz)
		master_clock_period = 1/7.68 Mhz = .13uS
		min_time = 50 *.13uS = 6.5uS
		RDATA, RDATAC,RREG Commands require min delay of:  50 clock cycles = 50 * 0.13uS = 6.5uS
	*/
	bcm2835_delayMicroseconds(8);	/* The minimum time delay 6.5us, using 8 to be safe */
}

// Assumes register to read has already been sent, only performing the read operation here
static uint8_t ADS1256_ReadByte()
{
	if(PRINT_DEBUG)
	{
    Print_Tabs( SECONDARY_FUNCTION_TABS );
		printf("READBYTE\r");
	}

	uint8_t read_byte = 0;                     // storage container for byte to read
  ADS1256_DelayDATA();	               			 /*delay time required by datasheet*/

  read_byte = bcm2835_spi_transfer(NOP);    // must "send" data (clocks) to receive data
	if(PRINT_DEBUG_TXRX)
	{
    Print_Tabs(TXRX_TABS);
		printf("[ TX: 0xFF  RX: ");
		printf("0x%02X ] \n", (read_byte | 0x00));
	}
	return read_byte;
}

static uint8_t ADS1256_ReadReg_LCK(ADC* ADC_chip, uint8_t RegID)
{
	uint8_t read_byte;
	uint8_t send_byte = (CMD_READ_REG | RegID);
  char ADC_string[6];

  memset(ADC_string,0,sizeof(ADC_string));
  ADC_string[0] = '\0';
  if(ADC_chip->CS_pin == ADS1256_CS_1)
  {
      strcpy(ADC_string, "ADC1");
      ADC_string[ strlen(ADC_string) ] ='\0';
      ADC_string[4] = '\0';
  }
  if(ADC_chip->CS_pin == ADS1256_CS_0)
  {
      strcpy(ADC_string, "ADC0");
      ADC_string[ strlen(ADC_string) ] ='\0';
      ADC_string[4] = '\0';
  }

	if(PRINT_DEBUG)
	{
      printf("\n");
      Print_Tabs( SECONDARY_FUNCTION_TABS );
			printf("%s READ_REG\r", ADC_string);
			Print_Tabs(TXRX_TABS);
      if( PRINT_DEBUG_TXRX)
      {
        printf("[ TX: 0x%02X ]\t", send_byte | 0x00);
        printf(" \t( read command, 0x10 | REG_ID==0x%02X )\n", RegID);
        Print_Tabs(TXRX_TABS);
        printf("[ TX: 0x00 ] \t        ( # regs to read - 1, 0x00 means read 1 register)\n");
      }
      printf("\n");
	}
  pthread_mutex_lock (&SPI_BUS_LOCK);
	  CS_LOW( ADC_chip );	/* write Chip Select low to start a transfer */
	  ADS1256_Write_Byte(CMD_READ_REG | RegID);	  /* Write register ID to the command register */
		bcm2835_delayMicroseconds(1);

	  ADS1256_Write_Byte(0x00);	             // Write register ID to the command register
		delayMicroseconds(10); 								// min delay: t6 = 50 * 1/freq.clkin = 50 * 1 / 7,68 Mhz = 6.5 micro sec
    read_byte = ADS1256_ReadByte();	    	// Read the register byte value
	  CS_HIGH( ADC_chip );										// take Chip Select high to end the transfer
  pthread_mutex_unlock (&SPI_BUS_LOCK);
	if(PRINT_DEBUG)
	{
		Print_Tabs(TXRX_TABS);
		printf("return val: " COLOR_LIGHT_CYAN "0x%02X\n" COLOR_RESET, read_byte);
	}
	return read_byte;
}

// Write to a register
static void ADS1256_WriteReg_LCK(ADC* ADC_chip, uint8_t RegID, uint8_t RegValue)
{
	uint8_t byte = 0;
	byte = (CMD_WRITE_REG | RegID);

  char ADC_string[6];

  memset(ADC_string,0,sizeof(ADC_string));
  ADC_string[0] = '\0';
  if(ADC_chip->CS_pin == ADS1256_CS_1)
  {
      strcpy(ADC_string, "ADC1");
      ADC_string[ strlen(ADC_string) ] ='\0';
      ADC_string[4] = '\0';
  }
  if(ADC_chip->CS_pin == ADS1256_CS_0)
  {
      strcpy(ADC_string, "ADC0");
      ADC_string[ strlen(ADC_string) ] ='\0';
      ADC_string[4] = '\0';
  }

  delayMicroseconds(4);

	if(PRINT_DEBUG)
	{
		printf("\t                       %s WRITE_REG\r", ADC_string);
		if( PRINT_DEBUG_TXRX ){ Print_Tabs(TXRX_TABS); printf("[ TX: 0x%02X ]\t\t( write command,  0x50 | REG_ID )\n", byte); }
	}
  pthread_mutex_lock (&SPI_BUS_LOCK);
	   CS_LOW( ADC_chip );
     bcm2835_delayMicroseconds(2);												/* bring Chip Select low to start a transfer */
	   bcm2835_spi_transfer(CMD_WRITE_REG | RegID);	 	     /* Send 1st byte, address of register to read */
		 bcm2835_delayMicroseconds(2);

	   bcm2835_spi_transfer(0x00);		           	        /* Send second byte, writing only 1 register, so second byte is 0 */
		 bcm2835_delayMicroseconds(2);

	   bcm2835_spi_transfer(RegValue);	                	/* write value to the register */
     bcm2835_delayMicroseconds(2);
	   CS_HIGH( ADC_chip );														 	/* take Chip Select high to end the transfer*/
  pthread_mutex_unlock (&SPI_BUS_LOCK);

  if(PRINT_DEBUG_TXRX)
  {
      Print_Tabs(TXRX_TABS);
      printf("[ TX: 0x00 ]\t\t( # regs to write - 1, 0x00 means write 1 register)\n");
      Print_Tabs(TXRX_TABS);
      printf("[ TX: 0x%02X ]\n", RegValue | 0x00);
  }
	if(WAIT_ENTER) Wait_Enter();

  bcm2835_delayMicroseconds(10);

	uint8_t Read_Back_Val=ADS1256_ReadReg_LCK( ADC_chip, RegID );

  if ( RegValue != Read_Back_Val)
  {
      if(PRINT_DEBUG) printf("%s: Write to Register 0x%02X failed.\n", ADC_string, RegID);
  		if(PRINT_DEBUG) printf("   Value read back was 0x%02X .\n", Read_Back_Val);
  		if(PRINT_DEBUG) printf("   Value assigned was 0x%02X . ]\n", RegValue);
	}

}

// Write a byte to ADS1256
// must have chip select low and buffer enabled already
static void ADS1256_Write_Byte(uint8_t data)
{
	bcm2835_delayMicroseconds(1);
	bcm2835_spi_transfer(data);
}

void ADS1256_Send_Cmd_LCK( ADC* ADC_chip, uint8_t _cmd)
{
	if(PRINT_DEBUG) printf("SEND CMD:\t\t0x%02X\n", _cmd);
  pthread_mutex_lock (&SPI_BUS_LOCK);
	    CS_LOW( ADC_chip );
      delayMicroseconds(2);
	    bcm2835_spi_transfer(_cmd);
      delayMicroseconds(2);
	    CS_HIGH( ADC_chip );
  pthread_mutex_unlock (&SPI_BUS_LOCK);
}

 // wait until ADS1256 finishes performing conversion and data is ready for reading.
 // interrupts are slow on the PI so just occupying the CPU with for loop while waiting
 // DRDY pin goes low when data is available for reading
static void ADS1256_WaitDRDY( ADC* ADC_chip)
{
  //clock_gettime(CLOCK_REALTIME, &time_start);
	uint32_t i;
	for (i = 0; i < 400000; i++)
	{
		delayMicroseconds(1);
		if ( DRDY_IS_LOW( ADC_chip ) ){ break; }
	}
	if (i >= 70000 && PRINT_DEBUG){ printf("\n\t----ADS1256_WaitDRDY() Time Out---- ...\r\n"); }

  //clock_gettime(CLOCK_REALTIME, &time_finish);
  //time_difference_nanos = time_finish.tv_nsec - time_start.tv_nsec;
  //if (time_difference_nanos < 0)
  //{ time_difference_nanos += 1000000000;	}			//(Rolls over every 1 second)
  //time_difference_micros = time_difference_nanos/1000;
  //if ( PRINT_WAIT_TIME )printf("\twait ms:\t%d \n", time_difference_micros/1000);
  //loop_micros += time_difference_micros;
  delayMicroseconds(1);
}

// read ADC 32 bit value
static int32_t ADS1256_ReadData_LCK( ADC* ADC_chip )
{
	uint32_t counts = 0;      // 32 bit storage to hold 24 bit return value
  static uint8_t read[3];  // Array to hold (3) byte reads

	if(PRINT_DEBUG)
	{
		if(PRINT_DEBUG) printf(COLOR_BRIGHT_GREEN "\tREAD_DATA\r" COLOR_RESET);
		Print_Tabs(TXRX_TABS);
		if( PRINT_DEBUG_TXRX ) printf("[ TX: 0x%02X ]\n", CMD_READ_DATA);
    if( PRINT_DEBUG && !PRINT_DEBUG_TXRX) printf("\n");

	}

  pthread_mutex_lock (&SPI_BUS_LOCK);
	    CS_LOW( ADC_chip );	/* Start Transfer by bringing Chip Select low */
	    bcm2835_spi_transfer(CMD_READ_DATA);	/* send ADC read command  */
	    ADS1256_DelayDATA();	/* delay time mandated before reading */

			/*Read the 24bit value in counts */
      read[0] = ADS1256_ReadByte();				// MSB
      delayMicroseconds(4);
      read[1] = ADS1256_ReadByte();
      delayMicroseconds(4);
      read[2] = ADS1256_ReadByte();				// LSB

			// combine 3 bytes into one 24 bit number
      counts = ((uint32_t)read[0] << 16) & 0x00FF0000; // uint32 is 32 bits, this byte is bits 16-24, shift 16 places
      counts |= ((uint32_t)read[1] << 8); // shift the second byte over 8 bits, then OR with result
      counts |= read[2]; // last 8 bits (LSB)

	    CS_HIGH( ADC_chip );	/* End the transfer by bringing Chip Select High*/
  pthread_mutex_unlock (&SPI_BUS_LOCK);

	// If negative number, fill leading zeroes with 1's to configure the "sign" as negative
	// If the MSB of the 24 bit number is 1, that means the result is negative (2's complement)
	// If the MSB is 1, then an AND with 1000 (8 in hex) will produce "true" in the if statement
  if (counts & 0x800000)
  {
		  //printf(COLOR_LIGHT_MAGENTA "\tNEGATIVE NUMBER: 0x%06X\n" COLOR_RESET, counts);
	    counts |= 0xFF000000; // Fill the rest of the leading bits with 1
  }
	if( PRINT_DEBUG )
	{
    printf("\t\tCount:\t" COLOR_LIGHT_MAGENTA "%d" COLOR_RESET " (dec), " COLOR_LIGHT_MAGENTA "0x%06X " COLOR_RESET "(hex)", counts, counts);
    printf( COLOR_LIGHT_MAGENTA "\t%f V\n\n" COLOR_RESET, ADS1256_Counts_to_Volts(counts) );
		// if( WAIT_ENTER ) Wait_Enter();
	}
  	if( TEMPORARY_DEBUG )
  	{
      printf("\t\tCount:\t" COLOR_LIGHT_MAGENTA "%d" COLOR_RESET " (dec), " COLOR_LIGHT_MAGENTA "0x%06X " COLOR_RESET "(hex)", counts, counts);
      printf( COLOR_LIGHT_MAGENTA "\t%f V\n\n" COLOR_RESET, ADS1256_Counts_to_Volts(counts) );
  		// if( WAIT_ENTER ) Wait_Enter();
  	}
	return (int32_t)counts;
}

// read ADC 32 bit value
static void ADS1256_Throw_Away_Reading_LCK( ADC* ADC_chip )
{
	if(PRINT_DEBUG)
	{
		printf( COLOR_BRIGHT_GREEN "\tTHROW_AWAY_READING:\t" COLOR_RESET "READ_CMD\r");
		Print_Tabs(TXRX_TABS);
		printf("[ TX: 0x%02X ]\n", CMD_READ_DATA);
	}
  delayMicroseconds(15);
  ADS1256_WaitDRDY( ADC_chip );
  delayMicroseconds(5);

  pthread_mutex_lock (&SPI_BUS_LOCK);
	CS_LOW( ADC_chip );	/* Start Transfer by bringing Chip Select low */
      delayMicroseconds(2);
	    bcm2835_spi_transfer(CMD_READ_DATA);	/* send ADC read command  */
	    ADS1256_DelayDATA();	/* delay time mandated before reading */
      delayMicroseconds(2);
      /*Read the 24bit value */
      ADS1256_ReadByte();				// MSB
      delayMicroseconds(2);
      ADS1256_ReadByte();
      delayMicroseconds(2);
      ADS1256_ReadByte();				// LSB
	CS_HIGH( ADC_chip );	/* End the transfer by bringing Chip Select High*/
  pthread_mutex_unlock (&SPI_BUS_LOCK);
  if( PRINT_DEBUG ) printf("\n\n");
	return;
}

#endif
