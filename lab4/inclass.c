#include <sys/types.h>
void* myalloc(size_t size)
{
	void* ret = sbrk(size); 	//get mem from OS
	
	//check success, otherwise ret null
	if (ret == (void*)-1)
	{
		printf("Error calling sbrk!\n");
		errno = ENOMEM;
		return NULL;
	}
	printf("Malloc with ... ptr\n");
}
	
void* myfree(void *ptr);

#define array_size 500
#define short_array 250

int main (int argc,char* argv[])
{
	int *array = (int*) malloc(sizeof(int)*array_size);
	int *array2 = (int*) malloc(sizeof(int)*array_size);
	int i;
	printf("Array 1 ptr: %p\n",array);
	printf("Array 2 ptr: %p\n",array2);

	for (i = 0; i < array_size; i++){ array[i]=i; }

	free(array);
	free(array2);

	//reallocate 2 arrays
	array = (int*) malloc(sizeof(int)*short_array);
	array2 = (int*) malloc(sizeof(int)*short_array);

	printf("Array 1 ptr: %p\n",array);
        printf("Array 2 ptr: %p\n",array2);

	
