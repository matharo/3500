#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#define total 100

void* entry_point(void* arg){
	printf("Pthread ID: %u\n", pthread_self());
	return NULL;
}

int main(int argc, char* argv[])
{
	int i;
	pthread_t tids[total];

//	int pids[total];

	for (i = 0; i < total; i++)
	{
	//	pids[i] = fork(); //100 processes
	//	if (pids[i] == 0){printf("child &d\n",getpid());return 0;}
		
		
		pthread_create(&tids[i],NULL,entry_point,NULL);
		       	//reference to pids, entry_point void* type
			//create 100 threads
	}
	for (i = 0 ; i < total; i++)
	{
		pthread_join(tids[i],NULL); 
			//join all 100 threads
	}

}
