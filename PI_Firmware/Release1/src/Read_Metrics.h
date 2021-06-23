#include "ADS1256.h"
#include <bcm2835.h>
#include "MAX31856.h"
#include "ADT7410.h"
#include "Macros.h"
#include "Struct_Defs.h"
#include "Timer_Helper.h"
#include "Interpolate_LUT.h"
#include "Save_File.h"
#include "temp_diode.h"


#ifndef READ_METRICS_H
#define READ_METRICS_H


extern float get_Temp_K(float diode_volts);
extern double Cooler_Watts_LUT(double volts, double amps);
extern double Diode_Temp_LUT( double diode_volts);
extern double Heat_Load_Watts_LUT( double volts, double amps);
extern void Write_Data_to_File(data_point Save[], int* index);

extern data_point Save_Data[ MAX_LOOP_SAMPLES ];
extern int save_index;
extern bool CAL_FUNCTIONS_ENABLED;

// Function pointer array. Each entry is a function in "ADS1256.h" or "MAX31856.h"
// This is a read sequence when Heat Load is ON
// Each function reads a different metric, or changes the on-chip multiplexer on the ADC
// LOOP1
static void (* const Function_Seq_Load_ON[])(void) =
{
    ADC0_Read_Temp_Diode, ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode,
    ADC0_Set_MUX_Cooler_Volts, ADC1_Read_Cooler_Amps, ADC0_Throw_Away_Reading,
    ADC1_Read_Cooler_Amps, ADC1_Set_MUX_Heat_Load_V, Read_Thermocouple_1,
    ADC0_Read_Cooler_Volts, ADC1_Throw_Away_Reading, ADC0_Read_Cooler_Volts,
    ADC1_Read_Heat_Load_V, ADC0_Read_Cooler_Volts, ADC1_Read_Heat_Load_V,
    ADC0_Read_Cooler_Volts, ADC0_Set_MUX_Cooler_Amps, ADC1_Read_Heat_Load_V,
    Read_Thermocouple_2, ADC0_Throw_Away_Reading, ADC1_Read_Heat_Load_V,
    ADC1_Set_MUX_Heat_Load_I, ADC0_Read_Cooler_Amps, ADC1_Throw_Away_Reading,
    ADC0_Read_Cooler_Amps, ADC1_Read_Heat_Load_I, ADC0_Read_Cooler_Amps,
    ADC1_Read_Heat_Load_I, ADC1_Set_MUX_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Throw_Away_Reading, ADC0_Read_Cooler_Amps, ADC0_Set_MUX_Temp_Diode,
    Read_Thermocouple_3, ADC0_Throw_Away_Reading, ADC1_Read_Cooler_Amps,
};

// Function pointer array. Each entry is a function in "ADS1256.h" or "MAX31856.h"
// This is a read sequence when Programmable Current Source (Heat_Load) is OFF
// Each function reads a different metric, or changes the on-chip multiplexer on the ADC
// LOOP2
static void (* const Function_Seq_Load_OFF[])(void) =
{
    ADC0_Read_Temp_Diode, ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode,
    ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode, ADC0_Set_MUX_Cooler_Volts,
    ADC1_Read_Cooler_Amps, Read_Thermocouple_1, ADC0_Throw_Away_Reading,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps, Read_Thermocouple_2,
    ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    Read_Thermocouple_3, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    ADC0_Read_Cooler_Volts, ADC0_Set_MUX_Temp_Diode, ADC1_Read_Cooler_Amps,
    ADC1_Set_MUX_Cooler_Amps, ADC0_Throw_Away_Reading, ADC1_Throw_Away_Reading,
};

// take as many current readings as possible
static void (* const Function_Seq_Current_Cal[])(void) =
{
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Amps,
    ADC0_Set_MUX_Cooler_Volts, ADC1_Set_MUX_Temp_Diode,
    ADC0_Throw_Away_Reading,  ADC1_Throw_Away_Reading,
    ADC0_Read_Cooler_Volts,   ADC1_Read_Temp_Diode,
    ADC0_Read_Cooler_Volts,   ADC1_Read_Temp_Diode,
    ADC0_Set_MUX_Cooler_Amps, ADC1_Set_MUX_Cooler_Amps,
    ADC0_Throw_Away_Reading,  ADC1_Throw_Away_Reading,
};

// reads only the PI->CCC voltage
static void (* const Function_Seq_Volt_Cal[])(void) =
{
    ADC0_Set_MUX_Cooler_Volts, ADC0_Throw_Away_Reading,
    ADC0_Read_Cooler_Volts, ADC0_Read_Cooler_Volts,
    ADC0_Read_Cooler_Volts, ADC0_Read_Cooler_Volts,
    ADC0_Read_Cooler_Volts, ADC0_Read_Cooler_Volts,
    ADC0_Read_Cooler_Volts, ADC0_Read_Cooler_Volts,
    ADC0_Read_Cooler_Volts, ADC0_Read_Cooler_Volts,
    ADC0_Read_Cooler_Volts, ADC0_Read_Cooler_Volts,
    ADC0_Read_Cooler_Volts,
};

// Function pointer array. Each entry is a function in "ADS1256.h" or "MAX31856.h"
// This is a read sequence when Heat Load is ON
// Each function reads a different metric, or changes the on-chip multiplexer on the ADC
static void (* const Function_Seq_Power_Cal[])(void) =
{
    ADC0_Set_MUX_Cooler_Volts, ADC1_Set_MUX_Cooler_Amps, ADC0_Throw_Away_Reading,
    ADC1_Throw_Away_Reading, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Cooler_Volts, ADC1_Read_Cooler_Amps,
    ADC0_Set_MUX_Temp_Diode, ADC1_Read_Cooler_Amps, ADC0_Throw_Away_Reading,
    ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode, ADC1_Read_Cooler_Amps,
    ADC0_Read_Temp_Diode, ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode,
    ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode, ADC1_Read_Cooler_Amps,
    ADC1_Read_Cooler_Amps, ADC0_Read_Temp_Diode, ADC1_Read_Cooler_Amps,
};

// Function declaration
void Increment_Index(int* index, READ_SEQ state);
void Store_Results();
void Clear_Loop();
extern char* Get_Time();
void Restart_Loop();

READ_SEQ Read_Sequence = HEAT_LOAD_OFF;

bool PAUSE_ACCESS_TO_SPI_BUS = false;
bool SPI_BUS_IN_USE = false;

void Read_Metrics_Loop()
{
    if(PRINT_THREAD_DEBUG) printf("READ_METRICS:\tstart loop\n");
    Clear_Loop();   // clear memory store locations
    //pause();
    static int function_ptr_index = 0;
    while(true)
    {
        usleep(5);      // gives opportunity for operating system to context switch threads
        if( PAUSE_ACCESS_TO_SPI_BUS )
            continue;

        SPI_BUS_IN_USE = true;
        if( Read_Sequence == HEAT_LOAD_ON )   // HEAT_LOAD_ON; need to measure additional metrics of load voltage and current
        {
            //printf(COLOR_LIGHT_CYAN "\tHeat Load ON\n" COLOR_RESET);
            pthread_mutex_lock(&METRICS_LOOP_LOCK);
                Function_Seq_Load_ON[ function_ptr_index ](); // Indexed Function pointer array, functions executed sequentially in specific order
            pthread_mutex_unlock(&METRICS_LOOP_LOCK);
            delayMicroseconds(5);
            Increment_Index(&function_ptr_index, HEAT_LOAD_ON);
        }
        else  if( Read_Sequence == HEAT_LOAD_OFF )   // HEAT_LOAD_OFF; so second ADC (ADC1) can be used for measuring the temp diode and cooler current
        {
            //printf(COLOR_LIGHT_CYAN "\tHeat Load OFF\n" COLOR_RESET);
            pthread_mutex_lock(&METRICS_LOOP_LOCK);
                Function_Seq_Load_OFF[ function_ptr_index ]();  // Indexed Function pointer array, functions executed sequentially in specific order
            pthread_mutex_unlock(&METRICS_LOOP_LOCK);

            Increment_Index(&function_ptr_index, HEAT_LOAD_OFF);
        }
        else if( Read_Sequence == ADC_POWER_CALIBRATION )
        {
            pthread_mutex_lock(&METRICS_LOOP_LOCK);
                Function_Seq_Power_Cal[ function_ptr_index ]();  // Indexed Function pointer array, functions executed sequentially in specific order
            pthread_mutex_unlock(&METRICS_LOOP_LOCK);

            delayMicroseconds(5);
            //delayMicroseconds(10000);
            Increment_Index(&function_ptr_index, ADC_POWER_CALIBRATION);
        }

        SPI_BUS_IN_USE = false;
    }
}

void Store_Results()
{
    //printf(COLOR_LIGHT_CYAN "\n\tSAVE ONE LOOP\n" COLOR_RESET);
    pthread_mutex_lock(&INCREMENT_LOCK);
        ++save_index;
    pthread_mutex_unlock(&INCREMENT_LOCK);

    if( save_index >= (50) )
    {
        if( Test.LOG_DATA ) Write_Data_to_File(Save_Data, &save_index);
        else
        {
              pthread_mutex_lock(&INCREMENT_LOCK);
                save_index = 0;
              pthread_mutex_unlock(&INCREMENT_LOCK);
        }
    }

    Get_TimeStamp( Save_Data[ save_index ].timestamp );
    Get_Elapsed_Time_String( Save_Data[ save_index ].elapsed_time );

    if( CAL_FUNCTIONS_ENABLED)
    {
        Save_Data[ save_index ].Cooler_V_raw = ADC0_Cooler_Volts.raw_average_value;
        Save_Data[ save_index ].ADC0_Cooler_A_raw = ADC0_Cooler_Amps.raw_average_value;
        Save_Data[ save_index ].ADC1_Cooler_A_raw = ADC1_Cooler_Amps.raw_average_value;

        Save_Data[ save_index ].diode_volts_raw = ADC0_Temp_Diode_Volts.raw_average_value;
        Save_Data[ save_index ].Heat_Load_V_raw  = ADC1_Heat_Load_Volts.raw_average_value;
        Save_Data[ save_index ].Heat_Load_mA_raw = ADC1_Heat_Load_milliAmps.raw_average_value;
        Save_Data[ save_index ].pcb_temp = pcb_temperature.average_value;
    }

    Save_Data[ save_index ].Cooler_V = ADC0_Cooler_Volts.average_value;
    Save_Data[ save_index ].ADC0_Cooler_A = ADC0_Cooler_Amps.average_value;
    Save_Data[ save_index ].ADC1_Cooler_A = ADC1_Cooler_Amps.average_value;

    if( Read_Sequence == HEAT_LOAD_ON )
        Save_Data[ save_index ].Cooler_A = ( ADC0_Cooler_Amps.average_value + ADC1_Cooler_Amps.average_value) / 2.0;
    else
        Save_Data[ save_index ].Cooler_A = ADC1_Cooler_Amps.average_value;

    Save_Data[ save_index ].Cooler_W = Cooler_Watts_LUT( ADC0_Cooler_Volts.average_value, Save_Data[ save_index ].Cooler_A );

    Save_Data[ save_index ].diode_volts = ADC0_Temp_Diode_Volts.average_value;
    Save_Data[ save_index ].diode_temp  = get_Temp_K(ADC0_Temp_Diode_Volts.average_value);
    Save_Data[ save_index ].ADC1_diode_volts  = ADC1_Temp_Diode_Volts.average_value;

    Save_Data[ save_index ].Heat_Load_V  = ADC1_Heat_Load_Volts.average_value;
    Save_Data[ save_index ].Heat_Load_mA = ADC1_Heat_Load_milliAmps.average_value;
    Save_Data[ save_index ].Heat_Load_mW = Heat_Load_mW_LUT( ADC1_Heat_Load_Volts.average_value, ADC1_Heat_Load_milliAmps.average_value);

    Save_Data[ save_index ].thermocouple1_temp = THRMCPL_1_temp_C;
    Save_Data[ save_index ].thermocouple2_temp = THRMCPL_2_temp_C;
    Save_Data[ save_index ].thermocouple3_temp = THRMCPL_3_temp_C;
}

// reset temporary store values
void Clear_Loop()
{
    ADC0_Cooler_Volts.count_sum     = 0;
    ADC0_Cooler_Volts.num_samples   = 0;
    ADC0_Cooler_Volts.average_value = 0;
    ADC0_Cooler_Volts.average_count = 0;
    ADC0_Cooler_Volts.raw_average_value = 0;

    ADC0_Cooler_Amps.count_sum     = 0;
    ADC0_Cooler_Amps.num_samples   = 0;
    ADC0_Cooler_Amps.average_value = 0;
    ADC0_Cooler_Amps.average_count = 0;
    ADC0_Cooler_Amps.raw_average_value = 0;

    ADC1_Cooler_Amps.count_sum     = 0;
    ADC1_Cooler_Amps.num_samples   = 0;
    ADC1_Cooler_Amps.average_value = 0;
    ADC1_Cooler_Amps.average_count = 0;
    ADC1_Cooler_Amps.raw_average_value = 0;

    ADC0_Temp_Diode_Volts.count_sum     = 0;
    ADC0_Temp_Diode_Volts.num_samples   = 0;
    ADC0_Temp_Diode_Volts.average_value = 0;
    ADC0_Temp_Diode_Volts.average_count = 0;
    ADC0_Temp_Diode_Volts.raw_average_value = 0;

    ADC1_Heat_Load_Volts.count_sum     = 0;
    ADC1_Heat_Load_Volts.num_samples   = 0;
    ADC1_Heat_Load_Volts.average_value = 0;
    ADC1_Heat_Load_Volts.average_count = 0;
    ADC1_Heat_Load_Volts.raw_average_value = 0;

    ADC1_Heat_Load_milliAmps.count_sum     = 0;
    ADC1_Heat_Load_milliAmps.num_samples   = 0;
    ADC1_Heat_Load_milliAmps.average_value = 0;
    ADC1_Heat_Load_milliAmps.average_count = 0;
    ADC1_Heat_Load_milliAmps.raw_average_value = 0;

    pcb_temperature.raw_average_value = 0;
    pcb_temperature.raw_average_value = 0;
    pcb_temperature.value_sum = 0;
	pcb_temperature.num_samples = 0;
}

void Restart_Loop()
{
    Calc_Measurement_Averages();
    Store_Results();
    Clear_Loop();
}

void Increment_Index(int* func_index, READ_SEQ state)
{

    (*func_index) += 1;
    if(state == HEAT_LOAD_OFF)
    {
        if( (*func_index) >= (int)ARRAY_SIZE(Function_Seq_Load_OFF) )  // comparing to heat load off array size
        {
            //printf("func index @ restart: %d\n", *func_index);
            (*func_index) = 0;
            Restart_Loop(func_index);
        }

    }
    else if( state == HEAT_LOAD_ON)  // HEAT_LOAD_ON
    {
        if( (*func_index) >= (int)ARRAY_SIZE(Function_Seq_Load_ON)  )  // comparing to heat load on function array size
        {
            //printf("func index @ restart: %d\n", *func_index);
            (*func_index) = 0;
            Restart_Loop(func_index);
        }
    }
    else if( state == ADC_CURRENT_CALIBRATION )  // HEAT_LOAD_ON
    {
        if( (*func_index) >= (int)ARRAY_SIZE(Function_Seq_Current_Cal)  )  // comparing to heat load on function array size
        {
            //printf("func index @ restart: %d\n", *func_index);
            (*func_index) = 0;
            Restart_Loop(func_index);
        }
    }
    else if( state == ADC_VOLT_CALIBRATION )  // HEAT_LOAD_ON
    {
        if( (*func_index) >= (int)ARRAY_SIZE(Function_Seq_Volt_Cal)  )  // comparing to heat load on function array size
        {
            //printf("func index @ restart: %d\n", *func_index);
            (*func_index) = 0;
            Restart_Loop(func_index);
        }
    }
    else if( state == ADC_POWER_CALIBRATION )  // HEAT_LOAD_ON
    {
        if( (*func_index) >= (int)ARRAY_SIZE(Function_Seq_Power_Cal)  )  // comparing to heat load on function array size
        {
            //printf("func index @ restart: %d\n", *func_index);
            (*func_index) = 0;
            Restart_Loop(func_index);
        }
    }
}
/*
///////////////////////////
HEAT_LOAD_ON
///////////////////////////
          // DO NOT MODIFY THIS SEQUENCE
          // THIS IS THE SEQUENCE FOR THE FUNCTION POINTER ARRAY FURTHER ABOVE IN THIS FILE.
          // THERE IS A COMPLEX RELATIONSHIP BETWEEN SETTING THE MUX AND WHEN YOU CAN READ (TIME DELAY)
          // WITH THIS SEQUENCE IT TAKES 937 milliseconds to complete a loop iteration
          // THE FOLLOWING # OF SAMPLES ARE RECORDED:
              // TEMP DIODE   x 2 samples
              // COOLER AMPS  x 9 samples   [ADC0x5  + ADC1x4]
              // COOLER_VOLTS x 4 samples
              // HEAT_LOAD_V  x 4 samples
              // HEAT_LOAD_I  x 3 samples
              // THRMCPL1     x 1 sample
              // THRMCPL2     x 1 sample
              // THRMCPL3     x 1 sample
          ADC0_Read_Temp_Diode();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Temp_Diode();
          ADC0_Set_MUX_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Throw_Away_Reading();
          ADC1_Read_Cooler_Amps();
          ADC1_Set_MUX_Heat_Load_V();
          Read_Thermocouple_1();
          ADC0_Read_Cooler_Volts();
          ADC1_Throw_Away_Reading();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Heat_Load_V();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Heat_Load_V();
          ADC0_Read_Cooler_Volts();
          ADC0_Set_MUX_Cooler_Amps();
          ADC1_Read_Heat_Load_V();
          Read_Thermocouple_2();
          ADC0_Throw_Away_Reading();
          ADC1_Read_Heat_Load_V();
          ADC1_Set_MUX_Heat_Load_I();
          ADC0_Read_Cooler_Amps();
          ADC1_Throw_Away_Reading();
          ADC0_Read_Cooler_Amps();
          ADC1_Read_Heat_Load_I();
          ADC0_Read_Cooler_Amps();
          ADC1_Read_Heat_Load_I();
          ADC1_Set_MUX_Cooler_Amps();
          ADC0_Read_Cooler_Amps();
          ADC1_Throw_Away_Reading();
          ADC0_Read_Cooler_Amps();
          ADC0_Set_MUX_Temp_Diode();
          Read_Thermocouple_3();
          ADC0_Throw_Away_Reading();
          ADC1_Read_Cooler_Amps();

//////////////////////////////////
HEAT LOAD OFF
///////////////////////////////////
          // DO NOT MODIFY THIS SEQUENCE
          // THERE IS COMPLEX RELATIONSHIP BETWEEN SETTING THE MUX AND WHEN YOU CAN READ FROM THE SETTING
          // WITH THIS SEQUENCE IT TAKES 1004 milliseconds to complete a loop iteration
          // THE FOLLOWING # OF SAMPLES ARE RECORDED:
              // TEMP DIODE   x 3 samples
              // COOLER AMPS  x 15 samples  (ADC1 dedicated to reading cooler current)
              // COOLER_VOLTS x 10 samples
              // THRMCPL1     x 1 sample
              // THRMCPL2     x 1 sample
              // THRMCPL3     x 1 sample
          ADC0_Read_Temp_Diode();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Temp_Diode();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Temp_Diode();
          ADC0_Set_MUX_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          Read_Thermocouple_1();
          ADC0_Throw_Away_Reading();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          Read_Thermocouple_2();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          Read_Thermocouple_3();
          ADC0_Read_Cooler_Volts();
          ADC1_Read_Cooler_Amps();
          ADC0_Read_Cooler_Volts();
          ADC0_Set_MUX_Temp_Diode();
          ADC1_Read_Cooler_Amps();
          ADC0_Throw_Away_Reading();

*/
#endif
