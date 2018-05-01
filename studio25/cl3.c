//Lorna Xiao
//Studio 24
//client.c
//Received source code and help from https://vcansimplify.wordpress.com/2013/03/14/c-socket-tutorial-echo-server/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
 
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof servaddr);
 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
 
    //set ip address to...
    //servaddr needs to be int
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
 
    //connect device whose address and port number is in servaddr
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
    //client repeats forever
      while(1)
      {
	//clear
        bzero( sendline, 100);
        bzero( recvline, 100);
	//reading string from stdin in sendline
	if (strcmp(recvline,"quit") == 0)
	{
		unlink(recvline);
		//sendline = NULL;
	}
        fgets(sendline,100,stdin); /*stdin = 0 , for standard input */
 
	//write sendline in sockfd
        write(sockfd,sendline,strlen(sendline)+1);
	//read from sockfd in screvline
        read(sockfd,recvline,100);
	//display recvline
        printf("%s",recvline);
//	unlink(sendline);
       }
 
}
