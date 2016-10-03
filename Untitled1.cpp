/***************** practice ***************
******************************************/
#include <stdlib.h>
#include <stdio.h>

int findMax(int array[], int n, int i);

int main()
{
	int maximum;
	int n = 0;
	int array[] = {11, 3, 5, 10, 4, 10, 2, 1};
	if(n > 0)
		maximum = findMax(array, n, 0);
	else
		maximum = -1;
	printf(" %d", maximum);
	return 0;
}

int findMax(int array[], int n, int i)
{
	int max;
	if(i == n - 1)
		return array[i];
	max = findMax(array, n, i + 1);
	if(array[i] > max)
		return array[i];
	else
		return max;
}
