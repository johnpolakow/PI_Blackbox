
#ifndef RECEIVE_SOCKET
#define RECEIVE_SOCKET

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "Command.h"
#include "String_Helper.h"
#include "Execute_Command.h"
#include "Execute_Query.h"
#include "colors.h"
#include "Macros.h"
#include "clientserver.h"

#define MAX_RESPONSE_LINES  100
#define MAX_WAITING_CLIENTS 1
#define DEFAULT_LISTEN_PORT		"2020"
#define PORT 2020
#define SA struct sockaddr

char complete_receive_string[200];
static bool SEND_DEBUG = false;
extern bool SEND_VERBOSE;
static bool ENABLE_CAL_FUNCTIONS = false;

#define ARRAY_SIZE(x) ( sizeof(x) / sizeof((x)[0]) )

extern Instruction_Info** Socket_Instructions;        // data structure containing list of commands received on socket, data structure defined in "Command.h"
extern const char* STR_COMMAND_LIST[];                // array of strings. strings received on socket compared to this list for validation as valid command, defined in "Command.h"
extern COMMAND ENUM_COMMAND_LIST[];                   // declared in Command.h
extern pthread_mutex_t STORE_INSTRUCTION_LOCK;        // declared in Thread_defs.h
extern pthread_mutex_t INCREMENT_LOCK;                // declared in Thread_defs.h


int socket_FD, connection_FD, client_length;
struct sockaddr_in server_addr, client;

// Function Declarations
void Create_PI_Socket();
void Socket_Listen();
void Process_Socket_Instruction(conn_t* client_conn, Instruction_Info* parse_instruction);
bool Is_Command(Instruction_Info* socket_instruction);
bool Is_Query(Instruction_Info* socket_instruction);
bool Is_In_Command_List(Instruction_Info* socket_instruction);
bool Has_Correct_Argument(Instruction_Info* socket_instruction);
COMMAND Get_Command(Instruction_Info* socket_instruction);
instruction_t Get_Instruction_Type(Instruction_Info* socket_instruction);
bool Is_Help_Command(Instruction_Info* socket_instruction);
int Get_Query_Index(char* socket_string);
bool Is_In_Query_List(Instruction_Info* socket_instruction);
extern void Execute_Command(Instruction_Info* socket_instruction);
extern void Execute_Query(Instruction_Info* socket_instruction);
QUERY Get_Query(Instruction_Info* socket_instruction);
void Send_Result_to_Hub(Instruction_Info* instruction);
void func(int sockfd);

bool Check_FD_Ready(conn_t* connection, fd_set* FD, struct timeval* tv);
int Receive_Data(conn_t* connection, char* buffer);
void Read_Socket_nBytes(conn_t* client_conn, char* buff, int num_bytes);
bool Read_Sock_FD_Ready(int fd, fd_set* set);
int Get_Bytes_Available(int fd);
void Free_Instruction_Mem(Instruction_Info* erase_instruction);
void Send_Instruction_Result(conn_t* client_conn, Instruction_Info* completed_instruction);

Instruction_Info* Store_Instruction(char* instruction_str);
bool Is_Debug_Command(Instruction_Info* socket_instruction);
void Change_Debug_State(Instruction_Info* instruction);

void Print_Socket_Instruction(Instruction_Info* instruction);
char* Array_to_String(char** array);
void Change_Verbose_State(Instruction_Info* instruction);
bool Is_Verbose_Command(Instruction_Info* socket_instruction);
void Send_Greeter_Message(conn_t* client_conn);

void Create_PI_Socket()
{
    struct timeval tv;
	  fd_set read_FD;

    if(PRINT_THREAD_DEBUG) printf("\tRECEIVE SOCKET... create pi socket & listen\n");

	  // use listen port from cmd line args if supplied, otherwise use default value
	  const char* listen_Port = DEFAULT_LISTEN_PORT;

	  conn_t* listen_conn = listen_tcp(listen_Port);
	  if (!listen_conn)
		    return;

	   printf("\n\nWaiting for connection on PORT " COLOR_BOLD_GREEN "%s" COLOR_RESET "...\n", listen_Port);

     while(1)   // accept a connection loop
     {
		      conn_t* client_conn = accept_tcp(listen_conn); 			// Accept a client socket
		      if (!client_conn)
				      continue;

		      char recv_Buf[200];

          Send_Greeter_Message(client_conn);
          while (1)
		      {
				        tv.tv_sec = 0;
				        tv.tv_usec = 10000; //10ms, amount of time select should block waiting for a file descriptor to become ready
			          FD_ZERO(&read_FD);
			          FD_SET(client_conn->sockfd, &read_FD);

			          Check_FD_Ready(client_conn, &read_FD, &tv);

			          // recv data if available
			          Erase_String_Contents(complete_receive_string);

			          if ( Read_Sock_FD_Ready(client_conn->sockfd, &read_FD) )	// If Read file descriptor can be read
			          {
					           printf("\n---------------------------------------------------\n\n");
					           printf( COLOR_BRIGHT_MAGENTA "\t***SERVER*** ( PI )\n\n" COLOR_RESET);

                     int num_bytes = Get_Bytes_Available(client_conn->sockfd);    // get bytes available for reading from the socket
                     if( !(num_bytes > 0) )
                        break;
					           Read_Socket_nBytes(client_conn, recv_Buf, num_bytes);				// read the socket until num_bytes have been read
                     Trim_Leading_Trailing_Whitespace( recv_Buf );

                     Instruction_Info* current_instruction = Store_Instruction( complete_receive_string); // store the string in Instruction_Info object, keep pointer to new object
                     current_instruction->instruction_type = Get_Instruction_Type(current_instruction);
                     if( current_instruction->instruction_type == syntax_error_t)
                          printf("RECV:  " COLOR_LIGHT_RED "%s\n" COLOR_RESET, complete_receive_string);

                     else if( current_instruction->instruction_type == command_t || current_instruction->instruction_type == query_t)
                          printf("RECV:  " COLOR_BOLD_GREEN "%s\n" COLOR_RESET, complete_receive_string);

                     else if( current_instruction->instruction_type == help_t)
                          printf("RECV:  " COLOR_BOLD_YELLOW "%s\n" COLOR_RESET, complete_receive_string);

                     Process_Socket_Instruction ( client_conn, current_instruction );
                     //Print_Socket_Instruction(current_instruction);
			           }
		        }
            printf("\nWaiting for connection on PORT " COLOR_BOLD_GREEN "%s" COLOR_RESET "...\n", listen_Port);
     }
}

void Free_Instruction_Mem(Instruction_Info* erase_instruction)
{
    erase_instruction->index_of_instruction = 0;
    erase_instruction->response_store_index = 0;
    erase_instruction->debug_store_index = 0;
    Free_String_Array_Memory( erase_instruction->response_array );
    Free_String_Array_Memory( erase_instruction->debug_array );
    free( erase_instruction );
}

Instruction_Info* Store_Instruction(char* instruction_str)
{
    Socket_Instruction = malloc(sizeof( Instruction_Info ) ); // Allocate the memory to hold the new Instruction_Info struct
    Instruction_Info* new_instruction = Socket_Instruction;   // create a pointer to make accessing the element cleaner

    strcpy( new_instruction->socket_receive, instruction_str );               // copy received instruction to data structure
    new_instruction->response_store_index = 0;                                // keep track of how many "lines" or strings are in the response string array (char **)
    new_instruction->debug_store_index = 0;

    new_instruction->response_array = (char**)malloc(sizeof(char*) * MAX_RESPONSE_LINES); // allocate memory for response string to client
    for(int i =0; i<MAX_RESPONSE_LINES; ++i)
        new_instruction->response_array[i] = NULL;    // initailize all pointers to NULL, so we know which memory locations to free later

    new_instruction->debug_array = (char**)malloc(sizeof(char*) * MAX_RESPONSE_LINES); // allocate memory for response string to client
    for(int i =0; i<MAX_RESPONSE_LINES; ++i)
        new_instruction->debug_array[i] = NULL;    // initailize all pointers to NULL, so we know which memory locations to free later

    Erase_String_Contents(new_instruction->response_str);
    return new_instruction;
}

int Get_Bytes_Available(int fd)
{
    int count;
    ioctl( fd, FIONREAD, &count);
    return count;
}

bool Read_Sock_FD_Ready(int fd, fd_set* set)
{
		return ( FD_ISSET(fd, set) );
}

void Read_Socket_nBytes(conn_t* client_conn, char* buff, int num_bytes)
{
		Erase_String_Contents(complete_receive_string);
		while(num_bytes>0)    // read until all bytes have been read
		{
			int read_chars = Receive_Data(client_conn, buff);  // returns number of bytes that were read
			num_bytes -= read_chars;                           // decrement number of bytes we still need to read
			strncat(complete_receive_string, buff, read_chars);  // add the characters we read to "complete_receive" string
			Erase_String_Contents(buff);                       // wipe memory for next read loop
		}
}

int Receive_Data(conn_t* connection, char* buffer)
{
		Erase_String_Contents((char*)buffer);
		int receive_Bytes = recvData(connection , (char*)buffer, (int)sizeof(buffer));
		buffer[receive_Bytes] = '\0';
		//printf("   recv: %s\n", buffer);
		return receive_Bytes;
}

bool Check_FD_Ready(conn_t* connection, fd_set* FD, struct timeval* tv)
{
		bool status = true;

		// argument order: (num_file descriptors+1, readFD, writeFD, fixed buffer, timeout value)
		if ( select(connection->sockfd + 1, FD, NULL, NULL, tv) == -1 )	// determine if file descriptors of either socket are ready
		{
				status = false;
				perror("select failed\n");
				disconnect_tcp(connection);
		}

		return status;
}

void Send_Greeter_Message(conn_t* client_conn)
{
    int str_len = strlen("\n") + strlen(FLIR_LOGO6) + strlen("\n\n") + 2;
    char start_message[str_len];

    Erase_String_Contents(start_message);
    strcpy(start_message, "\n");
    strcat(start_message, FLIR_LOGO6);
    strcat(start_message, "\n\n");
    sendData(client_conn, (char*)start_message, strlen(start_message) );
}

void Send_Instruction_Result(conn_t* client_conn, Instruction_Info* completed_instruction)
{
      int send_Bytes;
      int send_buffer_size = 0;

      char* buffer_2;
      char* buffer_3;
      bool send_buffer_1 = false;
      bool send_buffer_2 = false;
      bool send_buffer_3 = false;

      if( strlen( completed_instruction->response_str) > 0 )    // if there's a message in response_str, create a temp buffer to store it
      {
          send_buffer_size += strlen( completed_instruction->response_str) + 1;
          send_buffer_1 = true;             // turn on flag to send this buffer
      }

      if( SEND_DEBUG && completed_instruction->debug_store_index > 0 )      // if DEBUG flag is on, then send additional debug messages, so populate this buffer
      {
          //Print_String_Array(completed_instruction->debug_array);
          buffer_2 = Array_to_String( completed_instruction->debug_array);
          send_buffer_size += strlen( buffer_2) + 10;
          send_buffer_2 = true;           // turn on flag to send messages in this buffer
      }

      if( (completed_instruction->response_store_index > 0) && (completed_instruction->response_array[0] != NULL) )
      {
          //Print_String_Array(completed_instruction->response_array);
          buffer_3 = Array_to_String( completed_instruction->response_array);
          send_buffer_size += strlen( buffer_3) + 1;
          send_buffer_3 = true;
      }

      char send_buffer[ send_buffer_size +10];
      Erase_String_Contents( send_buffer );

			printf("\nSEND:\n" COLOR_BROWN );

			if( send_buffer_1 )
      {
          strcpy( send_buffer, completed_instruction->response_str);
          strcat( send_buffer, "\n");
      }

      if( send_buffer_3 )
      {
          strcat( send_buffer, buffer_3);
          send_buffer[ strlen(send_buffer)] = '\0';
          free(buffer_3);
      }

      if( send_buffer_2 )
      {
          strcat( send_buffer, "\n");
          strcat( send_buffer, buffer_2);
          free(buffer_2);
          //send_buffer[ strlen(send_buffer)] = '\0';
      }
      printf("%s", send_buffer);
      printf( COLOR_RESET );
      send_Bytes = sendData(client_conn, (char*)send_buffer, strlen(send_buffer) );
			printf("---------------------------------------------------\n");
}

char* Array_to_String(char** array)
{
      int buffer_length = 0, i = 0;

      if( array == NULL || array[0] == NULL)
          return NULL;

      while( array[i] != NULL )    // determine the buffer size necessary to hold all strings
      {
          buffer_length += strlen( array[i] ) + 2; // add space for newline and tabs
          ++i;
      }

      char* send_buffer = (char*)malloc( sizeof(char*) * buffer_length + 5 );
      Erase_String_Contents(send_buffer);

      char single_string[ MAX_RESPONSE_LENGTH];
      i = 0;

      while( array[i] != NULL )
      {
          Erase_String_Contents(single_string);
          sprintf(single_string, "\t%s\n", array[i] );
          strcat(send_buffer, single_string);
          ++i;
      }
      send_buffer[ strlen(send_buffer) ] = '\0';
      return send_buffer;
}

// allocate memory for new instruction
// get the correct index
// test for reaching max storage locations
// store instruction to new memory instruction
// proceed with parsing
void Process_Socket_Instruction(conn_t* client_conn, Instruction_Info* parse_instruction)
{
    char parse_str[MAX_RECEIVE_LENGTH];
    strcpy(parse_str, parse_instruction->socket_receive);
    instruction_t instruction_type = parse_instruction->instruction_type;

    if( instruction_type == syntax_error_t )
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "\t%s SyntaxError: received \"%s\", missing syntax '>' or '?'", X_ERROR, parse_instruction->socket_receive);
        strcat( parse_instruction->response_str, response);          // copy error message into parse_instruction data structure
        Send_Instruction_Result( client_conn, parse_instruction);
        Free_Instruction_Mem(parse_instruction);
        return;
    }
    else if( instruction_type == command_t )
    {
        if( Is_Command(parse_instruction) )
        {
            Execute_Command( parse_instruction );
            Send_Instruction_Result( client_conn, parse_instruction );
            Free_Instruction_Mem(parse_instruction);
            return;
        }
        else
        {
            Send_Instruction_Result( client_conn, parse_instruction);
            Free_Instruction_Mem(parse_instruction);
        }
    }
    else if( instruction_type == query_t )
    {
        if( Is_Query(parse_instruction) )
        {
            Execute_Query( parse_instruction );
            Send_Instruction_Result( client_conn, parse_instruction );
            Free_Instruction_Mem(parse_instruction);
            return;
        }
        else
        {
            char response[MAX_RESPONSE_LENGTH];
            sprintf(response, "\t%s SyntaxError: received \"%s\", no matching query", X_ERROR, parse_instruction->socket_receive);
            strcat( parse_instruction->response_str, response);          // copy error message into parse_instruction data structure
            Send_Instruction_Result( client_conn, parse_instruction);
            Free_Instruction_Mem(parse_instruction);
        }
    }
    else if( instruction_type == help_t)
    {
        parse_instruction->this_query = HELP;
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "DEBUG:\tSuccess, rec'vd \"%s\", parsed to HELP command", parse_instruction->socket_receive);
        parse_instruction->debug_array[ parse_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( parse_instruction->debug_array[ parse_instruction->debug_store_index ], response);
        ++parse_instruction->debug_store_index;    // add message into debug info data structure
        Execute_Query( parse_instruction );
        //Print_String_Array(parse_instruction->response_array);
        Send_Instruction_Result( client_conn, parse_instruction);
        Free_Instruction_Mem(parse_instruction);
    }
    else if( instruction_type == debug_t)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "DEBUG:\tSuccess, rec'vd \"%s\", parsed to DEBUG command", parse_instruction->socket_receive);
        parse_instruction->debug_array[ parse_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( parse_instruction->debug_array[ parse_instruction->debug_store_index ], response);
        ++parse_instruction->debug_store_index;    // add message into debug info data structure
        Change_Debug_State( parse_instruction );
        Send_Instruction_Result( client_conn, parse_instruction);
        Free_Instruction_Mem(parse_instruction);
    }
    else if( instruction_type == verbose_t)
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "DEBUG:\tSuccess, rec'vd \"%s\", parsed to VERBOSE command", parse_instruction->socket_receive);
        parse_instruction->debug_array[ parse_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( parse_instruction->debug_array[ parse_instruction->debug_store_index ], response);
        ++parse_instruction->debug_store_index;    // add message into debug info data structure
        Change_Verbose_State( parse_instruction );
        Send_Instruction_Result( client_conn, parse_instruction);
        Free_Instruction_Mem(parse_instruction);
    }
}

void Change_Debug_State(Instruction_Info* instruction)
{
    if( String_Contains_Ignore_Case( instruction->socket_receive, "debug on") || String_Contains_Ignore_Case( instruction->socket_receive, "debug_on") )
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "%s changed debug output to ON", CHECKMARK);
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( instruction->response_array[ instruction->response_store_index ], response);
        ++instruction->response_store_index;    // add message into debug info data structure
        instruction->response_array[ instruction->response_store_index ] = NULL;
        SEND_DEBUG = true;
    }
    if( String_Contains_Ignore_Case( instruction->socket_receive, "debug off") || String_Contains_Ignore_Case( instruction->socket_receive, "debug_off") )
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "%s changed debug output to OFF", CHECKMARK);
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( instruction->response_array[ instruction->response_store_index ], response);
        ++instruction->response_store_index;    // add message into debug info data structure
        instruction->response_array[ instruction->response_store_index ] = NULL;
        SEND_DEBUG = false;
    }
}

void Change_Verbose_State(Instruction_Info* instruction)
{
    if( String_Contains_Ignore_Case( instruction->socket_receive, "verbose on") || String_Contains_Ignore_Case( instruction->socket_receive, "verbose_on") )
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "%s changed verbose output to ON", CHECKMARK);
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( instruction->response_array[ instruction->response_store_index ], response);
        ++instruction->response_store_index;    // add message into debug info data structure
        instruction->response_array[ instruction->response_store_index ] = NULL;
        SEND_VERBOSE = true;
    }
    if( String_Contains_Ignore_Case( instruction->socket_receive, "verbose off") || String_Contains_Ignore_Case( instruction->socket_receive, "verbose_off") )
    {
        char response[MAX_RESPONSE_LENGTH];
        sprintf(response, "%s changed verbose output to OFF", CHECKMARK);
        instruction->response_array[ instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( instruction->response_array[ instruction->response_store_index ], response);
        ++instruction->response_store_index;    // add message into debug info data structure
        instruction->response_array[ instruction->response_store_index ] = NULL;
        SEND_VERBOSE = false;
    }
}

instruction_t Get_Instruction_Type(Instruction_Info* socket_instruction)
{
    Trim_Leading_Trailing_Whitespace(socket_instruction->socket_receive);
    char first_character = socket_instruction->socket_receive[0];
    char second_character = socket_instruction->socket_receive[1];

    if( first_character == '?')
    {
        socket_instruction->instruction_type = query_t;
        return query_t;
    }
    else if( first_character == '>')
    {
        socket_instruction->instruction_type = command_t;
        return command_t;
    }
    else if( first_character == 'h' || second_character == 'h')
    {
        if( Is_Help_Command(socket_instruction) )
        {
            return help_t;
        }
        else
            return syntax_error_t;
    }
    else if( Is_Debug_Command(socket_instruction) )
        return debug_t;
    else if( Is_Verbose_Command(socket_instruction) )
        return verbose_t;
    else
    {
        socket_instruction->instruction_type = syntax_error_t;
        return syntax_error_t;
    }
}

bool Is_Help_Command(Instruction_Info* socket_instruction)
{
    char response[MAX_RESPONSE_LENGTH];
    char* first_token = Parse_First_Token( socket_instruction->socket_receive);
    bool is_help_command = String_Equals_Ignore_Case(first_token, "HELP");
    free(first_token);
    if( is_help_command )
    {
        sprintf(response, "DEBUG:\tSuccess, rec'vd instruction: \"%s\"", socket_instruction->socket_receive);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        socket_instruction->instruction_type = help_t;
        socket_instruction->this_query = HELP;
        return true;
    }
    return false;
}

bool Is_Debug_Command(Instruction_Info* socket_instruction)
{
    char response[MAX_RESPONSE_LENGTH];
    bool is_debug_command = String_Contains_Ignore_Case( socket_instruction->socket_receive, "debug" );
    if( is_debug_command )
    {
        sprintf(response, "\tDEBUG: Success, rec'vd debug instruction: \"%s\"", socket_instruction->socket_receive);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        socket_instruction->instruction_type = debug_t;
        return true;
    }
    return false;
}

bool Is_Verbose_Command(Instruction_Info* socket_instruction)
{
    char response[MAX_RESPONSE_LENGTH];
    bool is_verbose_command = String_Contains_Ignore_Case( socket_instruction->socket_receive, "verbose" );
    if( is_verbose_command )
    {
        sprintf(response, "\tDEBUG: Success, rec'vd debug instruction: \"%s\"", socket_instruction->socket_receive);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        socket_instruction->instruction_type = verbose_t;
        return true;
    }
    return false;
}

// verify has leading '>' or '?'
// Parse command name to new string
// parse arguments if any, to new string
// verify command name
// verify arguments match command
bool Is_Command(Instruction_Info* socket_instruction)
{
    char response[MAX_RESPONSE_LENGTH];
    if( socket_instruction->instruction_type == syntax_error_t )
    {
        sprintf(response, "\t%s SyntaxError: rec'vd instruction \"%s\", missing syntax '>' or '?'", X_ERROR, socket_instruction->socket_receive);
        socket_instruction->response_array[ socket_instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->response_array[ socket_instruction->response_store_index ], response);
        ++socket_instruction->response_store_index;
        socket_instruction->response_array[ socket_instruction->response_store_index ] = NULL;
        return false;
    }
    else if( !Is_In_Command_List(socket_instruction) )           // verify the command received on socket is in the official command list
    {
        sprintf(response, "DEBUG: CMD_PARSE_ERROR, CMD \"%s\", does not have matching command", socket_instruction->socket_receive);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
        return false;
    }
    else if( !Has_Correct_Argument(socket_instruction) )    // verify the command received on socket is in the official command list
    {
        sprintf(response, "\t%s ARGUMENT_ERROR: rec'vd \"%s\", does not have valid argument", X_ERROR, socket_instruction->socket_receive);
        socket_instruction->response_array[ socket_instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->response_array[ socket_instruction->response_store_index ], response);
        ++socket_instruction->response_store_index;
        socket_instruction->response_array[ socket_instruction->response_store_index ] = NULL;
        return false;
    }
    return true;
}

bool Is_Query(Instruction_Info* socket_instruction)
{
    char response[MAX_RESPONSE_LENGTH];

    if( Get_Instruction_Type( socket_instruction ) == syntax_error_t )
    {

        sprintf(response, "DEBUG:\tSyntaxError, rec'vd instruction \"%s\", missing syntax '>' or '?'", socket_instruction->socket_receive);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        return false;
    }

    if( !Is_In_Query_List(socket_instruction) )           // verify the command received on socket is in the official command list
    {
        socket_instruction->instruction_type = syntax_error_t;
        return false;
    }

    if( !Has_Correct_Argument(socket_instruction) )    // verify the command received on socket is in the official command list
        return false;

    return true;
}

// get index of command in STR_COMMAND_LIST[], which matches string received on the socket
// if index greater than 0, then it is in command list ( function Get_Command_Index() returns -1 if not found )
bool Is_In_Command_List(Instruction_Info* socket_instruction)
{
    // parse command string out and store to field "instruction_str"
    char* first_token = Parse_First_Token( socket_instruction->socket_receive );
    strcpy(socket_instruction->instruction_str, first_token);       // copy command string into data structure
    free(first_token);                                              // free dynamically allocated memory

    char response[MAX_RESPONSE_LENGTH];
    socket_instruction->this_command = Get_Command( socket_instruction );  // get the command index which matches the received string
    if( socket_instruction->this_command == CMD_NOT_FOUND)       // Command not found
    {
        sprintf(response, "%s SYNTAX_ERROR: CMD \"%s\" in string \"%s\" not recognized.\n\t   to view CMD list enter: \">\" ", X_ERROR, socket_instruction->instruction_str, socket_instruction->socket_receive);
        socket_instruction->response_array[ socket_instruction->response_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->response_array[ socket_instruction->response_store_index ], response);
        ++socket_instruction->response_store_index;    // add message into debug info data structure
        socket_instruction->response_array[ socket_instruction->response_store_index ] = NULL;
        return false;
    }
    else
    {
        sprintf(response, "DEBUG:\tParse_Success, \"%s\" is valid CMD.", socket_instruction->instruction_str);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
        return true;
    }
}

// get index of command in STR_COMMAND_LIST[], which matches string received on the socket
// if index greater than 0, then it is in command list ( function Get_Command_Index() returns -1 if not found )
bool Is_In_Query_List(Instruction_Info* socket_instruction)
{
    // parse command string out and store to field "instruction_str"
    char* first_token = Parse_First_Token( socket_instruction->socket_receive );
    strcpy(socket_instruction->instruction_str, first_token);       // copy command string into data structure
    free(first_token);                                              // free dynamically allocated memory

    char response[MAX_RESPONSE_LENGTH];
    socket_instruction->this_query = Get_Query( socket_instruction );  // get the command index which matches the received string


    if( socket_instruction->this_query == NOT_A_QUERY)       // Command not found
    {
        sprintf(response, "DEBUG:\tSYNTAX_ERROR: QUERY \"%s\" not recognized.\n\tto view QUERY list enter: \"?\" ", socket_instruction->instruction_str);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
        return false;
    }
    else
    {
        sprintf(response, "DEBUG:\tParse_Success, QUERY \"%s\" is valid.", socket_instruction->instruction_str);
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
        strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
        ++socket_instruction->debug_store_index;    // add message into debug info data structure
        socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
        return true;
    }
}

COMMAND Get_Command(Instruction_Info* socket_instruction)
{
    COMMAND specific_command;
    int num_commands = ARRAY_SIZE( STR_COMMAND_LIST);
    bool found_match = false;

    // inspect which command the input string matches
    for(int command_index = 0; command_index<num_commands; ++command_index)
    {
        if( String_Equals_Ignore_Case( socket_instruction->instruction_str, STR_COMMAND_LIST[ command_index ] ) )
        {
            //printf(" \"%s\" matches command: %s, command index %d\n", socket_string, STR_COMMAND_LIST[command_index], command_index);
            specific_command = ENUM_COMMAND_LIST[ command_index ];
            socket_instruction->index_of_instruction = command_index;
            found_match = true;
            break;
        }
    }
    if( !found_match ) // in this case the command was not found
        return CMD_NOT_FOUND;
    else return specific_command;
}


QUERY Get_Query(Instruction_Info* socket_instruction)
{
    QUERY specific_query;
    int num_queries = ARRAY_SIZE( STR_QUERY_LIST);
    bool found_match = false;

    // inspect which command the input string matches
    for(int query_index = 0; query_index<num_queries; ++query_index)
    {
        if( String_Equals_Ignore_Case( socket_instruction->instruction_str, STR_QUERY_LIST[ query_index ] ) )
        {
            //printf(" \"%s\" matches query: %s, query index %d\n", socket_string, STR_QUERY_LIST[command_index], command_index);
            specific_query = ENUM_QUERY_LIST[ query_index ];
            socket_instruction->index_of_instruction = query_index;
            found_match = true;
            break;
        }
    }
    if( !found_match ) // in this case the command was not found
    {
        return NOT_A_QUERY;
    }

    else return specific_query;
}

bool Has_Correct_Argument(Instruction_Info* socket_instruction)
{
    char* socket_argument_string = Parse_Second_Token( socket_instruction->socket_receive );
    strcpy(socket_instruction->argument_str, socket_argument_string);
    free(socket_argument_string);

    instruction_t instruction_type = socket_instruction->instruction_type;

    ARGUMENT_TYPE arg_type;
    if( instruction_type == command_t )
    {
        arg_type = Command_Args[ socket_instruction->index_of_instruction ];
    }
    else if( instruction_type == query_t )
    {
        arg_type = Query_Args[ socket_instruction->index_of_instruction ];
    }
    else
        return false;

    int argument_length = strlen(socket_instruction->argument_str);
    char response[MAX_RESPONSE_LENGTH];
    if( arg_type == NONE)
    {
        if( argument_length == 0)
            return true;
        else
            return false;
    }
    else if( arg_type == DOUBLE)
    {
        if( String_Is_Double(socket_instruction->argument_str) )
        {
            sprintf(response, "DEBUG:\tArgumentSuccess: ARG \"%s\" is double", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return true;
        }
        else
        {
            sprintf(response, "DEBUG:\tIsDoubleError: ARG \"%s\"", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return false;
        }
    }
    else if( arg_type == STRING)
    {
        // verify nonzero string length
        if( argument_length > 0)
        {
            sprintf(response, "DEBUG:\tArgumentSuccess: ARG \"%s\" is STRING", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return true;
        }
        else
        {
            sprintf(response, "DEBUG:\tStringError: no string arg present. Received:\"%s\" ", socket_instruction->socket_receive);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return false;
        }
    }
    else if( arg_type == TIME_STRING)
    {
        if( String_Is_TimeDate(socket_instruction) )
        {
            sprintf(response, "DEBUG:\tArgumentSuccess: ARG \"%s\" is valid TIMEDATE ", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return true;
        }
        else
        {
            sprintf(response, "DEBUG:\tTimeDateError: argument \"%s\" not valid. Use format  MM-DD-YYYY_HH.MM.SS ", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return false;
        }
    }
    else if( arg_type == FILENAME)
    {
        if( String_Is_Filename(socket_instruction->argument_str) )
        {
            sprintf(response, "DEBUG:\tARGUMENT_SUCCESS: argument \"%s\" is a valid FILENAME\n", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return true;
        }
        else
        {
            sprintf(response, "DEBUG:\tARGUMENT_ERROR: argument \"%s\" not a valid FILENAME\n\tINFO: a valid FILENAME must have correct extension (.log, .profile, .config, etc.)\n", socket_instruction->argument_str);
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = (char*)malloc( sizeof(char*) * strlen(response) + 1);
            strcpy( socket_instruction->debug_array[ socket_instruction->debug_store_index ], response);
            ++socket_instruction->debug_store_index;    // add message into debug info data structure
            socket_instruction->debug_array[ socket_instruction->debug_store_index ] = NULL;
            return false;
        }
    }
    return false;
}


#endif
