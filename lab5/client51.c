#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct sock{
	int socket;
};

void *thread_entry(void *args)
{
	while(1){
		struct sock *sock_ptr = (struct sock*) args;
		char msg[50];
		int ret = read(sock_ptr->socket,msg,50);
		if (ret == -1){
			handle_error("Read Error");}
		write(stdout,msg,ret);
	}
}
int main(int argc,char* argv[]){
	int clientfd;
	char* ipaddr = argv[1];
	int port = atoi(argv[2]);
	char buffer[50];
	struct sockaddr_in servaddr;
	socklen_t addrsize = sizeof(struct sockaddr);

	clientfd = socket(AF_INET,SOCK_STREAM,0);
	if (clientfd == -1)
		handle_error("Socket Error");
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ipaddr);
	servaddr.sin_port = htons(port);
	memset(servaddr.sin_zero,'\0',sizeof(servaddr.sin_zero));
	
	addrsize = sizeof(servaddr);

	if(connect(clientfd,(struct sockaddr *) &servaddr,addrsize)==-1)
		handle_error("Connect Error");
	else
		printf("Successfully connected\n");

	pthread_t sockThread;
	struct sock sock_connect;
	sock_connect.socket = clientfd;

	pthread_create(&sockThread,NULL,thread_entry,&sock_connect);

	int ret = read(stdin,buffer,50);
	write(clientfd,buffer,ret);

	//exit when user types quit
	while(strncmp(buffer,"quit\n",5)){
		printf("Enter message: ");
		fgets(buffer,1024,stdin);
		write(clientfd,(void*)buffer,50);
	}
	return 0;
}
