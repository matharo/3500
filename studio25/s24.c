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
#include <sys/un.h>
#define MY_SOCK_PATH "./LOCAL"
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)
int main(){
	char str[100];
	int listen_fd, client_fd;	//listen is for server

	struct sockaddr_un servaddr;
	struct sockaddr_storage storaddr;
	socklen_t storsize;

	listen_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listen_fd == -1) handle_error("socket error");
	
	memset(&servaddr,0,sizeof(struct sockaddr_un)); 
	servaddr.sun_family=AF_UNIX;
	strncpy(servaddr.sun_path,MY_SOCK_PATH,sizeof(servaddr.sun_path)-1);

	if (bind(listen_fd, (struct sockaddr *) &servaddr, 
		sizeof(struct sockaddr_un)) == -1)
		handle_error("bind error"); 

	if (listen(listen_fd,10)==-1) handle_error("listen error");
	else	printf("Listening...\n");

	storsize = sizeof(struct sockaddr_un);

	while(1){
		client_fd = accept(listen_fd,(struct sockaddr*)&storaddr,
			&storsize);
		if (client_fd ==-1) handle_error("accept error");
		else
		{
			bzero(str,100);
			int ret = read(client_fd,str,100);
			if(ret==-1)handle_error("read error");
			if (strncmp(str,"quit\n",5)==0 || strncmp(str,"^C\n",3)==0)
				shutdown(client_fd,SHUT_RDWR);
			if (strncmp(str,"ls\n",3)==0){
				char buffer[1024];
				FILE* file = popen("ls -l","r");
				while(fgets(buffer,100,file)!=NULL)
					fprintf(stdout,"%s\n",buffer);
			}
			if (strncmp(str,"name ",5)==0)
				printf("user name has changed\n");
			write(client_fd,str,strlen(str)+1);
		}
	}
	unlink(MY_SOCK_PATH);
}
