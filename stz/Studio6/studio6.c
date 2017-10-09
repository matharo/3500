//Tanmayi Nagasuri
//
//Studio6

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

int max_args = 15;
int max_argv_size = max_args + 2;
char* cmd;
char* my_argv[max_argv_size];



char buf[100];
char *pch;
char *ab;
printf("Enter a string: ");
ab = fgets(buf, 100,stdin);
ab[strlen(ab) - 1] = '\0';
cmd = strtok(ab, " ,.");
my_argv[0] = cmd;
int counter; 
counter = 1;
while(pch != NULL){

	pch = strtok(NULL, " ,.");
	my_argv[counter] = pch;
	counter = counter + 1;

}
my_argv[counter] = '\0';
execvp(cmd, my_argv);

return 0;
}


