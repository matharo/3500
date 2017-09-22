//Tanmayi Nagasuri
//Studio 7 pipe.c


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define _GNU_SOURCE

int main(int argc, char* argv[]){
	
	pid_t pid1, pid2;
	char* cmd1 = "./print";
	char* cmd2 = "./input";
	char* myargv[] = {"print", '\0'};
	char* myargv2[] = {"input", '\0'};
	int ret;
	int ret2;

	int fd[2];
	pipe(fd);

	pid1 = fork();
	if (pid1 < 0){
		perror("First fork() failed");
		return -1;
	}

	if(pid1 == 0){
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		ret = execvp(cmd1, myargv);
		if(ret == -1) perror("Error exec'ing print");}

	pid2 = fork();
	if (pid2 < 0){
		perror("Second fork() failed");
		return -1;
	}

	if(pid2 == 0){
		dup2(fd[0],STDIN_FILENO);
		close(fd[1]);
		ret2 = execvp(cmd2, myargv2);
		if(ret2 == -1) perror("Error exec'ing input");}

	else {
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
}
return 0;
}






















