//Lorna Xiao and Vyshnavee Reddlapalli
//September 1, 2017
//Studio 2 copy.c


#include <stdio.h>
#include <unistd.h> 	//header files for read and write

#define bufferSize 200 

int main(int argc, char* argv[]){
	char buffer[bufferSize];

	while (read(STDIN_FILENO,buffer,bufferSize) ==0)
		break;
	write(STDOUT_FILENO,buffer,bufferSize);


	return 0;
}


//number 8
//number of read bytes is return for read()
//0 means end of file
//
