#include <stdio.h>
#include <stdlib.h>

#define SIZE	8 /*length of each side of the board*/

void printBoard(char *board, int len);

/* Program for solving the 8 queens puzzle.
 * VERY tentative at this point. As of now, contains prototype code for initializing
 * board;
 */
 
int main() {
	int len, x, y;
	char *board;
	
	len = SIZE;
	
	/* Allocate space for the board from memory */
	board = (char *)malloc(len * len * sizeof(char));
	if (board == NULL) {
		printf("Memory Allocation ERROR");
		return 1;
	}
	
	/* Clear the board of any junk data */
	for(x=0; x<len; x++) {
		for(y=0; y<len; y++) {
			/* Will be blanks in final program, testing to make sure these are 
			 * really getting filled in by this section of code
			 */
			*(board + x * len + y ) = 33 + x*len+y;
		}
	}
	
	printBoard(board, len);
}

void printBoard(char * board, int len) {
	int x, y;
	
	for(x=0; x<len; x++) {
		/* Draw top line of row */
		for(y=0; y<len; y++) {
			printf("+---");
		}
		printf("+\n");
		/* Draw row of characters */
		for(y=0; y<len; y++) {
			printf("| %c ", *(board + x * len + y));
		}
		printf("|\n");
			
	}
	/* Draw the bottom line of the board */
	for(y=0; y<len; y++)
		printf("+---");
	printf("+\n");
	
	return;
}