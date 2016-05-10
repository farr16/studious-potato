#include <stdio.h>

#define NUMCHAR	128 /*total number of char*/
#define LOWER	33 /*Value of lowest printable char*/
#define UPPER	126 /*Value of higest printable char*/

/* Program to print a horizontally oriented histogram of the frequency
 * of occurrences for each the printable ASCII characters in its input
 * Based on exercise 1-14 in The C Programming Language Second Edition
 */
 
 /* Process:
  * Get character from input stream
  * Increase value of that character's count in array of frequency counts
  * If the count for that char value is greater than max, change max value
  * Repeat till end
  * At end, iterate over array until we find char value with lowest non-zero
  *		value
  * For each char with more than zero occurrences, print number of = signs
  * 	equal to the number of occurrences of that char divided by the number
  *		of occurrences of the least common character
  */

main() {
	int c, i;
	
	int frequencies[NUMCHAR];
	
	/* Make sure array is clear of junk values */
	for(i=0; i<NUMCHAR; i++)
		frequencies[i] = 0;
	
	while( (c = getchar()) != EOF)
		if ( (c >= LOWER) && (c <=UPPER))
			frequencies[c]++;
	
	for(i=LOWER; i<= UPPER; i++){
		if (frequencies[i] > 0) {
			printf("Char '%c':\t%d\n", i, frequencies[i]);
		}
	}
	
	return 0;
}