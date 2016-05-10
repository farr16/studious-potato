#include <stdio.h>

/* Program for counting spaces, tabs, and newlines in input stream
 * Based on Exercise 1-8 in The C Programming Language Second Edition
 */
main() {

	int c; /* Stores char of input, or EOF */
	int sp, ta, nl; /* Counter variables */
	
	nl = sp = ta = 0;
	
	while ( (c = getchar()) != EOF ){
		if(c == ' '){
			sp++;
		}
		else if (c == '\t'){
			ta++;
		}
		else if (c == '\n'){
			nl++;
		}
	}
	
	printf("Num of spaces: %d\nNum of tabs: %d\nNum of newlines: %d\n", sp, ta, nl);

}