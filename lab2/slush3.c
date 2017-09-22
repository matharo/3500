#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define string_size 256
#define command_args 15
int main(int argc, char* argv[])
{
	char userString[string_size];
	char* input; 
	char* delim = " (";
	while (1)
        {
                printf("slush( ");
		input = fgets(userString,string_size,stdin);
		userString[(strlen(userString)-1)]=0;

		if ((userString[0] || userString[(strlen(userString)-1)]) == *delim)
		{
			printf("Invalid syntax for %s\n", userString);
		}

		runCommandLine(getTokens(input,delim),sizeof(getTokens(input,delim)));

		return 0;
	}
}

char* getTokens(char* input, char* delim)
{
	char* commands[command_args];
	char* str;
	int count = 0; 		//command counter that user inputs
	str = strtok(input,delim);
	while(str!=NULL)
	{
		commands[count] = str;
		str = strtok(NULL,delim);
		count++;
	}
	return *commands;
}
int runCommandLine(char* commands[],int cmdLen)
{
	pid_t child[cmdLen];
	char* cmd;
	int ret;
	int pipefd[2];

	pipe(pipefd);

	int i; 
	for (i = cmdLen-1; i > 0; i--)
	{
		if ( i % 2 != 0 ) //if odd
		{
			child[i] = fork();
			if (child[i] == 0)
			{
				dup2(pipefd[1],STDOUT_FILENO);
				close(pipefd[0]);
				cmd = "./" + *commands[i];
				char* myargv[] = {*commands[i], '\0'};
				ret = execvp(cmd,myargv);
				if (ret == -1) 
				{	perror("Error exec'ing %s\n",*commands[i]);	}
			}
		}
		else		//if even
		{
			child[i] = fork();
			if (child[i] == 0)
			{
				dup2(pipefd[0],STDIN_FILENO);
				close(pipefd[1]);
				cmd = "./" + *commands[i];
				char* myargv[] = {*commands[i], '\0'};
				ret = execvp(cmd,myargv);
				if (ret == -1) 
				{	perror("Error exec'ing %s\n",*commands[i]);	}
			}	
			else
			{
				close(pipefd[1]);
				close(pipefd[0]);
				waitpid(child[i],NULL,0);
			}
		}
	}	
	return 0;
}
