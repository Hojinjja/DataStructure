#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
	char name[10] ; 
	int age ;
} ;


int main ()
{
	struct person shin ;

	strcpy(shin.name, "Shin Hong") ; //shin.name¿¡ "Shin Hong" copy
	shin.age = 38 ;	
	

	printf("%ld\n", sizeof(struct person)) ;
	printf("name:%s , age:%d\n",shin.name, shin.age);

	return EXIT_SUCCESS ; 

}
