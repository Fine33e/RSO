#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "message.c"


void send_time_response(int sockfd, message * request){
    int id = get_rq_id(request);
    message response;
    byte code [4] = TIME_RESPONSE_CODE;


    time_t current_time = time(NULL);
    char * formatted_current_time = ctime(&current_time);
    int formated_current_time_len = strlen(formatted_current_time);
    printf("Length: %d\n", formated_current_time_len);

    write_message_code(&response, code);
    write_rq_id(&response, id);
    write_length(&response, formated_current_time_len);
    write_time(&response, formatted_current_time, formated_current_time_len);

    //byte * buffor = serialize_message(&response);

    write (sockfd, buffor, get_message_size());
    free(buffor);
    printf("Send time response\n");
}






int main ()
{
	int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_sockfd = socket (AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl (INADDR_ANY);
	server_address.sin_port = htons (9734);
	server_len = sizeof (server_address);
	bind (server_sockfd, (struct sockaddr *) &server_address, server_len);

	/*  Create a connection queue and wait for clients.  */

	listen (server_sockfd, 5);

	while (1)
	{
		

		printf ("server waiting\n");

		/*  Accept connection.  */

		client_len = sizeof (client_address);
		client_sockfd = accept (server_sockfd,
				(struct sockaddr *) &client_address,
				&client_len);

	
		if(strcmp(message_code, TIME_REQUEST_CODE) == 0){
			send_time_response(client_sockfd, &request);
		}

		

		else{
			close (client_sockfd);	
		}
	
	}
}
