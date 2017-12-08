//Lorna Xiao and Vyshnavee Reddlapalli
//lab5 and studio25
//server.c
//implements: quit, ls, multiple clients, name
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define num_user 50 
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)
//defines user
struct user_struct {
	char message[1024];
	char name[100];
	int online;
	int socket;
	int slot;
};
//array holding all users
struct user_struct userArray[num_user];
//checker for when user is connected
void *connectUser(void *args) {
	struct user_struct *new_user = (struct user_struct*) args;
	char send[1024];
	int i;
	int quit = 0;
	//user joins server
	for (i = 0; i < num_user; i++) {
		if (userArray[i].online == 1 && i == new_user->slot) {
			sprintf(new_user->name, "%s%d", "User", new_user->slot);
			printf("%s has joined the server.\n", new_user->name);
		}
	}
	while (1) {
		int ret;
		ret = read(new_user->socket, new_user->message, 1024);
		if (ret == -1) { 
			handle_error("Read Error"); 
			break; 
		}
		//if type quit or ^C
		if ((strncmp(new_user->message, "quit\n", 5) == 0) || (strncmp(new_user->message,"^C\n",3)==0)){
			sprintf(new_user->message, "%s", "has left.");
			quit = 1;
		}
		//change name
		if (strncmp(new_user->message, "name ", 5) == 0) {
			char *tok = strtok(new_user->message, " \n");
			tok = strtok(NULL, " \n");
			strcpy(new_user->name, tok);
			sprintf(new_user->message,"%s","changed their name.");
		}
		//display ls
		if (strncmp(new_user->message,"ls\n",3)==0){
			char buffer[1024];
			FILE* file;
                        file = popen("ls -l","r");
			if (file == NULL) handle_error("Failed to run command\n");
                        while(fgets(buffer,1024,file)!=NULL)
				printf(buffer);
			pclose(file);
                }	
		//prints out user name and message to server chat box
		sprintf(send, "%s: %s\n", new_user->name, new_user->message);
		printf("%s\n", send);

		for (i = 0; i < num_user; i++) {
			if (userArray[i].online == 1 && i != new_user->slot) {
				write(userArray[i].socket, send, 1024);
			}
		}
		if (quit) {
			new_user->online = 0;
			pthread_exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
	char buffer[50];
	int servfd, clientfd;
	struct sockaddr_in my_addr;
	struct sockaddr_storage stor_addr;
	socklen_t stor_addr_size;
	pthread_t th_array[num_user];

	int port = atoi(argv[2]);
	char* ipaddr = argv[1];
	printf("IP address is %s, port is %d\n", ipaddr,port);

	servfd = socket(AF_INET,SOCK_STREAM,0);
	if (servfd == -1)
		handle_error("Socket Error");
	
	//initialize ip and port 
 	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = inet_addr(ipaddr);
	my_addr.sin_port = htons(port);
	memset(my_addr.sin_zero,'\0',sizeof(my_addr.sin_zero));

	//binds to server
	if (bind(servfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) == -1)
		handle_error("Bind Error");
	else
		printf("Bind successful\n");

	//listens for connections
	if (listen(servfd, 50) == -1)
		handle_error("Listen Error");
	else
		printf("Listening...\n");

	stor_addr_size = sizeof(stor_addr);

	//accepts any connections
	int on;
	while (1) {
		clientfd = accept(servfd, (struct sockaddr *) &stor_addr, &stor_addr_size); 
		if (clientfd == -1) {
			handle_error("Accept Error");
		}
		//keeps track of number of clients that connect to server
		else {
			int j;
			for (j = 0; j < num_user; j++) {
				if (!userArray[j].online) {
					on = j;
					j = num_user + 1;
				}
			}
			if (j == num_user) {
				printf("Reached user max capacity.\n");
			}
			else {
				userArray[on].socket = clientfd;
				userArray[on].online = 1;
				userArray[on].slot = on;
				pthread_create(&th_array[on], NULL, connectUser, &userArray[on]);
			}
		}
	}
}
