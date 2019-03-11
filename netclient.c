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
#define BST (+1)
#define CCT (+8)


int
main ()
{
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;
	char ch = 'A';
	char *local;

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

	
  	time_t rawtime;
  	struct tm *info;

  	time(&rawtime); 
 	/* Get GMT time */
 	info = gmtime(&rawtime );
  	write (sockfd, &ch, 1);
	printf("Current world clock:\n");
	
	write (sockfd, &ch, 1);
	printf("China  : %2d:%02d\n", (info->tm_hour+CCT)%24, info->tm_min);

	write (sockfd, &ch, 1);
 	printf("London : %2d:%02d\n", (info->tm_hour+BST)%24, info->tm_min);
 	
	
	/*
	time_t czas;
    	time( & czas );
    	printf( "Czas lokalny: %s", asctime( localtime( & czas ) ) );
    	printf( "Czas UTC: %s", asctime( gmtime( & czas ) ) );
	
	*local.asctime( localtime( & czas ) );
	write (sockfd, &*local, 1);
	*/


	/*  We can now read/write via sockfd.  */
	write (sockfd, &ch, 1);
	read (sockfd, &ch, 1);
	printf ("char from server = %c\n", ch);
	close (sockfd);
	exit (0);
}
