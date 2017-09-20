//Tanmayi Nagasuri
//Studio 11


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int race;

pthread_mutex_t mutex1;


void* adder(void* r){
	int i;
	pthread_mutex_lock(&mutex1);
	for(i = 0; i < 20000000; i++){
		//pthread_mutex_lock(&mutex1);
		race++;
		//pthread_mutex_unlock(&mutex1);
	}
	pthread_mutex_unlock(&mutex1);
	printf("%d\n", race);
	return NULL;

}

void* subtractor(void* r){
	int i;
	pthread_mutex_lock(&mutex1);
	for(i = 0; i < 20000000; i++){
		//pthread_mutex_lock(&mutex1);
		race--;
		//pthread_mutex_unlock(&mutex1);
	}
	pthread_mutex_unlock(&mutex1);
	printf("%d\n", race);
	return NULL;
}

int main(){
	int counter = 0;
	race = 0;
	pthread_t thread1, thread2;
	
	//pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;	

	pthread_create(&thread1, NULL, adder, NULL);
	pthread_create(&thread2, NULL, subtractor, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	//pthread_mutex_lock(&mutex1);
//	printf("%d\n", race);
	//pthread_mutex_unlock(&mutex1);			
//	printf("%d\n", race);
	return 0;
}













