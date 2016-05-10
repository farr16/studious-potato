#include <stdio.h>

#define IN		1	/* State for inside a space */
#define OUT		0	/* State for outside a space */

/* Program to copy its input stream to its output stream, replacing each sequence
 * of more than one consecutive blank space with a single blank space.
 * Based on Exercies 1-9 of The C Programming Language Second Edition
 */
main() {
	
	int c; /*stores input char or EOF */
	int state;
	
	state = OUT;
	
	while ( (c = getchar() ) != EOF ) {
		if ( c != ' '){
			putchar(c);
			state = OUT;
		}
		else{
			if (state == OUT){
				putchar(c);
				state = IN;
			}
			else{
				;
			}
		}
	}

}