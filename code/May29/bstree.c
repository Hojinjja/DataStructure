#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

bst_t * 
bst_create (size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	bst_t * t = (bst_t *) malloc(sizeof(bst_t)) ;
	t->root = NULL ;
	t->usize = usize ;
	t->cmp = cmp ;
	return t ;
}

bst_node_t *
_bst_search (bst_t * t, void * data)
{
	bst_node_t * prev, * curr ;
	prev = NULL ;
	for (curr = t->root ; curr != NULL && t->cmp(curr->data, data) != 0 ; ) {
		prev = curr ;
		if (t->cmp(data, curr->data) < 0) {
			curr = curr->left ;
		}
		else {
			curr = curr->right ;
		}
	} 
	if (curr != NULL)
		return curr ;
	return prev ;
}

int
bst_search (bst_t * t, void * data)
{
	bst_node_t * n ; 

	n = _bst_search(t, data) ;
	if (n == NULL)
		return 0 ;
	if (t->cmp(n->data, data) != 0)
		return 0 ;

	memcpy(data, n->data, t->usize) ;
	return 1 ;
}



int
bst_insert (bst_t * t, void * data) 
{
	bst_node_t * parent;
	parent = _bst_search(t, data) ;
	if (parent != NULL && t->cmp(parent->data, data) == 0)
		return 0 ;

	bst_node_t * n = (bst_node_t *) malloc(sizeof(bst_node_t)) ;
	n->data = (char *) malloc(t->usize) ;
	memcpy(n->data, data, t->usize) ;
	n->left = NULL ;
	n->right = NULL ;
	
	if (parent== NULL) {
		t->root = n ;
		n->parent = NULL ;
	}
	else {
		n->parent = parent ;
		if (t->cmp(data, n->parent->data) < 0) {
			n->parent->left = n ;
		}
		else {
			n->parent->right = n ;
		}
	}
	return 1 ;
}

int
bst_remove (bst_t * t, void * data)
{
	bst_node_t * n ; // 지우려는 노드 n 
	n = _bst_search(t, data) ;
	if (n == NULL || t->cmp(n->data, data) != 0) 
		return 0 ;

/*TODO*/
	if(n->left = NULL){ // 지우려는 노드의 left가 NULL인 경우
		// n->parent ->XXX = n->right; => 경우의 수가 3개임 
		if(n->parent == NULL){
			t->root = n->right ; 
		}
		if(n->parent->left == n){
			n->parent->left = n->right;
		}
		else{ /*n ->parent->right ==n*/
			n->parent->right = n->right;
		}

		free(n->data);
		free(n);
		return 1;
	}
	/*assume (n->left != NULL)*/
	/*max_left 찾기*/

	bst_node_t * lmax = n->left ; // lmax는 right_child가 NULL인 node까지 
	
	while(n->left->right != NULL){
		lmax= lmax->right;
	} //여기까지 통과되면 lmax->right는 NULL인 상황 

	lmax->parent->right = lmax->left; //lmax->left도 NULL이면 lmax->parent는 자식이 없어지는 것 
	lmax->left = NULL;
	
	lmax->parent = n->parent;

	if(n->parent ==NULL){
		t->root = lmax;
	}
	else if (n->parent->left == n){
		n->parent->left = lmax;
	}
	else /*(n->parent=>right ==n)*/{
		n->parent ->right =lmax;
	}

	lmax->left = n->left;
	if(n->left!=NULL){
		n->left->parent = lmax;
	}

	lmax->right = n->right;
	if(n->right != NULL){
		n->right->parent=lmax;
	} 
	
	return 1 ;
}

void
bst_node_print (bst_node_t * n, void (* print)(void * data))
{
	printf("(") ;
	if (n->left != NULL) 
		bst_node_print(n->left, print) ;
	else
		printf("-") ;
	printf(",") ;
	print(n->data) ;
	printf(",") ;
	if (n->right != NULL) 
		bst_node_print(n->right, print) ;
	else
		printf("-") ;
	printf(")") ;
}

void
bst_print (bst_t * t, void (* print)(void * data)) 
{
	if (t->root != NULL)
		bst_node_print(t->root, print) ;
	printf("\n") ;
}

void
bst_node_free (bst_node_t * n)
{
	if (n->left != NULL)
		bst_node_free(n->left) ;
	if (n->right != NULL)
		bst_node_free(n->right) ;
	free(n->data) ;
}

void
bst_free (bst_t * t)
{
	if (t->root != NULL) 
		bst_node_free(t->root) ;
	free(t) ;
}
