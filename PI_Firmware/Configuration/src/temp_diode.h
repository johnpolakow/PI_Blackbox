
#define TEMPERATURE_VALUE 1 // index in the 2 dimensional LUT
#define VOLTAGE_VALUE 0     // index in the 2 dimensional LUT
#define NUM_LUT_ELEMENTS 49

//format of this LUT is { diode_voltage, temp_in_kelvins }
float diode_V_to_Temp[49][2] = {
    { 1.0704, 60 },
    { 1.0613, 65 },
    { 1.0529, 70 },
    { 1.0444, 75 },
    { 1.0410, 77 },
    { 1.0363, 80 },
    { 1.0269, 85 },
    { 1.0180, 90 },
    { 1.0084, 95 },
    { 1.0037, 100 },
    { 0.9971, 105 },
    { 0.9871, 110 },
    { 0.9809, 115 },
    { 0.9693, 120 },
    { 0.9642, 125 },
    { 0.9587, 130 },
    { 0.9472, 135 },
    { 0.9382, 140 },
    { 0.9299, 145 },
    { 0.9190, 150 },
    { 0.8988, 160 },
    { 0.8787, 170 },
    { 0.8567, 180 },
    { 0.8374, 190 },
    { 0.8176, 200 },
    { 0.7983, 210 },
    { 0.7786, 220 },
    { 0.7597, 230 },
    { 0.7404, 240 },
    { 0.7210, 250 },
    { 0.7006, 260 },
    { 0.6797, 270 },
    { 0.6594, 280 },
    { 0.6463, 290 },
    { 0.6412, 295 },
    { 0.6312, 300 },
    { 0.6095, 310 },
    { 0.5877, 320 },
    { 0.5658, 330 },
    { 0.5438, 340 },
    { 0.5228, 350 },
    { 0.4200, 360 },
    { 0.3965, 370 },
    { 0.3730, 380 },
    { 0.3495, 390 },
    { 0.3258, 400 },
    { 0.3022, 410 },
    { 0.2784, 420 },
    { 0.2546, 430 },
};

float get_Temp_K(float diode_volts);
float Interpolate_Temp(float temp_offset, float dV, float slope);
int Find_Upper_Bound(float diode_volts);


float get_Temp_K(float diode_volts)
{
    int index_lower_bound, index_upper_bound;
    float temp_lower_bound, temp_upper_bound, voltage_lower_bound, voltage_upper_bound;
    float slope, offset_V, temp_offset, delta_T, delta_V;
    float interpolated_temp, interpolated_voltage;

    index_upper_bound = Find_Upper_Bound(diode_volts);
    if(index_upper_bound == 0) // voltage is greater than max value in the LUT (colder than min temp)
    {
        return 500.0;

    }
    else index_lower_bound = index_upper_bound-1;


    // index_upper_bound = numerically larger index in LUT, lower voltage, higher K temp
    // index_lower_bound = numerically lower index in LUT, higher voltage, lower K temp
    temp_lower_bound = diode_V_to_Temp[index_lower_bound][TEMPERATURE_VALUE]; // lower temp
    voltage_lower_bound = diode_V_to_Temp[index_lower_bound][VOLTAGE_VALUE];  // higher voltage
    temp_upper_bound = diode_V_to_Temp[index_upper_bound][TEMPERATURE_VALUE];  // higher temp
    voltage_upper_bound= diode_V_to_Temp[index_upper_bound][VOLTAGE_VALUE]; // lower voltage

    delta_V = voltage_upper_bound- voltage_lower_bound;  // positive number
    delta_T = temp_upper_bound - temp_lower_bound;  // positive number
    slope = delta_V/delta_T;  // should be a negative number
    temp_offset = diode_V_to_Temp[index_lower_bound][TEMPERATURE_VALUE];
    interpolated_voltage = diode_volts - voltage_lower_bound; // how much voltage to interpolate (divide by slope) (should be negative number)

    interpolated_temp = Interpolate_Temp(temp_offset, interpolated_voltage, slope);

        //printf("TEMP_LOWER:\t%f \tINTERPOL:\t%f \tUpper:\t%f\n", temp_lower_bound, interpolated_temp, temp_upper_bound);
/*
    printf("index_lower_bound: %d\n", index_lower_bound );
    printf("index_upper_bound: %d\n", index_upper_bound );
    printf("temp_upper_bound: %f\n", temp_upper_bound );
    printf("voltage_upper_bound: %f\n", voltage_upper_bound );
    printf("temp_lower_bound: %f\n", temp_lower_bound );
    printf("voltage_lower_bound: %f\n", voltage_lower_bound );
    printf("slope: %f\n", slope );
        printf("interpolated_voltage: %f\n", interpolated_voltage );
        printf("interpolated_temp: %f\n", interpolated_temp );
        */

    return interpolated_temp;
}

float Interpolate_Temp(float temp_offset, float dV, float slope)
{
    float interpolated_temp = temp_offset;
    interpolated_temp += dV/slope;

    return interpolated_temp;
}

// Returns index of bounding value in LUT for a given voltage
// the index will be of a voltage value lower than the argument value diode_volts
int Find_Upper_Bound(float diode_volts)
{
  int index = 0;
  bool found = false;
  float voltage_at_index;

  while(!found)
  {
      voltage_at_index = diode_V_to_Temp[index][VOLTAGE_VALUE];
      if(voltage_at_index <= diode_volts)
      { return index; }
      else
      {
        index += 1;
        if( index >= NUM_LUT_ELEMENTS) return (NUM_LUT_ELEMENTS -1);
        continue;
      }
  }
}

float Kelvin_to_Celsius(float kelvins)
{
  return kelvins - 273.15;
}
