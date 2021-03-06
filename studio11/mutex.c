//Lorna Xiao
//Mutex, studio 11

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define iterations 200000000    //2hundred mil iterations
int race;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* adder(void* args)
{
	pthread_mutex_lock(&mutex);
        int i = 0;
        while (i < iterations)
        {
                //printf("Race #%d in adder: %d\n",i,race);
		//pthread_mutex_lock(&mutex);
                race++;
		//pthread_mutex_unlock(&mutex);
                i++;
        }
	pthread_mutex_unlock(&mutex);
        return args;
}

void* subtractor(void* args)
{
	pthread_mutex_lock(&mutex);
        int i = 0;
        while(i < iterations)
        {
                //printf("Race #%d in subtractor: %d\n",i,race);
		//pthread_mutex_lock(&mutex);
                race--;
		//pthread_mutex_unlock(&mutex);
                i++;
        }
	pthread_mutex_unlock(&mutex);

        return args;
}

int main(int argc, char* argv[])
{
        pthread_t thread1;
        pthread_t thread2;

        pthread_create(&thread1,NULL,&adder,&mutex);
        pthread_create(&thread2,NULL,subtractor,&mutex);

        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);

        printf("The final result of race is: %d\n",race);
        return 0;
}
