#include <stdio.h>
#include <stdlib.h>

void printWhite(int iCount2);
void printBlack(int iCount);

int main()
{
	int i;
	int n = 0;
	printf("P2\n800 800\n255\n");
	while(n < 8)
	{
		if((n % 2) == 0)
		{
			for(i = 0; i < 100; i++)
			{
				printBlack(0);
				printf("\n");
			}
			n++;
		}
		else
		{
			for(i = 0; i < 100; i++)
			{
				printWhite(0);
				printf("\n");
			}
			n++;
		}
	}
	return 0;
}

void printBlack(int iCount)
{
	int i;
	if(iCount == 8)
		return;
	for(i = 0; i < 100; i++)
	{
		printf("0 ");
	}
	printWhite(iCount + 1);
}

void printWhite(int iCount2)
{
	int j;
	if(iCount2 == 8)
		return;
	for(j = 0; j < 100; j++)
	{
		printf("255 ");
	}
	printBlack(iCount2 + 1);
}
