#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

//array list의 변형 

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
slist_top (slist_t * h, void * buf) //0번째 element 우선순위 1위.
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
		memcpy(h->arr + p*h->size,	//2번 인자에서 1번 인자로 옮김
			  	h->arr+(p+1)*h->size,
				h->usize);
	}
	h->size = h->size-1;
	return 1 ;
}

int
slist_push (slist_t * h, void * buf) //순서 관계를 맞춰야함. 
{
	if (h->size == h->capacity) 
		return 0 ;

	
	int p = 0 ; // 새로운 element가 들어갈 위치 
	for (p = 0 ; p < h->size ; p++) {
		if (0 < h->cmp(h->arr + p * h->usize, buf)) { //compare은 기본적으로 뺄셈. 
		//h->arr + p * h->usize 이것과 buf 비교 
			break ;
		}
	}

	memcpy(h->arr + p*h->usize, buf, h->usize);
	h->size++;

	/* TODO */
	//한 칸씩 미룬다. 
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
