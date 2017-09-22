#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define string_size 256
#define command_args 15

char* commandLine(char* input, char* delim)
{
        char* commands[command_args];
        char* str;
        int count = 0;          //command counter that user inputs
        str = strtok(input,delim);
        while(str!=NULL)
        {
                commands[count] = str;
                str = strtok(NULL,delim);
                count++;
        }
	

	pid_t child[command_args];
        char* cmd;
        int ret;
        int pipefd[2];

        pipe(pipefd);

        int i;
        for (i = command_args-1; i > 0; i--)
        {
                if ( i % 2 != 0 ) //if odd
                {
                        child[i] = fork();
                        if (child[i] == 0)
                        {
                                dup2(pipefd[1],STDOUT_FILENO);
                                close(pipefd[0]);
                                cmd = "./" + *commands[i];
                                char* myargv[] = {commands[i], '\0'};
                                ret = execvp(cmd,myargv);
                                if (ret == -1)
                                {       perror("Error exec'ing");     }
                        }
                }
                else            //if even
                {
                        child[i] = fork();
                        if (child[i] == 0)
                        {
                                dup2(pipefd[0],STDIN_FILENO);
                                close(pipefd[1]);
                                cmd = "./" + *commands[i];
                                char* myargv[] = {commands[i], '\0'};
                                ret = execvp(cmd,myargv);
                                if (ret == -1)
                                {       perror("Error exec'ing");     }
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

int main(int argc, char* argv[])
{
        char userString[string_size];
        char* input;
        char* delim = " (";
	char* commands[command_args];
        while (1)
        {
                printf("slush( ");
                input = fgets(userString,string_size,stdin);
                userString[(strlen(userString)-1)]=0;

                if ((userString[0] || userString[(strlen(userString)-1)]) == *delim)
                {
                        printf("Invalid syntax for %s\n", userString);
                }

                commandLine(input,delim);

                return 0;
        }
}
