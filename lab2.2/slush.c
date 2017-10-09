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
	char* commands[command_args];
	char* str;
	while (1)
	{
		printf("slush( ");
		input = fgets(userString,string_size,stdin);
		userString[(strlen(userString)-1)]=0;

		if ((userString[0] || userString[(strlen(userString)-1)]) == *delim)
		{
			printf("Invalid syntax for %s\n", userString);
		}

		str = strtok(input, delim);
		int count = 1;          //command counter, goes from 1 to 15
		while(str!=NULL)
		{
			commands[count] = str;
			str = strtok(NULL,delim);
			count++;
		}
		pid_t child[command_args];
		int ret;	//use to identify parent or children(ret = 0) ret = fork();
		int pipefd[2];
		int pipeFromLast;
		char* cmd;
		pipe(pipefd);

		int i;
		for (i = count; i > 0; i--)	//count tells the number of args inputted
		{
			if (count ==2)		//
			{
				child[i] = fork();
				if (child[i] == 0)
				{
					dup2(pipefd[1],STDOUT_FILENO);
					close(pipefd[0]);
					cmd = "./" + *commands[i];
					char* myargv[] = {commands[i], '\0'};
					ret = execvp(commands[i],myargv);
					if (ret == -1)
					{       perror("Error exec'ing\n");     }
				}
				else
				{
					child[i+1] = fork();
					if (child[i+1] == 0){
						dup2(pipefd[0],STDIN_FILENO);
						close(pipefd[1]);
						cmd = "./" + *commands[i];
						char* myargv[] = {commands[i+1], '\0'};
						ret = execvp(commands[i+1],myargv);
						if (ret == -1)
						{       perror("Error exec'ing\n");     }
					}
					else
					{
						waitpid(child[i],NULL,0);
						waitpid(child[i+1],NULL,0);
						close(pipefd[1]);
						close(pipefd[0]);
					}
				}
			}
		}

	}
	return 0;
}
