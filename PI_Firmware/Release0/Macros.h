

#ifndef MACROS
#define MACROS

#define handle_error_en(en, msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
        do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define ARRAY_SIZE(x) ( sizeof(x) / sizeof((x)[0]) )

bool PRINT_DEBUG = false;
bool WAIT_ENTER = false;
bool PRINT_DEBUG_TXRX = false;
bool WAIT_MUX_CHANGE = false;
bool PRINT_DEBUG_MUX = false;
bool PRINT_WAIT_TIME = false;
bool PRINT_THREAD_DEBUG = false;
bool TEMPORARY_DEBUG = false;


bool SEND_VERBOSE = true;
static const char CHECKMARK[] = "\033[01;32m\xE2\x9C\x94\x1b[22;33m";
static const char X_ERROR[] = "\u274C";

#define ONE_MILLISECOND 1000
#define PULSE_ON ONE_MILLISECOND*50
static const int ASCII_NEW_LINE  = 10;	       // ASCII integer code for new line
static const int ASCII_CARRIAGE_RETURN = 13;	// ASCII integer code for carriage return
static const int ASCII_QUIT      = 113;       // ASCII for 'q'
static const int ASCII_ENTER_KEY = 10;        // ASCII character code



void Print_Tabs(int num_to_print);
void Set_Process_Highest_Priority();

struct sched_param sched_param;

void Set_Process_Highest_Priority()
{
  memset(&sched_param, 0, sizeof(sched_param));
  sched_param.sched_priority = sched_get_priority_max(SCHED_FIFO);
  sched_setscheduler(0, SCHED_FIFO, &sched_param);
  mlockall(MCL_CURRENT | MCL_FUTURE);
}

void Print_Tabs(int num_to_print)
{
	for(int i =0; i< num_to_print; i++) printf("\t");
}






const char FLIR_LOGO5[] =
"                    ________    ________     _   ____    ______  \n"
"                   / ____/ /   /  _/ __ \\   / | / / /   / ____/ \n"
"                  / /_  / /    / // /_/ /  /  |/ / /   / /     \n"
"                 / __/ / /____/ // _, _/  / /|  / /___/ /___   \n"
"                /_/   /_____/___/_/ |_|  /_/ |_/_____/\\____/   \n"
"    ____  __    ___   ________ __ ____  ____ _  __          ___    ____ \n"
"   / __ )/ /   /   | / ____/ //_// __ )/ __ \\ |/ /    _   _|__ \\  / __ \n"
"  / __  / /   / /| |/ /   / ,<  / __  / / / /   /    | | / /_/ / / / / /\n"
" / /_/ / /___/ ___ / /___/ /| |/ /_/ / /_/ /   |     | |/ / __/_/ /_/ / \n"
"/_____/_____/_/  |_\\____/_/ |_/_____/\\____/_/|_|     |___/____(_)____/  \n";



const char FLIR_LOGO6[] =
"                    ________    ________     _   ____    ______  \n"
"                   / ____/ /   /  _/ __ \\   / | / / /   / ____/ \n"
"                  / /_  / /    / // /_/ /  /  |/ / /   / /     \n"
"                 / __/ / /____/ // _, _/  / /|  / /___/ /___   \n"
"                /_/   /_____/___/_/ |_|  /_/ |_/_____/\\____/   \n"
"    ____  __    ___   ________ __ ____  ____ _  __            ___     ____ \n"
"   / __ )/ /   /   | / ____/ //_// __ )/ __ \\ |/ /    _   _  |__ \\   / __ \\ \n"
"  / __  / /   / /| |/ /   / ,<  / __  / / / /   /    | | / / ___/ / / / / /\n"
" / /_/ / /___/ ___ / /___/ /| |/ /_/ / /_/ /   |     | |/ / | ___/_/ /_/ / \n"
"/_____/_____/_/  |_\\____/_/ |_/_____/\\____/_/|_|     |___/  |____(_)____/  \n";



const char FLIR_LOGO1[] =
"                                        )        (\n"
"                                     ( /(      )\\ )      (\n"
"                                     )\\())   (()/(      )\\\n"
"                                    ((_)\\      /(_))   (((_)\n";
const char FLIR_LOGO2[] =
" _______  __       __  .______";

const char FLIR_LOGO3[] =
"     .__((_)_. (__))     )\\____. \n";

const char FLIR_LOGO4[] =
"|   ____||  |     |  | |   _  \\    |  \\ |  | |  |     /       |\n"
"|  |__   |  |     |  | |  |_)  |   |   \\|  | |  |     |  ,----'\n"
"|   __|  |  |     |  | |      /    |  . `  | |  |     |  |     \n"
"|  |     |  `----.|  | |  |\\  \\    |  |\\   | |  `----.|  `----.\n"
"|__|     |_______||__| | _| `._\\   |__| \\__| |_______| \\______|\n";
#endif
