#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
			printf("INPUT mode: STRING");
			num_rows = strlen(argv[1]) + 1;
			num_cols = strlen(argv[2]) + 1;
		}
		else if(strcmp(argv[3],"file") == 0) {
			printf("INPUT mode: FILE");
			/*TODO: Input file reading functionality*/
		}
		else
			printf("Unrecognized input mode option. Use either string or file.\n");
		return EXIT_SUCCESS;
	}
	
	score_matrix = (int *) malloc(num_rows * num_cols * sizeof(int));
	direction_matrix = (char *) malloc(num_rows * num_cols * sizeof(char));
	if ( (score_matrix == NULL) || (direction_matrix == NULL) ){
		printf("Memory allocation failure\n");
		return EXIT_FAILURE;
	}
	
	free(score_matrix);
	free(direction_matrix);
	
	return 0;
}