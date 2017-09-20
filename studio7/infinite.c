//
//

#include <stdio.h>
#include <string.h>
#define string_size 1024
int main(int argc, char* argv[])
{
	char string[string_size];
	char* input; 
	while((input = fgets(string,string_size,stdin))!= NULL){
		printf("Program 2 got: %s\n",input);
	}
	return 0;
}
