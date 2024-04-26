#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct _llist_node_t {
		char * data ;
		struct _llist_node_t * next ;
	}
	llist_node_t ;

typedef 
	struct {
		llist_node_t * last ;
	}
	llist_t ;


llist_t * create_llist () 
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ;
	l->last = NULL ;
	return l ; 
}

int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ; // 노드 만들기
	n->data = s ;
	n->next = NULL ;
	
	if (l->last == NULL) {
		l->last = n ;
		n->next = n ;
		return 1 ;
	}

	// last의 next가 first.
	llist_node_t * last; // last를 지정해주고 
	n->next = last->next ; // n의 next는 이전 last의 next
	last->next = n ;
	last = n ;

	return 1 ;
}

char * delete_llist (llist_t * l, char * s) 
{
	llist_node_t * i ;
	llist_node_t * prev ; 

	if (l->last == NULL)
		return NULL ;

	int found = 0 ; // 찾았냐 못찾았냐.
	prev = l->last ;
	i = l->last->next ;
	do {
		if (strcmp(i->data, s) == 0) {
			found = 1 ;
			break ;
		}
		prev = i ;
		i = i->next ;
	} while (i != l->last->next) ;

	if (found == 0)
		return NULL ;

	char * r ;
	r = i->data ;

	if (i == l->last) {
		if (l->last == l->last->next) { // l->last랑 l->last->next 랑 같은 경우 (즉 하나 남은 경우 )
			l->last = NULL ;
		}
		else {
			prev->next = l->last->next ;
			l->last = prev ;
		}
	}
	else {
		prev->next = i->next ;
	}
	free(i) ;

	return r ;
}

void print_llist (llist_t * l) // 아직 안끝남.
{
	if (l->last == NULL)
		return ;

	llist_node_t * i ;

	i=l->last->next;
	do {
		printf("%s",i->data);
		i=i->next;
	}
	printf("\n") ;
}

void free_llist (llist_t * l)
{
	/*TODO < 아직*/
	llist_node_t * i ;
	for (i = l->last->next ; i != NULL ; ) {
		llist_node_t * current = i;
		i=i->next;
		free(current);
	}
	free(i);
}

/*****/

int main ()
{
	llist_t * l = create_llist() ;

	insert_llist(l, "BAT") ;
	insert_llist(l, "CAT") ;
	insert_llist(l, "EAT") ;
	insert_llist(l, "FAT") ;
	insert_llist(l, "GAT") ;
	insert_llist(l, "HAT") ;
	insert_llist(l, "VAT") ;
	insert_llist(l, "WAT") ;


	delete_llist(l, "FAT") ;
	delete_llist(l, "VAT") ;

	print_llist(l) ;

	free_llist(l) ;

	return EXIT_SUCCESS ;
}
