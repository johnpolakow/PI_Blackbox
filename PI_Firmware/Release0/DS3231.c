#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>



#define ADDR_SECONDS      0x00
#define ADDR_MINUTES      0x01
#define ADDR_HOURS        0x02
#define ADDR_DAY_OF_WEEK  0x03
#define ADDR_DAY_OF_MONTH 0x04
#define ADDR_MONTH        0x05
#define ADDR_YEAR         0x06

#define INDEX_START_ADDR        0x00
#define WRITE_INDEX_SECONDS       1
#define WRITE_INDEX_MINUTES       2
#define WRITE_INDEX_HOURS         3
#define WRITE_INDEX_DAY_OF_WEEK   4
#define WRITE_INDEX_DAY_OF_MONTH  5
#define WRITE_INDEX_MONTH         6
#define WRITE_INDEX_YEAR          7

#define READ_INDEX_SECONDS       0
#define READ_INDEX_MINUTES       1
#define READ_INDEX_HOURS         2
#define READ_INDEX_DAY_OF_WEEK   3
#define READ_INDEX_DAY_OF_MONTH  4
#define READ_INDEX_MONTH         5
#define READ_INDEX_YEAR          6


#define MASK_SECONDS      0x7F
#define MASK_MINUTES      0x7F
#define MASK_HOURS        0x3F
#define MASK_DAY_OF_WEEK  0x07
#define MASK_DAY_OF_MONTH 0x3F
#define MASK_MONTH        0x1F


#define DS3231_ADDRESS        0x68        ///  I2C address for DS3231
#define DS3231_CONTROL        0x0E        ///  Control register
#define DS3231_STATUS_REG     0x0F        ///  Status register

#define SECONDS_PER_DAY       86400       ///  60 * 60 * 24
#define SECONDS_1970_TO_2000  946684800   ///  Unixtime for 2000-01-01 00:00:00, useful for initialization

/**
  Number of days in each month, from January to November. December is not
  needed. Omitting it avoids an incompatibility with Paul Stoffregen's Time
  library. C.f. https://github.com/adafruit/RTClib/issues/114
//*/
const uint8_t daysInMonth [] = { 31,28,31,30,31,30,31,31,30,31,30 };

/**************************************************************************/
/*!
    @brief  Given a number of days, hours, minutes, and seconds, return the total seconds
    @param days Days
    @param h Hours
    @param m Minutes
    @param s Seconds
    @return Number of seconds total
*/
/**************************************************************************/
static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}


/**************************************************************************/
/*!
    @brief  Convert a binary coded decimal to binary. RTC stores time/date values as BCD.
    @param val BCD value
    @return Binary value
*/
/**************************************************************************/
static uint8_t BCD_To_Decimal (uint8_t bcd)
{
  //  return bcd - 6 * (bcd >> 4);    // gets day of week right
    // return (uint8_t)(10 * ((bcd & 0xF0) >> 4) + (bcd & 0x0F));
    uint8_t msb = bcd;
    return ((msb >> 4) * 10) + (bcd & 0x0F);
}

/**************************************************************************/
/*!
    @brief  Convert a binary value to BCD format for the RTC registers
    @param val Binary value
    @return BCD value
*/
/**************************************************************************/
static uint8_t Decimal_To_BCD(uint8_t dec)
{
//    return dec + 6 * (dec / 10);    // gets day of week right
    //    return (uint8_t)(((dec / 10) << 4) | (dec % 10));
    uint8_t msb = dec;
            return ((msb / 10) << 4) + (dec % 10);
}


struct time_stamp
{
    int month;
    int day;
    int year;
    int hour;
    int minute;
    int second;
};

typedef struct time_stamp Time_Stamp;
Time_Stamp Time_Now;

uint8_t TIME_bytes[8];
char *str[]  ={"SUN", "MON", "TUES", "WED", "THUR", "FRI", "SAT"};

struct tm *time_info;
time_t raw_time_now;
struct timespec current_time;

void DS3231_Set_From_Linux_Time()
{
    //char addr_byte[1] = { 0x00 };
    char timestamp_string[300];
    timestamp_string[0] = '\0';

    time( &raw_time_now);
    time_info = localtime(&raw_time_now);


    printf("\t --SET DS3231 FROM LINUX TIME--\n");
    strftime (timestamp_string,50,"%H:%M:%S  %m/%d/%Y ",time_info); // convert time info to string
    //printf("formatted string from get_time: \t%s\n", timestamp_string);
    for(int i=0; i<strlen(timestamp_string); i++)
    {
          if(timestamp_string[i] == '/' || timestamp_string[i] == ':') // remove slashes from date and replace with dashes so compatible with filename
          {	timestamp_string[i] = ' ';	}
    }

    // parse the string into individual integer values
    sscanf(timestamp_string, "%d %d %d  %d %d %d ", &Time_Now.hour, &Time_Now.minute, &Time_Now.second, &Time_Now.month, &Time_Now.day, &Time_Now.year );

    Time_Now.year -= 2000;
    //printf("SET before BCD %d:%d:%d %d/%d/%d\t\t(2 digit year)\n", Time_Now.hour, Time_Now.minute, Time_Now.second, Time_Now.month,
    //        Time_Now.day, Time_Now.year);

    TIME_bytes[INDEX_START_ADDR] = 0x00;
    TIME_bytes[WRITE_INDEX_SECONDS] = Decimal_To_BCD( (uint8_t) Time_Now.second & MASK_SECONDS ) ; //sec
    TIME_bytes[WRITE_INDEX_MINUTES] = Decimal_To_BCD( (uint8_t) Time_Now.minute & MASK_MINUTES );
    TIME_bytes[WRITE_INDEX_HOURS] = Decimal_To_BCD( (uint8_t) Time_Now.hour & MASK_HOURS );
    TIME_bytes[WRITE_INDEX_DAY_OF_WEEK] = 0;
    TIME_bytes[WRITE_INDEX_DAY_OF_MONTH] = Decimal_To_BCD((uint8_t) Time_Now.day & MASK_DAY_OF_MONTH );
    TIME_bytes[WRITE_INDEX_MONTH] = Decimal_To_BCD( (uint8_t) Time_Now.month & MASK_MONTH );
    //TIME_bytes[WRITE_INDEX_YEAR] = Decimal_To_BCD( (uint8_t) Time_Now.year -2000);
    TIME_bytes[WRITE_INDEX_YEAR] = (uint8_t)( Time_Now.year -2000 );


    //printf("SET After BCD: %d:%d:%d %d/%d/%d\t\t(two digit year)\n", TIME_bytes[WRITE_INDEX_HOURS], TIME_bytes[WRITE_INDEX_MINUTES], TIME_bytes[WRITE_INDEX_SECONDS], TIME_bytes[WRITE_INDEX_MONTH],
    //        TIME_bytes[WRITE_INDEX_DAY_OF_MONTH], TIME_bytes[WRITE_INDEX_YEAR]);
    //printf("\t --------------\n");
    bcm2835_i2c_write(TIME_bytes, 8);
}

void Read_Linux_Time()
{
    char line[256];
    //char addr_byte[1] = { 0x00 };
    int hour, minute, second, month, day, two_digit_year, four_digit_year;

    system("date +\"%H:%M:%S %D\" > /tmp/datefile");    // sends date command to terminal and redirects output to file @ /tmp/datefile
    FILE* file_pointer = fopen("/tmp/datefile", "r");   // opens the file for reading

    if(fgets(line, 256, file_pointer) != NULL)
    {
          for(int i=0; i<strlen(line); i++)
          {
              if(line[i] == '/' || line[i] == ':') // remove slashes from date and replace with dashes so compatible with filenames
              {	line[i] = ' ';	}
          }
          sscanf(line, "%d %d %d %d %d %d ", &hour, &minute, &second, &month, &day, &two_digit_year); // read the file into the variables
    }

    four_digit_year = two_digit_year + 2000;
    fclose(file_pointer);
    system("rm /tmp/datefile");  // delete the temporary file

    printf("\t --------------\n");
    printf("LINUX READ TIME \t %d:%d:%d %d/%d/%d\n", hour, minute, second, month, day, four_digit_year);
}

void DS3231_Read_Time()
{
    TIME_bytes[INDEX_START_ADDR] = 0x00;
    bcm2835_i2c_write_read_rs(TIME_bytes, 1, TIME_bytes, 7); // writes 0x00 to DS3231 (start address), then reads 7 bytes

    TIME_bytes[READ_INDEX_SECONDS] = TIME_bytes[READ_INDEX_SECONDS] & MASK_SECONDS; //sec
    TIME_bytes[READ_INDEX_MINUTES] = TIME_bytes[READ_INDEX_MINUTES] & MASK_MINUTES; //min
    TIME_bytes[READ_INDEX_HOURS]   = TIME_bytes[READ_INDEX_HOURS ] & MASK_HOURS; //hour
    TIME_bytes[READ_INDEX_DAY_OF_WEEK] = TIME_bytes[READ_INDEX_DAY_OF_WEEK] & MASK_DAY_OF_WEEK; //day of the week
    TIME_bytes[READ_INDEX_DAY_OF_MONTH] = TIME_bytes[READ_INDEX_DAY_OF_MONTH] & MASK_DAY_OF_MONTH; //day of the month
    TIME_bytes[READ_INDEX_MONTH] = TIME_bytes[READ_INDEX_MONTH] & MASK_MONTH; //month
  //  printf("READ After Mask, before BCD conversion %d:%d:%d %d/%d/%d\n", TIME_bytes[READ_INDEX_HOURS], TIME_bytes[READ_INDEX_MINUTES], TIME_bytes[READ_INDEX_SECONDS], TIME_bytes[READ_INDEX_MONTH],
    //        TIME_bytes[READ_INDEX_DAY_OF_MONTH], TIME_bytes[READ_INDEX_YEAR]);

    TIME_bytes[READ_INDEX_SECONDS] = BCD_To_Decimal( TIME_bytes[READ_INDEX_SECONDS] ); //sec
    TIME_bytes[READ_INDEX_MINUTES] = BCD_To_Decimal( TIME_bytes[READ_INDEX_MINUTES] ); //min
    TIME_bytes[READ_INDEX_HOURS]   = BCD_To_Decimal( TIME_bytes[READ_INDEX_HOURS ] ); //hour
    TIME_bytes[READ_INDEX_DAY_OF_WEEK] = BCD_To_Decimal( TIME_bytes[READ_INDEX_DAY_OF_WEEK] ); //day of the week
    TIME_bytes[READ_INDEX_DAY_OF_MONTH] = BCD_To_Decimal( TIME_bytes[READ_INDEX_DAY_OF_MONTH] ); //day of the month
    TIME_bytes[READ_INDEX_MONTH] = BCD_To_Decimal( TIME_bytes[READ_INDEX_MONTH] ); //month
    TIME_bytes[READ_INDEX_YEAR] = TIME_bytes[READ_INDEX_YEAR] +2000; //year



    //printf("READ After BCD conversion \t\t%s  ", str[(uint8_t)TIME_bytes[INDEX_DAY_OF_WEEK]-1]);
//    printf("READ After BCD conversion \t\t%s  \t", str[TIME_bytes[READ_INDEX_DAY_OF_WEEK]]);
    printf("DS3231 READ TIME \t %d:%d:%d  %d/%d/%d\n", TIME_bytes[READ_INDEX_HOURS], TIME_bytes[READ_INDEX_MINUTES], TIME_bytes[READ_INDEX_SECONDS], TIME_bytes[READ_INDEX_MONTH],
            TIME_bytes[READ_INDEX_DAY_OF_MONTH], TIME_bytes[READ_INDEX_YEAR]+2000);
    printf("\t ------------------\n");
}

int main(int argc, char **argv)
{
    if (!bcm2835_init())return 1;
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(DS3231_ADDRESS);
    bcm2835_i2c_set_baudrate(10000);
    printf(" DS3231 start..........\n");

    DS3231_Set_From_Linux_Time();
    while(1)
    {

        Read_Linux_Time();
        DS3231_Read_Time();

        bcm2835_delay(1000);
    }

    bcm2835_i2c_end();
    bcm2835_close();

    return 0;
}
