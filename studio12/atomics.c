//Lorna Xiao
//studio 12 atomics

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define iterations 20000000 
int race;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* adder(void* args)
{
        //pthread_mutex_lock(&mutex);
        int i = 0;
        while (i < iterations)
        {
		pthread_mutex_lock(&mutex);
		//race++
		__sync_add_and_fetch(&race,+1);
		//printf("Add iter #%d race = %d\n",i,race);
		pthread_mutex_unlock(&mutex);
                i++;
        }
        //pthread_mutex_unlock(&mutex);
        return args;
}
void* subtractor(void* args)
{
        //pthread_mutex_lock(&mutex);
        int i = 0;
        while(i < iterations)
        {
		pthread_mutex_lock(&mutex);
		//race--;
		__sync_add_and_fetch(&race,-1);
		//printf("Sub iter #%d race = %d\n",i,race);
		pthread_mutex_unlock(&mutex);
                i++;
        }
        //pthread_mutex_unlock(&mutex);

        return args;
}
int main(int argc, char* argv[])
{
	int atom = 0;
	printf("atom before = %d\n",atom);
	__sync_add_and_fetch(&atom,+1);
	printf("atom after = %d\n",atom);

        pthread_t thread1;
        pthread_t thread2;

        pthread_create(&thread1,NULL,&adder,&mutex);
        pthread_create(&thread2,NULL,subtractor,&mutex);

        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);

        printf("The final result of race is: %d\n",race);

	return 0;
}
