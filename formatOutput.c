#include <stdio.h>

/* Program to copy its input stream to its output stream, replacing tabs with \t,
 * replacing backspaces with \b, and replacing backslashes with \\.
 */
main() {
	
	int c; /*stores input char or EOF */
	
	while ( (c = getchar() ) != EOF ) {
		if ( c == '\t'){
			putchar('\\');
			putchar('t');
		}
		else if ( c == '\b'){
			putchar('\\');
			putchar('b');
		}
		else if (c == '\\'){
			putchar('\\');
			putchar('\\');
		}
		else {
			putchar(c);
		}
	}

}