//Tanmayi Nagasuri
//01/23/2017
//A program that does the cat function

#include <unistd.h>

#define bufferSize 100000
char buffer[bufferSize];

int main( int argc, char* argv[] ){
int readIn;
readIn = read(STDIN_FILENO, buffer, bufferSize);

while(readIn != 0) {

	write(STDOUT_FILENO, buffer, readIn);
	if(readIn == 0) {break;}
	readIn = read(STDIN_FILENO, buffer, bufferSize);

//make

}
return 0;
}























