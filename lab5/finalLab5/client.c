//Lorna Xiao and Vyshnavee Reddlapalli
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#include <netdb.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct sock {
	int socket;
};

void *thread_entry(void *args) {
	while (1) {
		struct sock *sock_ptr = (struct sock*) args;
		char msg[50];
		int ret;
		ret = read(sock_ptr->socket, msg, 50);
		if (ret == -1) handle_error("read");
		write(stdout, msg, ret);
	}
}

int main(int argc, char *argv[]) {
	int clientfd;
	char* ipaddr = argv[1];
	int port = atoi(argv[2]);
	char buffer[50];
	struct sockaddr_in my_addr;
	socklen_t addr_size = sizeof(struct sockaddr);

	printf("IP address is %s, port is %d\n",ipaddr,port);
	
	clientfd = socket(AF_INET, SOCK_STREAM, 0);   //1
	if (clientfd == -1)
		handle_error("socket error");

	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = inet_addr(ipaddr);
	my_addr.sin_port = htons(port);
	memset(my_addr.sin_zero,'\0',sizeof(my_addr.sin_zero));
	addr_size = sizeof my_addr;
	
	if(connect(clientfd, (struct sockaddr*) &my_addr, addr_size) == -1)
		handle_error("connect error");
	else
		printf("connected successfully\n");

	pthread_t thread;
	struct sock sock_connect;
	sock_connect.socket = clientfd;
	
	pthread_create(&thread, NULL, thread_entry, &sock_connect);

	int ret;
	ret = read(stdin, buffer, 50);
	while(1){
		printf("Enter message: ");
		fgets(buffer,1024,stdin);
		write(clientfd,(void*)buffer,50);
		if (strncmp(buffer,"quit\n",5)==0 || strncmp(buffer,"^C\n",3)==0)
			break;
		
	}

	return 0;
}
