#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Program for finding the longest common subsequence of two strings
 * Strings are entered in as arguments on the command line, and the longest
 * common subsequence is printed to the command line.
 */

void initMatrix(int *matrix, int rows, int cols);
void printMatrix(int *matrix, int rows, int cols);
void findLCS(int *matrix, int rows, int cols, char* s1, char*s2);
int minThree(int left, int diag, int top);

int main(int argc, char *argv[]) {
	
	int num_rows, num_cols;
	int *matrix;
	
	/* Elaborate more on use-cases when done implementing functionality */
	if (argc != 3) {
		printf("Improper number of arguments\n");
		return 1;
	}
	
	num_rows = strlen(argv[1]) + 1; /* first string determines num of rows */
	num_cols = strlen(argv[2]) + 1; /* second string informs num of columns */
		
	matrix = (int *)malloc(num_rows * num_cols * sizeof(int));
	
	/* Initialize starting matrix */
	initMatrix(matrix, num_rows, num_cols);
	
	findLCS(matrix, num_rows, num_cols, argv[1],argv[2]);
	
	/* Print matrix for debugging purposes */
	/* printMatrix(matrix, num_rows, num_cols); */
	
	return 0;
}

/* Function for initializing matrix to count from 1 to c across the top row 
 * where c is the number of cols, and to count from 1 to r across the first columns
 * where r is the number of rows.
 */
void initMatrix(int *matrix, int rows, int cols) {
	int i, j, count;
	count = 0;
	for (i=0; i < rows; i++) {
		for (j=0; j < cols; j++) {
			if (i == 0 || j == 0) {
				/* Initialize first row and first column to count up */
				*(matrix + i*cols + j) = count++;
			}
			else {
				/* Initialize all other spaces to 0 */
				*(matrix + i*cols + j) = 0;
			}
		}
		/* Reset counter for counting down the first column */
		if (i == 0) {
				count = 1;
		}
	}
}

/* Fills in the matrix, using a dynamic programming technique to determine the
 * lowest cost path from the origin to the bottom right.
 * Then, travel back from the bottom right to the origin, building up the LCS
 * as the program goes.
 */
void findLCS(int *matrix, int rows, int cols, char* s1, char*s2){
	int i, j;
	int left, diag, top;
	int len_LCS;
	char *LCS;
	int temp, k;
	
	/* Fill in the matrix of values with costs to get from the origin to the
	 * current spot in the array
	 */
	for(i=1; i<rows; i++) {
		for(j=1; j<cols; j++){
			left = *(matrix + i*cols + (j-1));
			if ( (*(s1+i-1)) == (*(s2+j-1)) )
				diag = *(matrix + (i-1)*cols + (j-1));
			else
				diag = INT_MAX; /*Arbitrarily large*/
			top = *(matrix + (i-1)*cols + j);
			*(matrix + i*cols + j) = minThree(left, diag, top) + 1;
		}
	}
	
	i = rows-1;
	j = cols-1;
	
	/* Determine length of LCS */
	len_LCS = ( strlen(s1) + strlen(s2) ) - *(matrix + i*cols + j);
	
	/* Allocate space for storing LCS */
	LCS = (char *)malloc((len_LCS+1)*sizeof(char));
	k = len_LCS - 1;
	
	/* Traverse matrix from bottom right to beginning, building up the LCS each
	 * time a diagonal is traversed.
	 */
	while ( ((temp = *(matrix + i*cols + j))) && (i!=0) && (j!=0) ) {
		left = *(matrix + i*cols + (j-1));
		diag = *(matrix + (i-1)*cols + (j-1));
		top = *(matrix + (i-1)*cols + j);
		
		/* If the lowest cost path is to the left, move to the left */
		if (left == (temp-1) )
			j--;
		/* If the lowest cost path is diagonal, move left and up, and build up LCS
		 * with the character from s1
		 */ 
		else if ( (diag == (temp-1)) && (*(s1+i-1)) == (*(s2+j-1)) ) {
			*(LCS+k) = *(s1+i-1);
			i--;
			j--;
			k--;
		}
		/* If the lowest cost path is up, move up */
		else {
			i--;
		}
	}
	
	*(LCS + len_LCS) = '\0';
	printf("Longest Common Subquence for %s and %s:\n%s\n", s1, s2 , LCS);
	
	return;
}

/* Code for determining where the lowest score path from the origin comes from
 * Returns 1 if the left score is the min (or tied for min)
 * Returns 2 if the diagonal score is the min (or tied with top)
 * Returns 3 if the top score is the min
 */
int minThree(int left, int diag, int top){
	if ( (left<=top) && (left<=diag) )
		return left;
	else if ( (diag<=left) && (diag<=top) )
		return diag;
	else
		return top;
}

/* Test code for printing contents of the matrix used for finding the longest
 * common subsequence.
 */
void printMatrix(int *matrix, int rows, int cols) {
	int i,j;
	
	for (i=0; i < rows; i++) {
		/* Print top line on matrix */
		for(j=0; j < cols; j++) {
			printf("+---");
		}
		printf("+\n");
		/* Print row of integers from matrix */
		for(j=0; j < cols; j++) {
			printf("|%3d", *(matrix + i*cols + j));
		}
		printf("|\n");
	}
	/* Print bottom line on matrix */
	for(j=0; j < cols; j++) {
			printf("+---");
	}
	printf("+\n");
	return;
}