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


#define DS3231_ADDRESS        0x68  ///< I2C address for DS3231
#define DS3231_CONTROL        0x0E  ///< Control register
#define DS3231_STATUS_REG     0x0F  ///< Status register
#define DS3231_TEMP_REG	      0x11  ///< Temperature register (high byte - low byte is at 0x12), 10-bit temperature value

#define SECONDS_PER_DAY       86400  ///< 60 * 60 * 24
#define SECONDS_1970_TO_2000  946684800  ///< Unixtime for 2000-01-01 00:00:00, useful for initialization




#	define DS3231_BIT_BBSQW		0x40 /* same as BBSQI */
/* RTC registers don't differ much, except for the century flag */
#define DS1307_REG_SECS		0x00	/* 00-59 */
#	define DS1307_BIT_CH		0x80
#	define DS1340_BIT_nEOSC		0x80
#	define MCP7941X_BIT_ST		0x80
#define DS1307_REG_MIN		0x01	/* 00-59 */
#define DS1307_REG_HOUR		0x02	/* 00-23, or 1-12{am,pm} */
#	define DS1307_BIT_12HR		0x40	/* in REG_HOUR */
#	define DS1307_BIT_PM		0x20	/* in REG_HOUR */
#	define DS1340_BIT_CENTURY_EN	0x80	/* in REG_HOUR */
#	define DS1340_BIT_CENTURY	0x40	/* in REG_HOUR */
#define DS1307_REG_WDAY		0x03	/* 01-07 */
#	define MCP7941X_BIT_VBATEN	0x08
#define DS1307_REG_MDAY		0x04	/* 01-31 */
#define DS1307_REG_MONTH	0x05	/* 01-12 */
#	define DS1337_BIT_CENTURY	0x80	/* in REG_MONTH */
#define DS1307_REG_YEAR		0x06	/* 00-99 */


/*
class RTC_DS1307 {
public:
  bool begin(void);
  static void adjust(const DateTime& dt);
  uint8_t isrunning(void);
  static DateTime now();

};

*/

/**
  Number of days in each month, from January to November. December is not
  needed. Omitting it avoids an incompatibility with Paul Stoffregen's Time
  library. C.f. https://github.com/adafruit/RTClib/issues/114
//*/
const uint8_t daysInMonth [] = { 31,28,31,30,31,30,31,31,30,31,30 };


/*!
    @brief  Given a date, return number of days since 2000/01/01, valid for 2001..2099
    @param y Year
    @param m Month
    @param d Day
    @return Number of days
*/
/**************************************************************************/
/*
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}
*/

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
    @brief  DateTime constructor from unixtime
    @param t Initial time in seconds since Jan 1, 1970 (Unix time)
*/
/**************************************************************************/

/*
DateTime::DateTime (uint32_t t) {
  t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

  ss = t % 60;
  t /= 60;
  mm = t % 60;
  t /= 60;
  hh = t % 24;
  uint16_t days = t / 24;
  uint8_t leap;
  for (yOff = 0; ; ++yOff) {
    leap = yOff % 4 == 0;
    if (days < 365 + leap)
      break;
    days -= 365 + leap;
  }
  for (m = 1; m < 12; ++m) {
    uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
    if (leap && m == 2)
      ++daysPerMonth;
    if (days < daysPerMonth)
      break;
    days -= daysPerMonth;
  }
  d = days + 1;
}
*/
/**************************************************************************/
/*!
    @brief  DateTime constructor from Y-M-D H:M:S
    @param year Year, 2 or 4 digits (year 2000 or higher)
    @param month Month 1-12
    @param day Day 1-31
    @param hour 0-23
    @param min 0-59
    @param sec 0-59
*/
/**************************************************************************/

/*
DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}
*/

/**************************************************************************/
/*!
    @brief  DateTime copy constructor using a member initializer list
    @param copy DateTime object to copy
*/
/**************************************************************************/

/*
DateTime::DateTime (const DateTime& copy):
  yOff(copy.yOff),
  m(copy.m),
  d(copy.d),
  hh(copy.hh),
  mm(copy.mm),
  ss(copy.ss)
{}


  uint8_t DateTime::dayOfTheWeek() const {
    uint16_t day = date2days(yOff, m, d);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}
*/

/**************************************************************************/
/*!
    @brief  Return unix time, seconds since Jan 1, 1970.
    @return Number of seconds since Jan 1, 1970
*/
/**************************************************************************/
/*
uint32_t DateTime::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

  return t;
}

*/
/**************************************************************************/
/*!
    @brief  Check the status register Oscillator Stop Flag to see if the DS3231 stopped due to power loss
    @return True if the bit is set (oscillator stopped) or false if it is running
*/
/**************************************************************************/
/*
bool RTC_DS3231::lostPower(void) {
  return (read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG) >> 7);
}
*/

/**************************************************************************/
/*!
    @brief  Set the date and flip the Oscillator Stop Flag
    @param dt DateTime object containing the date/time to set
*/
/**************************************************************************/
/*
void RTC_DS3231::adjust(const DateTime& dt) {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire._I2C_WRITE((byte)0); // start at location 0
  Wire._I2C_WRITE(bin2bcd(dt.second()));
  Wire._I2C_WRITE(bin2bcd(dt.minute()));
  Wire._I2C_WRITE(bin2bcd(dt.hour()));
  Wire._I2C_WRITE(bin2bcd(0));
  Wire._I2C_WRITE(bin2bcd(dt.day()));
  Wire._I2C_WRITE(bin2bcd(dt.month()));
  Wire._I2C_WRITE(bin2bcd(dt.year() - 2000));
  Wire.endTransmission();

  uint8_t statreg = read_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG);
  statreg &= ~0x80; // flip OSF bit
  write_i2c_register(DS3231_ADDRESS, DS3231_STATUSREG, statreg);
}
*/

/**************************************************************************/
/*!
    @brief  Get the current date/time
    @return DateTime object with the current date/time
*/
/**************************************************************************/
/*
DateTime RTC_DS3231::now() {
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire._I2C_WRITE((byte)0);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire._I2C_READ() & 0x7F);
  uint8_t mm = bcd2bin(Wire._I2C_READ());
  uint8_t hh = bcd2bin(Wire._I2C_READ());
  Wire._I2C_READ();
  uint8_t d = bcd2bin(Wire._I2C_READ());
  uint8_t m = bcd2bin(Wire._I2C_READ());
  uint16_t y = bcd2bin(Wire._I2C_READ()) + 2000;

  return DateTime (y, m, d, hh, mm, ss);
}
*/
/**************************************************************************/
/*!
    @brief  Get the current temperature from the DS3231's temperature sensor
    @return Current temperature (float)
*/
/**************************************************************************/
/*
float RTC_DS3231::getTemperature()
{
  uint8_t msb, lsb;
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire._I2C_WRITE(DS3231_TEMP_REG);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 2);
  msb = Wire._I2C_READ();
  lsb = Wire._I2C_READ();

  return (float) msb + (lsb >> 6) * 0.25f;
}
*/
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
    char addr_byte[1] = { 0x00 };
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
    printf("SET before BCD %d:%d:%d %d/%d/%d\t\t(2 digit year)\n", Time_Now.hour, Time_Now.minute, Time_Now.second, Time_Now.month,
            Time_Now.day, Time_Now.year);

    TIME_bytes[INDEX_START_ADDR] = 0x00;
    TIME_bytes[WRITE_INDEX_SECONDS] = Decimal_To_BCD( (uint8_t) Time_Now.second & MASK_SECONDS ) ; //sec
    TIME_bytes[WRITE_INDEX_MINUTES] = Decimal_To_BCD( (uint8_t) Time_Now.minute & MASK_MINUTES );
    TIME_bytes[WRITE_INDEX_HOURS] = Decimal_To_BCD( (uint8_t) Time_Now.hour & MASK_HOURS );
    TIME_bytes[WRITE_INDEX_DAY_OF_WEEK] = 0;
    TIME_bytes[WRITE_INDEX_DAY_OF_MONTH] = Decimal_To_BCD((uint8_t) Time_Now.day & MASK_DAY_OF_MONTH );
    TIME_bytes[WRITE_INDEX_MONTH] = Decimal_To_BCD( (uint8_t) Time_Now.month & MASK_MONTH );
    //TIME_bytes[WRITE_INDEX_YEAR] = Decimal_To_BCD( (uint8_t) Time_Now.year -2000);
    TIME_bytes[WRITE_INDEX_YEAR] = (uint8_t)( Time_Now.year -2000 );


    printf("SET After BCD: %d:%d:%d %d/%d/%d\t\t(two digit year)\n", TIME_bytes[WRITE_INDEX_HOURS], TIME_bytes[WRITE_INDEX_MINUTES], TIME_bytes[WRITE_INDEX_SECONDS], TIME_bytes[WRITE_INDEX_MONTH],
            TIME_bytes[WRITE_INDEX_DAY_OF_MONTH], TIME_bytes[WRITE_INDEX_YEAR]);
    printf("\t --------------\n");
    bcm2835_i2c_write(TIME_bytes, 8);
}

void Read_Linux_Time()
{
    char line[256];
    char addr_byte[1] = { 0x00 };
    int hour, minute, second, month, day, two_digit_year, four_digit_year;

    system("date +\"%H:%M:%S %D\" > /tmp/datefile"); // sends date command to terminal and redirects output to file @ /tmp/datefile
    FILE* file_pointer = fopen("/tmp/datefile", "r");   // opens the fille for reading


    if(fgets(line, 256, file_pointer) != NULL)
    {
        //  printf("scanned line: \t%s\n", line);
          for(int i=0; i<strlen(line); i++)
          {
              if(line[i] == '/' || line[i] == ':') // remove slashes from date and replace with dashes so compatible with filename
              {	line[i] = ' ';	}
          }
          sscanf(line, "%d %d %d %d %d %d ", &hour, &minute, &second, &month, &day, &two_digit_year); // read the file into the variables
    }

    four_digit_year = two_digit_year +2000;

    fclose(file_pointer);
    system("rm /tmp/datefile");  // delete the temporary file

//  printf("\t --LINUX TIME--\n");
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

    //DS3231_Set_Time();
    while(1)
    {

        Read_Linux_Time();
        DS3231_Read_Time();

      //  DS3231_Set_From_Linux_Time();
    //    DS3231_Read_Time();

        bcm2835_delay(1000);
    }

    bcm2835_i2c_end();
    bcm2835_close();

    return 0;
}
