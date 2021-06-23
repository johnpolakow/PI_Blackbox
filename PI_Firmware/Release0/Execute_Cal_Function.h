
#ifndef EXECUTE_CAL_FUNCTION
#define EXECUTE_CAL_FUNCTION

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

#include "Read_Metrics.h"
#include "Receive_Socket.h"
#include "DAC.h"

extern READ_SEQ Read_Sequence;


extern void Clear_Loop();   // defined in Read_Metrics.h
extern pthread_mutex_t METRICS_LOOP_LOCK;
extern void Change_Calibration_State(Instruction_Info* instruction);        // in Receive_Socket.h

void Set_Load(char* double_string, char* result);
void Wait_Enter_Key();
void Read_ADCs(Instruction_Info* command);
void Set_Loop1(Instruction_Info* command);
void Set_Loop2(Instruction_Info* command);


void CAL_Toggle_Current_Source();
void Cal_Help_Response(Instruction_Info* instruction);
void Set_DAC_Count(Instruction_Info* instruction);
void Set_DAC_milliWatts(Instruction_Info* instruction);
void CAL_Relay_ON();
void CAL_Relay_OFF();
void CAL_Toggle_Current_Source();
void Set_Current_Calibration(Instruction_Info* instruction);
void Set_ADC0_Cooler_Volt_Cal(Instruction_Info* instruction);
void Set_Diode_Volt_Cal(Instruction_Info* instruction);
void Set_Volt_Calibration(Instruction_Info* instruction);
void Set_Current_Calibration(Instruction_Info* instruction);
void Set_Diode_Volt_Cal(Instruction_Info* instruction);
void Set_DAC_milliAmps(Instruction_Info* instruction);
void Set_Power_Cal(Instruction_Info* instruction);
void Get_Curr_Mode(Instruction_Info* instruction);


// precursor to this command, command has been processed and command index stored
void Execute_Cal_Function(Instruction_Info* command)
{
    switch(command->this_function)
    {
        case CAL_ON:
            Change_Calibration_State(command);
            break;
        case CAL_OFF:
            Change_Calibration_State(command);
            break;
        case READ_ADC:
            Read_ADCs(command);
            break;
        case CAL_RELAY_ON:
            CAL_Relay_ON(command);
            break;

        case CAL_RELAY_OFF:
            CAL_Relay_OFF(command);
            break;

        case SET_DAC_COUNT:
            Set_DAC_Count(command);
            break;
        case SET_DAC_MW:
            Set_DAC_milliWatts(command);
            break;
        case SET_DAC_MA:
            Set_DAC_milliAmps(command);
            break;
        case LOOP1:
            Set_Loop1(command);
            break;
        case LOOP2:
            Set_Loop2(command);
            break;

        case NO_MATCH:
            Cal_Help_Response(command);
            break;

        case CURRENT_CAL:
            Set_Current_Calibration(command);
            break;

        case VOLT_CAL:
            Set_Volt_Calibration(command);
            break;

        case DIODE_CAL:
            Set_Diode_Volt_Cal(command);
            break;
        case POWER_CAL:
            Set_Power_Cal(command);
            break;
        case _MODE:
            Get_Curr_Mode(command);
            break;
        default:  // default case
            break;
    }
}

void Cal_Help_Response(Instruction_Info* instruction)
{
    int help_index = instruction->response_store_index;

    instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * ( strlen("List of valid Cal Functions:") +1 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[help_index], "List of valid Cal Functions:");
    instruction->response_array[help_index][strlen("List of valid Cal Functions:")] = '\0';
    ++help_index;

    int list_length = ARRAY_SIZE(CAL_HELP_LIST);
    int Cal_list_index = 0;
    while ( (Cal_list_index < list_length) && (CAL_HELP_LIST[ Cal_list_index ] != NULL) )     // Read the output a line at a time - output it.
    {
        instruction->response_array[help_index] = (char*)malloc( (sizeof(char) * ( strlen( CAL_HELP_LIST[Cal_list_index])) + strlen("\t") +1 ) ); // allocate memory for string in response
        strcpy(instruction->response_array[help_index], "\t");
        strcat(instruction->response_array[help_index], CAL_HELP_LIST[Cal_list_index]);
        ++help_index;
        ++Cal_list_index;
        if(Cal_list_index >= list_length)
            break;
    }

    instruction->response_array[help_index] = (char*)malloc(sizeof(char*) * ( strlen("To exit Cal mode enter command:\t \"CAL OFF\" \n") +1 ) ); // allocate memory for string in "response"
    strcpy(instruction->response_array[help_index], "To exit Cal mode enter command:\t \"CAL OFF\" \n");
    ++help_index;

    instruction->response_array[help_index] = NULL;
    instruction->response_store_index = help_index;
}


void Read_ADCs(Instruction_Info* instruction)
{
  int num_ADC_readings = Parse_Int( instruction->argument_str);

  char send_buffer[600];
  Erase_String_Contents(send_buffer);

  char ADC0_CoolV[30];
  char ADC0_CoolA[50];
  char DiodeV[50];
  char ADC1_CoolA[50];
  char ADC1_LoadV[50];
  char ADC1_LoadA[50];

  char ADC0_CoolV_raw[30];
  char ADC0_CoolA_raw[50];
  char DiodeV_raw[50];
  char ADC1_CoolA_raw[50];
  char ADC1_LoadV_raw[50];
  char ADC1_LoadA_raw[50];

  char timestamp_buffer[50];
  char timestamp_str[50];

  int save_index_current_value = save_index;

  for( int samples = 0; samples < num_ADC_readings; ++samples)
  {
      while(save_index_current_value == save_index)  // wait until a new reading is available
      {
          if( num_ADC_readings > 1)
              delayMicroseconds(5000);
      }

      save_index_current_value = save_index; // update which sample we are capturing and sending out over socket

      strcpy(timestamp_str, Save_Data[ save_index ].timestamp);

      if( (Read_Sequence == HEAT_LOAD_ON) || (Read_Sequence == HEAT_LOAD_OFF) )   // Normal Modes
      {
          sprintf(ADC0_CoolV, "ADC0_CoolV:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V );
          sprintf(ADC0_CoolA, "ADC0_CoolA:\t%2.5fV\n", Save_Data[ save_index ].ADC0_Cooler_A );
          sprintf(ADC1_CoolA, "ADC1_CoolA:\t%2.5fV\n", Save_Data[ save_index ].ADC1_Cooler_A );
          sprintf(DiodeV,     "ADC0_DiodeV:\t%2.5fV\n", Save_Data[ save_index ].diode_volts);
          sprintf(ADC1_LoadV, "ADC1_LoadV:\t%2.5fV\n", Save_Data[ save_index ].Heat_Load_V );
          sprintf(ADC1_LoadA, "ADC1_LoadmA:\t%2.5fmA\n", Save_Data[ save_index ].Heat_Load_mA );

          sprintf(ADC0_CoolV_raw, "ADC0_CoolV_Raw:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V_raw );
          sprintf(ADC0_CoolA_raw, "ADC0_CoolA_Raw:\t%2.5fV\n", Save_Data[ save_index ].ADC0_Cooler_A_raw );
          sprintf(ADC1_CoolA_raw, "ADC1_CoolA_Raw:\t%2.5fV\n", Save_Data[ save_index ].ADC1_Cooler_A_raw );
          sprintf(ADC1_LoadV_raw, "ADC1_LoadV_Raw:\t%2.5fV\n", Save_Data[ save_index ].Heat_Load_V_raw );
          sprintf(ADC1_LoadA_raw, "ADC1_LoadmA_Raw:\t%2.5fmA\n", Save_Data[ save_index ].Heat_Load_mA_raw );

          sprintf(send_buffer, "Sample#: %d\n%s%s%s%s%s%s%s%s%s%s%s%s\n", save_index, ADC0_CoolV, ADC0_CoolV_raw, ADC0_CoolA, ADC0_CoolA_raw, ADC1_CoolA, ADC1_CoolA_raw, DiodeV, ADC1_LoadV, ADC1_LoadV_raw, ADC1_LoadA, ADC1_LoadA_raw, timestamp_str);
      }
      else if( (Read_Sequence == ADC_CURRENT_CALIBRATION ) )      // reads only the current values
      {
          sprintf(ADC0_CoolV, "ADC0_CoolV:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V );
          sprintf(ADC0_CoolA, "ADC0_CoolA:\t%2.5fV\n", Save_Data[ save_index ].ADC0_Cooler_A );
          sprintf(ADC1_CoolA, "ADC1_CoolA:\t%2.5fV\n", Save_Data[ save_index ].ADC1_Cooler_A );
          sprintf(DiodeV,     "ADC1_DiodeV:\t%2.5fV\n", Save_Data[ save_index ].ADC1_diode_volts);

          sprintf(ADC0_CoolV_raw, "ADC0_CoolV_Raw:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V_raw );
          sprintf(ADC0_CoolA_raw, "ADC0_CoolA_Raw:\t%2.5fV\n", Save_Data[ save_index ].ADC0_Cooler_A_raw );
          sprintf(ADC1_CoolA_raw, "ADC1_CoolA_Raw:\t%2.5fV\n", Save_Data[ save_index ].ADC1_Cooler_A_raw );

          sprintf(send_buffer, "Sample#: %d\n%s%s%s%s%s%s%s%s\n", save_index, ADC0_CoolV, ADC0_CoolV_raw, ADC0_CoolA, ADC0_CoolA_raw, ADC1_CoolA, ADC1_CoolA_raw, DiodeV, timestamp_str);
      }
      else if( (Read_Sequence == ADC_VOLT_CALIBRATION ) )     // read only cooler volt values, which are only on ADC0
      {
          sprintf(ADC0_CoolV, "ADC0_CoolV:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V );
          sprintf(ADC0_CoolV_raw, "ADC0_CoolV_Raw:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V_raw );
          sprintf(DiodeV,     "ADC0_DiodeV:\t%2.5fV\n", Save_Data[ save_index ].diode_volts);
          sprintf(send_buffer, "Sample#: %d\n%s%s%s%s\n", save_index, ADC0_CoolV, ADC0_CoolV_raw, DiodeV, timestamp_str);
      }
      else if( (Read_Sequence == ADC_POWER_CALIBRATION ) )    // read only cooler volts on one ADC, cooler amps on the other ADC
      {
          sprintf(ADC0_CoolV, "ADC0_CoolV:\t%2.5fV\n", Save_Data[ save_index ].Cooler_V );
          sprintf(DiodeV,     "ADC0_DiodeV:\t%2.5fV\n", Save_Data[ save_index ].diode_volts);
          sprintf(ADC1_CoolA, "ADC1_CoolA:\t%2.5fV\n", Save_Data[ save_index ].ADC1_Cooler_A );
          sprintf(send_buffer, "Sample#: %d\n%s%s%s%s\n", save_index, ADC0_CoolV, DiodeV, ADC1_CoolA, timestamp_str);
      }

      instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(send_buffer) + 1);
      sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", send_buffer );
      ++instruction-> response_store_index;
  }
}


void Set_Loop1(Instruction_Info* instruction)
{
    Read_Sequence = HEAT_LOAD_ON;   // read sequence for ADCs

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("Read Metrics sequence has been set to HEAT_LOAD_ON") + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "Read Metrics sequence has been set to HEAT_LOAD_ON" );
    ++instruction->response_store_index;
}

void Set_Loop2(Instruction_Info* instruction)
{
    Read_Sequence = HEAT_LOAD_OFF;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("Read Metrics sequence has been set to HEAT_LOAD_OFF") + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "Read Metrics sequence has been set to HEAT_LOAD_OFF" );
    ++instruction->response_store_index;
}


void Set_DAC_Count(Instruction_Info* instruction)
{
      // change mux to heat load on
    Read_Sequence = HEAT_LOAD_ON;    // changes which function pointer array to use when reading ADC0 & ADC1. (changes to reading load values as well)
    int DAC_count_setting = Parse_Int( instruction->argument_str);
    DAC_Set_Count( channel_A, DAC_count_setting );

    char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
    char line2[] = "\u2502  ---SET DAC COUNT ---  \u2502";
    char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";
    char line4[50];
    sprintf(line4, "Dac set counts: %d", DAC_count_setting);

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line4) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line4 );
    ++instruction->response_store_index;
}

void Set_DAC_milliWatts(Instruction_Info* instruction)
{
      // change mux to heat load on
    Read_Sequence = HEAT_LOAD_ON;    // changes which function pointer array to use when reading ADC0 & ADC1. (changes to reading load values as well)
    double DAC_milliWatts = Parse_Double( instruction->argument_str);
    int DAC_counts = Load_milliWatts_to_DAC_Counts( DAC_milliWatts );
    DAC_Set_Count( channel_A, DAC_counts );

    char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
    char line2[] = "\u2502  ---SET DAC milliWatts ---  \u2502";
    char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";
    char line4[50];
    sprintf(line4, "Dac milliWatts: %f, counts: %d", DAC_milliWatts, DAC_counts);

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line4) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line4 );
    ++instruction->response_store_index;
}

void Set_Current_Calibration(Instruction_Info* instruction)
{
    Read_Sequence = ADC_CURRENT_CALIBRATION;
    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("Setting current cal mode. Will read only COOL_PWR_I, \n\tADC1_diodeV, ADC0_CoolV, on both ADC0 & ADC1") + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "Setting current cal mode. Will read only COOL_PWR_I, \n\tADC1_diodeV, ADC0_CoolV, on both ADC0 & ADC1" );
    ++instruction->response_store_index;
}

void Set_Volt_Calibration(Instruction_Info* instruction)
{
    Read_Sequence = ADC_VOLT_CALIBRATION;
    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("Setting ADC0 volt cal mode. Will read only \n\tCOOL_PWR_V on ADC0") + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "Setting ADC0 volt cal mode. \n\tWill read only COOL_PWR_V on ADC0" );
    ++instruction->response_store_index;
}

void Set_Diode_Volt_Cal(Instruction_Info* instruction)
{
    Read_Sequence = ADC_DIODE_CALIBRATION;
    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("Setting diode volt cal mode. \n\tWill read only TEMP_DIODE on ADC0 + ADC1") + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "Setting diode volt cal mode. \n\tWill read only TEMP_DIODE on ADC0 + ADC1" );
    ++instruction->response_store_index;
}

void Set_Power_Cal(Instruction_Info* instruction)
{
    Read_Sequence = ADC_POWER_CALIBRATION;
    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("Setting Power Calibration Test mode. \n") + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "Setting Power Calibration Test mode. \n" );
    ++instruction->response_store_index;
}

// Returns current blackbox mode of operation, either "STANDARD" or "CAL"
void Get_Curr_Mode(Instruction_Info* instruction)
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

void Set_DAC_milliAmps(Instruction_Info* instruction)
{
      // change mux to heat load on
    Read_Sequence = HEAT_LOAD_ON;    // changes which function pointer array to use when reading ADC0 & ADC1. (changes to reading load values as well)
    double DAC_mA_setting = Parse_Double( instruction->argument_str);
    int DAC_counts = Load_milliAmps_to_Counts( DAC_mA_setting );
    DAC_Set_Count( channel_A, DAC_counts );

    char line1[] = "\u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511";
    char line2[] = "\u2502  ---SET DAC MILLIAMPS ---  \u2502";
    char line3[] = "\u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519";
    char line4[50];
    sprintf(line4, "Dac set mA: %f, string: %s, counts: %d", DAC_mA_setting, instruction->argument_str, DAC_counts);

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line1) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line1 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line2) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line2 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line3) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line3 );
    ++instruction->response_store_index;

    instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(line4) + 1);
    sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", line4 );
    ++instruction->response_store_index;
}


/////-----------------------------------------------------------------------------------------------------
// Helper functions
void CAL_Relay_ON(Instruction_Info* instruction)
{
  printf(COLOR_BOLD_GREEN "\n     \u250D\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2511\n");
  printf("     \u2502  ---RELAY ON---   \u2502\n");
  printf(COLOR_BOLD_GREEN "     \u2515\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2519\n" COLOR_RESET);
	bcm2835_gpio_write(RELAY_RESET, LOW); 		// verifies other latching coil isnt being driven
  delayMicroseconds(100);
	bcm2835_gpio_write(RELAY_SET, HIGH);
	delayMicroseconds(PULSE_ON);
	bcm2835_gpio_write(RELAY_SET, LOW);

  instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("CAL RELAY ON") + 1);
  sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "CAL_RELAY_ON" );
  ++instruction->response_store_index;
}

void CAL_Relay_OFF(Instruction_Info* instruction)
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

  instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("CAL RELAY OFF") + 1);
  sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "CAL_RELAY_OFF" );
  ++instruction->response_store_index;
}

void CAL_Toggle_Current_Source(Instruction_Info* instruction)
{
	if(PRINT_DEBUG) printf("--Toggle_Current_Source--\n");
  delayMicroseconds(10);

  ++CURRENT_SOURCE_SELECT;
  if(CURRENT_SOURCE_SELECT > 1) CURRENT_SOURCE_SELECT = 0;

  if(CURRENT_SOURCE_SELECT) bcm2835_gpio_write(SW_CTRL_100uA, HIGH);

  else bcm2835_gpio_write(SW_CTRL_100uA, LOW);

  instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen("TOGGLE 100uA") + 1);
  sprintf( instruction->response_array[ instruction-> response_store_index ], "%s", "TOGGLE 100uA" );
  ++instruction->response_store_index;
}



#endif
