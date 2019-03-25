/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "message.c"


static int request_counter = 0;

static int id = 1;
int get_next_id(){
    return id++;
}

void send_time_request(int sockfd){
    request_counter++;
    printf("Send time request\n");
    message request;
    char code [4] = TIME_REQUEST_CODE;
    write_message_code(&request, code);
    write_rq_id(&request, get_next_id());
    //byte * buffor = serialize_message(&request);
    write (sockfd, buffor, get_message_size());
    free(buffor);
}

void read_and_handle_data(int sockfd){
	byte * buffor = (byte*) malloc(get_message_size());

	while(1){
	message response;

		if(strcmp(message_code, TIME_RESPONSE_CODE) == 0) {
            		request_counter--;
           		int len = get_length(&response);
            		char *msg = get_time(&response, len);
            		printf("The time: %s\n", msg);
		}







	}

}


int main ()
{
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;
	

	/*  Create a socket for the client.  */

	sockfd = socket (AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	address.sin_port = htons (9734);
	len = sizeof (address);

	/*  Now connect our socket to the server's socket.  */

	result = connect (sockfd, (struct sockaddr *) &address, len);

	if (result == -1)
	{
		perror ("oops: netclient");
		exit (1);
	}
  	
	


	/*  We can now read/write via sockfd.  */
	
	write (sockfd, NULL, 1);
	
	read_and_handle_data(sockfd);
	
	close (sockfd);
	exit (0);
}
