#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MY_SOCK_PATH "./local"
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct sock {
	int socket;
};

void *thread_entry(void *args) {
	while (1) {
		struct sock *sock_ptr = (struct sock*) args;
		char input[50];
		int ret;
		ret = read(sock_ptr->socket, input, 50);
		if (ret == -1) handle_error("read");
		write(stdout, input, ret);
	}
}

int main(int argc, char *argv[]) {
	int clientfd;
	int port = atoi(argv[2]);
	char* ip = argv[1];
	char buffer[50];
	struct sockaddr_in serverAddr;
	socklen_t addr_size = sizeof(struct sockaddr);
	
	//	struct struct_socket variable;
	
	clientfd = socket(AF_INET, SOCK_STREAM, 0);   //1
	if (clientfd == -1)
		handle_error("socket");

	//memset(&serverAddr, 0, sizeof(struct sockaddr));

	//strncpy(serverAddr.sun_path, MY_SOCK_PATH, sizeof(serverAddr.sun_path) - 1);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);
	memset(serverAddr.sin_zero,'\0',sizeof(serverAddr.sin_zero));
	addr_size = sizeof serverAddr;
	
	if(connect(clientfd, (struct sockaddr*) &serverAddr, addr_size) == -1)
		handle_error("connect");

	//similary to thread but read STDIN_FILENO and write to socket.

	pthread_t sock_t;
	struct sock sock_conn;
	sock_conn.socket = clientfd;
	
	pthread_create(&sock_t, NULL, thread_entry, &sock_conn);

	int ret;
	ret = read(stdin, buffer, 50);
	write(clientfd, buffer, ret);

	//instructions for client
	//recieve connection
	//read from socket
	//write to socket and send data to server
	while (strncmp(buffer, "quit\n", 5)) {
		printf("Send message to server: ");
		fgets(buffer, 1024, stdin);
		write(clientfd, (void*)buffer, 50);
	}

	return 0;
}
