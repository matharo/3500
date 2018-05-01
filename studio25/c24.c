//Lorna Xiao
//Studio 24
//client.c
//Received source code and help from https://vcansimplify.wordpress.com/2013/03/14/c-socket-tutorial-echo-server/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <netdb.h>
#define MY_SOCK_PATH "./LOCAL"
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_un servaddr;
 
    sockfd = socket(AF_UNIX,SOCK_STREAM,0);

    memset(&servaddr,0,sizeof(struct sockaddr_un));
    servaddr.sun_family=AF_UNIX;
    strncpy(servaddr.sun_path,MY_SOCK_PATH,sizeof(servaddr.sun_path)-1);

    //connect device whose address and port number is in servaddr
    connect(sockfd,(struct sockaddr *) &servaddr,sizeof(servaddr));

    //client repeats forever
      while(strncmp(recvline,"quit\n",5)==0 || strncmp(recvline,"^C\n",3)==0)
      {
	//clear
        bzero( sendline, 100);
        bzero( recvline, 100);
	printf("Enter message: ");
	//reading string from stdin in sendline
        fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
 
	//write sendline in sockfd
        write(sockfd,sendline,strlen(sendline)+1);
	//read from sockfd in screvline
        read(sockfd,recvline,100);
	//display recvline
        printf("%s",recvline);
       }
	unlink(MY_SOCK_PATH); 
}
