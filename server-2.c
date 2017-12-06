// Aime Nunez and Deondre Strickland
//May 4th, 2017

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<pthread.h>
#define MY_SOCK_PATH "./local"
#define LISTEN_BACKLOG 50
#define USER_COUNT 100

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)


struct user {
	char message[1024];
	char name[100];
	int active;
	int socket;
	int slot;
};

struct user structArray[USER_COUNT];

void *handler(void *c) {
	struct user *client = (struct user *) c;
	sprintf(client->name, "%s%d", "User_", client->slot);
	char toSend[1024];
	int i = 0;
	int quit = 0;

	// Used initially to broadcast to everyone user has joined the session
	for(i; i < USER_COUNT; i++) {
		if (structArray[i].active == 1 && i != client->slot) {
			char toSend[1024];
			sprintf(toSend, "%s", client->name, " has joined.");
			write(structArray[i].socket, toSend, 1024);
		}
	}

	while(1) {
		
		// Reads socket
		if (read(client->socket, client->message, 1024) == -1) { 
			handle_error("reading from client"); break;
		}

		// Alters users message if 
		if (strncmp(client->message,"quit\n", 5) == 0) {
			sprintf(client->message, "%s", "has left.");
			quit = 1;
		}

		if (strncmp(client->message, "name ", 5) == 0) {
			char *tok  = strtok(client->message, " ");
			tok = strtok(NULL, " "); // TODO error checking on this
			strcpy(client->name, tok);
		}

		// Assigns message to be delivered to client
		sprintf(toSend, "[%s]: %s", client->name, client->message);
		printf("%s\n", toSend);

		// Broadcasts message to all clients
		i = 0;
		for(i; i < USER_COUNT; i++) {
			if (structArray[i].active == 1 && i != client->slot) {
				write(structArray[i].socket, toSend, 1024);
			}
		}

		// Resets slot that was in use by client and exits
		if(quit) {
			client->active = 0;
			pthread_exit(0);
		}
	}	
}

int main(int argc, char *argv[]) {

	unlink(MY_SOCK_PATH); // necessary when server does not properly finish
	int sfd, cfd;
	struct sockaddr_un my_addr, peer_addr;
	socklen_t peer_addr_size;
	pthread_t threadArray[USER_COUNT];

	// Initializing all userSlots as inactive
	int counter;
	for (counter = 0; counter < USER_COUNT; counter++) { structArray[counter].active = 0; }
	
	// Creates socket
	sfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sfd == -1)
		handle_error("socket");

	// Clears structure
	memset(&my_addr, 0, sizeof(struct sockaddr_un));
	my_addr.sun_family = AF_UNIX;
	strncpy(my_addr.sun_path, MY_SOCK_PATH,
		sizeof(my_addr.sun_path) - 1);

	// Creates communication channel
	if (bind(sfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_un)) == -1)
		handle_error("bind");
	
	// Declares listening for incoming connections
	if (listen(sfd, LISTEN_BACKLOG) == -1)
		handle_error("listen");

	/* Now we can accept incoming connections one
	 *  at a time using accept(2) */
	peer_addr_size = sizeof(struct sockaddr_un);
	char buf[50];

	int firstAvailable;
	while(1) {
	
		cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
		if (cfd == -1) {
			handle_error("accept");

		} else {
			int i = 0;
			for (i; i < USER_COUNT; i++) {
				if (!structArray[i].active) {
					firstAvailable = i;
					i = USER_COUNT+1;
				}
			}

			if (i == USER_COUNT) {
				printf("Max capacity. Refused connection with client.\n");
			} else {
				structArray[firstAvailable].socket = cfd;
				structArray[firstAvailable].active = 1;
				structArray[firstAvailable].slot = firstAvailable;
				pthread_create(&threadArray[firstAvailable], NULL, handler, &structArray[firstAvailable]);
			}
		}
	}

	unlink(MY_SOCK_PATH);

}
