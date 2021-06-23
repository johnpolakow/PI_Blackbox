#ifndef _SAVE_FILE_
#define _SAVE_FILE_



#include <fcntl.h>  /* File Control Definitions          */
#include <errno.h>

#include <dirent.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "colors.h"

#define BUF_LEN   500

const static int COL_INDEX_COOLER_V   = 0;
const static int COL_INDEX_COOLER_A   = 9;
const static int COL_INDEX_COOLER_W   = 18;
const static int COL_INDEX_DIODE_TEMP = 29;
const static int COL_INDEX_DIODE_V    = 37;
const static int COL_INDEX_RLOAD_V    = 51;
const static int COL_INDEX_RLOAD_mA   = 58;
const static int COL_INDEX_RLOAD_mW   = 66;
const static int COL_INDEX_THRMCPL1   = 78;
const static int COL_INDEX_THRMCPL2   = 88;
const static int COL_INDEX_THRMCPL3   = 98;
const static int COL_INDEX_TIMESTAMP  = 110;
const static int COL_INDEX_ELAPSED_TIME = 135;
const static int COL_INDEX_RELAY_STATE  = 155;



const static int NUM_CHARS_COOLER        = 7;
const static int NUM_CHARS_TEMP_DIODE    = 7;
const static int NUM_CHARS_LOAD          = 7;
const static int NUM_CHARS_THRMCPL       = 8;
const static int NUM_CHARS_TIMESTAMP     = 20;
const static int NUM_CHARS_ELAPSED_TIME  = 16;
const static int NUM_CHARS_RELAY         = 4;



extern data_point Save_Data[ MAX_LOOP_SAMPLES ];
extern int save_index;
extern board_state Test;   // from "Execute_Command.h", struct definition in Struct_Defs.h


FILE* log_file_ptr = NULL;


static const char DUT_CONFIG_FILEPATH[] = "/home/pi/DUT_CONFIG/DUT_Config.txt";
static const char USB_FILEPATH[] = "/home/pi/USB_drive/Logs/";
static const char SD_FILEPATH[] = "/home/pi/Logs/";

char SAVE_FILEPATH[200];
char SAVE_FILE[50];

data_point cur_data;

void Initialize_Log();
bool File_Exists(const char* filename);
bool Create_Log_File(char* filename);
void Advance_to_Index(char* write_buffer, int* index_ptr, int target_index);
void Write_Chars(char* write_buffer, int* column_index, char* print_buffer, int MAX_CHARS);
void Clear_Print_Buffer(char* buffer);
void Write_Data_to_File(data_point Save[], int* index);

bool File_Exists(const char* filename)
{
    FILE *file;
    if ((file = fopen(filename, "r")))
    {
        fclose(file);
        return true;
    }
    return false;
}

bool Create_Log_File(char* filename)
{
    //Check to see if we have a thumbdrive inserted by performing ls /dev/sda.  If so we will datalog to USB drive
    //If not, datalog is written to /home/pi/Logs/
    int thumb_drive_exists = system("ls /dev/sda"); //thumb = 0 if thumbdrive detected or 512 if none available
                                                    //If drive available, it is mounted to /home/pi/USB_drive
                                                    //FOR REFERENCE see modified file in  /etc/FSTAB:
                                                    // /dev/sda  /home/pi/USB_drive  auto  uid=pi,gid=pi,umask=0022,sync,noauto,nosuid,rw,user 0   0
    if( thumb_drive_exists == 0 )
    {
      strcpy(SAVE_FILEPATH, USB_FILEPATH);
      strcat(SAVE_FILEPATH, filename);
    }
    else
    {
      strcpy(SAVE_FILEPATH, SD_FILEPATH);
      strcat(SAVE_FILEPATH, filename);
    }
    printf("save filepath:  \"%s\"\n", SAVE_FILEPATH);

    log_file_ptr = fopen(SAVE_FILEPATH, "w");
    if(log_file_ptr == NULL)
    {
        printf("error\n");
        perror("uh oh");
        return false;
    }

    fclose( log_file_ptr );
    Initialize_Log();

    return true;
}

void Initialize_Log()
{
    char Filename_Line[200];
    char Blackbox_ID[100];
    char Displacer_ID[100];
    char CCC_ID[100];
    char Compressor_ID[100];
    char DDCA_ID[100];
    char Exec_Mode[100];
    char Profile_Name[50];
	char Time_Date[100];

/* Format of file header is below

//filename: XXXXXX
	## PI_BB LOG FILE ##
	firmware version XXXXX, PCB version
	PI_BB: [blackbox#]
	CCC:	  		CCC_ID
	Compressor:		Compressor_ID
	Dewar:		Dewar_ID
	Displacer:		Displacer_ID
	Test Execution:	[Manual] or [profile filename]
	Test_Type:		[default/Performance/Lifetime/BurnIn]
	Log Start:		[Timestamp]

[COLUMN LEGEND]
_______________________________________________________________
*/
    const char* file_comment     = "// filepath:  ";
    const char* Declaration_Line = "\t\t\t\t      ## PI_BB LOG FILE ## ";
    const char* Blackbox_Line    = "\t\t\t\t      Blackbox: ";
    const char* Compressor_Line  = "\t\t\t\t    Compressor: ";
    const char* Displacer_Line   = "\t\t\t\t     Displacer: ";
    const char* DDCA_Line        = "\t\t\t\t          DDCA: ";
    const char* CCC_Line         = "\t\t\t\t           CCC: ";
    const char* Profile_Line     = "\t\t\t\tProfile/Manual: ";
    const char* Profile_Line_2   = "\t\t\t\t  Profile Name: ";
    const char* Time_Header      = "\t\t\t\t    Start_Time: ";

    const char* file_header1 = "  CCC \t  CCC \t   CCC       Dewar \t          RLoad  RLoad  R_PWR \t          THRMCPL\t\t\t\t\t     Elapsed         Relay";
    const char* file_header2 = "   V \t   A \t    W \t      \u00B0K    diodeV\t   V     \u3383      \u33BD         \u00B0C       \u00B0C       \u00B0C         Time       Date             Time            State";
    const char* line = "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\n";

// Create all string lines to write into the file header
    strcpy(Filename_Line, file_comment);
    strcat(Filename_Line, SAVE_FILEPATH);

    memset(Blackbox_ID,0,sizeof(Blackbox_ID));
    strcpy(Blackbox_ID, Blackbox_Line);
    strcat(Blackbox_ID, Test.hostname);
    Blackbox_ID[strlen(Blackbox_ID)] = '\0';

    Compressor_ID[0] = '\0';
    strcpy(Compressor_ID, Compressor_Line);
    strcat(Compressor_ID, Test.compressor_ID);
    Compressor_ID[strlen(Compressor_ID)] = '\0';

    memset(Displacer_ID,0,sizeof(Displacer_ID));
    strcpy(Displacer_ID, Displacer_Line);
    strcat(Displacer_ID, Test.displacer_ID);
    Displacer_ID[strlen(Displacer_ID)] = '\0';

    DDCA_ID[0] = '\0';
    strcpy(DDCA_ID, DDCA_Line);
    strcat(DDCA_ID, Test.DDCA_ID);
    DDCA_ID[strlen(DDCA_ID)] = '\0';

    CCC_ID[0] = '\0';
    strcpy(CCC_ID, CCC_Line);
    strcat(CCC_ID, Test.CCC_ID);
    CCC_ID[strlen(CCC_ID)] = '\0';

    memset(Exec_Mode,0,sizeof(Exec_Mode));
    strcpy(Exec_Mode, Profile_Line);
    strcat(Exec_Mode, Test.execution_mode_str);

    Exec_Mode[ strlen(Exec_Mode) ] = '\0';

    if(Test.execution_mode == PROFILE_CONTROL)
    {
        strcpy(Profile_Name, Profile_Line_2);
        strcat(Profile_Name, Test.profile_name);
        Profile_Name[ strlen(Profile_Name) ] = '\0';
    }

    char timestamp_str[50];
		Get_TimeStamp( timestamp_str );
    Time_Date[0] = '\0';
    strcpy(Time_Date, Time_Header);
    strcat(Time_Date, timestamp_str);
    Time_Date[strlen(Time_Date)] = '\0';

    // open file and start writing the prepared strings to file
    log_file_ptr = fopen(SAVE_FILEPATH, "a"); // open for writing, 'w' means overwrite any existing file, "a" means to append to file
    if(log_file_ptr == NULL)
    {
        printf("init log:open error\n");
        perror("Init Log open error");
        return;
    }

    fprintf(log_file_ptr , "%s\n\n", Filename_Line); // filename: XXXXXXX.log
    fprintf(log_file_ptr , "\t\t%s\n", Declaration_Line ); // write ""## PI_BB LOG FILE ## "
    fprintf(log_file_ptr , "\n\t\t%s\n", Blackbox_ID);
    fprintf(log_file_ptr , "\t\t%s\n", Compressor_ID);
    fprintf(log_file_ptr , "\t\t%s\n", Displacer_ID);
    fprintf(log_file_ptr , "\t\t%s\n", DDCA_ID);
    fprintf(log_file_ptr , "\t\t%s\n", CCC_ID);
    fprintf(log_file_ptr , "\t\t%s\n", Exec_Mode); // write "MANUAL" or "PROFILE" to file

    if(Test.execution_mode == PROFILE_CONTROL)
        fprintf(log_file_ptr , "\t\t%s\n", Profile_Name); // write profile name to file

		fprintf(log_file_ptr , "\t\t%s\n\n", Time_Date); // write timestamp to file

    fprintf(log_file_ptr , "%s\n", file_header1); // write the header1 to file
		fprintf(log_file_ptr , "%s\n", file_header2); // write the header2 to file
		fprintf(log_file_ptr , "%s", line);         // write separation line: ______________

	  fclose( log_file_ptr  );
}

void Write_Data_to_File(data_point Save[], int* index)
{
    char write_buffer[250];
    char cooler_buffer[50];
    char temp_diode_buffer[50];
    char heat_load_buffer[50];
    char thermocouple_buffer[50];
    char timestamp_buffer[50];

    char relay_buffer[4];

    if( Test.relay_state == RELAY_ON)
        strcpy(relay_buffer, "ON");
    else
        strcpy(relay_buffer, "OFF");

    log_file_ptr = fopen(SAVE_FILEPATH, "a"); // 'w' means overwrite any existing file, "a" means to append to file
    if(log_file_ptr == NULL)
    {
        perror("Write_Data file open error");
        return;
    }

    static int column_index = 0;
    char write_line[BUF_LEN];
    char print_buffer[50];

    for(int write_index = 0; write_index<(*index); ++write_index)
    {
        Erase_String_Contents(write_line);
        for(int i=0; i<300; ++i)
            write_line[i] = '\0';
        Erase_String_Contents(print_buffer);
        column_index = 0;

        Advance_to_Index(write_line, &column_index, COL_INDEX_COOLER_V );
        sprintf( print_buffer, "%2.3fV", Save_Data[ write_index ].Cooler_V );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_COOLER);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_COOLER_A );
        sprintf( print_buffer, "%1.4fA", Save_Data[ write_index ].Cooler_A );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_COOLER);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_COOLER_W );
        sprintf( print_buffer, "%2.3fW", Save_Data[ write_index ].Cooler_W );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_COOLER);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_DIODE_TEMP );
        sprintf( print_buffer, "%3.1f\u00B0K", Save_Data[ write_index ].diode_temp );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_TEMP_DIODE);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_DIODE_V);
        sprintf( print_buffer, "%1.4fV", Save_Data[ write_index ].diode_volts );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_TEMP_DIODE);
        Clear_Print_Buffer(print_buffer);


        Advance_to_Index(write_line, &column_index, COL_INDEX_RLOAD_V);
        sprintf( print_buffer, "%2.2fV", Save_Data[ write_index ].Heat_Load_V );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_LOAD);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_RLOAD_mA);
        sprintf( print_buffer, "%3.1f\u3383", Save_Data[ write_index ].Heat_Load_mA );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_LOAD);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_RLOAD_mW);
        sprintf( print_buffer, "%3.1f\u33BD", Save_Data[ write_index ].Heat_Load_mW );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_LOAD);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_THRMCPL1);
        sprintf( print_buffer, "%2.2f\u00B0C", Save_Data[ write_index ].thermocouple1_temp );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_THRMCPL);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_THRMCPL2);
        sprintf( print_buffer, "%2.2f\u00B0C", Save_Data[ write_index ].thermocouple2_temp );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_THRMCPL);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_THRMCPL3);
        sprintf( print_buffer, "%2.2f\u00B0C", Save_Data[ write_index ].thermocouple3_temp );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_THRMCPL);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_TIMESTAMP);
        sprintf( print_buffer, "%s", Save_Data[ write_index ].timestamp );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_TIMESTAMP);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_ELAPSED_TIME);
        sprintf( print_buffer, "%s", Save_Data[ write_index ].elapsed_time );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_ELAPSED_TIME);
        Clear_Print_Buffer(print_buffer);

        Advance_to_Index(write_line, &column_index, COL_INDEX_RELAY_STATE);
        sprintf( print_buffer, "%s", relay_buffer );
        Write_Chars(write_line, &column_index, print_buffer, NUM_CHARS_RELAY);
        Clear_Print_Buffer(print_buffer);

        //printf("\n%s\n", write_line);
        fprintf(log_file_ptr , "%s\n", write_line);
    }
/*
    for(int write_index = 0; write_index<(*index); ++write_index)
    {
        sprintf(cooler_buffer, "%2.3fV  %1.4fA  %2.3fW   ", Save_Data[ write_index ].Cooler_V , Save_Data[ write_index ].Cooler_A , Save_Data[ write_index ].Cooler_W);
        sprintf(temp_diode_buffer, " %3.1f\u00B0\u212A   %1.4fV ", Save_Data[ write_index ].diode_volts, Save_Data[ write_index ].diode_temp );
        sprintf(heat_load_buffer, " %2.2fV     %3.1f\u3383    %3.1f\u33BD   ", Save_Data[ write_index ].Heat_Load_V , Save_Data[ write_index ].Heat_Load_mA , Save_Data[ write_index ].Heat_Load_mW );
        sprintf(thermocouple_buffer, " %2.2f\u2103  %2.2f\u2103   %2.2f\u2103  ", Save_Data[ write_index].thermocouple1_temp, Save_Data[ write_index].thermocouple2_temp, Save_Data[ write_index].thermocouple3_temp);
        sprintf(timestamp_buffer, " %s   %s   %s", Save_Data[ write_index ].timestamp, Save_Data[ write_index ].elapsed_time, relay_buffer);
        sprintf(write_buffer, "%s%s%s%s%s\n", cooler_buffer, temp_diode_buffer, heat_load_buffer, thermocouple_buffer, timestamp_buffer);

        //printf("Line: %s %s  %s %s %s\n", cooler_buffer, temp_diode_buffer, heat_load_buffer, thermocouple_buffer, timestamp_buffer);
        fprintf(log_file_ptr , "%s", write_buffer);
    }
    */
    pthread_mutex_lock(&INCREMENT_LOCK);
      (*index) = 0;   // reset save index
    pthread_mutex_unlock(&INCREMENT_LOCK);

    fclose(log_file_ptr);
}


void Advance_to_Index(char* write_buffer, int* index_ptr, int target_index)
{
    if( write_buffer == NULL)
        return;

    while( (*index_ptr < target_index) && (*index_ptr < BUF_LEN ) )
    {
        write_buffer[ (*index_ptr) ] = ' ';
        ++(*index_ptr);
    }
}


void Write_Chars(char* write_buffer, int* column_index, char* print_buffer, int MAX_CHARS)
{
    int num_chars_written = 0;
    int print_index = 0;

    while( (*column_index < BUF_LEN) && (num_chars_written < MAX_CHARS) )
    {
        //printf(" ind:%d,'%c'  ", (int)(*column_index), print_buffer[ print_index ]);
        //printf("   wri_ind:%d   ", (int)(*column_index));
        if( print_buffer[ (print_index) ] == '\0')      // don't want to print the null character in the middle of concatenating strings
        {
            write_buffer[ (*column_index) ] = ' ';

        }
        else
          write_buffer[ (*column_index) ] = print_buffer[ print_index ];
        ++print_index;
        ++num_chars_written;
        ++(*column_index);

    }
    write_buffer[ (*column_index) ] = '\0';   // will get overwritten if more strings are added to write_buffer
    return;
}


void Clear_Print_Buffer(char* buffer)
{
    for(int i= 0; i<50; ++i)
        buffer[i] = '\0';
}











#endif
