#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	heap_t * h = malloc(sizeof(heap_t)) ;
	h->arr = calloc(capacity + 1, usize) ; 
	//capacity +1을 해준다 (힙에서는 0번 주소 사용 x = 부모-자식 관계 찾기 쉽게 하기 위해)
	h->capacity = capacity ;
	h->size = 0 ;
	h->usize = usize ;
	h->cmp = cmp ;
	return h ;
}

void
heap_free (heap_t * h) 
{
	free(h->arr) ;
	free(h) ;
}

int
heap_size (heap_t * h)
{
	return h->size ;
}

int
parent (int i) 
{ 
	return i / 2 ;
}

int
left (int i) 
{ 
	return i * 2 ; //i번째 left 노드는 i*2에 존재.
}

int
right (int i) 
{ 
	return i * 2 + 1 ; 
}

void *
arr (heap_t * h, int i) 
{
	return h->arr + h->usize * i ;
}

void
swap (heap_t * h, int a, int b) // index a와 b를 교환 
{
	char * tmp = (char *) malloc(h->usize) ;
	memcpy(tmp, arr(h,a), h->usize) ;
	memcpy(arr(h,a), arr(h,b), h->usize) ;
	memcpy(arr(h,b), tmp, h->usize) ;
	free(tmp) ;
}

int
cmp (heap_t * h, int a, int b) //compare 하는 코드 
{
	return h->cmp(h->arr + a * h->usize, h->arr + b * h->usize) ;
}

int
heap_top (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 0 ;
	memcpy(buf, arr(h, 1), h->usize) ; // 1번 위치를 memcpy
	return 1 ;
}

int
heap_pop (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 0 ;

	/*TODO*///root날라가고 맨 마지막 요소를 root에 집어넣고 복사해서 가져옴
	memcpy(buf,arr(h,1),h->usize); //일단 root 복사
	swap(h,1,h->size); //마지막 요소 root로 올리고 
	h->size -- ; 

//중요 부분. 
	int i=1; 
	while((left(i)<=h->size && cmp (h,i,right(i))>0) ||
			right(i)<=h->size && cmp(h,i,right(i))>0) {

			int r = left(i);
			if(right(i)<= h->size && cmp(h,left(i),right(i))<0){
				r=right(i);
			}
		}


	
	

	return 1 ;
}

int
heap_push (heap_t * h, void * buf) //인덱스 1번부터 쓰고 있다는 것을 유념
{
	if (h->size == h->capacity) 
		return 0 ;

	h->size += 1 ;
	memcpy(arr(h, h->size), buf, h->usize) ;

	int i;
	for(i=h->size; i>0; i=parent(i)){
		if(cmp(h,parent(i),i)<0){
			break;
		}
		else{
			swap(h,parent(i),i);
		}
	}

	// for (int i = h->size ; parent(i) > 0 ; ) {
	// 	if (cmp(h, parent(i), i) < 0) {
	// 		swap(h, parent(i), i) ;
	// 		i = parent(i) ;
	// 	}
	// 	else {
	// 		break ;
	// 	}
	// }
	return 1 ;
}


//segmentation fault 잡는 법 -> gcc -g -fsanitize=adress *.c 