//Tanmayi Nagasuri
//Studio 9 

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct new_struct{
	int arg1;
	char arg2[100];
	int ret;
};



void* thread_entry (void *ptr){
	struct new_struct* arg_ptr = (struct new_struct*) ptr;
	//printf("thread arg1: %d\n", arg_ptr->arg1);
	printf("thread arg2: %s\n", arg_ptr-> arg2);
	//printf("thread arg3: %d\n", arg_ptr->ret);
	arg_ptr->ret = 5;

	return NULL;
}


	
int main(int argc, char* argv[]) {
	int rv;
	pthread_t thread1;
	//rv = pthread_create(&thread_id, NULL, &thread_entry, &thread_struct);
	//if(rv != 0){
	//	printf("Error code from pthread_create is %d\n", rv);
	//}
	//pthread_join(thread_id, NULL);

	struct new_struct threadStruct;
	//threadStruct.arg1 = 10;
	strncpy(threadStruct.arg2, "hello",100);
	//threadStruct.ret = 55;

	struct new_struct *struct_ptr = &threadStruct;
	pthread_create(&thread1, NULL, &thread_entry, &threadStruct);
	pthread_join(thread1, NULL);
	printf("After thread join: %d\n", threadStruct.ret);

	unsigned bufSize = 100;
	int n = 5;
        struct new_struct array[n];
        int i;
        for(i = 0; i < n; i++){
                snprintf(array[i].arg2, bufSize, "This is thread %d", i); }
	int j;
	pthread_t ids[n];
	for(j = 0; j < n; j++){
		pthread_create(&ids[j], NULL, &thread_entry, &array[j]);
	}
	int k;
	for(k = 0; k < n; k++){
		pthread_join(ids[k], NULL);
	}

	




	//return 0;
}











































