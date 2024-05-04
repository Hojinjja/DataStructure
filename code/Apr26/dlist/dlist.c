#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

dlist_t * 
dlist_alloc (int unit) 
{
	dlist_t * l = (dlist_t *) malloc(sizeof(dlist_t)) ;
	l->left = l  ;	
	l->right = l ;
	l->element = malloc(sizeof(int)) ;
	int * u = (int *) l->element ;
	*u = unit ;

	return l ;
}

void
dlist_free (dlist_t * l)
{
	node_t * curr ;
	node_t * next ;

	curr = l->right ;
	while (curr != l) {
		next = curr->right ;
		free(curr->element) ;
		free(curr) ;
		curr = next ;
	}
	free(l->element) ;
	free(l) ;
}

int 
dlist_length (dlist_t * l)
{
	int len = 0 ;

	node_t * curr = l->right ;
	while (curr != l) {
		len += 1 ;
		curr = curr->right ; 
	}
	return len ; 
}

void 
dlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
	_new->element = malloc(unit) ; // element �޸� �Ҵ�
	memcpy(_new->element, e, unit) ; // element�� e�� unit ũ�⸸ŭ ����

	node_t * right = left->right ; // right ���� new����� right�� �� �κ� (���� new�� ������ �ȵ� �����̹Ƿ� left�� �����ʿ� right ���)

	_new->left = left ;
	_new->right = right ;

	left->right = _new ;
	right->left = _new ;
}

void
dlist_insert_first (dlist_t * l, void * e)
{
	dlist_insert(l, e, *((int *)(l->element))) ; // l�� �����ʿ� insert
}

void
dlist_insert_last (dlist_t * l, void * e)
{
	dlist_insert(l->left, e, *((int *)(l->element))) ; // l�� ������ �����ʿ� insert
}

int
dlist_remove (dlist_t * l, node_t * n)
{
	if (l->left == l)
		return 0 ;

	n->left->right = n->right ; // ���� ��� n
	n->right->left = n->left ;

	free(n->element) ;
	free(n) ;
	return 1 ;
}

int 
dlist_remove_first (dlist_t * l, void * e)
{
	if (l->right == l)
		return 0 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ;
	dlist_remove(l, l->right) ;
	return 0 ;
}

int
dlist_remove_last (dlist_t * l, void * e)
{
	if (l->left == l)
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ;
	dlist_remove(l, l->left) ;
	return 1 ;
}

int
dlist_get (dlist_t * l, int index, void * e)
{
	return 0 ;
}

void
dlist_apply (dlist_t * l, void (* func)(void * e)) // �����Ű��
{
	node_t * i ;

	for (i = l->right ; i != l ; i = i->right) {
		func(i->element) ;
	}
}








