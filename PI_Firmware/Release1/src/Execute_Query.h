
#ifndef EXECUTE_QUERY
#define EXECUTE_QUERY

#include "File_Helper.h"
#include "MAX31856.h"

#define HELP_NUM_LINES 50


void Send_Query_List(Instruction_Info* instruction);
void Get_System_Time(Instruction_Info* instruction);
void Get_Status(Instruction_Info* instruction);
void Get_Mode(Instruction_Info* instruction);
void Get_Execution_Mode_String(char* mode_string);
void Test_is_Running(char* is_running);
char* Get_USB_Disk_Use();
void Assemble_Help_Response(Instruction_Info* instruction);
void List_Profiles(Instruction_Info* instruction);
void Print_Current_Profile();
void Get_Metrics(Instruction_Info* instruction);
double parseDouble(char* integer_string);
char** Exec_Shell_Command(char* command);
void Get_CPU_Temperature_C(char* temperature_string);
void Get_Disk_Usage();
void Parse_Disk_Use(char* console_line, struct Disk_Usage* device);

struct Disk_Usage uSD_Card;                      // root filesystem stored on micro SD card
struct Disk_Usage Flash_Drive;

extern bool CAL_FUNCTIONS_ENABLED;

// precursor to this command, command has been processed and command index stored
void Execute_Query(Instruction_Info* query)
{
    //printf("execute query function. socket receive: %s\n", query->socket_receive);

    switch(query->this_query)
    {
        case HELP:
            Assemble_Help_Response(query);
            break;

        case LOGS:

            break;

        case METRICS:
            Get_Metrics(query);
            break;

        case PRINT_QUERY_LIST:
            Send_Query_List(query);
            break;

        case PROFILES:
            List_Profiles(query);
            break;

        case PROFILE:
            Print_Current_Profile(query);
            break;

        case TIME:
            Get_System_Time(query);
            break;

        case SHOW:

            break;

        case STATUS:
            Get_Status(query);
            break;

        case MODE:
            Get_Mode(query);
            break;

        case NOT_A_QUERY:
            break;

        default:  // default case
            break;
    }
}


void Get_Metrics(Instruction_Info* instruction)
{
  char metrics_header1[] = "  CCC \t  CCC \t   CCC      Dewar \t        RLoad    RLoad\t  R_PWR \t    THRMCPL\t\t\t\t        Elapsed\t        Relay";
  char metrics_header2[] = "   V \t   A \t    W \t     \u00B0\u212A      diodeV\t  V\t  \u3383\t   \u33BD         \u2103       \u2103       \u2103       Time\t Date\t        Time\t        State";
  char line_delim[] = "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\n";

  char send_buffer[200];
  char cooler_buffer[50];
  char temp_diode_buffer[50];
  char heat_load_buffer[50];
  char thermocouple_buffer[50];
  char timestamp_buffer[50];
  //char elapsed_time_buffer[] = "05hr36min12sec";
  char relay_buffer[4];

  if( Test.relay_state == RELAY_ON)
      strcpy(relay_buffer, "ON");
  else
      strcpy(relay_buffer, "OFF");

  char timestamp_str[50];
  memset(timestamp_str, 0, sizeof(timestamp_str) );
  Get_TimeStamp(timestamp_str);
  char elapsed_time_str[50];
  memset(elapsed_time_str, 0, sizeof(elapsed_time_str) );
  Get_Elapsed_Time_String(elapsed_time_str);

  sprintf(cooler_buffer, "%2.3fV  %1.4fA  %2.3fW   ", Save_Data[ save_index ].Cooler_V , Save_Data[ save_index ].Cooler_A , Save_Data[ save_index ].Cooler_W);
  sprintf(temp_diode_buffer, " %3.1f\u00B0\u212A   %1.4fV ", Save_Data[ save_index ].diode_temp, Save_Data[ save_index ].diode_volts );
  sprintf(heat_load_buffer, "   %2.2fV    %3.1f\u3383    %3.1f\u33BD   ", Save_Data[ save_index ].Heat_Load_V , Save_Data[ save_index ].Heat_Load_mA , Save_Data[ save_index ].Heat_Load_mW );
  sprintf(thermocouple_buffer, " %2.2f\u2103   %2.2f\u2103   %2.2f\u2103  ", Save_Data[ save_index ].thermocouple1_temp, Save_Data[ save_index ].thermocouple2_temp, Save_Data[ save_index ].thermocouple3_temp);
  sprintf(timestamp_buffer, " %s   %s    %s", timestamp_str, elapsed_time_str, relay_buffer);

  sprintf(send_buffer, "%s%s%s%s%s", cooler_buffer, temp_diode_buffer, heat_load_buffer, thermocouple_buffer, timestamp_buffer);

  if( SEND_VERBOSE )
  {
      instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(metrics_header1) + 1);
      sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", metrics_header1 );
      ++instruction-> response_store_index;

      instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(metrics_header2) + 1);
      sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", metrics_header2 );
      ++instruction-> response_store_index;

      instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line_delim) + 1);
      sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line_delim );
      ++instruction-> response_store_index;
  }

  instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(send_buffer) + 1);
  sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", send_buffer );
  ++instruction-> response_store_index;
}



void Print_Current_Profile(Instruction_Info* instruction)
{
    if( Test.profile != NULL)
        Print_Profile( Test.profile );
    else
    {
        instruction->response_array[ instruction->response_store_index] = (char*)malloc( sizeof(char*) * ( strlen( "no profile set\n") +2 ) ); // allocate memory for string in response
        sprintf( instruction->response_array[instruction->response_store_index], "%s no profile set", X_ERROR );
        ++instruction->response_store_index;
        instruction->response_array[instruction->response_store_index] = NULL;
    }
}

void List_Profiles(Instruction_Info* instruction)
{
    char** SD_profiles =  Shell_List_Files(SD_PROFILE_LOCATION); // get profiles in this directory location
    char** USB_profiles = Shell_List_Files(USB_PROFILE_DIR);    // get profiles in this directory location

    //Print_String_Array(SD_profiles);
    //Print_String_Array(USB_profiles);

    // Now put the files from each directory listing into the response
    int profile_index = instruction->response_store_index;    // local index variable to keep track of where to store strings in the response array
    int SD_index = 0;
    while ( SD_profiles[ SD_index ] )
    {
        instruction->response_array[profile_index] = (char*)malloc(sizeof(char*) * ( strlen( SD_profiles[ SD_index ]) +2 ) ); // allocate memory for string in response
        if( SD_index == 0)
            strcpy( instruction->response_array[profile_index], SD_profiles[ SD_index ] );

        else if( (SD_index > 0) && (SD_profiles[ SD_index + 1] != NULL) )   // child in tree structure part of response
        {
            char temp[15];
            sprintf( temp, "     \u251C\u2500 ");
            strcpy( instruction->response_array[profile_index], temp);
            strcat( instruction->response_array[profile_index], SD_profiles[ SD_index ] );
        }
        else    // child in tree structure
        {
            char temp[15];
            sprintf( temp, "     \u2514\u2500 ");
            strcpy( instruction->response_array[profile_index], temp);
            strcat( instruction->response_array[profile_index], SD_profiles[ SD_index ] );
        }
        ++profile_index;
        ++SD_index;
    }
    Free_String_Array_Memory(SD_profiles);

    int USB_index = 0;
    while ( USB_profiles[ USB_index ] )
    {
        instruction->response_array[profile_index] = (char*)malloc(sizeof(char*) * ( strlen( USB_profiles[ USB_index ]) +2 ) ); // allocate memory for string in response
        if( USB_index == 0)
            strcpy( instruction->response_array[profile_index], USB_profiles[ USB_index ] );

        else if( (USB_index > 0) && (USB_profiles[ USB_index + 1] != NULL) )   // child in tree structure
        {
            char temp[15];
            sprintf( temp, "     \u251C\u2500 ");
            strcpy( instruction->response_array[profile_index], temp);
            strcat( instruction->response_array[profile_index], USB_profiles[ USB_index ] );
        }
        else    // child in tree structure
        {
            char temp[15];
            sprintf( temp, "     \u2514\u2500 ");
            strcpy( instruction->response_array[profile_index], temp);
            strcat( instruction->response_array[profile_index], USB_profiles[ USB_index ] );
        }
        ++profile_index;
        ++USB_index;
    }
    Free_String_Array_Memory(USB_profiles);
    instruction->response_array[profile_index] = NULL;
    instruction->response_store_index = profile_index;
}

void Assemble_Help_Response(Instruction_Info* instruction)
{
    int help_index = instruction->response_store_index;

    instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * ( strlen("List of Commands & Queries, w/ usage:") +1 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[help_index], "List of Commands & Queries, w/ usage:");
    instruction->response_array[help_index][strlen("List of Commands & Queries, w/ usage:")] = '\0';
    ++help_index;

    instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * ( strlen("COMMANDS:\n") +1 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[help_index], "COMMANDS:\n");
    ++help_index;

    int CMD_list_index = 0;
    int list_length = ARRAY_SIZE(COMMAND_HELP_LIST);
    while ( (CMD_list_index< list_length) && (COMMAND_HELP_LIST[ CMD_list_index ] != NULL) )     // Read the output a line at a time - output it.
    {
        instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * ( strlen( COMMAND_HELP_LIST[CMD_list_index]) + 1 ) ); // allocate memory for string in response
        strcpy( instruction->response_array[help_index], "\t" );
        strcat( instruction->response_array[help_index], COMMAND_HELP_LIST[CMD_list_index] );
        ++help_index;
        ++CMD_list_index;
        if(CMD_list_index >= list_length)
            break;
    }

    instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * 1 );
    strcpy(instruction->response_array[help_index], "\n");
    ++help_index;

    instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * ( strlen("QUERIES:\n") +1 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[help_index], "QUERIES:");
    ++help_index;

    list_length = ARRAY_SIZE(QUERY_HELP_LIST);
    int QRY_list_index = 0;
    while ( (QRY_list_index< list_length) && (QUERY_HELP_LIST[ QRY_list_index ] != NULL) )     // Read the output a line at a time - output it.
    {
        instruction->response_array[help_index] = (char*)malloc( (sizeof(char) * ( strlen( QUERY_HELP_LIST[QRY_list_index])) + strlen("\t") +1 ) ); // allocate memory for string in response
        strcpy(instruction->response_array[help_index], "\t");
        strcat(instruction->response_array[help_index], QUERY_HELP_LIST[QRY_list_index]);
        ++help_index;
        ++QRY_list_index;
        if(QRY_list_index >= list_length)
            break;
    }
    instruction->response_array[help_index] = NULL;
    instruction->response_store_index = help_index;
}

void Get_Status(Instruction_Info* instruction)
{
  int str_len;

  Read_Hostname( Test.hostname);
  str_len = strlen("       hostname:  \n") + strlen(Test.hostname) + 2;
  char hostname_str[str_len];
  sprintf(hostname_str, "       hostname:  %s\n", Test.hostname);


  str_len = strlen("        eth0 IP:  \n") + strlen(Test.eth0_IP) + 2;
  char eth0_str[str_len];
  sprintf(eth0_str, "        eth0 IP:  %s\n", Test.eth0_IP);

  str_len = strlen("       wlan0 IP:  \n") + strlen(Test.wlan0_IP) + 2;
  char wlan0_str[str_len];
  sprintf(wlan0_str, "       wlan0 IP:  %s\n", Test.wlan0_IP);

  char* sys_time = Get_Time();
  str_len = strlen("    system time:  \n") + strlen(sys_time) + 2;
  char time[str_len];
  sprintf(time, "    system time:  %s\n", sys_time);
  free(sys_time);

  //Test.USB_flash_disk_use = Get_USB_Disk_Use();
  str_len = strlen("   USB disk use:  %s\n") + strlen(Test.USB_flash_disk_use) + 2;
  char USB_disk_use[str_len];
  sprintf(USB_disk_use, "   USB disk use:  %s\n", Test.USB_flash_disk_use);

  Get_CPU_Temperature_C(Test.CPU_temperature);
  str_len = strlen("CPU temperature:  \n") + strlen(Test.CPU_temperature) + 2;
  char CPU_temperature[str_len];
  sprintf(CPU_temperature, "CPU_temperature:  %s\n", Test.CPU_temperature);

  Test_is_Running(Test.is_running_str);
  str_len = strlen("Test is Running:  \n") + strlen(Test.is_running_str) + 2;
  char Test_is_running[str_len];
  sprintf(Test_is_running, "Test is Running:  %s\n", Test.is_running_str);

  Get_Execution_Mode_String(Test.execution_mode_str);
  str_len = strlen(" Execution Mode:  \n") + strlen(Test.execution_mode_str) + 2;
  char execution_mode_str[str_len];
  sprintf(execution_mode_str, " Execution Mode:  %s\n", Test.execution_mode_str);

  str_len = strlen("  Profile Name:  \n") + 2 + 30;
  char profile_name_str[str_len];
  if(Test.execution_mode == PROFILE_CONTROL)
  {
      if( Test.profile_name == NULL)
      {
          sprintf(profile_name_str, "   Profile Name:  not set\n");

      }
      else
      {
          sprintf(profile_name_str, "   Profile Name:  %s\n", Test.profile_name);
      }
  }
  else sprintf(profile_name_str, "   Profile Name:  N/A\n");

  str_len = strlen("  Compressor ID:  \n") + strlen(Test.compressor_ID) + 2;
  char compressor_str[str_len];
  sprintf(compressor_str, "  Compressor ID:  %s\n", Test.compressor_ID);

  str_len = strlen("        DDCA ID:  \n") + strlen(Test.DDCA_ID) + 2;
  char dewar_str[str_len];
  sprintf(dewar_str, "        DDCA ID:  %s\n", Test.DDCA_ID);

  str_len = strlen("   Displacer ID:  \n") + strlen(Test.displacer_ID) + 2;
  char displacer_str[str_len];
  sprintf(displacer_str, "   Displacer ID:  %s\n", Test.displacer_ID);

  str_len = strlen("         CCC ID:  \n") + strlen(Test.CCC_ID) + 2;
  char CCC_str[str_len];
  sprintf(CCC_str, "         CCC ID:  %s\n", Test.CCC_ID);

  str_len = strlen("Status: \n") + strlen(hostname_str) + strlen(eth0_str) + strlen(wlan0_str) + strlen(time) + strlen(USB_disk_use) + strlen(CPU_temperature) +  + strlen(Test_is_running) +
            strlen(execution_mode_str) + strlen(profile_name_str) + strlen("    ---------------------\n") + strlen(compressor_str) + strlen(dewar_str) + strlen(displacer_str) + strlen(CCC_str) + 20;
  char status_str[str_len];

  strcpy(status_str, "\0");
  strcat(status_str, "\t");
  strcat(status_str, hostname_str);

  strcat(status_str, "\t");
  strcat(status_str, eth0_str);

  strcat(status_str, "\t");
  strcat(status_str, wlan0_str);

  strcat(status_str, "\t");
  strcat(status_str, time);

  strcat(status_str, "\t");
  strcat(status_str, USB_disk_use);

  strcat(status_str, "\t");
  strcat(status_str, CPU_temperature);

  strcat(status_str, "\t");
  strcat(status_str, Test_is_running);

  strcat(status_str, "\t");
  strcat(status_str, execution_mode_str);

  strcat(status_str, "\t");
  strcat(status_str, profile_name_str);

  strcat(status_str, "\t");
  strcat(status_str, "    ---------------------\n");

  strcat(status_str, "\t");
  strcat(status_str, compressor_str);

  strcat(status_str, "\t");
  strcat(status_str, dewar_str);

  strcat(status_str, "\t");
  strcat(status_str, displacer_str);

  strcat(status_str, "\t");
  strcat(status_str, CCC_str);

  strcpy(instruction->response_str, status_str);
}


// Returns current blackbox mode of operation, either "STANDARD" or "CAL"
void Get_Mode(Instruction_Info* instruction)
{
  int str_len;
  char* mode_str;

  if(CAL_FUNCTIONS_ENABLED == true)
  {
      str_len = strlen("CAL\n") + 2;
      mode_str = malloc(sizeof(char) * str_len);
      sprintf(mode_str, "CAL\n");
  }
  else
  {
      str_len = strlen("STANDARD\n") + 2;
      mode_str = malloc(sizeof(char) * str_len);
      sprintf(mode_str, "STANDARD\n");
  }
 
  strcpy(instruction->response_str, mode_str);
  free(mode_str);
}

void Get_System_Time(Instruction_Info* instruction)
{
    char current_time[50];
    Erase_String_Contents(current_time);
    Read_DateTime( current_time );
    int i=0;
    while(current_time[i] != '\0')
    {
        if(current_time[i] == '_')
            current_time[i] = ' ';
        if(current_time[i] == '.')
            current_time[i] = ':';
        if(current_time[i] == '-')
            current_time[i] = '/';
        ++i;
    }
    strcpy(instruction->response_str, "\t");
    strcat(instruction->response_str, current_time);
    //printf("inst time: \"%s\"\n", instruction->response_str);
    //printf("cur time: \"%s\"\n", current_time);

}

// free mem afterwards
void Send_Query_List(Instruction_Info* instruction)
{
    // create string of all commands
    // print the commands to console and the socket
    // return success
    instruction->response_array[instruction->response_store_index ] = (char*)malloc(sizeof(char*) * ( strlen("Query list w/ args:\n") +2 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[ instruction->response_store_index ], "Query list w/ args:");
    instruction->response_array[ instruction->response_store_index ][ strlen("Query list w/ args:") ] = '\0';
    ++instruction->response_store_index;

    int list_length = ARRAY_SIZE(QUERY_HELP_LIST);
    int list_index = 0;
    while ( QUERY_HELP_LIST[ list_index ] )     /* Read the output a line at a time - output it. */
    {
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc(sizeof(char) * ( strlen( QUERY_HELP_LIST[list_index]) +10 ) ); // allocate memory for string in response
        strcpy(instruction->response_array[ instruction->response_store_index ], "   ");
        strcat(instruction->response_array[ instruction->response_store_index ], QUERY_HELP_LIST[list_index]);
        ++instruction->response_store_index;
        ++list_index;
        if( list_index >= list_length)
            break;
    }
    instruction->response_array[instruction->response_store_index] = NULL;
}

/*
|--------------------------------------------------------------------------
| Get_CPU_Temp
|--------------------------------------------------------------------------
|
| Query the linux kernel for the CPU temperature. Returns a double of the
| temperature in Celsius. Not super precise but gives pretty good results.
| Succesive reads may return the same temperature. Seems to change in around
| 0.5C increments, despite showing finer resolution. Tested with cold spray
| and temperature reporting is accurate- returns values in vicinity of -20
| when hit with cold spray.
|
| @return    tempC    temperature of pi CPU in degrees Celsius
*/
void Get_CPU_Temperature_C(char* temperature_string)
{
    char temperature_command[] = "/opt/vc/bin/vcgencmd measure_temp";
    char** shell_response = Exec_Shell_Command( temperature_command );
    double tempC = parseDouble( shell_response[0] );
    Free_String_Array_Memory( shell_response );


    Erase_String_Contents( temperature_string );
    sprintf( temperature_string, "%2.1f", tempC);
}



/*
|--------------------------------------------------------------------------
| ge
|--------------------------------------------------------------------------
|
|	Gets disk space stats for the local micro SD card, and any attached Flash drives.
| Stats are collected using the "df" shell command . "df" returns more stats than
| just the USB flash and micro SD card, so the output from df is piped to grep,
| which filters the output. grep only returns lines that contain /dev/root (microSD),
| or /dev/sd (USB flash). The full shell command is:
|				df -Tha --total | grep -E "/dev/root|/dev/sd"
|
|Flags for df:
|			-T			print filesystem type
|			-h			print human readable output
|			--total	produce grand totals
|
|Flags for grep
|			-E			use regular expressions in search pattern
|
| Example output:
| /dev/sda1      vfat         970M   297M  664M   32% /home/pi//USB_DRIVE
|
*/
void Get_Disk_Usage()
{
  char SD_card_line[200];
  char Flash_Drive_line[200];
  //char SD_card_use[100];
  //char Flash_Drive_Use[100];
  char shell_command[300];
	bool FLASH_DRIVE = false;

  strcpy( shell_command, "df -Tha --total" );
  strcat( shell_command, " | grep -E \"/dev/root|/dev/sd\""); // list disk usage, then search only for root use and flash use in /dev/sd*

  char**  return_string_array = Exec_Shell_Command( shell_command );
  strcpy(SD_card_line, return_string_array[0]);
	if( return_string_array[1] != NULL )
			FLASH_DRIVE = true;
	if( FLASH_DRIVE )
	{
      Flash_Drive.exists = true;
			strcpy(Flash_Drive_line, return_string_array[1]);
  		Trim_Trailing_WhiteSpace(Flash_Drive_line);
		  Parse_Disk_Use(Flash_Drive_line, &Flash_Drive);
      sprintf(Test.USB_flash_disk_use, "%s of %s", Flash_Drive.percent_filled, Flash_Drive.total_space);
	}

  Free_String_Array_Memory(return_string_array);
  Trim_Trailing_WhiteSpace(SD_card_line);
  Parse_Disk_Use(SD_card_line, &uSD_Card);
  sprintf(Test.SD_card_disk_use, "%s of %s", uSD_Card.percent_filled, uSD_Card.total_space);

}


/*
|--------------------------------------------------------------------------
| Parse_Disk_Use
|--------------------------------------------------------------------------
|
|	Parses the output from the "df" shell command into tokens, and stores the
| output into a data structure for reporting. The output from a command df
| command is passed as argument "console_line". This string is split into
| tokens delimited by whitespace, and the tokens are stored in struct of
| type Disk_Use.
|
| Example output from df:
| /dev/sda1      vfat         970M   297M  664M   32% /home/pi//USB_DRIVE
|
| fields the tokens are stored into:
| kernel_location filesystem   total_space  used_space  free_space   percent_used  mount_location
|
| @param				console_line			single line string output from df command
| @param 				device						Disk_Usage struct object, populated by this command
|
*/
void Parse_Disk_Use(char* console_line, struct Disk_Usage* device)
{
    char token_array[7][50];    // 7 tokens with 50 characters max length each
    int index_token_start = 0;
    int index_token_end = 0;
    int index_consumed = 0;
    int token_index = 0;

    Trim_Leading_WhiteSpace( console_line );
    char* substring;
    while(index_consumed < strlen(console_line))
    {
        while( isspace( console_line[ index_consumed ] ) && index_consumed < strlen(console_line) )   // skip whitespace between tokens
        { ++index_consumed;  }

        index_token_start = index_consumed;
        index_token_end = index_token_start;

        while( !isspace( console_line[ index_consumed ] ) && index_consumed < strlen(console_line) )   // consume any non whitespace characters (part of token)
        { ++index_consumed;  }
        index_token_end = index_consumed;
        substring = Get_Substring( console_line, index_token_start, index_token_end );
        strcpy( token_array[ token_index ], substring );
        free(substring);
        ++token_index;
    }

    strcpy(device->kernel_location,  token_array[ 0 ] );
    strcpy(device->filesystem,       token_array[ 1 ] );
    strcpy(device->total_space,      token_array[ 2 ] );
    strcpy(device->used_space,       token_array[ 3 ] );
    strcpy(device->free_space,       token_array[ 4 ] );
    strcpy(device->percent_filled,   token_array[ 5 ] );
    strcpy(device->mount_location,   token_array[ 6 ] );
}


/*
|--------------------------------------------------------------------------
| Exec_Shell_Command
|--------------------------------------------------------------------------
|
| Execute a command at the terminal prompt. The command is passed as argument.
| A string of the shell output response is returned. The string captures
| stdout and stderr.
|
| @param:  command    the shell command to execute
| @return:            a string of the shell response is returned
*/
char** Exec_Shell_Command(char* command)
{
    int MAX_LINES = 100;
    char read_line[250];

    FILE* command_shell = popen(command, POPEN_READ);                 //  The popen() function opens a process by creating a pipe, forking and invoking the shell.
    if (command_shell == NULL)
    {
        printf("%s  Error opening pipe for shell command!!\n", X_ERROR );
        exit(1);
    }

    int line_count = 0;
    char**  string_array = malloc(sizeof(char*) * MAX_LINES);        // allocate memory for pointer to strings
    while (fgets(read_line, sizeof(read_line), command_shell) != NULL)     /* Read the output a line at a time - output it. */
    {
        Trim_Trailing_WhiteSpace(read_line);
        //printf("LINE:\t%s\n", read_line);
        //string_array[line_count] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH); // allocate memory for the
				string_array[line_count] = (char*)malloc(sizeof(char) * ( strlen(read_line) +10 ) ); // allocate memory for the
        strcpy(string_array[line_count], read_line);
        ++line_count;
    }
    string_array[line_count] = NULL;   // Add a marker for the last string in the array
    pclose(command_shell);     // close file pointer to STDOUT
    return string_array;
}


double parseDouble(char* integer_string)
 {

   Trim_Trailing_WhiteSpace(integer_string);

   // Get index of start of integer portion. Could be a digit or + or -
   int start_index = 0;
   for(int i = 0; i<strlen(integer_string); ++i )
   {
       if( (integer_string[i] == '+' || integer_string[i] == '-') && i==0 )
       {
           if( isdigit(integer_string[i+1]) )
           {
               start_index = i;
               break;
           }
       }
       if( isdigit(integer_string[i]) )
       {
           start_index = i;
           break;
       }
   }

   // get index of last digit
   int end_index = start_index;    // start search of last "digit" character at the beginning of the integer portion
   char first_character = integer_string[start_index];

   if( first_character == '+' || first_character == '-' )  // if the first char is a sign, move on to the digits
       end_index = start_index + 1;
   else
       end_index = start_index;

   for(end_index = start_index; end_index<strlen(integer_string); ++end_index )
   {
       if( isdigit( integer_string[end_index] ) )
           continue;
       else
       {
           if( integer_string[end_index] == '.' && isdigit( integer_string[ end_index +1 ] ) )
               continue;
           else
               break;
       }
   }

   // Copy Substring from start_index to end index
   char integer_substring[end_index - start_index + 2];     // create temp storage for the substring
   memset(integer_substring, 0, sizeof(integer_substring) );
   for( int i = 0; i< (end_index - start_index +1); ++i)
   {
       integer_substring[i] = integer_string[i + start_index];
   }
   integer_substring[ strlen(integer_substring) ] = '\0';    // add null terminating character

   char* end_ptr;
   double parsed_double = strtod(integer_substring, &end_ptr);   // parse the substring to integer using stringtolong function

   return parsed_double;
 }


void Test_is_Running(char* is_running)
{
    if(Test.is_running == false)
        sprintf(is_running, "false");
    else
        sprintf(is_running, "true");
}

void Get_Execution_Mode_String(char* mode_string)
{
    if(Test.execution_mode == MANUAL_CONTROL)
        sprintf(mode_string, "Manual Control");
    else
        sprintf(mode_string, "Profile Control");
    return;
}


char* Get_USB_Disk_Use()
{
    Get_Disk_Usage();
    char* disk_use = (char*)malloc( sizeof(char*) * strlen(Test.USB_flash_disk_use) + 1);
    strcpy(disk_use, Test.USB_flash_disk_use);
    return disk_use;
}






#endif
