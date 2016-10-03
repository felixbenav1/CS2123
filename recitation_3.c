/******************* Recitation 3 *********************

******************************************************/
#include <stdio.h>
#include <stdlib.h>

//void change(int row, int column, int m, int array[][m], int array2[][m]);
int area(int topR, int topC, int botR, int botC, int m, int array[][m]);

int main()
{
	FILE *file;
	int rows;
	int columns;
	int i;
	int j;
	int **array;
	file = fopen("a.txt", "r");
	if(file == NULL)
	{
		printf("File does not exist.");
		return 0;
	}
	i = fscanf(file, "%d %d", &rows, &columns);
	if(i != 2)
	{
		printf("Not enough information.");
		return 0;
	}
	array = (int **)malloc(rows*sizeof(int *));
	if(array == NULL)
	{
		printf("No memory availale.");
		return 0;
	}
	for (i = 0; i < rows; i++)
	{
        *(array+i) = (int*) malloc(columns*sizeof(int));
		for(j = 0; j < columns; j++) 
		{
			if (fscanf(file, "%d ", &array[i][j]) != 1)
			{
				printf("File input error.");
				return 0;
			}
		}
    }
	
	int m, n;
	int array2[rows][columns];
	int sum = 0;
	for(i = 0; i < rows; i++)
	{
		
		for(j = 0; j < columns; j++)
		{
			sum = 0;
			for(m = 0; m <= i; m++)
			{
				for(n = 0; n <= j; n++)
				{
					sum += array[m][n];
				}
			}
			array2[m-1][n-1] = sum;
		}
	}
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			printf("%d ", array2[i][j]);
		}
		printf("\n");
	}
	printf("Enter top left and bottom right coordinates of rectangle (-1 to quit):\n");
	int topR, topC, botR, botC;
	while(1)
	{
		scanf("%d", &topR);
		if(topR == -1)
			break;
		i = scanf("%d %d %d", &topC, &botR, &botC);
		if(i < 3)
			printf("Invalid coordinates.\n");
		else if(topR < 0 || topC < 0 || botR < 0 || botC < 0)
		{
			if(topR == -1 || topC == -1 || botR == -1 || botC == -1)
				break;
			printf("Please enter positive numbers only.\n");
		}
		else if(topR > rows - 1 || topC > columns - 1 || botR > rows - 1 || botC > columns - 1)
			printf("Invalid coordinates.\n");
		else
		{
			sum = area(topR, topC, botR, botC, columns, array2);
			printf("Sum = %d\n", sum);
		}
	}
    //Free the array
    
	for(i = 0; i < rows; i++)
    {
    	free(*(array+i));
	}
	printf("Goodbye.");
	fclose(file); //Close the file
}

int area(int topR, int topC, int botR, int botC, int m, int array[][m])
{
	int sum = array[botR][botC];
	if(topR - 1 < 0 && topC - 1 < 0)
		return sum;
	else if(topC - 1 < 0)
	{
		sum -= array[topR - 1][botC];
		return sum;
	}
	else if(topR - 1 < 0)
	{
		sum -= array[botR][topC - 1];
		return sum;
	}
	else
	{
		sum -= array[topR - 1][botC];
		sum -= array[botR][topC - 1];
		sum += array[topR - 1][topC - 1];
		return sum;
	}
}
