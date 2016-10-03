/*-----------------------------------------------------*/
/*  Name: Javier Faustino, Felix Benavides             */
/*                                                     */
/*  This program reads an array of positive integers   */
/*  from the user and displays how each positive       */
/*  integer can be formed as sum of subsets of numbers */ 
/*  from the array.                                    */
/*                                                     */
/*  Ex.                                                */
/*          2 1 8 3                                    */
/*      The output for this should be                  */
/*      1: 1                                           */
/*      2: 2                                           */
/*      3: 3                                           */
/*      4: 3 + 1                                       */
/*      5: 3 + 2                                       */
/*      6: 3 + 2 + 1                                   */
/*      7: NA                                          */
/*                                                     */
/*                                                     */
/*******************************************************/

// include headers and constants

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int solve(int array[], int aSub, int arrayB[], int bSub, int target, int sum, int n);	

int main()
{
	// Asks the user how many number in the array they want
	 
	int MAX_ARRAY_LENGTH;
	
	printf("How many numbers do you want to input into the array ?\n");
	scanf("%d", &MAX_ARRAY_LENGTH);
	printf("\n");
	
	// Asks the user to input the numbers into the array
	
	int array[MAX_ARRAY_LENGTH];
	int i = 0, j = 0, a;
	
	
	printf("Enter %d positive integers into the array:\n", MAX_ARRAY_LENGTH);
	
	// Needs improvement (do while) ? for negative numbers wasn't asked but doesn't hurt
	
	for (i = 0; i < MAX_ARRAY_LENGTH; i++){
		scanf("%d", &array[i]);
	}
	
	// Sorts the array in descending order
	
	for (i = 0; i < MAX_ARRAY_LENGTH; i++){
		for (j = i + 1; j < MAX_ARRAY_LENGTH; j++){
			if (array[i] < array [j])
			{
				a = array[i];
				array[i] = array [j];
				array [j] = a;
			}
		}
	}
	
	
	// Prints the array for descending order
	
	int sum = 0;
	printf("\nArray: ");
	for (i = 0; i < MAX_ARRAY_LENGTH; i++){
		printf("%d ", array[i]);
		sum += array[i];
	}
	printf("\n");
	
	
	int bool = FALSE;
	// initialize new array to keep track of numbers used to represent certain integer
	int arrayB[MAX_ARRAY_LENGTH];
	for(i = 1; i <= sum + 1; i++)
	{
		bool = solve(array, 0, arrayB, 0, i, 0, MAX_ARRAY_LENGTH);
		if(bool == FALSE)
		{
			printf("%d: NA", i);
			break;
		} 
	}
	
	
  return 0;
}

void printSum(int array[], int iCount, int target)
{
	int i;
	// print target and first number
	printf("%d: %d", target, array[0]);
	// print the rest of the array
	for(i = 1; i < iCount; i++)
	{
		printf(" + %d", array[i]);
	}
	printf("\n");
}

// send in: array of user input, subscript of number in user input array the program is on, new array of numbers being added to represent target,
// subscript of new array to insert new number, target number, sum of numbers so far, count for all numbers in array
int solve(int array[], int aSub, int arrayB[], int bSub, int target, int sum, int n)
{
	int bool;
	int i;
	if(sum > target)
		return FALSE;
	if(sum == target)
	{
		printSum(arrayB, bSub, target);
		return TRUE;	
	}
	for(i = aSub; i < n; i++)
	{
		// save number added to new array
		arrayB[bSub] = array[i];
		bool = solve(array, i + 1, arrayB, bSub + 1, target, sum + array[i], n);
		// if boolean is true, then representation for number is already found
		if(bool == TRUE)
			return TRUE;
	}
	return FALSE;	
}

