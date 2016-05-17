#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATCH		5	/*Positive reward for sequence nucleotide matching*/
#define GAP			-4	/*Negative reward for gap in a nucleotide sequence*/
#define MISMATCH	-6	/*Negative reward for mismatch in a nucleotide sequence*/

void initScores(int *matrix, int num_rows, int num_cols);
void initDirections(char *matrix, int num_rows, int num_cols);
void printScores(int *matrix, int num_rows, int num_cols);
void printDirections(char *matrix, int num_rows, int num_cols);
int maxThree(int first, int second, int third);

/* Program for computing the global alignment score of two nucleotide sequences
 * using a dynamic programming method.
 */
 
int main(int argc, char *argv[]) {
	
	int num_rows, num_cols, row, col;
	int *score_matrix;
	char *direction_matrix;
	
	/*Input format: [.exe] [string1] [string2] [input_mode] */
	if (argc != 4) {
		puts("\nSequenceAlign\nWritten by Matthew Farr\n");
			puts("This code outputs the optimal sequence alignment of two nucleotide sequences.");
			puts("Format: [.exe name] [seq1] [seq2] [input mode]");
			puts("Where [exe name] is the name of the .exe file created after compilation");
			puts("of SequenceAlign.c, [seq1] is either the first sequence to be compared ");
			puts("or the name of a FASTA formatted file containing the sequence, ");
			puts("[seq2] is either the second sequence to be compared or the name of a FASTA");
			puts("formatted filed containing the sequence, and [input mode] is either string or");
			puts("file.");
		return EXIT_SUCCESS;
	}
	
	if( argv[3] != NULL) {
		if(strcmp(argv[3],"string") == 0) {
			printf("INPUT mode: STRING\n");
			num_rows = strlen(argv[1]) + 1;
			num_cols = strlen(argv[2]) + 1;
		}
		else if(strcmp(argv[3],"file") == 0) {
			printf("INPUT mode: FILE\n");
			/*TODO: Input file reading functionality*/
		}
		else
			printf("Unrecognized input mode option. Use either string or file.\n");
	}
	
	score_matrix = (int *) malloc(num_rows * num_cols * sizeof(int));
	direction_matrix = (char *) malloc(num_rows * num_cols * sizeof(char));
	if ( (score_matrix == NULL) || (direction_matrix == NULL) ){
		printf("Memory allocation failure\n");
		return EXIT_FAILURE;
	}
	
	initScores(score_matrix, num_rows, num_cols);
	initDirections(direction_matrix, num_rows, num_cols);
	
	int top, left, dag, val;
	
	/* Fill in rows of the cost table with path costs, starting at the top row
	 * and going left to right. Fill in the directions table with direction each
	 * calculated cost came from.
	 */
	for (row=1; row<num_rows; row++) {
		for (col=1; col<num_cols; col++) {
			/* Cost of gap between the top and bottom sequences */
			top = *(score_matrix + (row-1)*num_cols + col) + GAP;
			left = *(score_matrix + row*num_cols + (col-1)) + GAP;
			
			/* Determine if sequences match or mismatch at the substrings being
			 * compared, increase diagonal score for match, decrease for mismatch
			 */
			if( *(argv[1]+ (row-1)) == *(argv[2] + (col-1)) )
				dag = *(score_matrix + (row-1)*num_cols + (col-1)) + MATCH;
			else
				dag = *(score_matrix + (row-1)*num_cols + (col-1)) + MISMATCH;
			
			val = maxThree(top, left, dag);
			*(score_matrix + row*num_cols + col) = val;
			
			/* Fill in directions table with where max score came from */
			if(val == left)
				*(direction_matrix + row*num_cols + col) = 'L';
			else if (val == dag)
				*(direction_matrix + row*num_cols + col) = 'D';
			else
				*(direction_matrix + row*num_cols + col) = 'T';
		}
	}
	
	printScores(score_matrix, num_rows, num_cols);
	printDirections(direction_matrix, num_rows, num_cols);
	
	free(score_matrix);
	free(direction_matrix);
	
	return 0;
}

/* Function for initializing the table of values used to calculate the cost of
 * each path from the origin to the final alignment
 */
void initScores(int *matrix, int num_rows, int num_cols) {
	int row, col, count;
	count = 0;
	for (row=0; row < num_rows; row++) {
		for (col=0; col < num_cols; col++) {
			if (row == 0 || col == 0) {
				/* Initialize first row and first column to decrement by 6 */
				*(matrix + row*num_cols + col) = count;
				count += MISMATCH;
			}
			else {
				/* Initialize all other spaces to 0 */
				*(matrix + row*num_cols + col) = 0;
			}
		}
		/* Reset counter for counting down the first column */
		if (row == 0) {
				count = MISMATCH;
		}
	}
}

/* Function for initializing the table of directions used to trace our way
 * to the final alignment once the path scores have been calculated
 */
void initDirections(char *matrix, int num_rows, int num_cols) {
	int row, col;
	char c = 'F';
	for (row=0; row < num_rows; row++) {
		for (col=0; col < num_cols; col++) {
			if (row == 0 && col == 0){
				*(matrix + row*num_cols + col) = c;
				c = 'L';
			}
			else if (row == 0 || col == 0) {
				/* Initialize first row to L's and first column to T's */
				*(matrix + row*num_cols + col) = c;
			}
			else {
				/* Initialize all other spaces to blank */
				*(matrix + row*num_cols + col) = ' ';
			}
		}
		/* Set 'T' for first column after setting 'L' across first row */
		if (row == 0) {
				c = 'T';
		}
	}
}

/* Returns the maximum of three integer values
 */
int maxThree(int first, int second, int third) {
	if (first >= second && first >= third)
		return first;
	else if (second >= first && second >= third)
		return second;
	else
		return third;
}

/* Test code for printing contents of the scores matrix used for finding the ideal
 * sequence alignment
 */
void printScores(int *matrix, int num_rows, int num_cols) {
	int row, col;
	
	for (row=0; row < num_rows; row++) {
		/* Print top line on matrix */
		for(col=0; col < num_cols; col++)
			printf("+---");
		printf("+\n");
		
		/* Print row of integers from matrix */
		for(col=0; col < num_cols; col++)
			printf("|%3d", *(matrix + row*num_cols + col));
		printf("|\n");
	}
	/* Print bottom line on matrix */
	for(col=0; col < num_cols; col++) {
			printf("+---");
	}
	printf("+\n");
	return;
}

/* Test code for printing contents of the directions matrix used for finding the
 * ideal sequence alignment
 */
void printDirections(char *matrix, int num_rows, int num_cols) {
	int row, col;
	
	for (row=0; row < num_rows; row++) {
		/* Print top line on matrix */
		for(col=0; col < num_cols; col++)
			printf("+---");
		printf("+\n");
		
		/* Print row of directions from matrix */
		for(col=0; col < num_cols; col++)
			printf("| %c ", *(matrix + row*num_cols + col));
		printf("|\n");
	}
	/* Print bottom line on matrix */
	for(col=0; col < num_cols; col++) {
			printf("+---");
	}
	printf("+\n");
	return;
}