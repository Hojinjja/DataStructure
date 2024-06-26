#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "intstack.h"


int
main ()
{
	stack_t * operands ;
	operands = create_stack(100) ;

	char tok[8] ; //최대 8자리 
	do {
		print_stack(operands) ;

		scanf("%7s", tok) ;

		if (tok[0] == ';') 
			break ;

		if (isdigit(tok[0])) { //만약 tok으로 들어온 값이 피연산자라면
			int num = atoi(tok) ;
			push(operands, num) ;
		}
		else /* operator */ {
			switch (tok[0]) {
				case '+' : {
					int n1, n2, res ;
					pop(operands, &n2) ;
					pop(operands, &n1) ;
					res = n1 + n2 ;
					push(operands, res) ;
					break ;
				} 

				case '-' : {
					int n1, n2, res ;
					pop(operands, &n2) ;
					pop(operands, &n1) ;
					res = n1 - n2 ;
					push(operands, res) ;
					break ;
				}

				case '*' : {
					int n1, n2, res ;
					pop(operands, &n2) ;
					pop(operands, &n1) ;
					res = n1 * n2 ;
					push(operands, res) ;
					break ;
				}

				case '/' : {
					int n1, n2, res ;
					pop(operands, &n2) ;
					pop(operands, &n1) ;
					res = n1 / n2 ;
					push(operands, res) ;
					break ;
				}
			}
		}
	} while (tok[0] != ';') ;

	int result ;
	pop(operands, &result) ;
	printf("%d\n", result) ;
	
	delete_stack(operands) ;
	return EXIT_SUCCESS ;
}
