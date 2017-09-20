//Tanmayi Nagasuri
//Studio 10

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int race;



void* adder(void* r){
	int i;
	for(i = 0; i < 200000000; i++){
		race++;
	}
return NULL;
//	printf("%d\n", race);
}

void* subtractor(void* r){
	int i;
	for(i = 0; i < 200000000; i++){
		race--;
	}
return NULL;
//	printf("%d\n", r);
}

int main(){
	race = 0;

	//	adder(race);
	//	subtractor(race);
	
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, adder, NULL );
	pthread_create(&thread2, NULL, subtractor, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("%d\n", race);
	return 0;
}


































