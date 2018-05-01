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
 
int main(){
    char str[100];
    int listen_fd, client_fd;	//listen is for server

    struct sockaddr_in servaddr;
    struct sockaddr_storage storaddr;
    socklen_t storsize;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) { perror("Socket error"); exit(EXIT_FAILURE);}
	
    bzero( &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(22000);
  
    if (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1){
	    perror("Unable to bind\n");
	    exit(EXIT_FAILURE);
    }
    if(listen(listen_fd, 10) == -1){
	    perror("Unable to connect to server\n");
	    exit(EXIT_FAILURE);
    }
    else{
    	printf("Listening for connections....\n");
    }

    storsize = sizeof(struct sockaddr_in);

    while(1)
    {
	client_fd = accept(listen_fd, (struct sockaddr*) &storaddr, &storsize);
        bzero( str, 100);	//clears str
        read(client_fd,str,100);	//read up to 100 bytes into str
        fopen(str,NULL);
	//if (strncmp(str,"quit\n",5)==0 || strncmp(str,"^C\n",3)==0)
		//shutdown(client_fd,SHUT_RDWR);
	//	break;
	write(client_fd, str, strlen(str)+1);	//send back str
   }
}

