//Tanmayi Nagasuri
//1 February 2017
//studio5

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	pid_t pid = fork();
	char* child_argv[] = {"ls", "-l", NULL};
	char* child_prog = child_argv[0];

	if (pid == 0) {
		sleep(3);
		printf("This is the child. My pid is %d and my parent's pid is %d\n", getpid(), getppid());
		execvp(child_prog, child_argv);
	}
	else {
		waitpid(pid, NULL, 0);
		printf("This is the parent. My pid is %d\n", getpid());
	}	





return 0;

	
	

}
