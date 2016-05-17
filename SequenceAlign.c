#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCORES	0	/*Print mode for scores table*/
#define DIRECTIONS	1 /*Print mode for directions table*/

void initScores(int *matrix, int num_rows, int num_cols);
void initDirections(char *matrix, int num_rows, int num_cols);
void printScores(int *matrix, int num_rows, int num_cols);
void printDirections(char *matrix, int num_rows, int num_cols);

/* Program for computing the global alignment score of two nucleotide sequences
 * using a dynamic programming method.
 */
 
int main(int argc, char *argv[]) {
	
	int num_rows, num_cols;
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
	
	printScores(score_matrix, num_rows, num_cols);
	printDirections(direction_matrix, num_rows, num_cols);
	
	free(score_matrix);
	free(direction_matrix);
	
	return 0;
}

void initScores(int *matrix, int num_rows, int num_cols) {
	int row, col, count;
	count = 0; /*Test value*/
	for (row=0; row < num_rows; row++) {
		for (col=0; col < num_cols; col++) {
			if (row == 0 || col == 0) {
				/* Initialize first row and first column to count up */
				*(matrix + row*num_cols + col) = count++;
			}
			else {
				/* Initialize all other spaces to 0 */
				*(matrix + row*num_cols + col) = 0;
			}
		}
		/* Reset counter for counting down the first column */
		if (row == 0) {
				count = 1;
		}
	}
}

void initDirections(char *matrix, int num_rows, int num_cols) {
	int row, col;
	char c = '!';/*Test value*/
	for (row=0; row < num_rows; row++) {
		for (col=0; col < num_cols; col++) {
			if (row == 0 || col == 0) {
				/* Initialize first row and first column to count up */
				*(matrix + row*num_cols + col) = c++;
			}
			else {
				/* Initialize all other spaces to blank */
				*(matrix + row*num_cols + col) = ' ';
			}
		}
		/* Reset counter for counting down the first column */
		if (row == 0) {
				c = '!' + 1;/*Test value*/
		}
	}
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