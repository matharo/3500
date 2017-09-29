//In class exercise, lock/unlock mutex

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define iters 1000000
#define chunk 1000

void* adder(void*args)
{
	int i = 0,j;
	while (i < iters)
	{
		pthread_mutex_lock(&m);
		for (j = 0; j < chunk; j++)
			sum += 1;
		pthread_mutex_unlock(&m);
		i += chunk;
	}
	return NULL;
}
void* subtractor(void* args)
{
	int i;
	for ( i = 0; i < iters; i++){
		_sync_add_and_fetch(&sum,-1);
		//sum -=1;
	}
	return NULL;
}
