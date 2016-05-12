#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Program for finding the longest common subsequence of two strings
 * Strings are entered in as arguments on the command line, and the longest
 * common subsequence is printed to the command line.
 * Work in progress, currently contains test code for initializing a two 
 * dimensional array of ints at the proper size for use with the two strings
 */

void printMatrix(int *matrix, int rows, int cols);

int main(int argc, char *argv[]) {
	
	int num_rows, num_cols, row, col, count;
	int *matrix;
	
	if (argc == 3) {
		num_rows = strlen(argv[1]) + 1; /* first string determines num of rows */
		num_cols = strlen(argv[2]) + 1; /* second string informs num of columns */
		
		matrix = (int *)malloc(num_rows * num_cols * sizeof(int));
		
		/* Test code for making sure memory access works as expected */
		count = 0;
		for (row=0; row < num_rows; row++) {
			for (col=0; col < num_cols; col++) {
				*(matrix + row*num_cols + col) = ++count;
			}
		}
	}
	
	printMatrix(matrix, num_rows, num_cols);
	
	return 0;
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