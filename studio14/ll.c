//Lorna Xiao
//studio 14 mp2

#include <stdio.h>
#include <unistd.h>
#include <omp.h> 
int main(){
        int number, j, i, isPrime;
        number = 25;

	omp_set_num_threads(5);

        #pragma omp parallel for schedule(dynamic,10)
        for(i =2 ; i <= number; i++){
		isPrime = 1;
	//	if (i <=4) sleep(1);
		for (j = 2; j*j <= i; j++)
		{
			if (i % j == 0)
			{
				isPrime = 0;
				break;
			}
		}
	printf("i %d exe thread %d\n",i,omp_get_thread_num());
	//	if (isPrime == 1)
	//		printf("%d ",i);
	}
	printf("max threads %d\n",omp_get_max_threads());
	
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
