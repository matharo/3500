//Tanmayi Nagasuri
//Lab2

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>





//this function handles the signal 
void sig_handler(int signum){
		
}

//this function prints out the shortened directory path 
void calc_dir( char* buf ){

	char* cwd = getcwd(NULL, 0);
	char* hdir = getenv("HOME");
	
	int g = 0;
	while(cwd[g] == hdir[g]){
		g++;
	}
	strncpy(buf, &cwd[g], PATH_MAX);
		


}

int main(int argc, char* argv[]) {
	
	char cwd[1024];
	int size  =strlen(getenv("HOME"));
	char buf[100];
	char* ret;
	char* ab;
	char* commands[15];
	char dir[PATH_MAX+1];

			
            
	signal(2, sig_handler);	
		
	//calc_dir(dir);

	while(1){	
		signal(2, sig_handler);
		calc_dir(dir);
		char *newDir = dir + 1;
		printf("slush|%s$ ", newDir);
		printf("Enter commands: ");
		ab = fgets(buf, 100, stdin);
		if(ab == NULL){break;}
		ab[strlen(ab)-1] = '\0';
		//error checking
		if(ab[strlen(ab)-1] == '(') {
			printf("Invalid syntax\n");
			continue;
		}
		if(ab[0] == '('){
			printf("Invalid syntax\n");
			continue;
		}

		int j;
		int pcounter = 0;
		for(j = 0; j < strlen(ab); j++){
			if(ab[j] == '('){
				pcounter++;
			}
		} 
		ret = strtok(ab, "(");
		int counter = 0;
		while(ret != NULL){
			commands[counter] = ret;
			ret = strtok(NULL, "(");
			counter++;
			
		}
		


		

		int i;
		char* ret2;
		int ret3; 
		char* argv0[15];
		char* cmd;
		pid_t pid;
		int ctr;
		int fd[2];
		int readFromMe;		

		for(i = counter -1; i >= 0; i--){
			ctr = 0;
			ret2 = strtok(commands[i], " ");
			//change directory code here
			if(ret2 != NULL && strncmp(ret2, "cd", 2) == 0){
				chdir(strtok(NULL, " "));
			}
			cmd = ret2;
			argv0[0] = cmd;
			while(ret2 != NULL){
				argv0[ctr] = ret2;
				ret2 = strtok(NULL, " ");
				ctr++;	
			}
			
			
			argv0[ctr] = '\0';
			
			if (counter == 1) { //no pipes case
				pid = fork();
				if(pid < 0){
					perror("Fork failed");
					return -1;
				}
				if(pid == 0){
					ret3 = execvp(cmd, argv0);
					if(ret3 == -1) perror("Error exec'ing program"); continue;
				}
					else{
						waitpid(pid, NULL, 0);
						break;
					}
				}
				int ret4 = pipe(fd);
				if(ret4 == -1) perror("Error - Pipe Error\n");


				pid = fork();
				if (pid < 0){
					perror("Fork failed");
					return -1;
				}
				if(pid == 0){
					if(i == (counter - 1)){
						dup2(fd[1], STDOUT_FILENO);
						close(fd[0]);
					//	printf("%s\n", "Yay this works!");
						ret3 = execvp(cmd, argv0);
						if(ret3 == -1) perror("Error exec'ing program"); continue;
					}
					if(i == 0){
						dup2(readFromMe,STDIN_FILENO);
						ret3 = execvp(cmd, argv0);
					}
					else{
						dup2(readFromMe, STDIN_FILENO);
						dup2(fd[1], STDOUT_FILENO);
						close(fd[0]);
					//	printf("%s\n", "OMG ROCKSTAR!");
						ret3 = execvp(cmd, argv0);
						if(ret3 == -1) perror("Error exec'ing program");continue;
					}
				}
				else{
					close(fd[1]);
					if(readFromMe != 0) close(readFromMe);
					readFromMe = fd[0];
					
					
					waitpid(pid, NULL, 0);
					//printf("Done");
					}

			}
		}
		return 0;
	}



















