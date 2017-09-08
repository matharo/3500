//Lorna Xiao
//Sept 7 2017
//This program illustrates some uses of pointers in C

#include <stdio.h>

char linString[] = "Linux!";
int  linSize = 6;

char *winString = "Windows!\0";

int  winSize = 8;

int main ( int argc, char* argv[] ){

	printf("%s\n", linString);
	printf("%s\n", winString);

	int i;
	for (i = 0; i < linSize; i++)
	{ printf("%c\n", linString[i]); }
	
	printf("%c\n", *winString);
	printf("%c\n", *(winString + 1));
	printf("%c\n", *(winString + 2));
	printf("%c\npointer arithmetic\n", *(winString + 3));

	for (i = 0; i < 8; i++)
	{ printf("%c\n",*(winString + i)); }


//number9 help
	for (i = 0; i < 8; i++)
        { printf("%s\n",*(winString+i)); }

	*linString = 'M';
	printf("%s\n",linString);
	
//number11 help
	*winString = 'T';
	printf("%s\n",*winString);

	return 0;
}
