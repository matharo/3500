//Tanmayi Nagasuri
//Studio13


#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

int main(){
	int number, j, i;
	int isPrime = 0;
	number = 100;

	#pragma omp parallel for
	for(i = 3; i <= number; i+=2){
		isPrime = 0;
		int j;
		for(j = 3; j*j<i; j++){
			if (i % j == 0) {
				isPrime = 1;
				break;
			}
		
		}
		if(isPrime == 0){
			printf("%d ", i);}
	}
	printf("\n");
	if (isPrime == 0){
		printf("%d is prime\n", number);
	}
	else{
		printf("%d composite \n", number);
	}

	return 0;

}
