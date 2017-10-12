#include <stdio.h>
#include <unistd.h>
#include <math.h>

int main(){
        int number, j, i, isPrime;
        number = 20000000;
        
        for(i =2 ; i <= number; i++){
		isPrime = 1;
		for (j = 2; j*j<= i; j++)
		{
			if (i % j == 0)
			{
				isPrime = 0;
				break;
			}
		}
	//	if (isPrime == 1)
	//		printf("%d ",i);
	}
/*	printf("\n");
	if (isPrime == 1){
                printf("%d is prime\n", number);
        }
        else{
                printf("%d composite\n", number);
        }
*/
	return 0;
}
