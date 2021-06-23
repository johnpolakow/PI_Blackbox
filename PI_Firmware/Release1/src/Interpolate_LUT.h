#ifndef INTERPOLATE_LUT
#define INTERPOLATE_LUT

// This file used to convert measured values into corrected data, via look up tables from calibration

#define ADC_VALUE          1     // index in the 2 dimensional LUT
#define ACTUAL_VALUE       0     // index in the 2 dimensional LUT

#define DAC_COUNT            1     // index in the 2 dimensional LUT
#define MILLIAMP_MEAS        0     // index in the 2 dimensional LUT

double Cooler_Watts_LUT(double volts, double amps);
double Diode_Temp_LUT( double diode_volts);
double Heat_Load_mW_LUT( double volts, double amps);
float get_Corrected_Value(float raw_value, float LUT[][2], int LUT_numElements );
int Find_Index_Upper_Bound(float raw_value, float LUT[][2], int LUT_numElements);


double Cooler_Watts_LUT(double volts, double amps)
{
    return volts*amps;
}


double Diode_Temp_LUT( double diode_volts)
{


}


double Heat_Load_mW_LUT( double volts, double amps)
{
  return volts*amps;
}

// Format is [Actual_value][Measured_value]
float get_Corrected_Value(float ADC_value, float LUT[][2], int LUT_numElements)
{
    int index_lower_bound=0, index_upper_bound=1;
    float actual_val_lower_bound, actual_val_upper_bound, ADC_val_lower_bound, ADC_val_upper_bound;
    float local_slope, local_offset, delta_actual_val, delta_ADC_val;
    float interpolated_value, local_distance;

    index_upper_bound = Find_Index_Upper_Bound(ADC_value, LUT, LUT_numElements);
    //printf("index upper bound: %d\n", index_upper_bound);
    if(index_upper_bound == 0) // value is smaller than smallest val in LUT
    {
        //printf("LUT data point at upper bound: %f\n", LUT[index_upper_bound][ADC_VALUE]);
        // working with only one value in the LUT, not 2, theres no lower bound val, so equation is y = mx
         ADC_val_upper_bound = LUT[0][ADC_VALUE]; // first element in the LUT
         ADC_val_lower_bound = 0;

         actual_val_upper_bound = LUT[0][ACTUAL_VALUE];
         actual_val_lower_bound = 0;
    }
    else if(index_upper_bound == -1) // value is greater than largest value in LUT
    {
        return ADC_value;
    }
    else
    {
        // 2 data points to interpolate from
        // y axis is actual value measured by precision DMM
        // x axis is ADC measured volts
        // LUT is of the form: { DMM_measured_value, ADC_measured_value}
        index_lower_bound = index_upper_bound-1;
        ADC_val_lower_bound = LUT[index_lower_bound][ADC_VALUE]; // closest ADC returned value in the LUT, that is less than our ADC value now
        ADC_val_upper_bound = LUT[index_upper_bound][ADC_VALUE];  // closest ADC returned value in the LUT, that is greater than our ADC value now

        actual_val_upper_bound = LUT[index_upper_bound][ACTUAL_VALUE];
        actual_val_lower_bound = LUT[index_lower_bound][ACTUAL_VALUE];
    }

    delta_actual_val = actual_val_upper_bound - actual_val_lower_bound;  // y2 - y1
    delta_ADC_val   =  ADC_val_upper_bound - ADC_val_lower_bound;         // x2 - x1

    local_slope = delta_actual_val / delta_ADC_val;   // delta_Y / delta_X
    local_offset = actual_val_lower_bound;  // "b" in y = mx + b
    local_distance = ADC_value - ADC_val_lower_bound;

    interpolated_value = ( local_slope * local_distance ) + local_offset;  // y = mx + b

    //printf("index lower bound: %d \t index upper_bound: %d \n", index_lower_bound, index_upper_bound);
    //printf("ADC lower bound: %f \t ADC upper_bound: %f \n", ADC_val_lower_bound, ADC_val_upper_bound);
    //printf("DMM lower bound: %f \t DMM upper_bound: %f \n", actual_val_lower_bound, actual_val_upper_bound);
    //printf("delta DMM: %f \t delta ADC: %f \n", delta_actual_val, delta_ADC_val);
    //printf("local slope: %f \t local offset: %f \n", local_slope, local_offset);
    //printf("\ninterpolated value: %f \t input value: %f \n", interpolated_value , ADC_value);

    return interpolated_value;
}

// Returns index of bounding value in LUT for a given value
int Find_Index_Upper_Bound(float ADC_val, float LUT[][2], int LUT_numElements)
{
  int index = 0;
  bool found = false;
  double LUT_val_at_index;

  while(!found)
  {
      LUT_val_at_index = LUT[index][ADC_VALUE];
      if(LUT_val_at_index >= ADC_val)
      { return index; }
      else
      {
        index += 1;
        if( index >= LUT_numElements){ return -1 ; }
      }
  }
}






#endif
