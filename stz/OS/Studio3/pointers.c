//Your name
//The date
//This program illustrates some uses of pointers in C

#include <stdio.h>

char linString[] = "Linux!";
int  linSize = 6;

char *winString = "Windows!";
int  winSize = 8;

int main ( int argc, char* argv[] ){
	int i;
	for(i = 0; i<linSize; i++){	
//	printf("%c\n", linString[i]);
	}
	for(i = 0; i < winSize; i++){
//	printf("%c\n", winString[i]);
	}
	printf("%c\n", *winString);
//	printf("%c\n", *(winString + 1));
//	printf("%c\n", *(winString +2));
//	printf("%c\n", *(winString + 3));


for(i=0; i<winSize; i++) {
	printf("%c\n", *(winString + i));
}

for(i = 0; i<winSize; i++) {
	printf("%s\n", (winString + i));
}
linString[0] = "M";
*(linString) = "M";
printf("%c\n", linString[0]);
	return 0;
}
