
#include "Save2.h"

void Display_Data()
{
  printf(COLOR_LIGHT_CYAN " %.4f V  \t" COLOR_RESET, Save_Data[save_index].CCC_V);
  printf(COLOR_LIGHT_CYAN " %.4f A \t" COLOR_RESET, Save_Data[save_index].CCC_A );
	printf(COLOR_LIGHT_RED " %.3f W \t" COLOR_RESET, Save_Data[save_index].CCC_W);
	printf(COLOR_LIGHT_GREEN "    %.3f K  " COLOR_RESET, Save_Data[save_index].diode_temp );
  printf(COLOR_YELLOW "\t   %.2f C, %.2f C, %.2f C \t\t" COLOR_RESET, Save_Data[save_index].thermocouple1_temp,
        Save_Data[save_index].thermocouple2_temp, Save_Data[save_index].thermocouple3_temp);
  printf(COLOR_LIGHT_BLUE "%.2fV, " COLOR_RESET, Save_Data[save_index].Heat_Load_V);
	printf(COLOR_LIGHT_BLUE "%.2fmA, " COLOR_RESET, Save_Data[save_index].Heat_Load_mA);
  if( Save_Data[save_index].Heat_Load_mW > 1)
  {
      printf(COLOR_LIGHT_MAGENTA " %.2fmW     " COLOR_RESET, Save_Data[save_index].Heat_Load_mW);
  }
  else
  {
      printf(COLOR_LIGHT_BLUE " %.2fmW    " COLOR_RESET, Save_Data[save_index].Heat_Load_mW);
  }
  	printf(COLOR_YELLOW "   %s " COLOR_RESET, Save_Data[save_index].elapsed_time);
}

void Clear_Console()
{
  printf( "\033[0m\033[2J\033[H");  // clears the terminal and brings cursor to first line
  printf("\n");
}

void Print_Console_Header()
{
  printf(COLOR_LIGHT_CYAN);
  printf(" CCC_VBUS ");
  printf(COLOR_RESET);
  printf(COLOR_LIGHT_BLUE);
  printf("");
  printf(COLOR_RESET);
  printf(COLOR_LIGHT_CYAN);
  printf("");
  printf("\t CCC_AMPS ");
  printf(COLOR_RESET);
  printf(COLOR_LIGHT_RED);
  printf("\tCCC_WATTS ");
  printf(COLOR_RESET);
  printf(COLOR_LIGHT_GREEN);
  printf("\t    DEWAR TEMP\t");
  printf(COLOR_RESET);
  printf(COLOR_YELLOW);
  printf("\tTHRMCPL 1,2,3\t");
  printf(COLOR_RESET);
  printf(COLOR_LIGHT_BLUE);
  printf("\t\t\tHEAT LOAD \t");
  printf(COLOR_RESET);
  printf(COLOR_YELLOW);
  printf("     ELAPSED TIME\n");
  printf(COLOR_RESET);

  printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}
