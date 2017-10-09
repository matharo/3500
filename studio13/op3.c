//Lorna Xiao
//studio 13, OpenMP
#include <stdio.h>
#include <math.h>
#include <unistd.h>
void printPrimes(int* primes)
{
        int i;
        for (i = 0; i < sizeof(primes); i++)
        {
                printf("%d ",primes[i]);
        }
        printf("\n");
}
int test(int num)
{
	int isPrime;
	int size = 1/log(num);
	int primes[size];
	if (num <= 1)
		return num;
	else
	{
		int i, j, candidate;
		j = 0;
		candidate = (int)sqrt(num);
		for (i = 3; i*i <= candidate; i+=2)
		{
			if ((num % i) != 0)
			{
				isPrime = 1;
				primes[j] = i;
				j++;
			}
			else
				isPrime = 0;	//composite
		}
		printPrimes(primes);
	}
	return isPrime;
}
int main(int argc, char* argv[])
{
	int res;	
	int num = 100;
	res = test(num);

	if (res == 0)
		printf("%d is composite\n",num);
	else if (res == 1)
		printf("%d is prime\n",num);
	else 			//res = 2
		printf("%d is neither prime or composite\n",num);
	return 0;
}
