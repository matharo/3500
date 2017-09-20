//
//
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
	pid_t child_one = fork();
	pid_t child_two = fork();

	if (child_one == 0){
		char* cmd = "./print";
		char* myargv[] = {"Print", '\0'};
		int ret = execvp(cmd,myargv);
		if (ret == -1) perror("Error exec'ing print");
	}
	else if (child_two == 0){
		char* cmd = "./infinite";
                char* myargv[] = {"Infinite", '\0'};
                int ret = execvp(cmd,myargv);
                if (ret == -1) perror("Error exec'ing infinite");
        }
	else{
		waitpid(child_one,NULL,0);
		waitpid(child_two,NULL,0);
	}
	return 0;
}
