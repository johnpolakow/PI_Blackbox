
#include <pthread.h>



pthread_mutex_t STORE_INSTRUCTION_LOCK;
pthread_mutex_t SPI_BUS_LOCK;
pthread_mutex_t HEAT_LOAD_LOCK;
pthread_mutex_t LOGGING_LOCK;
pthread_mutex_t METRICS_LOOP_LOCK;
pthread_mutex_t SOCKET_RW_LOCK;
pthread_mutex_t INCREMENT_LOCK;

typedef struct thread_info
{
    pthread_t thread_id;        /* ID returned by pthread_create() */
    int       thread_num;       /* Application-defined thread # */
    char     *thread_description;      /* From command-line argument */
} thread_object;


thread_object* Socket_Receive_Thread;
thread_object* Read_Metrics_Thread;
thread_object* Write_to_File_Thread;
thread_object* GUI_Thread;
