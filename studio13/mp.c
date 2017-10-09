#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[])
{
	int i, num, candidate,isPrime;
	printf("enter number: \n");
	scanf("%d",&num);

	candidate = (int)sqrt(num);
	if (num == 1)
		printf("neither prime or composite\n");
	else{
		for (i = 3; i*i < candidate; i+=2)
		{	if ((num%i)==0)
				isPrime = 0;
			else{	
				isPrime = 1;
				printf("%d ", i);
			}
		}
	}
	if (isPrime == 0)
		printf("composite\n");
	else
		printf("prime\n");
	return 0;
}
