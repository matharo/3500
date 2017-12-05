#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
int main(){
	int servSocket, newSocket;
	char buffer[1024];
	char buff[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	servSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	if(bind(servSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))==-1){
		perror("Unable to bind");
		exit(-1);
	}
	
	//connect server
	if(listen(servSocket,5)==0)	{printf("Listening\n");}
	else	{printf("Error\n");}
	addr_size = sizeof serverStorage;
	
	while(1){
		//accept client, client socket
		newSocket = accept(servSocket, (struct sockaddr *) &serverStorage, &addr_size);
	
		strcpy(buffer,("Server connected for client %d\n",newSocket));
		write(newSocket,buffer,strlen(buffer));

		int ret;
		int result;
		ret = read(newSocket, buff, 50);
		fopen(buff,NULL);
		result = 1;
		printf("From client: %s\n", buff);
		char str1[15];
		strcpy(str1, "quit");
		result = strncmp(str1, buff, 4);
		
		while (result != 0){
			int ret3;
			char new_buff[1024];
			memset(new_buff, 0, 1024);
			ret = read(newSocket, new_buff, 50);
			if(ret <= 0) {
				printf("Error\n");
				break;}
			
			printf("From client: %s\n", new_buff);
			result = strncmp(str1, new_buff, 4);
			if(result == 0){
				break;
			}
			char* errorFile = "Invalid file";
			FILE *fid = fopen(new_buff, "r");
			if(fid == NULL){
				write(newSocket, "Invalid file",strlen(errorFile));
			}
			else{
				while(1){
					ret3 = read(fid, new_buff, 1024); 
					if(ret3 == -1) {
						perror("Error\n");
						break;
					}
					else{
						write(newSocket,fid, ret3); 
						shutdown(newSocket, SHUT_RDWR);
					}
						break;
				}
			
			}
			shutdown(newSocket, SHUT_RDWR);
		}				
	}	
	unlink();
	return 0;
}	
