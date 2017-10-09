//Lorna Xiao
//studio 13, OpenMP
#include <stdio.h>
#include <math.h>
#include <unistd.h>
int prime(int num)
{
	//double candidate = sqrt(num);
	if (num == 1)			//1 is neither comp or prime
		return 2;

	else if (num % 2 == 0)	//divisible by 2
		return 0;

	else if ((num % (int)sqrt(num)) == 0)
		return 0;

	else
	{
		int i;
		for (i = 3; i < (int)sqrt(num); i+2) 	//i != 1 or num
		{
			if ((num % i) != 0)
				return 1; 	//composite
			else
				return 0;
		}
	}	
}

int main(int argc, char* argv[])
{
	int res;	
	int num = 0;
	//while (num != -1)
	//{
		printf("Enter number, (quit -1): ");
		scanf("%d",&num);	//read in num from terminal
	
		if (num == -1)		//quit
			return 0;
		
		res = prime(num);

		if (res == 0)
			printf("%d is composite\n",num);
		else if (res == 1)
			printf("%d is prime\n",num);
		else 			//res = 2
			printf("%d is neither prime or composite\n",num);
	//}
	return 0;	
}
