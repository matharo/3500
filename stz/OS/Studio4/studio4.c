//Tanmayi Nagasuri
//27 January 2017
//Studio 4

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define bufferSize 1000

int main( int argc, char* argv[] ){
	char buffer [bufferSize];

	char* readFile = argv[1];
	//printf(readFile);
	int openReadFile;
	int readIn;
	openReadFile = open(readFile, O_RDWR);
	if (openReadFile == -1) {
		perror("There was an error opening the read file\n");
		exit(-1);}

	readIn = read(openReadFile, buffer, bufferSize);
	
	while(readIn != 0) {
		write(STDOUT_FILENO, buffer, readIn);
		if(readIn == 0) {break;}
		readIn = read(openReadFile, buffer, bufferSize);
	}




	


	return 0;
}




















