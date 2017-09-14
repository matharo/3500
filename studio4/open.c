//Lorna Xiao and Vyshnavee Reddlapalli
//Sep 8 2017
//Error Checking

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define buffer_size 200
int main(int argc, char* argv[])
{
	int fd;
	int textLen;
	int text; 
	char buffer[buffer_size];

	fd = open(argv[1],O_RDONLY);

	if (fd==-1) {
		perror("error opening file\n");
		printf("errno = %d\n",errno);
		exit(1);
	}

	while((text = read(fd,buffer,buffer_size)!=0)){
		write(STDOUT_FILENO,buffer,buffer_size);
		
	}
	close (fd);
	return 0;
}
