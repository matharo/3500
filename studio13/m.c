#include <stdio.h>
#include <unistd.h>
#include <math.h>
int main()
{
	int num, j, i, isPrime;
	j = 1;
	num = 100;
	int candidate = (int)sqrt(num);
	for (i = 3; i <= num; i+=2)
	{
		isPrime = 0;
		for (j = 3; j*j < i; j++)
		{
			if ((i % j) == 0){
				isPrime = 1;
				break;
			}
		}
		printf("%d ",i);
	}
	if (isPrime == 0)
		printf("composite\n");
	else
		printf("prime\n");

	return 0;
}
