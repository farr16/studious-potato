#include <stdio.h>
#include <stdlib.h>

void printBoard(char *board, int len);

/* Program for solving the 8 queens puzzle.
 * VERY tentative at this point. As of now, contains prototype code for initializing
 * board;
 */
 
int main() {
	int len, x, y;
	char *board;
	
	/* Allocate space for the board from memory */
	board = (char *)malloc(len * len * sizeof(char));
	
	/* Clear the board of any junk data */
	for(x=0; x<len; x++) {
		for(y=0; y<len; y++) {
			*(board + x * len + y ) = ' ';
		}
	}
	
}

void printBoard(char * board, int len) {
	int x, y;
	
	for(x=0; x<len; x++) {
		/* Draw top line of row */
		/* Draw row of characters */
		;
	}
	/* Draw the bottom line of the board */
	
	return;
}