
#ifndef EXECUTE_COMMAND
#define EXECUTE_COMMAND

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <time.h>
#include <sys/time.h>

#include "colors.h"
#include "String_Helper.h"
#include "ADS1256.h"
#include "Struct_Defs.h"
#include "Profile_Helper.h"
#include "File_Helper.h"
#include "Read_Metrics.h"
#include "DAC.h"


extern void Clear_Loop();   // defined in "Read_Metrics.h"
extern pthread_mutex_t METRICS_LOOP_LOCK;   // defined in "Thread_Defs.h"
extern bool LOG_DATA;
extern READ_SEQ Read_Sequence;
extern int save_index;

// this structure is in "Struct_Defs.h"
/*
typedef struct board_state
{
    Test_Mode execution_mode;
    char* execution_mode_str;
    Relay_State relay_state;
    Heat_Load_State load_state;
    double load_setting_mW;
    profile_object* profile;

    bool* LOG_DATA;
    bool  is_running;
    char* is_running_str;
    char* PI_CPU_temp;
    char* hostname;
    char eth0_IP;
    char wlan0_IP;
    char* USB_filepath;
    char* profile_name;
    char* log_filename;
    char* IP_Address;
    char* CCC_ID;
    char* CPU_temperature;
    char* compressor_ID;
    char* displacer_ID;
    char* DDCA_ID;
    char* current_time;
    char* start_time;
    char* USB_flash_disk_use;
    char* SD_card_disk_use;
} board_state;
*/

board_state Test;   // struct definition in Struct_Defs.h


extern void Get_Disk_Usage();

void Initialize_Test_Settings();
void Load_On(Instruction_Info* instruction);
void Load_Off(Instruction_Info* instruction);
void Stop_Test(Instruction_Info* instruction);
void Start_Test(Instruction_Info* start_command);
void Set_Load(char* double_string, char* result);
void Turn_Relay_On(Instruction_Info* instruction);
void Turn_Relay_Off(Instruction_Info* instruction);

void Action_Relay_ON();
void Action_Relay_OFF();
int Lookup_Load_Setting();
Relay_State Get_Relay_State();
void Turn_Relay_On();
Test_Mode Get_Test_Mode();

void Use_Profile(Instruction_Info* instruction);
void Set_CCC_ID(char* ccc_ID, char* result);
void Set_DDCA_ID(char* DDCA_ID, char* result);
void Set_Displacer_ID(char* displacer_ID, char* result);
void Set_Compressor_ID(char* compressor_ID, char* result);
void Send_All_Logs(char* result);
void Send_Log(char* result);
void Set_Manual_Mode(char* result);
void Set_System_Time(char* time_argument, char* result);
void Self_Test(char* result);
void Set_Profile_Mode(char* result);
void Print_Command_List(Instruction_Info* instruction);
void Action_Relay_ON();
void Action_Relay_OFF();
void Wait_Enter_Key();
void Read_Test_Config_File();
void Read_Hostname(char* host_str);
void Get_eth0_IP_Addr(char* eth0_ip);
void Get_wlan0_IP_Addr(char* wlan0_ip);
void Search_USB_Flash_Attached(char* path_to_drive);
void Read_DateTime(char* time_buffer);
void Print_Initialization();
void Get_Log_Filename(char* filename);

char** Get_Network_Interfaces();
char* Get_Relay_State_String();
char* Test_Confirmation_Message();


// strings received on socket, then parsed to commands are routed here
// precursor to this command, command has been processed and command index stored
void Execute_Command(Instruction_Info* command)
{
    switch(command->this_command)
    {
        case LOAD_ON:
            Load_On(command);
            break;

        case LOAD_OFF:
            Load_Off(command);
            break;

        case PRINT_COMMAND_LIST:
            Print_Command_List(command);
            break;

        case TURN_RELAY_ON:
            Turn_Relay_On(command);
            break;

        case TURN_RELAY_OFF:
            Turn_Relay_Off(command);
            break;

        case SET_LOAD:
            Set_Load( command->argument_str, command->response_str );
            break;

        case START_TEST:
            Start_Test(command);
            break;

        case STOP_TEST:
            Stop_Test(command);
            break;

        case SET_MANUAL_MODE:
            Set_Manual_Mode(command->response_str);
            break;

        case SET_PROFILE_MODE:
            Set_Profile_Mode(command->response_str);
            break;

        case SELFTEST:
            Self_Test(command->response_str);
            break;

        case SET_TIME:
            Set_System_Time( command->argument_str, command->response_str );
            break;

        case SEND_LOG:
            Send_Log(command->response_str);
            break;

        case SEND_ALL_LOGS:
            Send_All_Logs(command->response_str);
            break;

        case SET_COMPRESSOR_ID:
            Set_Compressor_ID( command->argument_str, command->response_str );
            break;

        case SET_DISPLACER_ID:
            Set_Displacer_ID( command->argument_str, command->response_str );
            break;

        case SET_DDCA_ID:
            Set_DDCA_ID( command->argument_str, command->response_str );
            break;

        case SET_CCC_ID:
            Set_CCC_ID( command->argument_str, command->response_str );
            break;

        case USE_PROFILE:
            Use_Profile( command );
            break;

        case CMD_NOT_FOUND:
            break;

        default:  // default case
            break;
    }
}

// verify a load value has been set
// if load val is 0, then do not turn the load on, return error message
// change ADC read sequence to HEAT LOAD ON
// read some values and adjust load to proper mW disipation
void Load_On(Instruction_Info* instruction)
{
    pthread_mutex_lock(&METRICS_LOOP_LOCK);     //
        printf(COLOR_BOLD_GREEN "     \u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511\n");
        printf("     \u2502  ---LOAD ON---    \u2502\n");
        printf(COLOR_BOLD_GREEN "     \u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519\n" COLOR_RESET);
    pthread_mutex_unlock(&METRICS_LOOP_LOCK);

    if(Test.execution_mode == PROFILE_CONTROL)
    {
        if( instruction != NULL )
        {
            char response[MAX_RESPONSE_LENGTH];
            sprintf(response, "\t%s !ERROR! in profile mode, cannot manually change load.\n", X_ERROR);
            strcpy( instruction->response_str, response);          // copy message into return string
        }
        return;
    }

    // Lookup what current Load setting is
    if( Test.load_setting_mW == 0)
    {
        printf("Error\n");
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t%s !ERROR! Load not configured to a value (mW), cannot turn on\n", X_ERROR);
        strcpy( instruction->response_str, response);          // copy message into return string
        return;
    }
    else if( Test.load_setting_mW < 0)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t%s!ERROR! cannot set load to a value less than 0.\n", X_ERROR);
        strcpy( instruction->response_str, response);          // copy message into return string
        return;
    }
    else
    {
        // change mux to heat load on
        Read_Sequence = HEAT_LOAD_ON;    // changes which ADC read sequence to use when reading ADC0 & ADC1. (changes to reading load values as well)
        int DAC_counts = Load_milliWatts_to_DAC_Counts( Test.load_setting_mW );   // calculate DAC counts for target mW load disipation

        PAUSE_ACCESS_TO_SPI_BUS = true;           // let read metrics know we need the SPI bus
        while( SPI_BUS_IN_USE){ usleep(10); }     // wait until SPI bus is free
        DAC_Set_Count( channel_A, DAC_counts);    // set the count
        PAUSE_ACCESS_TO_SPI_BUS = false;

        usleep(15000);                                                            // wait for 15 ms for ADC to take new reading

        while( Save_Data[ save_index ].Heat_Load_V < 0.2 )  // wait until there is some load voltage (it is actually turned on)
            usleep(2000);

        int save_index_current_value = save_index;
        while(save_index_current_value >= (save_index - 1) )  // wait until new readings to measure data
        {   usleep(5000); }

        double Load_V = Save_Data[ save_index ].Heat_Load_V;
        double Load_I = Save_Data[ save_index ].Heat_Load_mA;
        double Load_mW = Load_V * Load_I;
        double Target_mW = Test.load_setting_mW;
        double error_mW = Target_mW - Load_mW;  // determine error between target and setpoint

        if(error_mW < 0)
            error_mW *= -1;

        double percent_error = (error_mW / Target_mW) * 100;

        if( percent_error > 0.5 )   // adjust programmed load to correct discrepency
        {
            double ratio_error = Target_mW / Load_mW;
            double new_set_value_mW = Target_mW * ratio_error;
            DAC_counts = Load_milliWatts_to_DAC_Counts( new_set_value_mW );
            DAC_Set_Count( channel_A, DAC_counts);
        }
    }
    char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
    char line2[] = "\u2502  ---LOAD ON---    \u2502";
    char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
    ++instruction->response_store_index;
}

void Load_Off(Instruction_Info* instruction)
{
    printf(COLOR_RED "     \u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511\n");
    printf("     \u2502  ---LOAD OFF---   \u2502\n");
    printf(COLOR_RED "     \u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519" COLOR_RESET);

    if( (Test.execution_mode == PROFILE_CONTROL) && (instruction != NULL) )
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t!ERROR! in profile mode, cannot manually change load.\n");
        strcpy( instruction->response_str, response);          // copy message into return string
        return;
    }
    // first verify the load is in fact on (read some values)
        // get mutex for spi bus
        // get mutex for set load
        // verify mux is on for reading load
        // set load to 0
        // verify current falls to 0
        // change mux reading scheme to load off
        // unlock mutex
        // unlock mutex
        // return success

    PAUSE_ACCESS_TO_SPI_BUS = true;
    while( SPI_BUS_IN_USE){ usleep(10); }   // wait until SPI bus is free
    DAC_Set_Count( channel_A, 0);
    Read_Sequence = HEAT_LOAD_OFF;
    PAUSE_ACCESS_TO_SPI_BUS = false;

    if( instruction != NULL)
    {
        char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
        char line2[] = "\u2502  ---LOAD OFF---   \u2502";
        char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
        sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
        ++instruction->response_store_index;

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
        sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
        ++instruction->response_store_index;

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
        sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
        ++instruction->response_store_index;
    }

}

void Initialize_Test_Settings()
{
    printf( COLOR_GRAY "     --------------------------      \n");
    printf("\t---INITIALIZING---\n");
    printf("     --------------------------     \n" COLOR_RESET);
    Action_Relay_OFF(NULL);
    Load_Off(NULL);
    Test.is_running = false;
    strcpy(Test.is_running_str, "false");
    Test.execution_mode = MANUAL_CONTROL;
    Test.relay_state = RELAY_OFF;
    Test.load_state = HEAT_LOAD_OFF;
    Test.load_setting_mW = 0;
    Read_Hostname(Test.hostname);
    Get_eth0_IP_Addr(Test.eth0_IP);
    Get_wlan0_IP_Addr(Test.wlan0_IP);

    Erase_String_Contents(Test.USB_filepath);
    Search_USB_Flash_Attached(Test.USB_filepath);

    Erase_String_Contents(Test.timestamp);
    Get_TimeStamp(Test.timestamp);

    Erase_String_Contents(Test.profile_name);
    sprintf(Test.profile_name, "not set");

    Erase_String_Contents(Test.start_time);
    sprintf(Test.start_time, "not started");

    Erase_String_Contents(Test.CCC_ID);
    sprintf(Test.CCC_ID, "not set");

    Erase_String_Contents(Test.compressor_ID);
    sprintf(Test.compressor_ID, "not set");

    Erase_String_Contents( Test.DDCA_ID ) ;
    sprintf(Test.DDCA_ID, "not set");

    Erase_String_Contents( Test.displacer_ID );
    sprintf(Test.displacer_ID, "not set");

    Erase_String_Contents(Test.USB_flash_disk_use);
    Erase_String_Contents(Test.SD_card_disk_use);
    Get_Disk_Usage();
    Print_Initialization();

    printf( COLOR_GRAY "      ---------------------------     \n");
    printf("\t---DONE INITIALIZING---\n");
    printf("      ---------------------------     \n" COLOR_RESET);
}

void Print_Initialization()
{
    printf( COLOR_BROWN "\n\u250C\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2510\n");
    printf("\u2502\t    ---HARDWARE SETTINGS---"); printf("\33[75D"); printf( "\033[52C"); printf("\u2502\n") ;

    printf("\u2502       relay_state:  \033[s");  printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf( "\033[u");
    if(Test.relay_state == RELAY_OFF)
        printf("RELAY OFF\n");
    else
        printf("RELAY ON\n");

    printf("\u2502          hostname:  %s", Test.hostname); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");
    printf("\u2502           eth0 IP:  %s", Test.eth0_IP); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");
    printf("\u2502          wlan0 IP:  %s", Test.wlan0_IP); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");
    printf("\u2502          USB path:  %s", Test.USB_filepath); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");
    printf("\u2502       system time:  %s", Test.timestamp); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");
    printf("\u2502      USB disk use:  %s", Test.USB_flash_disk_use); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");
    printf("\u2502       SD card use:  %s", Test.SD_card_disk_use); printf("\33[75D"); printf( "\033[52C"); printf("\u2502"); printf("\n");

    printf( COLOR_BROWN "\u2514\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2518\n" COLOR_RESET);
}

// free memory afterwords
char** Get_Network_Interfaces()
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    int MAX_INTERFACES = 5; // assuming a pi has no more than 5 network interfaces (in reality it has at most 3: lo, eth0, wlan0)
    int interface_count = 0;
    char address[NI_MAXHOST];

    if ( getifaddrs(&ifaddr) == -1 )
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    char** network_interfaces = malloc(sizeof(char*) * MAX_INTERFACES);
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET)
        {
            s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), address, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0)
            {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }
            network_interfaces[ interface_count ] = (char*)malloc(sizeof(char*) * 40 );  // allocate memory to store this interface name
            strcpy( network_interfaces[ interface_count ], ifa->ifa_name);
            ++interface_count;
            if(PRINT_DEBUG) printf("<Interface>: %s \t <Address> %s\n", ifa->ifa_name, address);
        }
    }
    free(ifaddr);
    network_interfaces[ interface_count ] = NULL; // null terminate the string array
    return network_interfaces;
}

// must free mem after
void Get_eth0_IP_Addr(char* eth0_ip)
{
    char** valid_interfaces = Get_Network_Interfaces();
    if( String_Array_Contains(valid_interfaces, "eth0") )
    {
        int fd;
        struct ifreq ifr;

        fd = socket(AF_INET, SOCK_STREAM, 0);

        /* I want to get an IPv4 IP address */
        ifr.ifr_addr.sa_family = AF_INET;

        /* I want IP address attached to "eth0" */
        strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
        ioctl(fd, SIOCGIFADDR, &ifr);
        close(fd);

        /* display result */
        sprintf(eth0_ip,"%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    }
    else
    {
        sprintf( eth0_ip, "interface not up");
    }
    Free_String_Array_Memory( valid_interfaces);

    return;
}

// must free mem after
void Get_wlan0_IP_Addr(char* wlan0_ip)
{
      char** valid_interfaces = Get_Network_Interfaces();

      if( String_Array_Contains(valid_interfaces, "wlan0") )
      {
          int fd;
          struct ifreq ifr;

          fd = socket(AF_INET, SOCK_STREAM, 0);

          /* I want to get an IPv4 IP address */
          ifr.ifr_addr.sa_family = AF_INET;

          /* I want IP address attached to "eth0" */
          strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
          ioctl(fd, SIOCGIFADDR, &ifr);
          close(fd);

          /* copy result */
          sprintf(wlan0_ip,"%s", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
      }
      else
      {
          sprintf(wlan0_ip, "interface not up");
      }
      Free_String_Array_Memory( valid_interfaces);
      return;
}

// must free mem after
void Get_Log_Filename(char* filename)
{
    Read_Hostname(Test.hostname);
    char timestamp[50];
    Read_DateTime(timestamp);

    strcpy(filename, Test.hostname);
    strcat(filename, "_");
    strcat(filename, timestamp);
    strcat(filename, ".log");
    return;
}

// needs implementing
void Search_USB_Flash_Attached(char* path_to_drive)
{
    strcpy(path_to_drive, "~/USB_Drive/");
    path_to_drive[ strlen( path_to_drive ) ] = '\0';
    return;
}

/*
 |--------------------------------------------------------------------------
 | Read_Hostname
 |--------------------------------------------------------------------------
 |
 | Reads hostname of the pi by opening /etc/hostname file
 | Must free char* memory after done with string.
 |
 | @return:  hostname of the pi
 */
 void Read_Hostname(char* host_str)
 {
   	FILE *file_pointer;
   	char read_line[512];
    char host_file[] = "/etc/hostname";

    if( host_str == NULL)
        return;

   	if( (file_pointer = fopen(host_file, "r")) == NULL )
    {
         printf("couldn't open file\n");
         printf("%s\n", host_file);
   		  return;
   	}

   	while( fgets(read_line, 512, file_pointer) != NULL )
    {
        Trim_Leading_Trailing_Whitespace(read_line);
        if( strlen(read_line) > 0 )
            sprintf(host_str, "%s", read_line);
   	}
    return;
 }

void Read_DateTime(char* time_buffer)
{
	 time_t rawtime;
	 struct tm* timeinfo;
	 time (&rawtime);
	 timeinfo = localtime(&rawtime);
	 strftime (time_buffer,49,"%m-%d-%Y_%H.%M.%S",timeinfo);
	 return;
}

void Print_Command_List(Instruction_Info* instruction)
{
    // create string of all commands
    // print the commands to console and the socket
    // return success
    instruction->response_array[instruction->response_store_index ] = (char*)malloc(sizeof(char*) * ( strlen("Query list w/ args:\n") +1 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[ instruction->response_store_index ], "Command list w/ args:");
    instruction->response_array[ instruction->response_store_index ][ strlen("Command list w/ args:") ] = '\0';
    ++instruction->response_store_index;


    int list_length = ARRAY_SIZE(COMMAND_HELP_LIST);
    int list_index = 0;
    while ( COMMAND_HELP_LIST[ list_index ] )     /* Read the output a line at a time - output it. */
    {
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc(sizeof(char) * ( strlen( COMMAND_HELP_LIST[list_index]) +5 ) ); // allocate memory for string in response
        strcpy(instruction->response_array[ instruction->response_store_index ], "   ");
        strcat(instruction->response_array[ instruction->response_store_index ], COMMAND_HELP_LIST[list_index]);
        ++instruction->response_store_index;
        ++list_index;
        if( list_index >= list_length)
            break;
    }
    instruction->response_array[instruction->response_store_index] = NULL;
}

void Turn_Relay_On(Instruction_Info* instruction)
{
    // get current relay state (read some readings), check if already on
            // if already on, return response that it is already on
    // check if test has been started if in profile mode
    // if in profile mode and test has not been started, return error
    // if in manual mode anything goes
    // if relay off, turn it on, take some readings to verify, then return success

    // New plan
    //Manual Mode
        // send relay on signal
        // read some readings
        // verify state
    //Profile Mode
        // return error

    if(Test.execution_mode == PROFILE_CONTROL)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t!ERROR! in profile mode, cannot manually change relay.");
        strcpy( instruction->response_str, response);          // copy message into return string
        return;

    }

    Action_Relay_ON();
    Test.relay_state = RELAY_ON;

    if( instruction == NULL ) // only record the outcome of turning relay on if we are sure the place to write the string is not null
        return;

    char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
    char line2[] = "\u2502  ---RELAY ON---   \u2502";
    char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
    ++instruction->response_store_index;
}

void Turn_Relay_Off(Instruction_Info* instruction)
{
    if(Test.execution_mode == PROFILE_CONTROL)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t!ERROR! in profile mode, cannot manually change relay.");
        strcpy( instruction->response_str, response);          // copy message into return string
        return;

    }

    Action_Relay_OFF();
    Test.relay_state = RELAY_OFF;

    if( instruction == NULL ) // only record the outcome of turning relay on if write destination is not null
        return;

    char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
    char line2[] = "\u2502  ---RELAY OFF---  \u2502";
    char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
    ++instruction->response_store_index;
/*
    if(Test.execution_mode == PROFILE_CONTROL)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t!ERROR! in profile mode, cannot manually change load.\n");
        strcpy( instruction->response_str, response);          // copy message into return string
        return;

    }
    char* result_str;
    bool record_result = false;   // only record the outcome of turning off if we are sent a valid object to put the result into
    if(instruction != NULL)
    {
        record_result = true;
        result_str = instruction->response_str;
    }

    result_str = instruction->response_str;
    bool relay_state = Get_Relay_State();
    printf("finished relay state\n");

        // New plan
    //Manual Mode
        // send relay off signal
        // read some readings
        // verify state
    //Profile Mode
        // return error
    if( relay_state == RELAY_ON )
    {
        Action_Relay_OFF();
        if( !record_result )
            return;
        relay_state = Get_Relay_State();
            printf("finished relay state\n");
        if( relay_state == RELAY_OFF )
        {
            char response[MAX_RESPONSE_LENGTH];
            sprintf(response, "\t%s Success, relay turned off\n", CHECKMARK);
            strcpy( result_str, response);          // copy message into return string
            return;
        }
        else  // relay didnt change state by turning on
        {
            char response[MAX_RESPONSE_LENGTH];
            sprintf(response, "\t%s !ERROR! relay did not turn off\n", X_ERROR);
            strcpy( result_str, response);          // copy message into return string
            return;
        }
    }
    else  // (RELAY already on)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t%s Relay is already off.\n", CHECKMARK);
        strcpy( result_str, response);          // copy message into return string
        return;
    }
    */
}

void Set_Load(char* double_string, char* result)
{
    if(Test.execution_mode == PROFILE_CONTROL)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t%s !ERROR! in profile mode, cannot manually change load.\n", X_ERROR);
        strcpy( result, response);          // copy message into return string
        return;
    }

    double load_val = Parse_Double(double_string);
    if( load_val >  0)
    {
        Test.load_setting_mW = load_val;
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t%s Set load value to %3.1f \u33BD.", CHECKMARK, load_val);
        strcpy( result, response);          // copy message into return string
        return;
    }
}

void Start_Test(Instruction_Info* start_command)
{

  // verify a profile has been set, or set to manual control
  // start the test, record start time, and begin logging
  // timestamp start time
  Action_Relay_OFF();
  Test.relay_state = RELAY_OFF;
  Load_Off(NULL);

  Test_Mode tst_mode = Test.execution_mode;
  if( tst_mode == PROFILE_CONTROL)
  {
      // verify profile has been set, it is found, and file parse is valid
      // if those things are not valid, return error along with the problems
  }

  char* message = Test_Confirmation_Message();
  strcpy(start_command->response_str, message);
  free(message);

  if( Test.execution_mode == PROFILE_CONTROL)
      strcpy(Test.execution_mode_str, "PROFILE");
  else
      strcpy(Test.execution_mode_str, "MANUAL");

  Get_Time(Test.start_time);

  Create_Log_File(Test.log_filename);
  Start_Test_Timer();

  Test.is_running = true;
  Test.load_state = HEAT_LOAD_OFF;
  Test.load_setting_mW = 0;
  Test.LOG_DATA = true;

  // reset the index of the array where data points are stored ( dont use existing data in save array )
  pthread_mutex_lock(&INCREMENT_LOCK);
    save_index = 0;
  pthread_mutex_unlock(&INCREMENT_LOCK);
  Clear_Loop();   // clear read data in memory

  Erase_String_Contents(Test.USB_flash_disk_use);
  sprintf(Test.USB_flash_disk_use, "%s", " N/A ");

  Erase_String_Contents(Test.SD_card_disk_use);
  sprintf(Test.SD_card_disk_use, "%s", " N/A ");

  // In response include start time, & log file name
  // log filepath
  // whether flash drive is installed

          // create log file
          // write test params to file
          // start logging

      // if(profile)
          // create command list
          // start execution
}

char* Test_Confirmation_Message()
{
      char line_break[] = "\t   \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\n";
      char header_line[] = "\t ---TEST SETTINGS--- \n\n";

      char PI_Blackbox[50];
      memset(PI_Blackbox, 0, sizeof(PI_Blackbox) );
      Read_Hostname(PI_Blackbox);

      int str_len = strlen("\tBlackbox:  ") + strlen(PI_Blackbox) +1;
      char blackbox_ID[ str_len ];
      sprintf(blackbox_ID, "\tBlackbox:  %s\n", PI_Blackbox);
      blackbox_ID[ strlen(blackbox_ID) ] = '\0';

      memset(Test.log_filename, 0, sizeof(Test.log_filename) );
      Get_Log_Filename( Test.log_filename );

      str_len = strlen(Test.log_filename) + strlen("Log_File:  \n")+ 2;
      char log_line[str_len];
      Erase_String_Contents(log_line);
      sprintf(log_line, "\tLog File:  %s\n", Test.log_filename);
      log_line[ strlen(log_line) ] = '\0';

      str_len = strlen(Test.compressor_ID) + strlen("\tCompressor_ID:  \n") + 2;
      char comp_ID[str_len];
      Erase_String_Contents(comp_ID);
      sprintf(comp_ID, "\t   Compressor_ID:  %s\n", Test.compressor_ID);
      comp_ID[ strlen(comp_ID) ] = '\0';

      str_len = strlen(Test.displacer_ID) + strlen("\tDisplacer_ID:  \n") + 2;
      char displac_ID[str_len];
      Erase_String_Contents(displac_ID);
      sprintf(displac_ID, "\t    Displacer_ID:  %s\n", Test.displacer_ID);
      displac_ID[ strlen( displac_ID) ] = '\0';

      str_len = strlen(Test.DDCA_ID) + strlen("\tDDCA_ID:  \n") + 2;
      char ddca_ID[str_len];
      Erase_String_Contents(ddca_ID);
      sprintf(ddca_ID, "\t\t DDCA_ID:  %s\n", Test.DDCA_ID);
      ddca_ID[ strlen( ddca_ID) ] = '\0';

      str_len = strlen(Test.CCC_ID) + strlen("\t\t  CCC_ID:  \n") + 2;
      char ccc_ID[str_len];
      Erase_String_Contents(ccc_ID);
      sprintf(ccc_ID, "\t\t  CCC_ID:  %s\n", Test.CCC_ID);
      ccc_ID[ strlen( ccc_ID) ] = '\0';

      str_len = strlen("               test_mode:  PROFILE CONTROL\n") + 2;
      char* mode_str = (char*)malloc( sizeof(char*) * str_len);
      char* execution_mode_msg = NULL;
      if(Test.execution_mode == PROFILE_CONTROL)
      {
          execution_mode_msg = (char*)malloc( sizeof(char*) * 100 );
          // if profile
              // length of test
              /// different load_values
              // print each command and associated times

          sprintf( mode_str, "               test_mode:  PROFILE CONTROL\n");
      }

      if(Test.execution_mode == MANUAL_CONTROL)
      {
          char manual_mode_msg[] = "\n\t\t**Note: after issuing 'start_test', these commands available: (not case sensitive)\n";
          char commmands_available[] = "\t\t\t'LOAD_ON', 'LOAD_OFF', 'RELAY_ON', 'RELAY_OFF', 'SET_LOAD', 'STOP_TEST'\n";
          char queries_msg[] = "\t\t**These queries available:\n";
          char queries_available[] = "\t\t\t'METRICS', 'STATUS', 'TIME'\n";
          str_len = strlen(manual_mode_msg) + strlen(commmands_available) + strlen(queries_msg) + strlen(queries_available) + 2;
          execution_mode_msg = (char*)malloc( sizeof(char*) * str_len);
          sprintf(execution_mode_msg, "%s %s %s %s", manual_mode_msg, commmands_available, queries_msg, queries_available );

          sprintf( mode_str, "               test_mode:  MANUAL CONTROL\n");
      }

    char* profile_str = NULL;
    if( Test.execution_mode == PROFILE_CONTROL && (Test.profile != NULL) )
    {
        str_len = strlen("          Profile:  \n") + strlen(Test.profile->filename) + 1;
        profile_str = malloc( sizeof(char*) * str_len);
        sprintf( profile_str, "          Profile:  %s\n", Test.profile->filename);
    }

    char starting_test[] = "\t   Test started. Logging started ...\n";

    int response_length = strlen(line_break) + strlen(header_line) + strlen(log_line) + strlen("Confirm test settings: \n") + strlen(comp_ID) + strlen(displac_ID) + strlen(ddca_ID) + strlen(ccc_ID)
                          + strlen(mode_str) + strlen(line_break) + strlen(execution_mode_msg) + strlen(starting_test) + 1;

    char test_settings_str[response_length];

    strcpy(test_settings_str, line_break);
    strcat(test_settings_str, "\t");
    strcat(test_settings_str, header_line);
    strcat(test_settings_str, "\t");
    strcat(test_settings_str, blackbox_ID);
    strcat(test_settings_str, "\t");
    strcat(test_settings_str, log_line);


    strcat(test_settings_str, comp_ID);
    strcat(test_settings_str, displac_ID);
    strcat(test_settings_str, ddca_ID);
    strcat(test_settings_str, ccc_ID);
    strcat(test_settings_str, mode_str);
    strcat(test_settings_str, execution_mode_msg);
    free(execution_mode_msg);

    if( Test.execution_mode == PROFILE_CONTROL && (Test.profile != NULL) )
    {
        strcat(test_settings_str, profile_str);
        free(profile_str);
    }

    strcat(test_settings_str, line_break);
    strcat(test_settings_str, "\n");
    strcat(test_settings_str, starting_test);

    return strdup(test_settings_str);
}

// turn off logging
// close log file
// print message on how to send log file
// free memory and clear variables in test structure
void Stop_Test(Instruction_Info* instruction)
{
  printf(COLOR_BRIGHT_GREEN "STOP TEST\n" COLOR_RESET);
  Test.LOG_DATA = false;   // turn off read_metrics loop
  Test.LOG_DATA = false;
  Turn_Relay_Off( instruction );
  Load_Off(NULL);
  Stop_Test_Timer();
  Reset_Test_Timer();
  if( Test.is_running == true)
  {
      Test.is_running = false;
      char response[MAX_RESPONSE_LENGTH];
      sprintf(response, "\tTest Execution stopped.\n");
      strcpy( instruction->response_str, response);          // copy message into return string
      return;
  }
  else    // Test was not running
  {
      Test.execution_mode = MANUAL_CONTROL;
      char response[MAX_RESPONSE_LENGTH];
      sprintf(response, "\tTest Execution is already stopped.\n");
      strcpy( instruction->response_str, response);          // copy message into return string
      return;
  }
  // send test logs to hub
}

void Set_Manual_Mode(char* result_str)
{
  if( Test.is_running == true)
  {
      char response[MAX_RESPONSE_LENGTH];
      sprintf(response, "\t%s Error: Cannot change test execution mode while test running. Must stop test first.", X_ERROR);
      strcpy( result_str, response);          // copy message into return string
      return;
  }
  else
  {
      Test.execution_mode = MANUAL_CONTROL;
      char response[MAX_RESPONSE_LENGTH];
      sprintf(response, "\t%s Test Execution changed to MANUAL control.", CHECKMARK);
      strcpy( result_str, response);          // copy message into return string
      return;
  }
}

void Set_Profile_Mode(char* result_str)
{
  if( Test.is_running == true)
  {
      char response[MAX_RESPONSE_LENGTH];
      sprintf(response, "\t%s Error: Cannot change test execution mode while test running. Must stop test first.", X_ERROR);
      strcpy( result_str, response);          // copy message into return string
      return;
  }
  else
  {
      Test.execution_mode = PROFILE_CONTROL;
      char response[MAX_RESPONSE_LENGTH];
      sprintf(response, "\t%s Test Execution changed to PROFILE control.", CHECKMARK);
      strcpy( result_str, response);          // copy message into return string
      return;
  }
}

void Self_Test(char* result)
{
  printf("FUNC)  " COLOR_BRIGHT_GREEN "SELFTEST\n" COLOR_RESET);
}

// must set DS3231 time too
// copy result into result parameter
void Set_System_Time(char* time_argument, char* result)
{
  printf(COLOR_BRIGHT_GREEN "SET TIME\n" COLOR_RESET);

  time_t raw_time = time(NULL);
  struct tm* tm_ptr = localtime(&raw_time);


  int month, day, year, hour, minute, second;
  sscanf(time_argument, "%d-%d-%d_%d.%d.%d", &month, &day, &year, &hour, &minute, &second);

  if (tm_ptr)
  {
    tm_ptr->tm_mon  = month - 1;  // this time structure is 0 based, so January == 0. Subtract 1 to convert
    tm_ptr->tm_mday = day;
    tm_ptr->tm_year = year - 1900;  // year is # of years since 1900
    tm_ptr->tm_hour = hour;
    tm_ptr->tm_min  = minute;
    tm_ptr->tm_sec  = second;

    const struct timeval time_val = { mktime(tm_ptr), 0 };


    char time_buffer[50];
    strftime (time_buffer,30,"%m/%d/%Y_%H:%M:%S",tm_ptr);
    printf("converted time: %s \n", time_buffer);
    settimeofday(&time_val, NULL);
  }
    // check to verify time update, return success
}

void Send_Log(char* result)
{
  printf("FUNC)  " COLOR_BRIGHT_GREEN "SEND LOG\n" COLOR_RESET);
    // send whatever recent log youre supposed to to the hub

}

void Send_All_Logs(char* result)
{
  printf("FUNC)  " COLOR_BRIGHT_GREEN "SEND ALL LOGS\n" COLOR_RESET);
  // find all logs and send them
  // return response of what files were sent
}



void Set_Compressor_ID(char* compressor_ID, char* result)
{
  if( compressor_ID != NULL)
  {
      strncpy(Test.compressor_ID, compressor_ID, ID_STRING_SIZE);
      sprintf(result, "\t%s Compressor ID set to: %s", CHECKMARK, compressor_ID);
  }
  else
      sprintf(result, "\t%s Error, invalid ID given as argument", X_ERROR);
}

void Set_Displacer_ID(char* displacer_ID, char* result)
{
  if( displacer_ID != NULL)
  {
      strncpy(Test.displacer_ID, displacer_ID, ID_STRING_SIZE);
      sprintf(result, "\t%s Displacer ID set to: %s", CHECKMARK, displacer_ID);
  }
  else
      sprintf(result, "\t%s Error, invalid ID given as argument", X_ERROR);
}

void Set_DDCA_ID(char* DDCA_ID, char* result)
{
  if( DDCA_ID != NULL)
  {
      strncpy(Test.DDCA_ID, DDCA_ID, ID_STRING_SIZE);
      sprintf(result, "\t%s DDCA ID set to: %s", CHECKMARK, DDCA_ID);
  }
  else
      sprintf(result, "\t%s Error, invalid ID given as argument", X_ERROR);
}


void Set_CCC_ID(char* CCC_ID, char* result)
{
  if( CCC_ID != NULL)
  {
      strncpy(Test.CCC_ID, CCC_ID, ID_STRING_SIZE);
      sprintf(result, "\t%s CCC ID set to: %s", CHECKMARK, CCC_ID);
  }
  else
      sprintf(result, "\t%s Error, invalid ID given as argument", X_ERROR);
}


void Use_Profile(Instruction_Info* instruction)
{

  char* selected_profile = instruction->argument_str;
  // if test is running, then return error
  // check valid name of profile
  // search for profile
  // if found then parse the profile

    if( Test.is_running )   // profile changes are only allowed while test is NOT running
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "%s TEST_RUNNING_ERROR: Cannot change profile while test is running. Must stop test first.\n", X_ERROR);
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1 );
        strcpy( instruction->response_array[ instruction->response_store_index ], response);          // copy message into return string
        ++instruction->response_store_index;
        return;
    }

    // verify target profile has a ".profile" file extension
    char* file_extension = Get_File_Extension( selected_profile );
    if( !String_Equals_String(file_extension, "profile"))   //  verify has a ".profile" file extension
    {
        free(file_extension);
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "%s FILE_EXTENSION_ERROR: profile must have a \".profile\" file extension.\n", X_ERROR);
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1 );
        strcpy( instruction->response_array[ instruction->response_store_index ], response);          // copy message into return string
        ++instruction->response_store_index;
        return;
    }
    free(file_extension);   // free dynamic memory

    // Get list of files in two directories where profiles are stored
    char** SD_profiles = Shell_List_Files(SD_PROFILE_LOCATION); // get profiles in this directory location
    char** USB_profiles = Shell_List_Files(USB_PROFILE_DIR);    // get profiles in this directory location

    // Create String array to store search results
    char** search_results;
    search_results = (char**)malloc( sizeof(char*) * 20 ); // allocate memory for max expected number of results
    for(int i = 0; i<20; ++i)
        search_results[i] = NULL;     // makes freeing memory easier, just check if its null before freeing the mem location
    int search_result_index = 0;    // local index variable to keep track of where to store strings in the response array

    // create string to store fully qualified file path
    char search_result_filepath[ 100 ];
    char SD_path_prefix[ strlen(SD_profiles[0])+1 ];
    strcpy( SD_path_prefix, SD_profiles[0]);

    int SD_index = 1;   // keep track of search results from micro SD card, starting with second string ( SD_profiles[1] ) in the array. SD_profiles[0] is the path prefix
    while ( SD_profiles[ SD_index ] )
    {
        strcpy( search_result_filepath, SD_path_prefix);
        strcat(search_result_filepath, "/");
        strcat( search_result_filepath, SD_profiles[ SD_index ] );
        if( String_Contains( search_result_filepath, selected_profile ) )    // if the target profile argument is found matching the full filepath
        {
            search_results[ search_result_index ] = (char*)malloc( sizeof(char*) * strlen(search_result_filepath) +2 ); // allocate memory for search result including filepath
            strcpy( search_results[ search_result_index ], search_result_filepath);
            ++search_result_index;
        }
        ++SD_index;
    }
    Free_String_Array_Memory(SD_profiles);

    char USB_path_prefix[ strlen(USB_profiles[0])+1 ];
    strcpy( USB_path_prefix, USB_profiles[0]);

    int USB_index = 1;   // keep track of search results from USB flash drive
    while ( USB_profiles[ USB_index ] )
    {
        strcpy( search_result_filepath, USB_path_prefix);
        strcat(search_result_filepath, "/");
        strcat( search_result_filepath, USB_profiles[ USB_index ] );

        if( String_Contains( search_result_filepath, selected_profile ) )    // if the target profile argument is found matching the full filepath
        {
            search_results[ search_result_index ] = (char*)malloc( sizeof(char*) * strlen(search_result_filepath) +2 ); // allocate memory for search result including filepath
            strcpy( search_results[ search_result_index ], search_result_filepath);
            ++search_result_index;
        }
        ++USB_index;
    }
    Free_String_Array_Memory(USB_profiles);

    if( search_result_index == 0)     // if no results, print error message to use ?profiles to check available profiles
    {
        int error_msg_length = strlen("NOT_FOUND_ERROR: no profiles found matching target \"\"") + strlen(selected_profile) + 4;
        char error_msg[ error_msg_length];
        Erase_String_Contents( error_msg);
        sprintf(error_msg, "%s NOT_FOUND_ERROR: no profiles found matching target \"%s\"", X_ERROR, selected_profile);

        int suggestion_msg_length = strlen("View available profiles with  \"?\" query") + strlen(selected_profile) + 2;
        char suggestion_msg[ suggestion_msg_length];
        Erase_String_Contents( suggestion_msg);
        sprintf(suggestion_msg, "View available profiles with  \"?\" query");

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(error_msg) +2 ); // allocate memory for error msg
        strcpy( instruction->response_array[ instruction->response_store_index ], error_msg);          // copy message into return string
        ++instruction->response_store_index;

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(suggestion_msg) +2 ); // allocate memory for error msg
        strcpy( instruction->response_array[ instruction->response_store_index ], suggestion_msg);          // copy message into return string
        ++instruction->response_store_index;
    }
    search_results[ search_result_index ] = NULL;   // null terminate the search results

    if( search_result_index > 1)  // if there is more than one matching file, print a message & the matching files
    {
        int info_msg_length = strlen("\u25B0INFO: multiple files found matching target \"\"") + strlen(selected_profile) + 2;
        char info_msg_1[ info_msg_length];
        sprintf(info_msg_1, "\u25B0INFO: multiple files found matching target \"%s\".", selected_profile);

        info_msg_length = strlen("\u25B0Matches below. Please specify using fully qualified filepath.") + strlen(selected_profile) + 2;
        char info_msg_2[ info_msg_length];
        sprintf(info_msg_2, "\u25B0Matches below. Please specify using fully qualified filepath.");

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(info_msg_1) +2 ); // allocate memory for error msg
        strcpy( instruction->response_array[ instruction->response_store_index ], info_msg_1);          // copy message into return string
        ++instruction->response_store_index;

        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(info_msg_2) +2 ); // allocate memory for error msg
        strcpy( instruction->response_array[ instruction->response_store_index ], info_msg_2);          // copy message into return string
        ++instruction->response_store_index;

        for(int i=0; i<search_result_index; ++i)   // copy search results here into response
        {
            instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen( search_results[i] ) +2 ); // allocate memory for result
            strcpy(instruction->response_array[ instruction->response_store_index ], "\t");
            strcat( instruction->response_array[ instruction->response_store_index ], search_results[i]);          // copy result into return string
            ++instruction->response_store_index;
        }
    }

    if( search_result_index == 1)  // if exactly one result, parse to verify it is valid
    {
        char selected_profile_filepath[ strlen(search_results[0]) +1];
        strcpy(selected_profile_filepath, search_results[0]);
        Test.profile = Parse_Profile(selected_profile_filepath);
        // check error messages
        //Print_Profile( Test.profile );
        // add to response

    }
    Free_String_Array_Memory(search_results);
    instruction->response_array[ instruction->response_store_index ] = NULL;
  //Parse_Profile("./Firmware/Profiles/lifetime_test.profile");
}


/////-----------------------------------------------------------------------------------------------------
// Helper functions
////-------------------------------------------------------------------------------------------------------


void Action_Relay_ON()
{
  printf(COLOR_BOLD_GREEN "\n     \u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511\n");
  printf("     \u2502  ---RELAY ON---   \u2502\n");
  printf(COLOR_BOLD_GREEN "     \u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519\n" COLOR_RESET);
	bcm2835_gpio_write(RELAY_RESET, LOW); 		// verifies other latching coil isnt being driven
  delayMicroseconds(100);
	bcm2835_gpio_write(RELAY_SET, HIGH);
	delayMicroseconds(PULSE_ON);
	bcm2835_gpio_write(RELAY_SET, LOW);
}

void Action_Relay_OFF()
{
  printf(COLOR_RED "     \u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511\n");
  printf("     \u2502  ---RELAY OFF---  \u2502\n");
  printf(COLOR_RED "     \u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519\n" COLOR_RESET);
  delayMicroseconds(10);
	bcm2835_gpio_write(RELAY_SET, LOW); 		// verifies other latching coil isnt being driven
  delayMicroseconds(100);
	bcm2835_gpio_write(RELAY_RESET, HIGH);
	delayMicroseconds(PULSE_ON);
	bcm2835_gpio_write(RELAY_RESET, LOW);
}

void Toggle_Current_Source()
{
	if(PRINT_DEBUG) printf("--Toggle_Current_Source--\n");
  delayMicroseconds(10);

  ++CURRENT_SOURCE_SELECT;
  if(CURRENT_SOURCE_SELECT > 1) CURRENT_SOURCE_SELECT = 0;

  if(CURRENT_SOURCE_SELECT) bcm2835_gpio_write(SW_CTRL_100uA, HIGH);

  else bcm2835_gpio_write(SW_CTRL_100uA, LOW);

  printf("\tchanged pin %d to %d\n", SW_CTRL_100uA, CURRENT_SOURCE_SELECT);
}

Relay_State Get_Relay_State()
{
    if(PRINT_DEBUG) printf("\t Get_Relay_State\n");

    pthread_mutex_lock(&METRICS_LOOP_LOCK);
        printf("got the lock\n");
        ADC0_Set_MUX_Cooler_Volts();
        ADC0_Throw_Away_Reading();
        ADC0_Cooler_Volts.num_samples = 0;
        for(int i = 0; i<NUM_MEAS_SAMPLES; ++i)
        {
            ADC0_Read_Cooler_Volts();   // read CCC volts & average the results
        }
    pthread_mutex_unlock(&METRICS_LOOP_LOCK);

    //printf("count sum: %d\n", Cooler_Volts.count_sum);
    //printf("count samples: %d\n", Cooler_Volts.num_samples);

    int AVG_Cooler_V_counts  = ADC0_Cooler_Volts.count_sum / ADC0_Cooler_Volts.num_samples;
        //printf("AVG count: %d\n", AVG_Cooler_V_counts);
    double Average_Cooler_Volts = Cooler_Counts_to_Volts( AVG_Cooler_V_counts );
  //printf("AVG volts: %f\n", Average_Cooler_Volts);
    if( Average_Cooler_Volts >= 2.0 ) // greater than 2.0 volts & conclude relay is on (though load may be shorted)
        return RELAY_ON;

    return RELAY_OFF;
}

char* Get_Relay_State_String()
{
  char* relay_buffer = malloc( sizeof(char*) * 5 );

  if( Test.relay_state == RELAY_ON)
      strcpy(relay_buffer, "ON");
  else
      strcpy(relay_buffer, "OFF");
  return relay_buffer;
}
/////////////---------------------------------------------------------------////////////////////////

// Helper Functions



void Wait_Enter_Key()
{
	int key_pressed;
	bool Enter_Pressed = false;
  printf("wait enter\n");
	while(!Enter_Pressed)
	{
			key_pressed = getchar();
			if((key_pressed == ASCII_NEW_LINE) || (key_pressed == ASCII_CARRIAGE_RETURN))
			{ Enter_Pressed = true; }
			if(key_pressed == ASCII_QUIT)
			{ Enter_Pressed = true; }
	}
	return;
}






#endif
