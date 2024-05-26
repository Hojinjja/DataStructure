#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

//array list�� ���� 

slist_t *
slist_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	slist_t * h = malloc(sizeof(slist_t)) ;
	h->arr = calloc(capacity, usize) ;
	h->capacity = capacity ;
	h->size = 0 ;
	h->usize = usize ;
	h->cmp = cmp ;
	return h ;
}

void
slist_free (slist_t * h) 
{
	free(h->arr) ;
	free(h) ;
}

int
slist_size (slist_t * h)
{
	return h->size ;
}

int
cmp (slist_t * h, int a, int b)
{
	return h->cmp(h->arr + a * h->usize, h->arr + b * h->usize) ;
}

int
slist_top (slist_t * h, void * buf) //0��° element �켱���� 1��.
{
	if (h->size == 0)
		return 0 ;
	memcpy(buf, h->arr, h->usize) ;
	return 1 ;
}

int
slist_pop (slist_t * h, void * buf)
{
	if (h->size == 0)
		return 0 ;
	/* TODO */
	memcpy(buf, h->arr, h->usize);
	int p = 0;
	
	for(p=0; p <h->size-1; p++){
		memcpy(h->arr + p*h->size,	//2�� ���ڿ��� 1�� ���ڷ� �ű�
			  	h->arr+(p+1)*h->size,
				h->usize);
	}
	h->size = h->size-1;
	return 1 ;
}

int
slist_push (slist_t * h, void * buf) //���� ���踦 �������. 
{
	if (h->size == h->capacity) 
		return 0 ;

	
	int p = 0 ; // ���ο� element�� �� ��ġ 
	for (p = 0 ; p < h->size ; p++) {
		if (0 < h->cmp(h->arr + p * h->usize, buf)) { //compare�� �⺻������ ����. 
		//h->arr + p * h->usize �̰Ͱ� buf �� 
			break ;
		}
	}

	memcpy(h->arr + p*h->usize, buf, h->usize);
	h->size++;

	/* TODO */
	//�� ĭ�� �̷��. 
	int i ; 
	for (i=h->size; i > p ; i-- ){
		memcpy(h->arr + i*h->usize,
		h->arr + (i-1) * h->usize,
		h->usize);
	}
	memcpy(h->arr + p *h->usize, buf, h->usize);
	h->size ++ ;

	return 1 ;
}
