#include <stdio.h>
#include <stdlib.h>

#include "lalist.h"

void print_element (void * e)
{
	int * a ; 

	a = (int *) e ;

	printf("%d ", *a) ;
}

void double_element (void * e)
{
	/* TODO */
	void double_element(void * e) {
    int *value; 
    value = (int *) e; // int 포인터로 형 변환
    *value = *value * 2; // 가리키는 값에 2를 곱하여 저장
}
}


int main () 
{
	int data ;
	lalist_t * l ; 

	l = lalist_alloc(3, sizeof(int)) ;

	data = 1 ;
	lalist_insert_last(l, &data) ; //[1, ,]

	data = 2 ;
	lalist_insert_last(l, &data) ; //[1,2, ]

	data = 3 ;
	lalist_insert_last(l, &data) ; // [1,2,3]

	data = 4 ;
	lalist_insert_first(l, &data) ; //[4, , ]-> [1,2,3]

	data = 5 ;
	lalist_insert_last(l, &data) ; //[4, , ]->[1,2,3] -> [5 , ,]

	data = 6 ;
	lalist_insert_at (l, 2, &data) ; // [4, ,]->[1,6, ] -> [2,3, ] -> [5,,]

	data = 7 ;
	lalist_insert_at(l, 3, &data) ; // [4,,]->[1,6,7]->[2,3,]->[5,,]

	data = 8 ;
	lalist_insert_last(l, &data) ; // [4,,]->[1,6,7]->[2,3,]->[5,8,]

	lalist_apply(l, print_element) ; 
	printf("\n") ;

	lalist_info(l) ;

	// lalist_remove_first(l, &data) ; // [1,6,7]->[2,3,]->[5,6,]
	// lalist_remove_last(l, &data) ; //[1,6,7]->[2,3,]->[5,,]
	// lalist_remove_last(l, &data) ; //[1,6,7]->[2,3,]

	lalist_apply(l, print_element) ; 
	printf("\n") ;
	lalist_info(l) ;

	data = 9; 
	// lalist_insert_at(l,1,&data) ; // [1,9,]->[7, ,]->
	// lalist_pack(l) ;
	lalist_apply(l, print_element) ; 
	printf("\n") ;
	lalist_info(l) ;

	lalist_free(l) ;

	return EXIT_SUCCESS ;
}
