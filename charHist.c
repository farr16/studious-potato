#include <stdio.h>

#define NUMCHAR	128 /*total number of char*/
#define LOWER	33 /*Value of lowest printable char*/
#define UPPER	126 /*Value of higest printable char*/

/* Program to print a horizontally oriented histogram of the frequency
 * of occurrences for each the printable ASCII characters in its input
 * Based on exercise 1-14 in The C Programming Language Second Edition
 */

main() {
	int c, i, j;
	
	int frequencies[NUMCHAR];
	
	/* Make sure array is clear of junk values */
	for(i=0; i<NUMCHAR; i++)
		frequencies[i] = 0;
	
	while( (c = getchar()) != EOF)
		if ( (c >= LOWER) && (c <=UPPER))
			frequencies[c]++;
	
	for(i=LOWER; i<= UPPER; i++){
		if (frequencies[i] > 0) {
			printf("Char '%c'|", i);
			for (j=0; j<frequencies[i];j++)
				putchar('=');
			putchar('\n');
		}
	}
	
	return 0;
}