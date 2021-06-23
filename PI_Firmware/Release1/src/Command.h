#ifndef COMMAND_H
#define COMMAND_H

#define MAX_RESPONSE_LENGTH     1000
#define MAX_INSTRUCTION_LENGTH  50
#define MAX_RECEIVE_LENGTH      150
#define MAX_ARGUMENT_LENGTH     40
#define MAX_INSTRUCTIONS        10
#define MAX_NUM_INSTRUCTIONS    50    // max number of instructions stored, waiting to be processed by execution engine

// "Command.h" is used for parsing commands received on the socket into the approriate function to execute


// List of different data types which may be arguments to a command OR query
typedef enum Argument_t
{
    NONE,
    DOUBLE,
    STRING,
    TIME_STRING,
    FILENAME,
    INT,
} ARGUMENT_TYPE;

// String List to match against strings received on socket
const char* STR_COMMAND_LIST[] = {    "LOAD_ON", "LOAD_OFF", "", "RELAY_ON",
                                  "RELAY_OFF", "SET_LOAD", "START_TEST", "STOP_TEST", "SET_MANUAL_MODE",
                                  "SET_PROFILE_MODE", "SELFTEST", "SET_TIME", "SEND_LOG", "SEND_ALL_LOGS",
                                  "SET_COMPRESSOR_ID", "SET_DISPLACER_ID", "SET_DDCA_ID", "SET_CCC_ID",
                                  "USE_PROFILE", "CMD_NOT_FOUND" };

// string list to print as help
const char* COMMAND_HELP_LIST[] = {    ">LOAD_ON", ">LOAD_OFF", ">  (print this list)", ">RELAY_ON",
                                  ">RELAY_OFF", ">SET_LOAD [integer in milliWatts]", ">START_TEST", ">STOP_TEST", ">SET_MANUAL_MODE",
                                  ">SET_PROFILE_MODE", ">SELFTEST", ">SET_TIME [MM/dd/YYYY_HH.mm.ss] (HH is 24 hour based)", ">SEND_LOG", ">SEND_ALL_LOGS",
                                  ">SET_COMPRESSOR_ID [string]", ">SET_DISPLACER_ID [string]", ">SET_DDCA_ID [string]", ">SET_CCC_ID [string]",
                                  ">USE_PROFILE [filename]" };

typedef enum Command_t{           LOAD_ON, LOAD_OFF, PRINT_COMMAND_LIST, TURN_RELAY_ON,
                                  TURN_RELAY_OFF, SET_LOAD, START_TEST, STOP_TEST, SET_MANUAL_MODE,
                                  SET_PROFILE_MODE, SELFTEST, SET_TIME, SEND_LOG, SEND_ALL_LOGS,
                                  SET_COMPRESSOR_ID, SET_DISPLACER_ID, SET_DDCA_ID, SET_CCC_ID,
                                  USE_PROFILE, CMD_NOT_FOUND } COMMAND;

COMMAND ENUM_COMMAND_LIST[] = {   LOAD_ON, LOAD_OFF, PRINT_COMMAND_LIST, TURN_RELAY_ON,
                                  TURN_RELAY_OFF, SET_LOAD, START_TEST, STOP_TEST, SET_MANUAL_MODE,
                                  SET_PROFILE_MODE, SELFTEST, SET_TIME, SEND_LOG, SEND_ALL_LOGS,
                                  SET_COMPRESSOR_ID, SET_DISPLACER_ID, SET_DDCA_ID, SET_CCC_ID,
                                  USE_PROFILE, CMD_NOT_FOUND };

// Index matched list of arguments required for a given command
// This list helps determine if a given string command received on the
// socket is paired with the correct argument
// For example:
//      COMMAND_LIST[ 0 ] == LOAD_ON      Command_Args[ 0 ] == NONE
//      therefore the LOAD_ON command needs no arguments
//
//      COMMAND_LIST[ 5 ] == SET_LOAD      Command_Args[ 0 ] == DOUBLE
//      the SET_LOAD command referred to by index 5 requires argument of type double
ARGUMENT_TYPE Command_Args[] = {  NONE, NONE, NONE, NONE,
                                  NONE, DOUBLE, NONE, NONE, NONE,
                                  NONE, NONE, TIME_STRING, STRING, NONE,
                                  STRING, STRING, STRING, STRING,
                                  FILENAME, NONE };

//-------------------------------------------------------------------------------//
// string List to match against strings received on socket
const char* STR_QUERY_LIST[] = {  "HELP", "LOGS", "METRICS", "", "PROFILES", "PROFILE", "TIME",
                                  "SHOW", "STATUS", "MODE", "NOT_A_QUERY" };

const char* QUERY_HELP_LIST[] = {  "?HELP", "?LOGS", "?METRICS", "?  (print this list)", "?PROFILES", "?PROFILE", "?TIME",
                                  "?SHOW [filename]", "?STATUS", "?MODE" };

typedef enum Query_t{             HELP, LOGS, METRICS, PRINT_QUERY_LIST, PROFILES, PROFILE, TIME,
                                  SHOW, STATUS, MODE, NOT_A_QUERY } QUERY;

QUERY ENUM_QUERY_LIST[] = {       HELP, LOGS, METRICS, PRINT_QUERY_LIST, PROFILES, PROFILE, TIME,
                                  SHOW, STATUS, MODE, NOT_A_QUERY };

ARGUMENT_TYPE Query_Args[] = {    NONE, NONE, NONE, NONE,
                                  NONE, NONE, NONE, FILENAME,
                                  NONE, NONE, NONE };

//-------------------------------------------------------------------------------//
// string List to match against strings received on socket, used in calibration mode
const char* STR_CAL_FUNCTION_LIST[] = {  "CAL_ON", "CAL_OFF", "READ_ADC", "SET_DAC_COUNT", "SET_DAC_MW", "SET_DAC_MA", "LOOP1", "LOOP2", "CAL_RELAY_ON", "CAL_RELAY_OFF",
                                         "CURRENT_CALIBRATION", "ADC_LOAD_CALIBRATION", "VOLT_CALIBRATION", "ADC_DIODE_CALIBRATION", "POWER_CALIBRATION", "MODE",
                                      };

const char* CAL_HELP_LIST[] =         {  "CAL_ON  (enable calibration mode)", "CAL OFF   (exit calibration mode)", "READ_ADC", "SET_DAC_COUNT  (0-65536)",
                                          "SET_DAC_mW  (0-500)", "SET_DAC_MA (0-70)", "LOOP1", "LOOP2", "CAL_RELAY_ON", "CAL_RELAY_OFF", "CURRENT_CALIBRATION",
                                          "ADC_LOAD_CALIBRATION", "VOLT_CALIBRATION", "ADC_DIODE_CALIBRATION", "POWER_CALIBRATION", "MODE" };

typedef enum Cal_Function_t{       CAL_ON, CAL_OFF, READ_ADC, SET_DAC_COUNT, SET_DAC_MW, SET_DAC_MA, LOOP1, LOOP2, CAL_RELAY_ON, CAL_RELAY_OFF,
                                   CURRENT_CAL, LOAD_CAL, VOLT_CAL, DIODE_CAL, POWER_CAL, _MODE, NO_MATCH,   } CAL_FUNCTION;

CAL_FUNCTION ENUM_CAL_FUNCTIONS[] = {   CAL_ON, CAL_OFF, READ_ADC, SET_DAC_COUNT, SET_DAC_MW, SET_DAC_MA, LOOP1, LOOP2, CAL_RELAY_ON, CAL_RELAY_OFF,
                                        CURRENT_CAL, LOAD_CAL, VOLT_CAL, DIODE_CAL, POWER_CAL, _MODE, NO_MATCH,};

ARGUMENT_TYPE Cal_Function_Args[] = {    NONE, NONE, INT, INT, DOUBLE, DOUBLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE };


// something received on the socket interface can be grouped into one of these categories
typedef enum Instruction_type
{
    command_t,
    query_t,
    syntax_error_t,
    help_t,
    debug_t,
    verbose_t,
    cal_state_change_t,
    cal_function_t,
    cal_state_query_t,
} instruction_t;

// data structure for instructions parsed from the socket interface
// instruction_executed refers to whether or no the execution engine has processed the command and populated the response field
// The enumeration instruction refers to the specific command or query to be processed
// response is the string to send back to the client socket
typedef struct instruction_info_t
{
    instruction_t instruction_type;                 // either command, query, help, or error
    int  index_of_instruction;                      // after parsing, holds index of specific instruction in COMMAND_LIST[] or QUERY_LIST[]
    char socket_receive[ MAX_RECEIVE_LENGTH ];      // entire string received on socket
    char instruction_str[ MAX_INSTRUCTION_LENGTH ];
    char argument_str[ MAX_ARGUMENT_LENGTH ];
    char response_str[ MAX_RESPONSE_LENGTH ];
    char**  response_array;
    char**  debug_array;
    int response_store_index;
    int debug_store_index;
    QUERY this_query;
    COMMAND this_command;
    CAL_FUNCTION this_function;
}Instruction_Info;

Instruction_Info* Socket_Instruction; // Array of structs, this is the data structure containing the list of commands received on socket

#endif
