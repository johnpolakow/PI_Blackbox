
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include "clientserver.h"



#define MESSAGE_LENGTH 100
#define DEFAULT_SERVER_IP		"10.198.21.156"
//#define DEFAULT_SERVER_IP		"127.0.0.1"
#define DEFAULT_SERVER_PORT		"2020"

int packet_index = 0;
char complete_receive_string[200];

int Receive_Data(conn_t* connection, char* buffer);
void Erase_String_Contents(char* string);
bool Check_FD_Ready(conn_t* connection, fd_set* FD, struct timeval* tv);

void Erase_String_Contents(char* string)
{
   memset(string,0,sizeof(string));                                     // zero out string memery locations
   string[0] = '\0';                                                    // add null terminator
}

int Receive_Data(conn_t* connection, char* buffer)
{
		Erase_String_Contents((char*)buffer);
		int receive_Bytes = recvData(connection , (char*)buffer, (int)sizeof(buffer));
		buffer[receive_Bytes] = '\0';
		return receive_Bytes;
}

void Read_Socket_nBytes(conn_t* client_conn, char* buff, int num_bytes)
{
		Erase_String_Contents(complete_receive_string);
		while(num_bytes>0)
		{
			int read_chars = Receive_Data(client_conn, buff);
			num_bytes -= read_chars;
			strncat(complete_receive_string, buff, read_chars);
			Erase_String_Contents(buff);
		}

}

void Get_String(char* usr_string)
{
	        size_t characters;
	      	size_t bufsize = 128;
        	char* keyboard_input_buffer;
					keyboard_input_buffer = (char*)malloc(sizeof( char* ) * 100 );
					char send_buffer[MESSAGE_LENGTH];

	        		printf("----------------------------------\n");
							printf( COLOR_BRIGHT_MAGENTA "\t***CLIENT*** ( HUB )\n\n" COLOR_RESET);
	        		printf("##: ");
	            characters = getline(&keyboard_input_buffer,&bufsize,stdin);
	        		keyboard_input_buffer[characters-1] = '\0';	// null terminate the string
	        		//sprintf(send_buffer, "%s [client send# %d]", keyboard_input_buffer, packet_index);  // copy text read from keyboard to send buffer
              sprintf(send_buffer, "%s", keyboard_input_buffer);  // copy text read from keyboard to send buffer
	            send_buffer[strlen(send_buffer)] = '\0';
							++packet_index;

							strcpy(usr_string, send_buffer);

	            /* print the packet message */
	            //printf("\nSEND:\t%s\n", usr_string);
	            //printf("\n%s\n", usr_string);

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



int main (int argc, char* argv[]) {
	fd_set read_FD;
	struct timeval tv;

	const char* serverIP = DEFAULT_SERVER_IP;
	const char* serverPort = DEFAULT_SERVER_PORT;

	printf("Connecting to server " COLOR_BOLD_GREEN " %s " COLOR_RESET " on PORT " COLOR_BOLD_GREEN "%s\n\n" COLOR_RESET, serverIP, serverPort);

	conn_t* server_conn = connect_tcp(serverIP, serverPort);
	if (!server_conn )
		return -1;

	//"data" to send, and to receive and verify
	char recv_Buf[2000];
	char send_Buf[1];
	char console_string[100];

  bool expect_response = false;
	while (1)
	{
		tv.tv_sec = 0;
		tv.tv_usec = 10000; // 100ms
		FD_ZERO(&read_FD);
		FD_SET(server_conn ->sockfd, &read_FD);

		if ( !Check_FD_Ready(server_conn, &read_FD, &tv)	)
		{
					break;
		}


		// recv data if available
		if (FD_ISSET(server_conn ->sockfd, &read_FD))
		{

			int count;
			ioctl( server_conn->sockfd, FIONREAD, &count);

			Read_Socket_nBytes(server_conn, recv_Buf, count);

			//printf("\nRECV: %s\n", complete_receive_string);
      printf(COLOR_BROWN "%s\n" COLOR_RESET, complete_receive_string);

			int receive_Bytes = strlen(recv_Buf);
			strncpy(complete_receive_string, (const char*)recv_Buf, receive_Bytes);

      expect_response = false;
		}
		else if( expect_response )
        continue;
		usleep(100);

		Erase_String_Contents(console_string);
		Get_String(console_string);
		int send_Bytes = sendData(server_conn , (char*)console_string, (int)strlen(console_string));
		if (send_Bytes <= 0)
					break;
    else expect_response = true;

	}

	// print final stats before exiting
	//stats_finalize(stats);

	return 0;
}
