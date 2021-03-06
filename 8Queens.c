#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE	8 /*length of each side of the board*/

void place(char *board, int row, int len);
void printBoard(char *board, int len);

int sol_num;

/* Program for solving the 8 queens puzzle.
 * Prints each found solution onto the command line as it finds them.
 * Upon finding final solution, prints number of solutions found.
 */
 
int main(int argc, char *argv[]) {
	int len, x, y;
	char *board;
	
	if(argc==2)
		len = atoi(argv[1]);
	else if (argc==1)
		len = DEFAULT_SIZE;
	else {
		puts("Invalid number of arguments. Either invoke with no additional arguments\n");
		puts("to use default board size of 8, or with a single additional integer argument\n");
		puts("specifying the len of each side of the board.");
		return EXIT SUCCESS;
	}
	
	sol_num = 0;
	
	/* Allocate space for the board from memory */
	board = (char *)malloc(len * len * sizeof(char));
	if (board == NULL) {
		printf("Memory Allocation ERROR");
		return EXIT_FAILURE;
	}
	
	/* Clear the board of any junk data */
	for(x=0; x<len; x++) {
		for(y=0; y<len; y++) {
			*(board + x*len + y ) = ' ';
		}
	}
	
	/* Begin recursive backtracking, starting at the first row */
	place(board, 0, len);
	
	printf("========EXECUTION COMPLETE========\n\n%d Solutions Found\n", sol_num);
	
	free(board);
	
	return EXIT_SUCCESS;
}

void place(char *board, int current_row, int len){
	int col, row, check_col;
	
	/* If this is called past final row, this is a solution/base case, return */
	if(current_row == len) {
		sol_num++;
		printf("========Solution #%d Found========\n", sol_num);
		printBoard(board, len);
		return;
	}
	
	/* Check upper rows for attacking positions, one column at a time.
	 * When an attack is found, break statements move computation to the next column
	 */
	for(col=0; col<len; col++) {
		for(row=0; row<current_row; row++) {
			/* Check for queen in above column*/
			if( *(board + len*row + col) == 'Q')
				break;
			
			/* check for diagonal attacks */
			/* upper left */
			check_col = col - (current_row - row);
			if ( (check_col >= 0) && (*(board + len*row + check_col) == 'Q') ){
				break;
			}
			/* upper right */
			check_col = col + (current_row - row);
			if ( (check_col < len) && (*(board + len*row + check_col) == 'Q') ){
				break;
			}
		}
		
		/* If we reach the current row, place a queen here */
		if(row == current_row)
		{
			*(board + len*current_row + col) = 'Q';
			place(board, current_row + 1, len);
			/* Recursion returns here */
			/* Remove placed queen to scout for valid queen placements in same row
			 */
			*(board + len*current_row + col) = ' ';
		}
	}
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
			printf("| %c ", *(board + x*len + y));
		}
		printf("|\n");
			
	}
	/* Draw the bottom line of the board */
	for(y=0; y<len; y++)
		printf("+---");
	printf("+\n\n");
	
	return;
}