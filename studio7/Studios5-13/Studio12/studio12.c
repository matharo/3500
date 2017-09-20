//Tanmayi Nagasuri
//Studio 12

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int atvar = 0;
int race;

/*void *atvarFunc(void *x){
	printf("Before: %d\n", atvar);
	__sync_add_and_fetch(&atvar, 1);
	return NULL;
}
*/



void* adder(void* r){
        int i;
	for(i = 0; i < 20000000; i++){
                __sync_add_and_fetch(&race, 1);
                
        }
        printf("%d\n", race);
        return NULL;
}

void* subtractor(void* r){
        int i;
	for(i = 0; i < 20000000; i++){
                __sync_sub_and_fetch(&race, 1);
        }
        printf("%d\n", race);
        return NULL;
}
int main(void){
	
	/*pthread_t thread1;
	pthread_create(&thread1, NULL, atvarFunc, NULL);
	pthread_join(thread1, NULL);
	printf("After: %d\n", atvar);
*/

	race = 0;
        pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, adder, NULL);
        pthread_create(&thread2, NULL, subtractor, NULL);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
	return 0;
}





























