#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

heap_t *
heap_create (int capacity, size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	heap_t * h = malloc(sizeof(heap_t)) ;
	h->arr = calloc(capacity + 1, usize) ;
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
	return i * 2 ; 
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
swap (heap_t * h, int a, int b)
{
	char * tmp = (char *) malloc(h->usize) ;
	memcpy(tmp, arr(h, a), h->usize) ;
	memcpy(arr(h, a), arr(h, b), h->usize) ;
	memcpy(arr(h, b), tmp, h->usize) ;
	free(tmp) ;
}

int
cmp (heap_t * h, int a, int b)
{
	return h->cmp(h->arr + a * h->usize, h->arr + b * h->usize) ;
}


int
heap_top (heap_t * h, void * buf)
{
	if (h->size == 0)
		return 0 ;
	memcpy(buf, arr(h, 1), h->usize) ;
	return 1 ;
}


int
heap_pop (heap_t * h, void * buf)
{
	/* FIXME: fix this function for Task 1 */

	if (h->size == 0)
		return 0 ;

	memcpy(buf, arr(h, 1), h->usize) ;

	swap(h, 1, h->size) ;
	h->size-- ;

	int i = 1 ;
	while ((left(i) <= h->size && cmp(h, i, left(i)) > 0) || 
		right(i) <= h->size && cmp(h, i, right(i)) > 0) {

		int r = i ;
		if (left(i) <= h->size && cmp(h, r, left(i)) > 0) {
			r = left(i) ;
		}
		if (right(i) <= h->size && cmp(h, r, right(i)) > 0) {
			r = right(i) ;
		}

		swap(h, i, r) ;

		i = r ;
	}
	// ������ �� ���� --�߰�  
    if (h->size > 0 && h->size < h->capacity / 4) {
        h->capacity /= 2;
        h->arr = realloc(h->arr, (h->capacity + 1) * h->usize);
    }

	return 1 ;
}

int
heap_push (heap_t * h, void * buf) 
{
	/* FIXME: fix this function for Task 1 */

	//������ ������
	if (h->size == h->capacity) {
        // ������ �� ���� . 
        h->capacity *= 2;
        h->arr = realloc(h->arr, (h->capacity + 1) * h->usize);
    }

	h->size += 1 ;
	memcpy(arr(h, h->size), buf, h->usize) ;

	int i ;
	for (i = h->size ; i > 1 ; i = parent(i)) {
		if (cmp(h, parent(i), i) < 0) {
			break ;
		}
		else {
			swap(h, parent(i), i) ;
		}
	}

	return 1 ;
}

int 
heap_remove (heap_t * h, void * buf)
{
	int i;
	// ���� element�� ���ٸ� ����
    if (i > h->size) {
        return 0;
    }

    // ������ element�� index ã�� 
    for (i = 1; i <= h->size; i++) {
        if (h->cmp(arr(h, i), buf) == 0) {
            break;
        }
    }

    // ������ element�� ������ element�� ��ġ �ٲٰ�, ������ ���̱� 
	swap(h, i, h->size);
    h->size--;

    // min_heap���� �ٽ� ����� 
    while ((left(i) <= h->size && cmp(h, i, left(i)) > 0) || 
           (right(i) <= h->size && cmp(h, i, right(i)) > 0)) {

        int r = left(i);
        if (right(i) <= h->size && cmp(h, left(i), right(i)) < 0) {
            r = right(i);
        }

        swap(h, i, r);
        i = r;
    }

    return 1;
}

//task 1,2 ��

	

