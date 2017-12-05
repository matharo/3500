//Tanmayi Nagasuri, Alex Lambrecht
//1/20/17
//Hello world program 

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
	char buffer[] = "Hello, world!\n";
	write(STDOUT_FILENO, buffer,140);
	return 0;
}





















 
