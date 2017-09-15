//Lorna Xiao and Vyshnavee Reddlapalli
//September 13, 2017
//Fork and Exec studio5

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	pid_t pid = fork();
	pid_t child_PID = getpid();
	pid_t parent_PID = getpid();

	char* child_argv[] = {"ls","-l",NULL};
	char* child_prog = child_argv[0];

	if (pid==0){
                sleep(3);
                printf("I am the child %d\n",child_PID);

                execvp(child_prog,child_argv);
        }
	else{
		waitpid(-1,NULL,0);
		printf("I am the parent %d\n",parent_PID);
	}
	return 0;
}
