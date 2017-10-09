// Vyshnavee Reddlapalli and Lorna Xiao
// September 29, 2017
// Lab 3: crack - Brute Force Password Cracking
// Help from stackoverflow, studio 9, studio 11

#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <crypt.h>

//global variables 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char ascii_dec = 32;

struct struct_name {
	char arg1[20];
	char arg2[1];
	int arg3;
	char arg4[4]; //optional
};

//search_all is the optional argument for extra credit
void* find_password(char* key, char* salt, struct crypt_data* data, char* target, int pos, int count, char* search_all) {
	char letter;
	//position cannot exceed count, count helps identify the position/place in the key array
	if(pos != count) {
		if(search_all != "ASCII") {
			for(letter = 97; letter <= 122; letter++) {
				key[pos] = letter;
				find_password(key, salt, data, target, pos + 1, count,  search_all);
			}
		}
		//Extra Credit: search all uppercase, lowercase chars, numbers, symbols. ACSII DEC 32-122
		else if(search_all == "ASCII") {
			for(letter = 32; letter <= 122; letter++) {
				key[pos] = letter;
				find_password(key, salt, data, target, pos + 1, count,  search_all);
			}
		}
	}
	else {
		char* password;
		password = crypt_r(key, salt, data);
		if(strcmp(password, target) == 0){
			printf("Password is: %s\n", key);
			exit(0);
		}
	//if no password found, doesn't return anything
	}
	return;
};

void* thread_entry(void* args) {
	struct struct_name* arg_ptr = (struct struct_name*) args;
	struct crypt_data data;
	data.initialized = 0;
	char key[7];
	int count;
	while(1) {
		count = 1;
		char curr_letter;
		pthread_mutex_lock(&mutex);
		curr_letter = ascii_dec;
		ascii_dec++;
		key[0] = curr_letter;
		pthread_mutex_unlock(&mutex);
		if((curr_letter < 32) || (curr_letter > 122)) {
			break;
		}
		while(count <= arg_ptr -> arg3) {
			find_password(key, arg_ptr -> arg2, &data, arg_ptr -> arg1, 1, count, arg_ptr -> arg4);
			count++;
		}
	}
}

int main(int argc, char* argv[]) {
	if((argc < 4) || (argc > 5)) {
		printf("Arguments: Number of threads, keysize, target. 4th argument is optional by adding ASCII \n"); 
		exit(0);
	}
	//convert string to integer
	int N_threads = atoi(argv[1]);
	int keysize = atoi(argv[2]);
	char* target = argv[3];
	char* search_all = argv[4];	
	char key[7]; //same as keysize length
	char salt[1]; //salt is a size of 2
	struct struct_name struct_thread;
	pthread_t thread[N_threads];
	int i;

	strncpy(salt, target, 2); //copy first two characters from target to salt
	if(keysize > 8) {
                printf("Invalid! Keysize cannot be greater than 8 \n");
		exit(0);
        }
	if(search_all == NULL) {
                search_all = "EMPTY";
        }
	strncpy(struct_thread.arg1, target, 20); //maximum hash size of 20
	strncpy(struct_thread.arg2, salt, 2);
	struct_thread.arg3 = keysize;
	strncpy(struct_thread.arg4, search_all, 5);
	for(i = 0; i < N_threads; i++) {
		pthread_create(&thread[i], NULL, &thread_entry, &struct_thread);
	}
	for(i = 0; i < N_threads; i++) {
		pthread_join(thread[i], NULL);
	}

	return 0;
}
