//Lorna Xiaoq
//Studio 24, server.c
//Received source and code from https://vcansimplify.wordpress.com/2013/03/14/c-socket-tutorial-echo-server/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
int main()
{
 
    char str[100];
    int listen_fd, client_fd;	//listen is for server

    //struct to hold ip address and port numbers
    struct sockaddr_in servaddr;

    //creates socket, of type sock-strema, all devices wanting
    //to connect to this socket will redirect to listen_fd
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    //clear
    bzero( &servaddr, sizeof(servaddr));
 
    //set addressing scheme
    servaddr.sin_family = AF_INET;
    //allow any ip to connect
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    //listen on port 22000
    servaddr.sin_port = htons(22000);
 
    //listen to connections from address/port specified in sockaddr
    if (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1){
	    perror("Unable to bind\n");
	    exit(EXIT_FAILURE);
    }
 
    //keep at most 10 connection requests waiting
    //11th one will fail
    if(listen(listen_fd, 10) == -1){
	    perror("Unable to connect to server\n");
	    exit(EXIT_FAILURE);
    }
    else{
    	printf("Listening for connections....\n");


    	//accept connection, if no connections to accept, wait
   	//file descriptor is returned, can be used to communicate
    	//whatever is sent by device accepted can be read from comm_fd
    	//whatever written to comm_fd is sent to other device
    	client_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
    	//printf("Found a connection with: %s\n",comm_fd); 
    }

    while(1)
    {
        bzero( str, 100);	//clears str
        read(client_fd,str,100);	//read up to 100 bytes into str
        printf("Echoing back - %s",str); 	//display what is read
        write(client_fd, str, strlen(str)+1);	//send back str
   }
}

