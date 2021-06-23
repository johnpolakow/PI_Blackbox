
#ifndef STRUCT_DEFS
#define STRUCT_DEFS

#define MAX_LOOP_SAMPLES 				150
#define ID_STRING_SIZE					30
#define TIMESTAMP_STRING_SIZE 	        50
#define FILEPATH_LENGTH					100
#define DISK_USE_LENGTH					80


typedef struct data_point
{
	char timestamp[50];       // format: 16:25:13 4/22/2020
    char date[25];               // format: 4/22/2020
    char elapsed_time[50];       // format: 5hr 36min 07sec
	long long elapsed_secs;  // total elapsed seconds since test began
    char relay_state[5];     // ON or OFF

    double Cooler_V;
	double Cooler_V_raw;
    double ADC0_Cooler_A;
	double ADC0_Cooler_A_raw;
	double ADC1_Cooler_A;
	double ADC1_Cooler_A_raw;
	double Cooler_A;
    double Cooler_W;
    double diode_volts;
	double diode_volts_raw;
	double ADC1_diode_volts;
	double diode_temp;
	double Heat_Load_V;
	double Heat_Load_V_raw;
	double Heat_Load_mA;
	double Heat_Load_mA_raw;
	double Heat_Load_mW;
    double thermocouple1_temp;
    double thermocouple2_temp;
    double thermocouple3_temp;
    double pcb_temp;
}data_point;

data_point Save_Data[ MAX_LOOP_SAMPLES ];
int save_index = 0;

typedef enum profile_command_t
{
    PROFILE_START_LOG,
    PROFILE_RELAY_ON,
    PROFILE_RELAY_OFF,
    PROFILE_SET_LOAD,
    PROFILE_LOAD_ON,
    PROFILE_LOAD_OFF,
    PROFILE_STOP_TEST,
    PROFILE_COMMAND_UNKNOWN,
} profile_command_t;

typedef struct profile_command
{
    profile_command_t profile_cmd;
    char* time_execute_str;
    long execute_time_seconds;
    double load_setting_mW;
} profile_command;

const char* PROFILE_COMMAND_LIST[] = { "START_LOG", "RELAY_ON", "RELAY_OFF", "SET_LOAD",
                                   "LOAD_ON", "LOAD_OFF", "STOP_TEST" };
typedef enum profile_t
{
    LIFETIME,
    PERFORMANCE,
    SADA,
    BURNIN,
    CUSTOM,
    PROFILE_NO_MATCH,
} profile_t;

typedef enum profile_key_t
{
    PROFILE_DECLARATION,
    PROFILE_TYPE,
    PROFILE_NAME,
    PROFILE_DESCRIPTION,
    PROFILE_KEY_UNKNOWN,
} profile_key_t;

typedef struct profile_object
{
    char* filename;
    profile_t type;
    char* name;
    char* description;
    profile_command** cmd_list;
    int store_index;
		long long run_time;

    char** parse_response;
    bool parse_success;
    int response_index;
} profile_object;

typedef enum test_t
{
    MANUAL_CONTROL,
    PROFILE_CONTROL,
} Test_Mode;

typedef enum relay_st
{
    RELAY_ON,
    RELAY_OFF,
} Relay_State;

typedef enum read_sequence
{
    HEAT_LOAD_ON,
    HEAT_LOAD_OFF,
		ADC_CURRENT_CALIBRATION,
		ADC_LOAD_CALIBRATION,
		ADC_VOLT_CALIBRATION,
		ADC_DIODE_CALIBRATION,
		ADC_POWER_CALIBRATION,
} READ_SEQ;


typedef struct board_state
{
    Test_Mode execution_mode;
    char execution_mode_str[20];
    Relay_State relay_state;
    READ_SEQ load_state;
    double load_setting_mW;
    profile_object* profile;

    bool  LOG_DATA;
    bool  is_running;

    char  is_running_str[10];
    char  hostname[30];
    char  eth0_IP[25];
    char  wlan0_IP[25];
		char  timestamp[TIMESTAMP_STRING_SIZE];
		char start_time[TIMESTAMP_STRING_SIZE];
    char  USB_filepath[FILEPATH_LENGTH];
    char  profile_name[FILEPATH_LENGTH];
    char  log_filename[FILEPATH_LENGTH];
    char  CCC_ID[ID_STRING_SIZE];
    char  CPU_temperature[10];
    char compressor_ID[ID_STRING_SIZE];
    char displacer_ID[ID_STRING_SIZE];
    char DDCA_ID[ID_STRING_SIZE];
    char USB_flash_disk_use[DISK_USE_LENGTH];
    char SD_card_disk_use[DISK_USE_LENGTH];
} board_state;


struct Disk_Usage{
		char kernel_location[30];
    char filesystem[20];
    char total_space[10];
		char used_space[10];
    char free_space[10];
    char mount_location[100];
    char percent_filled[20];
    char percent_of_total[20];
    int percent_disk_filled;
    bool exists;
};
#endif
