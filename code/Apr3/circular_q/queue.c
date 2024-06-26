#include <stdlib.h>
#include <string.h>
#include "queue.h"

gqueue_t * 
create_queue (int capacity, int unit) 
{
	gqueue_t * queue = (gqueue_t *) malloc(sizeof(gqueue_t)) ;
    queue->unit = unit; // 들어오는 타입 
	queue->front = 0; 
    queue->rear = 0; // 들어오는 곳 
	queue->capacity = capacity ; // 최대 용량
	queue->size = 0 ; // 현재 들어온 크기 
	queue->buffer =  calloc(capacity, unit) ;
	return queue ; 
}

void
delete_queue (gqueue_t * queue) 
{
	if (queue->buffer) {
		free(queue->buffer) ;
	}
	free(queue) ;
}

int 
enqueue (gqueue_t * queue, void * elem)
{
	if (is_full(queue)) // 큐가 full 이면 enqueue 불가
		return 0 ;

	memcpy((queue->buffer)+((queue->rear)*(queue->unit)), elem, queue->unit); //word 단위로 복사
    queue->rear = (queue->rear +1) % queue->capacity; // circular queue를 구현하기 위한 모듈러 연산으로 인덱스.
    queue->size +=1;
	return 1 ;
}

int
dequeue (gqueue_t * queue, void * elem)
{
	if (is_empty(queue)) 
		return 0 ;
	
	memcpy(elem, (queue->buffer) + ((queue->front)*(queue->unit)), queue->unit);
	queue->front = (queue->front +1) % queue->capacity; // circular queue를 위한 모듈러 연산으로의 front
	
	queue->size -= 1 ;
	return 1;
}



int 
front (gqueue_t * queue, void * elem)
{
	if (is_empty(queue)) {
		return 0 ;
    }
	memcpy(elem, (queue->buffer) + ((queue->front) * (queue->unit)), queue->unit); // ?? 
	return 1;
}




int 
is_empty (gqueue_t * queue) 
{
	return (queue->size == 0) ;
}

int 
is_full (gqueue_t * queue) 
{
	return (queue->size == queue->capacity) ;
}

int
get_size (gqueue_t * queue) 
{
	return queue->size ;
}

int
get_elem (gqueue_t * queue, int i, void * elem)
{
	if (queue->front < 0)
		return 0 ;
	if (queue->size <= i)
		return 0 ;

	int index = (queue->front +i) & queue->capacity;
	memcpy(elem, (queue->buffer)+queue->front * index + queue->unit, queue->unit); // ??
	return 1 ;
}