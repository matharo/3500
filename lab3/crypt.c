#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int main(int argc,char* argv[])
{
	if (argc != 4)
	{
		printf("Usage: <num of threads> <2 char salt> <8 char key> \n");
		return -1;
	}
	
	int numThreads = argv[1];
	char* salt = argv[2];
	char* key = argv[3];
	char* result;

	result = crypt(key,salt);
	if (result == NULL)
	{
		perror("Crypt() failed");
		return -1;
	}
	printf("Salt: %s\nPassword: %s\nResult: %s\n",salt,key,result);
}

