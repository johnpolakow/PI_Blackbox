#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <signal.h>
#include <bcm2835.h>

#include "Pin_Defs.h"
#include "ADS1256.h"
#include "Thread_Defs.h"
#include "Init_BCM2835.h"
#include "Receive_Socket.h"
#include "Read_Metrics.h"
#include "Macros.h"
#include "Profile_Helper.h"
#include "DAC.h"
#include "MAX31856.h"

struct sigaction signal_action;
extern Instruction_Info** Socket_Instructions;

//
//  FUNCTION DECLARATIONS
//
void* Receive_Socket_Commands(void *arg);
void* Write_to_File(void *arg);
void* Read_Metrics(void *arg);
void* Refresh_GUI(void *arg);
bool Start_Threads();
extern void Execute_Command(Instruction_Info* socket_instruction);
void Execute_Query(Instruction_Info* command);
void Wait_Enter();
void Initialize_Signal_Handler();
void Signal_Handler(int sig_id);

extern void Get_Disk_Usage();

// give write to file thread and GUI refresh thread low priority
bool Start_Threads()
{
    pthread_attr_t thread_attributes;
    int result;
    int create_result;
    void* return_val;

    // Initialize thread creation attributes
    result = pthread_attr_init( &thread_attributes );
    if (result != 0) { handle_error("pthread_attr_init error"); }

    pthread_mutex_init(&STORE_INSTRUCTION_LOCK, NULL);
    pthread_mutex_init(&SPI_BUS_LOCK, NULL);    // SPI_BUS_LOCK declared in Thread_Defs.h
    pthread_mutex_init(&HEAT_LOAD_LOCK, NULL);
    pthread_mutex_init(&LOGGING_LOCK, NULL);

    // Allocate memory for thread struct, and initialize member variables
    Socket_Receive_Thread = malloc( sizeof(struct thread_info) );
    Socket_Receive_Thread->thread_num = 1;
    Socket_Receive_Thread->thread_description = strdup("Socket Receive Thread");

    Read_Metrics_Thread = malloc( sizeof(struct thread_info) );
    Read_Metrics_Thread->thread_num = 2;
    Read_Metrics_Thread->thread_description = strdup("Read Metrics Thread");

    //Write_to_File_Thread = malloc( sizeof(struct thread_info) );
    //Write_to_File_Thread->thread_num = 3;
    //Write_to_File_Thread->thread_description = strdup("Write to File Thread");

    //GUI_Thread = malloc( sizeof(struct thread_info) );
    //GUI_Thread->thread_num = 4;
    //GUI_Thread->thread_description = strdup("GUI Thread");

    create_result = pthread_create( &Socket_Receive_Thread->thread_id, &thread_attributes, &Receive_Socket_Commands, (void *)Socket_Receive_Thread);
    if (create_result != 0){ handle_error_en(create_result, "pthread_create error, receive socket thread"); }
    if(PRINT_DEBUG) printf("\nCreated: %s  [Thread 1]\t", Socket_Receive_Thread->thread_description);

    create_result = pthread_create( &Read_Metrics_Thread->thread_id, &thread_attributes, &Read_Metrics, (void *)Read_Metrics_Thread);
    if (create_result != 0){ handle_error_en(create_result, "pthread_create error, read metrics thread"); }

    if(PRINT_DEBUG) printf("\nCreated: %s [Thread 2]\t", Read_Metrics_Thread->thread_description);

    //create_result = pthread_create( &Write_to_File_Thread->thread_id, &thread_attributes, &Write_to_File, (void *)Write_to_File_Thread);
    //if (create_result != 0){ handle_error_en(create_result, "pthread_create error, write to file thread"); }
    //if(PRINT_DEBUG) printf("\nCreated: %s [Thread 3]\t", Write_to_File_Thread->thread_description);

    //create_result = pthread_create( &GUI_Thread->thread_id, &thread_attributes, &Refresh_GUI, (void *)GUI_Thread);
    //if (create_result != 0){ handle_error_en(create_result, "pthread_create error, GUI thread"); }
    //if(PRINT_DEBUG) printf("\nCreated: %s [Thread 4]\t", GUI_Thread->thread_description);
    //if(PRINT_DEBUG) printf("\n\n");

    // Destroy the thread attributes object, since it is no longer needed
    result = pthread_attr_destroy( &thread_attributes );
    if (result != 0) { handle_error("pthread_attr_destroy"); }
}

void* Receive_Socket_Commands(void *arg)
{
  thread_object* thread = (thread_object*)arg;
  if(PRINT_THREAD_DEBUG) printf("\tthread #: %d\tdescription: %s\n", thread->thread_num, thread->thread_description);
  Create_PI_Socket();
  return strdup("socket");
}

void* Write_to_File(void *arg)
{
  thread_object* thread = (thread_object*)arg;
  if(PRINT_THREAD_DEBUG) printf("\tthread #: %d\tdescription: %s\n", thread->thread_num, thread->thread_description);
  //
  //  WRITE TO FILE FUNCTION HERE
  //
  return strdup("write-file");
}

void* Read_Metrics(void *arg)
{
  thread_object* thread = (thread_object*)arg;
  if(PRINT_THREAD_DEBUG) printf("\tthread #: %d\tdescription: %s\n", thread->thread_num, thread->thread_description);
  Read_Metrics_Loop();
  return strdup("read_metrics");
}

/*
void* Refresh_GUI(void *arg)
{
  thread_object* thread = arg;
  if(PRINT_THREAD_DEBUG) printf("\tthread #: %d\tdescription: %s\n", thread->thread_num, thread->thread_description);
  //
  //  GUI FUNCTION HERE
  //
  return strdup("GUI");
}
*/
/*
void Initialize_Signal_Handler()
{
    memset(&signal_action, 0, sizeof(signal_action));
    signal_action.sa_handler = Signal_Handler;
    sigemptyset(&signal_action.sa_mask);

    sigaction(SIGUSR1, &signal_action, NULL);
    sigaction(SIGUSR2, &signal_action, NULL);
}
*/
/*
void Signal_Handler(int sig_id)
{
  if (SIGUSR1 == sig_id)
  {
      if(PRINT_THREAD_DEBUG) printf("PAUSE THREAD\n");
      pause();
      return;
  }
}
*/
int main(int argc, char *argv[])
{
    ADC0.CS_pin 		= ADS1256_CS_0;
    ADC0.DRDY_pin 	= ADS1256_DRDY_0;
    ADC0.RESET_pin	= ADS1256_RESET;
    ADC0.BUF_EN_pin = BUFFER_EN_0;

    ADC1.CS_pin 		= ADS1256_CS_1;
    ADC1.DRDY_pin 	= ADS1256_DRDY_1;
    ADC1.RESET_pin	= ADS1256_RESET;
    ADC1.BUF_EN_pin = BUFFER_EN_0;

    //Initialize_Signal_Handler();

    Init_BCM2835_Library();
    Get_Disk_Usage();
    printf(COLOR_LIGHT_CYAN "\n%s" COLOR_RESET, FLIR_LOGO1);
    printf(COLOR_BOLD_WHITE "%s" COLOR_RESET, FLIR_LOGO2);
    printf(COLOR_LIGHT_CYAN "%s" COLOR_RESET, FLIR_LOGO3);

    printf(COLOR_BOLD_WHITE "%s\n\n" COLOR_RESET, FLIR_LOGO4);
    Initialize_Test_Settings();
    MAX31856_Init();
    ADS1256_Init();
    if(PRINT_DEBUG) printf(" DEFAULT REGS, ADC0:\n");
    Read_Default_Regs(&ADC0);
    if(PRINT_DEBUG) printf("\n");
    ADS1256_Config_LCK(&ADC0, ADS1256_GAIN_1, DRATE_15SPS);
    ADS1256_Config_LCK(&ADC1, ADS1256_GAIN_1, DRATE_15SPS);
    if(PRINT_DEBUG) printf(" DEFAULT REGS, ADC1:\n");
    Read_Default_Regs(&ADC1);
    if(PRINT_DEBUG) printf("\n");
    DAC_Start();

    //Set_Process_Highest_Priority();

    Start_Threads();

    usleep(10);

    pthread_join( Socket_Receive_Thread->thread_id, NULL );
    //pthread_join( Write_to_File_Thread->thread_id, NULL );
    //pthread_join( GUI_Thread->thread_id, NULL );
    pthread_join( Read_Metrics_Thread->thread_id, NULL );

    // release memory for thread structs
    exit(EXIT_SUCCESS);

  }



void Wait_Enter()
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



/*
static void display_pthread_attr(pthread_attr_t *attr, char *prefix)
{
        int result, i;
        size_t v;
        void *stkaddr;
        struct sched_param sp;

        result = pthread_attr_getdetachstate(attr, &i);
        if (result != 0)
            handle_error("pthread_attr_getdetachstate");
        printf("%sDetach state        = %s\n", prefix,
                (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
                (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
                "???");

        result = pthread_attr_getscope(attr, &i);
        if (result != 0)
            handle_error("pthread_attr_getscope");
        printf("%sScope               = %s\n", prefix,
                (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
                (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
                "???");

        result = pthread_attr_getinheritsched(attr, &i);
        if (result != 0)
            handle_error("pthread_attr_getinheritsched");
        printf("%sInherit scheduler   = %s\n", prefix,
                (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
                (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
                "???");

        result = pthread_attr_getschedpolicy(attr, &i);
        if (result != 0)
            handle_error("pthread_attr_getschedpolicy");
        printf("%sScheduling policy   = %s\n", prefix,
                (i == SCHED_OTHER) ? "SCHED_OTHER" :
                (i == SCHED_FIFO)  ? "SCHED_FIFO" :
                (i == SCHED_RR)    ? "SCHED_RR" :
                "???");

        result = pthread_attr_getschedparam(attr, &sp);
        if (result != 0)
            handle_error("pthread_attr_getschedparam");
        printf("%sScheduling priority = %d\n", prefix, sp.sched_priority);

        result = pthread_attr_getguardsize(attr, &v);
        if (result != 0)
            handle_error("pthread_attr_getguardsize");
        printf("%sGuard size          = %zu bytes\n", prefix, v);

        result = pthread_attr_getstack(attr, &stkaddr, &v);
        if (result != 0)
            handle_error("pthread_attr_getstack");
        printf("%sStack address       = %p\n", prefix, stkaddr);
        printf("%sStack size          = 0x%zx bytes\n", prefix, v);
    }
*/
