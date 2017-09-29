#define _XOPEN_SOURCE
#define GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <crypt.h>

int main(int argc, char* argv[]){

(if argc!= 3)
{
	print("Usage: <2 char salt> <8 char key>\n");
	return -1;
}
char* salt= argv[1]; //prevents generating all hash ahead of time, precomputation
	//2 ascii char, first 2 characters of result
char* key = argv[2]; //the password
char* result;	//hashed password

result = crypt(key,salt);
if (result==NULL)
{
	perror("Crypt() failed");
	return -1;
}
printf("Salt: %s\n Password: %s\n Result: %s\n");

