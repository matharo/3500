//Lorna Xiao
//Studio 25
//Received and modified code from https://vcansimplify.wordpress.com/2013/03/14/c-socket-tutorial-echo-server/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
 
int main()
{
    char str[1024];
    int listen_fd, client_fd;	//listen is for server
    char counter[1024]; //client counter
    socklen_t addr_size;
    //struct to hold ip address and port numbers
    struct sockaddr_in servaddr;
    struct sockaddr_storage servstorage;
    //creates socket, of type sock-strema, all devices wanting
    //to connect to this socket will redirect to listen_fd
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    //clear
    //bzero( &servaddr, sizeof(servaddr));
 
    //set addressing scheme
    servaddr.sin_family = AF_INET;
    //listen on this port 7891
    servaddr.sin_port = htons(7891);
    //allow any ip to connect
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //memset(servaddr.sin_zero,'\0',sizeof servaddr.sin_zero);
    bzero(&servaddr,sizeof(servaddr));

    //listen to connections from address/port specified in sockaddr
    if (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1){
	    perror("Unable to bind\n");
	    return 0; 
    }
 
    //keep at most 10 connection requests waiting
    //11th one will fail
    if(listen(listen_fd, 10) == -1){
	    perror("Unable to connect to server\n");
	    return 0;
    }
    else{
    	printf("Listening for connections....\n");
	addr_size = sizeof servstorage;
	while(1){
    	//accept connection, if no connections to accept, wait
   	//file descriptor is returned, can be used to communicate
    	//whatever is sent by device accepted can be read from comm_fd
    	//whatever written to comm_fd is sent to other device
    	client_fd = accept(listen_fd, (struct sockaddr*) &servstorage, &addr_size);
    	//printf("Found a connection with: %s\n",comm_fd);
    	
	strcpy(str,"Server connected ");
	write(client_fd,str,strlen(str)+1);
	
	int readin = read(client_fd,counter,50);
	fopen(counter,NULL);//reads in what client typed
	printf("to client: %s\n", counter);
    }}

/*    while(1)
    {
        bzero( str, 100);			//clears str
        read(client_fd,str,100);		//read up to 100 bytes into str
        printf("Echoing back - %s",str); 	//display what is read
        write(client_fd, str, strlen(str)+1);	//send back str

	}*/    
}
