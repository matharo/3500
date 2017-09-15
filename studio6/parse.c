//Lorna Xiao and Vyshnavee Reddlapalli
//September 13 2017
//Parsing String Input studio6

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define string_size 1024
int main(int argc, char* argv[]){
	char string[string_size];
	printf("Enter input: ");
	fgets(string,string_size,stdin);	
	printf("Your input is: %s\n",string);
	return 0;
}
