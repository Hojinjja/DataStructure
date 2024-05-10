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
tree_search (node_t * t, char key)
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

}


int
tree_height(tree_t * t) 
{
	/*TODO*/
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
