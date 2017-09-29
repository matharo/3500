//Lorna Xiao
//Race conditions, studio 10

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define iterations 200000000	//2hundred mil iterations
int race;

void* adder(void* args)
{
	int i = 0;
	while (i < iterations)
	{
		printf("Race #%d in adder: %d\n",i,race);
		race++;
		i++;
	}
	return NULL;
}
void* subtractor(void* args)
{
	int i = 0;
	while(i < iterations)
	{
		printf("Race #%d in subtractor: %d\n",i,race);
		race--;
		i++;
	}
	return NULL;
}

int main(int argc, char argv)
{
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1,NULL,adder,NULL);
	pthread_create(&thread2,NULL,subtractor,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

	printf("The final result of race is: %d\n",race);
	return 0;
}

