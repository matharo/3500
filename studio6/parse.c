//Lorna Xiao and Vyshnavee Reddlapalli
//September 13 2017
//Parsing String Input studio6

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define string_size 1024
int main(int argc, char* argv[]){
	char string[string_size];
	char* input;
	char* res;

	int max_args = 15;
	int max_argv_size = max_args + 2; //one for argv[0], one for null terminator
	char* cmd;
	char* my_argv[max_argv_size];

	printf("Enter input: ");
	input = fgets(string,string_size,stdin);
	string[(strlen(string)-1)]=0;

	printf("Your input is: %s\n",string);	

	int i;
	cmd = strtok(input, " ");
	my_argv[0] = cmd;
	printf("First token: %s\n", cmd);
	for (i = 1; i < max_args; i++)
	{
		res = strtok(NULL, " ");
		if (res == NULL) {
			my_argv[i] = '\0';
		}
		else {
			my_argv[i] = res;
			printf("Other tokens: %s\n",res);
		}
	}
	
	for (i = 0; i < sizeof(my_argv); i++)
	{
		execvp(cmd,my_argv);
	}
	return 0;
}
