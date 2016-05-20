#include <stdio.h>

void reverse(char *str);

/*Program for reversing an input string*/
main(int argc, char *argv[]) {
	
	if(argv[1]!=NULL) {
		printf("Input string: %s\n", argv[1]);
		reverse(argv [1]);
		printf("Reversed string: %s\n", argv[1]);
	}
	
	
}

/*Reverse the input string using bitwise operators*/
void reverse(char *str) {
	int i, j;
	
	/*Get index of last char of string*/
	i = 0;
	while(*(str+i)!='\0')
		i++;
	i--;
	
	/* Swap contents of pointers to front and back of string using bitwise 
	 * operators, incrementing front and decrementing back each pass
	 */
	for (j=0; j<i; j++){
		*(str + j) = *(str + i) ^ *(str + j);
		*(str + i) = *(str + i) ^ *(str + j);
		*(str + j) = *(str + i) ^ *(str + j);
		i--;
	}
	return;
}