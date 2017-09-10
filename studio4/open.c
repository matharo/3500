//Lorna Xiao and Vyshnavee Reddlapalli
//Sep 8 2017
//Error Checking

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	int fd;
	int textLen;

	fd = open(argv[1],O_RDONLY);
	struct stat buf;
	fstat(fd,&buf);
	textLen = buf.st_size;
	numBytes = read(fd,argv[1],textLen);
	write(STDOUT_FILENO,fd,numBytes);

	return 0;
}
