#include <stdio.h>
#include <unistd.h>

int isPrime(int num)
{
	int i, j;
	
	for (i = 3; i*i <= num; i+=2)
	{
		if (num%i==0)
			return 0;
	}
	return 1;
}
int main()
{
	int num = 100;
	int ret = isPrime(num);

	if (ret == 0)
		printf("composite");
	else
		printf("prime");

	return 0;
}
