//Lorna Xiao and Vyshnavee Reddlapalli
//Sep 19 2017
//Lab 2 SLUSH - SLU Shell

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#define string_size 8 

int main(int argc, char* argv[])
{
	char string[string_size];
	char* str;
	while (strlen(string) != 0)
	{
		printf("Enter input: ");
		fgets(string,string_size,stdin);
		string[(strlen(string)-1)]=0;
		if (strtok(string, " ( ")==NULL)
		{
			printf("Invalid null command\n");

		}


		else
		{
			str = strtok(string, " ( ");
			while (str!=NULL)
			{
				printf("token: %s\n",str);
				str = strtok(NULL," ( ");
			}
		}
	}
	return 0;
}
