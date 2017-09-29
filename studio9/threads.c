//Lorna Xiao
//Studio 9, Threads
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define NUM_THREADS 10

struct el_struct
{
	int arg1;
	char arg2[NUM_THREADS];
	int ret;
};

void *thread_entry(void *threadIdentifier)
{
	struct el_struct* ptr = (struct el_struct*) threadIdentifier;
	printf("thread arg1: %d\n", ptr->arg1);
	printf("thread arg2: %s\n",ptr->arg2);
	printf("thread ret: %d\n",ptr->ret);
	printf("Hello World. Greetings from thread %d\n",threadIdentifier);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread;

	struct el_struct st;
	st.arg1 = 5;
	strcpy(st.arg2,"arg2");
	st.ret = 10;
	
	struct el_struct *ptr = &st;
	
	printf("Main func. Creating thread %d\n",thread);
	
	unsigned bufSize = 100;
	struct el_struct arg[NUM_THREADS];
	pthread_t threads[NUM_THREADS];
	int i;
	for (i = 0; i < NUM_THREADS;i++){
		snprintf(arg[i].arg2,bufSize,"This is thread %d\n",i);
		pthread_create(&threads[i],NULL,thread_entry,&arg[i]);
	}
	for (i = 0; i < NUM_THREADS;i++)
	{
		pthread_join(threads[i],NULL);
	}
	return 0;
}
