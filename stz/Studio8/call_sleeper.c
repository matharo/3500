//A simple program that fork()s and exec()s the ./sleep program
//September 10th, 2016
//David Ferry

#include <unistd.h> //fork(), execvp(), perror(), waidpid() 
#include <stdlib.h> //For exit()
#include <stdio.h> //For printf()
#include <signal.h>

void sig_handler(int signum){
	printf("\nProgram is ignoring SIGINT\n");
}
int main( int argc, char* argv[] ){

	pid_t ret;

	printf("Forking sleeper...\n");	

	ret = fork();
	if( ret == -1 ){
		perror("Could not fork");
		exit(-1);
	} 

	if( ret == 0 ){ //Child
		int exec_ret;
		char* cmd = "./sleep";
		char* myargv[] = {"sleep", NULL};
		exec_ret = execvp( cmd, myargv );
		if( exec_ret == -1 ){
			perror("Error calling execvp");
			exit(-1);
		}


	}
	signal(2, sig_handler);
	//Parent
	printf("Waiting for sleeper...\n");
	waitpid( ret, NULL, 0 );

	printf("Parent finished waiting and returned successfully!\n");
	
	
	return 0;
}
