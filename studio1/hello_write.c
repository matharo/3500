//Lorna Xiao				//number 1
//Aug 30 2017
//Hello World Program

#include <unistd.h>			//number 7

//number 3
//printf() takes a constant character
//fprintf() takes an output stream and then a string/constant character


//number 4
//The difference betweeen printf() and fprintf() is that
//printf() writes to the stdout standard output stream
//fprintf() writes to a given output stream


//number 9	OUTPUT (when size is 13): Hello, World
//
int main(int argc, char* argv[]){
	char buffer[] = "Hello, World\n";
	write(STDOUT_FILENO, buffer, 1000);	//code for number 9
	
	return 0;
}

//number 10
//Foreign characters get added on after the new line
//This happens because write() is printing out characters
//for how much count is. Since buffer does not contain anything
//else after the newline \n, the system pulls in letters
//from memory, as many as how many more characters are in count


//number 11
//I would use a C library function when I am changing a program that can work
//on any OS. So if I wanted to change Microsoft Word, I would use the C Library functions
//
//For an OS system call, that would be when I want to make changes to the 
//OS that can also affect hardware and the kernel. A situation would be if I wanted 
//to adjust the time zone of the OS or change the OS settings.

//number 6
//section number 2


//number 7
#include <unistd.h>

//see hello_write.c
