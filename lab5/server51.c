#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define num_users 100
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct user_struct{
	char msg[1024];
	char name[25];
	int online;
	int socket;
	int slot;
};
struct user_struct userArray[num_users];

void *connectUser(void *args){
	struct user_struct *new_user = (struct user_struct*) args;
	char send[1024];
	int quit = 0;

	int i;
	for (i = 0; i < num_users; i++){
		if (userArray[i].online == 1 && i == new_user->slot)
		{
			sprintf(new_user->name,"%s%d","User",new_user->slot);
			printf("%s has joined the server.\n",new_user->name);
		}
	}
	while(1){
		if (read(new_user->socket,new_user->msg,1024) == -1)
		{	handle_error("Read Error");	}
		if (strncmp(new_user->msg,"quit\n",5) ){
			quit = 1;
			sprintf(new_user->msg,"%s"," has left the server.");
		}
		if (strncmp(new_user->msg,"name ", 5) ){
			char *token = strtok(new_user->msg," \n");
			token = strtok(NULL," \n");
			strcpy(new_user->name,token);
			sprintf(new_user->msg,"%s"," changed his name.");
		}
		for (i = 0; i < num_users;i++){
			if (userArray[i].online == 1 && i != new_user->slot)
				write(userArray[i].socket,send,1024);
		}
		if (quit){
			new_user->online = 0;
			pthread_exit(0);
		}

                sprintf(send,"%s: %s",new_user->name,new_user->msg);
                printf("%s\n",send);
		
	}
}
int main(int argc,char* argv[]){
	int servfd,clientfd;
	struct sockaddr_in servaddr;
	struct sockaddr_storage storaddr;
	socklen_t stor_size = sizeof(storaddr);
	pthread_t array[num_users];

	char* ipaddr = argv[1];
	int port = atoi(argv[2]);
	printf("IP Address is %s, Port is %d\n",ipaddr,port);

	servfd = socket(AF_INET,SOCK_STREAM,0);
	if (servfd == -1)
		handle_error("Socket Error");

	//initialize ip address and port
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ipaddr);
	servaddr.sin_port = htons(port);
	memset(servaddr.sin_zero,'\0',sizeof(servaddr.sin_zero));
	
	if (bind(servfd,(struct sockaddr *) &servaddr,sizeof(struct sockaddr_in))==-1)
		handle_error("Bind Error");
	else
		printf("Bind successful\n");

	if (listen(servfd,50)==-1)
		handle_error("Listen Error");
	else
		printf("Listening...\n");

	//accept connections between multiple clients
	int connect;
	char buffer[1024];
	while(1){
		clientfd = accept(servfd,(struct sockaddr *) &storaddr, &stor_size);
		if (clientfd == -1)
			handle_error("Accept Error");
		else{
			int j;
			for (j = 0; j < num_users; j++){
				if (!userArray[j].online){
					connect = j;
					j = num_users + 1;
				}
			}
			if (j == num_users)
				printf("Max user capacity\n");
			else{
				userArray[connect].socket = clientfd;
				userArray[connect].online = 1;
				userArray[connect].slot = connect;
				pthread_create(&array[connect],NULL,connectUser,&userArray[connect]);
			}
		}
	}
}
