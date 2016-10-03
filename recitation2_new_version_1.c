/*-------------------------------------------------------*/
/*  Name: Javier Faustino, Felix Benavides               */
/*                                                       */
/*  This program solves the N Queens problem recursively */
/*  it places N queens on an NxN chessboard so that none */
/*  of them can move to a square occupied by any of the  */
/*  others in a single turn                              */
/*                                                       */
/*********************************************************/

// include files
#include <stdio.h>
#include <math.h>
 

// Global Variables
int board[20];
 
// start of main
int main()
{
 int n,i,j;
 int queen(int row,int n);
 
 printf("Enter the number of Queens: ");
 scanf("%d",&n);
 i = queen(1,n);
 if(i == 0)
 	printf("No Solution\n");
 return 0;
 
}
 
// function for printing the solution
void print(int n)
{
 int i,j;
 printf("\n\nSolution:\n\n");
 
 for(i=1;i<=n;++i)
 {
  printf("\n"); 
  for(j=1;j<=n;++j)	//for nxn board
  {
   if(board[i]==j)
    printf("  Q");	//queen at i,j position
   else
    printf("  -");	//empty slot
  }
 }
 printf("\n");
}
 
/* funtion to check conflicts
   If no conflict for desired postion returns 1 otherwise returns 0*/
   
int place(int row,int column)
{
 int i;
 for(i=1;i<=row-1;++i)
 {
  //checking column and digonal conflicts
  if(board[i]==column)
   return 0;

  else
   if(abs(board[i]-column)==abs(i-row))
    return 0;
 }
 
 return 1; // no conflicts
}
 
//function to check for proper positioning of queen
int queen(int row,int n)
{
 int column; 
 int boolean = 0;
 for(column=1;column<=n;++column)
 {
  if(place(row,column))
  {
   board[row]=column; 	//no conflicts so place queen
   if(row==n) 		//dead end
    {
	print(n);
	return 1;
	}
			//printing the board configuration
    else{			//try queen with next position
    boolean = queen(row+1,n);
    if(boolean == 1)
    	return 1;
}
  }
 }
 return 0;
}
