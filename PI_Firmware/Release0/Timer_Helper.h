#ifndef TEST_TIMER
#define TEST_TIMER


#include <sys/time.h>
#include <time.h>
#include "Struct_Defs.h"

void Start_Test_Timer();
long Get_Elapsed_Seconds();
long Time_String_to_Seconds(char* time_string);
bool Is_Valid_Time_Argument(char* time_str);
int Parse_Hour(char* time_string);
int Parse_Minute(char* time_string);
int Parse_Second(char* time_string);
void Get_Elapsed_Time_String(char* target_string);
void Get_TimeStamp(char* target_string);
long Time_String_to_Seconds(char* time_string);
char* Get_Date();
char* Get_Time();

extern struct board_state Test; // defined in Execute_Command.h
time_t test_start_time = 0; //, time_now;
time_t time_now = 0;

static long long total_elapsed_secs = 0;


void Start_Test_Timer()
{
    time(&test_start_time);
}

void Stop_Test_Timer()
{
    if( Test.is_running)
        total_elapsed_secs  = difftime(time_now, test_start_time);

    test_start_time = 0;    // reset the start timer
}

void Reset_Test_Timer()
{
    total_elapsed_secs = 0;
    test_start_time = 0;
}

long Get_Elapsed_Seconds()
{
    if( (intmax_t)test_start_time == 0 && total_elapsed_secs == 0)
        return 0;
    else if( (intmax_t)test_start_time == 0 && total_elapsed_secs > 0)
        return total_elapsed_secs;

    time(&time_now);
    total_elapsed_secs = difftime(time_now, test_start_time);
    return (long)total_elapsed_secs;
}

void Get_Elapsed_Time_String(char* target_string)
{
    char elapsed_time[50];
    memset(elapsed_time, 0, sizeof(elapsed_time) );
    int hours_running, minutes_running, seconds_running;

    if( !(total_elapsed_secs > 0) && !Test.is_running )
    {
        strcpy(target_string, "  not started  ");
        return;
    }

    long total_seconds_running = Get_Elapsed_Seconds();
    int  total_minutes_running = total_seconds_running/60;
    int  total_hours_running   = total_minutes_running/60;
    int   days_running   = 0;

    if(total_hours_running >= 24)
    {
        days_running = total_hours_running / 24;
        hours_running = total_hours_running % 24;
    }
    else
        hours_running = total_hours_running;

    minutes_running = total_minutes_running % 60;
    seconds_running = total_seconds_running % 60;

    if( days_running > 0)
        sprintf(target_string, "%02ddays %02dhr %02dmin", days_running, hours_running, minutes_running);
    else
        sprintf(target_string, "%02dhr %02dmin %02dsec", hours_running, minutes_running, seconds_running);
}


void Get_TimeStamp(char* target_string)
{
   Erase_String_Contents(target_string);
	 time_t rawtime;
	 struct tm* timeinfo;
	 time (&rawtime);
	 timeinfo = localtime(&rawtime);
	 strftime (target_string,50,"%H:%M:%S  %m/%d/%Y ",timeinfo);
   //printf("timestamp string: %s \t  length: %d\n", target_string, strlen(target_string));
	 return;
}

char* Get_Time()
{
   char* buffer = malloc(sizeof(char*) * 22);
	 time_t rawtime;
	 struct tm* timeinfo;
	 time (&rawtime);
	 timeinfo = localtime(&rawtime);
   buffer[0] = '\0';
	 strftime (buffer,22,"%H:%M:%S  ",timeinfo);
	 buffer[strlen(buffer)-1] = '\0';
	 return buffer;
}

// in format HH:MM:SS
long Time_String_to_Seconds(char* time_string)
{
    int hours = Parse_Hour( time_string );
    int minutes  = Parse_Minute( time_string );
    long seconds  = Parse_Second( time_string );

    seconds += minutes*60;
    seconds += hours*3600;

    return seconds;
}


char* Get_Date()
{
    char* buffer = malloc(sizeof(char*) * 22);
	 time_t rawtime;
	 struct tm* timeinfo;
	 time (&rawtime);
	 timeinfo = localtime(&rawtime);
	 strftime (buffer,30,"%m/%d/%y",timeinfo);


	 return buffer;
}

int Parse_Hour(char* time_string)
{
    int look_ahead_index = 0;

    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first ':', two digit hour will be before ':'
    int substr_start_index = Get_Index_Open_Bracket(time_string) + 1;
    int substr_end_index = look_ahead_index-1;          // end of substring containing two digit hour

    char* str_hour = Get_Substring(time_string, substr_start_index, substr_end_index);
    int hour = Parse_Int( str_hour );     // parse month string to an integer

    free(str_hour);
    return hour;
}

int Parse_Minute(char* time_string)
{
    int look_ahead_index = 0;
    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first ':', two digit minute will be before ':'
    int substr_start_index = look_ahead_index+1;
    ++look_ahead_index;

    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of second ':'
    int substr_end_index = look_ahead_index-1;          // end of substring containing two digit minute

    char* str_minute = Get_Substring(time_string, substr_start_index, substr_end_index);
    int minute = Parse_Int( str_minute );     // parse month string to an integer

    //printf("ParseMinute: \"%d\"\n", minute);
    free(str_minute);
    return minute;
}

int Parse_Second(char* time_string)
{
    int look_ahead_index = 0;

    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first ':', two digit minute will be before ':'
    ++look_ahead_index;

    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of second ':'
    int substr_start_index = look_ahead_index+1;
    int substr_end_index = strlen(time_string) -1;

    char* str_second = Get_Substring(time_string, substr_start_index, substr_end_index);
    int second = Parse_Int( str_second );     // parse month string to an integer

    //printf("ParseSecond: \"%d\"\n", second);
    free(str_second);
    return second;
}

bool Is_Valid_Time_Argument(char* time_str)
{
// PARSE "TIME"
//
    // PARSE THE HOUR
    int look_ahead_index = 0;          // increment, so now look_ahead_index should be in "HOUR" part of the timedate string
    int substr_start_index = 0;        // start of substring containing one or two digit hour
    char* str_hour;
    char* str_minute;
    char* str_second;
    int hour, minute, second;


    int time_start_index = Get_Index_Open_Bracket(time_str);
    int time_end_index = Get_Index_Closed_Bracket(time_str);
    char* time_string = Get_Substring( time_str, time_start_index+1, time_end_index-1);

    //printf(" time string: %s\n", time_string);
    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first ':', two digit hour will be before ':'

    int substr_end_index = look_ahead_index-1;                    // end of substring containing two digit hour
    int substring_length = substr_end_index - substr_start_index;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "hour", but at least one character
    {
        printf("Error: hour in time string \"%s\" has less than one or more than 2 digits\n", time_string);
        printf("start_index: %d\tend index: %d\n", substr_start_index, substr_end_index);
        return false;
    }
    else
    {
        str_hour = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_hour) )
        {
          printf("doesnt contain only digits\n");
          return false;
        }
        hour = Parse_Int( str_hour );     // parse hour string to an integer

        //printf("\tHour: \"%d\"\n", hour);
        free(str_hour);
    }
    // PARSE THE MINUTE
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "MINUTE" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing one or two digit minute
    while( time_string[look_ahead_index] != ':' && time_string[look_ahead_index] != '\0'){ ++look_ahead_index; }    // find index of first ':', should be max 2 chars before ':'

    substr_end_index = look_ahead_index-1;          // end of substring containing one or two digit minute
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "minute", but at least one character
    {
        printf("Error: minute in time string \"%s\" has less than one or more than 2 digits\n", time_string);
        return false;
    }
    else
    {
        str_minute = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_minute) )
            return false;
        minute = Parse_Int( str_minute );     // parse minute string to an integer
        if( minute < 0 )
        {
            printf("Error: minute \"%d\" is not in valid range ( greater than or equal to 0)\n", minute);
            return false;
        }
        //printf("\tMinute: \"%d\"\n", minute);
        free(str_minute);
    }
    // PARSE THE SECOND
    ++look_ahead_index;                           // increment, so now look_ahead_index should be in "SECOND" part of the timedate string
    substr_start_index = look_ahead_index;        // start of substring containing one or two digit SECOND


    substr_end_index = strlen(time_string)-1;          // end of substring containing one or two digit SECOND
    substring_length = substr_end_index - substr_start_index + 1;
    if( substring_length > 2 || substring_length < 1)             // max 2 characters for "SECOND", but at least one character
    {
        printf("Error: second \"%s\" has less than one or more than 2 digits)\n", str_second);
        return false;
    }
    else
    {
        str_second = Get_Substring(time_string, substr_start_index, substr_end_index);
        if( !Contains_Only_Digits(str_second) )
            return false;
        second = Parse_Int( str_second );     // parse second string to an integer
        if( second < 0 )
        {
            printf("Error: second \"%d\" is not in valid range ( >= 0)\n", second);
            return false;
        }
        //printf("\tSecond: \"%d\"\n", second);
        free(str_second);
    }
    free(time_string);
    return true;
}












#endif
