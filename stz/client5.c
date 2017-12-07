#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <un.h>
void* reader(void* args){
  int sock = *(int*)args;
  int got;
  char buff[1024];
  while(1){
    got = read(sock, buff, sizeof(buff));
    if( got == -1 ){
      perror("Error reading socket");
      exit(-1);
    }
    buff[got]  = '\0';
    printf("%s", buff);
  }
}

int main(int argc, char *argv[]){
  
  int sock;
  struct sockaddr_in server;
  char buff[1004];
  char tosend[1024];
  char quit[4] = "quit";
  char* ip = argv[1];
  printf("ip is %s\n", ip);

  pthread_t x;
  int port = atoi(argv[2]);
  char user[4] = "User";
  srand(time(NULL));
  int random = rand() % (999 + 1 - 100) + 100;
  char name[20];
  char conne[14] = "has connected\n";
  int first = 1;
  char welcome[100];
  sprintf(name, "%s%d",user, random);
  sprintf(welcome, "%s %s",name, conne); 
  //while(1){
        
    memset(&buff, 0, sizeof(buff));
    memset(&tosend, 0, sizeof(tosend));
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0){
      perror("socket failed\n");
      exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons(port);
    
    if(connect(sock, (struct sockaddr *) &server,  sizeof(server)) == -1){
      perror("connection failed\n");
      close(sock);
      exit(1);
    }
    write(sock,welcome, strlen(welcome));
    first--;
    pthread_create(&x,NULL,reader,&sock);
    while(1){
      int got= read(STDIN_FILENO, buff, sizeof(buff));
      if( got == -1 ){
	perror("couldn't read\n");
	exit(-1);
      }
      memset(tosend, 0, sizeof(tosend));
      buff[got] = '\0';
      if(strncmp(buff, "quit", 4)==0 && strlen(buff)==4) {
	write(sock,quit, sizeof(quit)) ;
	sprintf(tosend, "%s has quit the chatting room", name);
	close(sock);
	exit(1);
      }else if(strncmp(buff, "name", 4)==0){
	char old[20];
	buff[got-1]='\0';
	strncpy(old, name, strlen(name));
	strncpy(name, buff+5, 20);
	sprintf(tosend,"%s change name into %s", old, name);
      }else{
	sprintf(tosend, "%s: %s",name,buff);
      }
      if(write(sock,tosend, strlen(tosend)) <0){
	perror("send failed");
	close(sock);
	exit(1);
	
      //      got = read(sock, buff, sizeof(buff));
      //if( got == -1 ){
      //	perror("Error reading socket");
      //	exit(-1);
      // }
      // buff[got]  = '\0';
      //printf("%s", buff);
      //printf("Sent %s\n", buff);
      }
    }
  return 0;
}
