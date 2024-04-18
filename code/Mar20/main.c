#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int
main () 
{
	stack_t * st ;
	int data ;

	st = create_stack(4) ;
	push(st, 11) ;
	push(st, 12) ;
	push(st, 13) ;
	push(st, 14) ;
	push(st, 15) ; // พ๊ดย push x 

	for(int i=0; i<st->capacity; i++){
	pop(st,&data);
	printf("%d\n",data);
	}

	// pop(st, &data) ;
	// printf("%d\n", data) ;

	delete_stack(st) ;

	return EXIT_SUCCESS ;
}
