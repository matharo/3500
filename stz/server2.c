
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include<sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>


#define MY_SOCK_PATH "./local"
#define LISTEN_BACKLOG 50
#define user_Count 100
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

struct user_struct {
	char message[1024];
	char username[100];
	int isactive;
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
		if (userArray[i].isactive == 1 && i == new_client->user_slot) {
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
		if (ret == -1) { handle_error("Read"); break; }

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
			if (userArray[i].isactive == 1 && i != new_client->user_slot) {
				write(userArray[i].socket, toSend, 1024);
			}
		}
		if (quit) {
			new_client->isactive = 0;
			pthread_exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
	char buffer[50];
	unlink(MY_SOCK_PATH);
	int sfd, cfd, new_sfd;
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;
	pthread_t th_array[user_Count];

	int port = atoi(argv[2]);
	char iP = argv[1];
	printf("IP address is %s.\n", iP)
	

	//make the user active
	int i;  //counter
	for (i = 0; i < user_Count; i++)
	{
		userArray[i].isactive = 0;
	}

	//sfd = socket(AF_UNIX, SOCK_STREAM, 0);   //for local
	sfd = socket(AF_NET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	
	if (sfd == -1)
		handle_error("socket");

	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	/* Clear structure */
	//my_addr.sun_family = AF_UNIX;   //for local access to server
 	my_addr.sin_family = AF_NET;
	my_addr.sin_addr = inet_addr(iP);
	my_addr.sin_port = htons(port);
	
	strncpy(my_addr.sun_path, MY_SOCK_PATH, sizeof(my_addr.sun_path) - 1);

	if (bind(sfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un)) == -1)
		handle_error("bind");  //2

	if (listen(sfd, LISTEN_BACKLOG) == -1)
		handle_error("listen");  //3

								 /* Now we can accept incoming connections one at a time using accept(2) */

	peer_addr_size = sizeof(struct sockaddr_un);

	int available;

	while (1) {
		cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);  //4
		if (cfd == -1) {
			handle_error("accept");
		}
		else {
			int j = 0;
			for (j; j < user_Count; j++) {
				if (!userArray[j].isactive) {
					available = j;
					j = user_Count + 1;
				}
			}
			if (j == user_Count) {
				printf("Reached max capacity.\n");
			}
			else {
				userArray[available].socket = cfd;
				userArray[available].isactive = 1;
				userArray[available].user_slot = available;
				pthread_create(&th_array[available], NULL, function, &userArray[available]);
			}
		}
	}

	/* When no longer required, the socket pathname, MY_SOCK_PATH
	should be deleted using unlink(2) or remove(3) */
	unlink(MY_SOCK_PATH);

}