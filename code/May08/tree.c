#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

tree_t * 
tree_create (char data) 
{
	node_t * root ;
	root = (node_t *) malloc(sizeof(node_t)) ;
	root->data = data ;
	root->down = NULL ;
	root->next = NULL ; 
	return root ;
}

tree_t *
tree_add_child (tree_t * parent, tree_t * child)
{
	/*TODO*/
	if (parent->down == NULL){
		parent->down = child;
	}else{
		tree_t *last;
		for(last = parent->down; 
			last->next !=NULL;
			last = last->next){
				last ->next = child ;
			}

	}
	return parent ;
}

tree_t *
tree_search (tree_t * t, char key)
{
	/*TODO*/
	if(t->data ==key){
		return t;
	}
	tree_t *i ;
	for (i = t->down ; i != NULL ; i = i->next){ //child 링크 리스트들 쭉 돈다
		tree_t *r ;
		r = tree_search(i,key); // 각각의 children 마다 tree_search()를 재귀한다. 
		if (r) {
			return r;
		}
	}

<<<<<<< HEAD
=======
	tree_t * i ;
	for (i = t->down ; i != NULL ; i = i->next) {
		tree_t * r ;
		r = tree_search(i, key) ;
		if (r)
			return r ;
	}
	return NULL ;
}


void
tree_delete (tree_t * t)
{
	tree_t * i ;
	for (i = t->down ; i != NULL ; ) {
		tree_t * next ;
		next = i->next ;
		free(i) ;
		i = next ;
	}
	free(t) ;
}
/*
void
tree_delete (tree_t * t)
{
	if (t->down)
		tree_delete(t->down)  ;
	if (t->next)
		tree_delete(t->next) ;
	free(t) ;
>>>>>>> fdd86a0cd99d7920500bd91770bd30db84ad93f1
}
*/

int
tree_height(tree_t * t) 
{
	tree_t * s ;
	int max = 0 ;
	for (s = t->down ; s != NULL ; s=s->next) {
		int h ;
		h = tree_height(s) ;
		if (max < h)
			max = h ;
	}
	return max + 1 ;
}

int
tree_degree (tree_t * t)
{
	int d = 0 ;
	tree_t * s ;
	for (s=t->down ; s != NULL ; s=s->next) {
		d++ ;
	}

	for (s=t->down ; s != NULL ; s=s->next) {
		int s_d ;
		s_d = tree_degree(s) ;
		if (d < s_d) {
			d = s_d ;
		}
	}
	return d  ;
}


void
tree_print (tree_t * t)
{
	printf("%c", t->data) ;
	if (t->down) {
		printf("(") ;
		tree_print(t->down) ;
		printf(")") ;
	}
	if (t->next) {
		printf("-") ;
		tree_print(t->next) ;
	}
}

void
tree_delete (tree_t * t)
{
	/*TODO*/
	// tree_t *i ;
	// for (i = t->down ; i != NULL ; i = i->next){ //child 링크 리스트들 쭉 돈다
	// 	tree_t * next; 
	// 	next = i->next ; 
	// 	free(i);
	// 	i=next;
	// }
	// free(t);
}
