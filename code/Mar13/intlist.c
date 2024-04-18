#include <stdio.h>
#include <stdlib.h>

typedef
	struct  {
	int * items ;
	int n_items ;
	}intlist_t;

struct intlist_t * intlist_create () ;
int intlist_size (intlist_t * l) ;
int intlist_get (intlist_t * l, int i) ;
int intlist_insert (intlist_t * l, int i) ;

int main ()
{
	return EXIT_SUCCESS ;
}
