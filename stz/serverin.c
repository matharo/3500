#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MY_SOCK_PATH "./local"
#define user_Count 100
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct user_struct {
	char message[1024];
	char username[100];
	int online;
	int socket;
	int user_slot;
};

struct user_struct userArray[user_Count];

void *function(void *args) {
	struct user_struct *new_client = (struct user_struct*) args;
	char toSend[1024];
	int i;
	int quit = 0;

	for (i = 0; i < user_Count; i++) {
		if (userArray[i].online == 1 && i == new_client->user_slot) {
			char toSend[1024];
			sprintf(new_client->username, "%s%d", "User", new_client->user_slot);
			printf("%s has joined the server.\n", new_client->username);

		//	sprintf(toSend, "%s", new_client->username, "has joined the server.");
			//write(userArray[i].socket, toSend, 1024);
		}
	}
	while (1) {
		int ret;
		ret = read(new_client->socket, new_client->message, 1024);
		if (ret == -1) { 
			handle_error("Read Error"); 
			break; 
		}

		if (strncmp(new_client->message, "quit\n", 5) == 0) {
			sprintf(new_client->message, "%s", "has left.");
			//printf("%s has left the server.\n", new_client->username)
			quit = 1;
		}
		
		if (strncmp(new_client->message, "name ", 5) == 0) {
			char *tok = strtok(new_client->message, " \n");
			tok = strtok(NULL, " \n");
			strcpy(new_client->username, tok);
		}

		sprintf(toSend, "[%s]: %s\n", new_client->username, new_client->message);
		printf("%s\n", toSend);

		for (i = 0; i < user_Count; i++) {
			if (userArray[i].online == 1 && i != new_client->user_slot) {
				write(userArray[i].socket, toSend, 1024);
			}
		}
		if (quit) {
			new_client->online = 0;
			pthread_exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
	char buffer[50];
	unlink(MY_SOCK_PATH);
	int servfd, clientfd, new_sfd;
	struct sockaddr_in my_addr;
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_size;
	pthread_t th_array[user_Count];

	int port = atoi(argv[2]);
	char* ip = argv[1];
	printf("IP address is %s\n", ip);

	//make the user active
	int i;  //counter
	for (i = 0; i < user_Count; i++)
	{
		userArray[i].online = 0;
	}

	//servfd = socket(AF_UNIX, SOCK_STREAM, 0);   //for local
	//servfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0); makes nonblocking, but cannot keep listening
	servfd = socket(AF_INET,SOCK_STREAM,0);
	if (servfd == -1)
		handle_error("Socket Error");

	//my_addr.sun_family = AF_UNIX;   //for local access to server
	//my_addr.sun_addr = inet_addr(ip);
 	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = inet_addr(ip);
	my_addr.sin_port = htons(port);
	memset(my_addr.sin_zero,'\0',sizeof(my_addr.sin_zero));
	//strncpy(my_addr.sun_path, MY_SOCK_PATH, sizeof(my_addr.sun_path) - 1); //for un

	if (bind(servfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) == -1)
		handle_error("Bind Error");
	else
		printf("Bind successful\n");
	//listens for connections
	if (listen(servfd, 50) == -1)
		handle_error("Listen Error");
	else
		printf("Listening...\n");

	peer_addr_size = sizeof(peer_addr);

	int available;
	while (1) {
		//accepts client	
		clientfd = accept(servfd, (struct sockaddr *) &peer_addr, &peer_addr_size); 
		if (clientfd == -1) {
			handle_error("Accept Error");
		}
		else {
			int j;
			for (j = 0; j < user_Count; j++) {
				if (!userArray[j].online) {
					available = j;
					j = user_Count + 1;
				}
			}
			if (j == user_Count) {
				printf("Reached user max capacity.\n");
			}
			else {
				userArray[available].socket = clientfd;
				userArray[available].online = 1;
				userArray[available].user_slot = available;
				pthread_create(&th_array[available], NULL, function, &userArray[available]);
			}
		}
	}
	//deletes socket pathname, MY_SOCK_PATH
	unlink(MY_SOCK_PATH);

}
