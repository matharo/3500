//Lorna Xiao
//Studio 7
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
	pid_t child_one, child_two;
	char* cmd;
	int ret;
	int pipefd[2];

	pipe(pipefd);
	
	child_one = fork(); //child_one process
	if (child_one == 0){
		dup2(pipefd[1],STDOUT_FILENO);
		close(pipefd[0]);
		cmd = "./print";
		char* myargv[] = {"print", '\0'};
		ret = execvp(cmd,myargv);
		if (ret == -1) perror("Error exec'ing print");
	}
	else
	{
		child_two = fork(); //child_two process
		if (child_two == 0){
			dup2(pipefd[0],STDIN_FILENO);
			close(pipefd[1]);
			cmd = "./infinite";
               		char* myargv[] = {"infinite", '\0'};
               		ret = execvp(cmd,myargv);
              		if (ret == -1) perror("Error exec'ing infinite");
        	}	
		else //parent process for both child_one and child_two
		{
			close(pipefd[1]);
			close(pipefd[0]);
			waitpid(child_one,NULL,0);
                        waitpid(child_two,NULL,2);
		}
	}
	return 0;
}
