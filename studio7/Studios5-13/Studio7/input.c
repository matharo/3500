//Tanmayi Nagasuri
//Studio 7 input.c



#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> 

int main(int argc, char* argv[]) {
	char buf[100];
        char* ab;
        printf("Enter a string: ");
        ab = fgets(buf, 100, stdin);
        while(ab!=NULL){
                printf("Program 2 got: %s\n", ab);
                printf("Enter a string: ");
                ab = fgets(buf, 100, stdin);
        }
	return 0;
}







