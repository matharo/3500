//Lorna Xiao
//Studio 7
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
	pid_t child_one = fork();
	pid_t child_two = fork();
	char* cmd;
	int ret;

	int fd[2];
	if (child_one == 0){
		cmd = "./print";
		char* myargv[] = {"print", '\0'};
		ret = execvp(cmd,myargv);
		if (ret == -1) perror("Error exec'ing print");
	}
	else
		waitpid(child_one,NULL,0);

	if (child_two == 0){
		cmd = "./infinite";
                char* myargv[] = {"infinite", '\0'};
                ret = execvp(cmd,myargv);
                if (ret == -1) perror("Error exec'ing infinite");
        }
	else
		waitpid(child_two,NULL,0);

	return 0;
}
