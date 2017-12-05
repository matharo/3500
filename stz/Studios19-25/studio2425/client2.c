#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
int clientSocket,newSocket;

void *readwrite(void* r){
	while(1){
		char buffer[1024];
		int ret2;
		ret2 = read(clientSocket, buffer, 1024);
		if (ret2 == -1){
			perror("Unable to read from server");
			exit(-1);
		} else if (ret2 == 0){
			printf("Disconnect\n");
			exit(-1);
		}
		printf("Data in: %s\n", buffer);
	}
}

int main(){
	char buff[1024];
	char buff2[1024];
	
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	pthread_t thread;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof serverAddr;
	int retConnect;
	retConnect = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	if (retConnect == -1){
		perror("Unable to connect");
	}

	pthread_create(&thread,NULL,readwrite,NULL);
	
	//while(1){
		char* ret;
		ret = fgets(buff2, 100, stdin);
		buff2[strlen(buff2)-1] = '\0';
		if (ret == NULL){//break;
			return 0;}
		write(clientSocket,buff2, strlen(buff2));
		while(1){
			int ret3 = read(clientSocket, buff, 1024);
                        if(ret3 == -1) {
                        	break;
                        }
                        else{
                        	write(STDOUT_FILENO,buff, ret3);
                                shutdown(newSocket, SHUT_RDWR);
                        }
		if(strncmp(buff2, "quit",4)==0) {
			pthread_cancel(thread);
			exit(0);
			break;
		}
		if(strncmp(buff2,"ls",4)==0)
		{
			fgets(popen(buff2,NULL));
			exit(0);
			break;
		}
			
	}
	
	pthread_join(thread,NULL);
	return 0;
}

