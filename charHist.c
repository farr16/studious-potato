#include <stdio.h>

#define LOWER	33 /* Lower limit of char values we are counting*/
#define UPPER	126 /* Upper limit of char values we are counting*/

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
	int i;
	
	for (i = LOWER; i <= UPPER; i++) {
		printf("Char Value %d:\t%c\n", i, i);
	}
}