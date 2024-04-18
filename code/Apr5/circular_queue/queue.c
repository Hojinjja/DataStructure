#include <stdlib.h>
#include <string.h>
#include "queue.h"

gqueue_t * 
create_queue (int capacity, int unit) 
{
	gqueue_t * queue = (gqueue_t *) malloc(sizeof(gqueue_t)) ;
    queue->unit = unit; //큐에 저장될 요소의 크기 
	queue->front = 0; // 큐의 맨 앞 인덱스 
    queue->rear = 0; // 큐의 맨 뒤 인덱스
	queue->capacity = capacity ; // 큐가 저장할 수 있는 최대 요소의 수.
	queue->size = 0 ; // 큐에 들어가 있는 요소의 수 
	queue->buffer =  calloc(capacity, unit) ; // 실제 요소를 저장하는데 사용되는 메모리 영역 
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
	if (is_full(queue))
		return 0 ;

	// buffer+ (rear(인덱스)*unit) -> 새로운 요소를 집어넣을 시작 주소 계산 
	// buffer 시작점 + (rear까지 * unit의 크기만큼)
	// elem의 위치에서 unit 크기 만큼 (이때 elem이 포인터 이면 elem , 포인터가 아니면 &elem)
	memcpy((queue->buffer)+(queue->rear)*(queue->unit), elem, queue->unit); //word 단위로 복사
    
	//큐가 원형으로 유지될 수 있도록, rear+1로 rear 위치를 하나 뒤로 옮기고 만약 최대 용량 이상인 경우 다시 0으로 오도록.
	queue->rear = (queue->rear +1) % queue->capacity;
    queue->size +=1;
	return 1 ;
}

int
dequeue (gqueue_t * queue, void * elem)
{
	if (is_empty(queue)) 
		return 0 ;
	
	//elem에 buffer+(front*unit)의 위치에서 unit만큼 복사 -> elem에 dequeue된 값 저장
	memcpy(elem, (queue->buffer) + (queue->front)*(queue->unit), queue->unit);
	
	//front의 위치를 1칸 뒤로 옮김, 원형 큐 유지를 위해 %capacity 해서 capacity 크기 이상이면 다시 인덱스 0부터
	queue->front = (queue->front +1) % queue->capacity;
	
	queue->size -= 1 ;
	return 1;
}

int 
front (gqueue_t * queue, void * elem)
{
	if (is_empty(queue)) {
		return 0 ;
    }

	//elem에 front 값 담음. (buffer+(front*unit))의 위치에서 unit크기 만큼 메모리 복사
	memcpy(elem, queue->buffer + queue->front * queue->unit, queue->unit);
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
	//queue의 size(큐에 들어간 값의 수)와 capacity(큐에 들어갈 수 있는 값의 최대 수)가 같으면 1
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

	//index= front의 index에 i만큼 더해서 % capacity하면 -> 원형 큐에서의 인덱스가 나옴 
	int index = (queue->front +i) % queue->capacity;

	//elem에 지정한 index에 들어있는 값을 복사
	memcpy(elem, queue->buffer+queue->front*index+queue->unit, queue->unit);
	return 1 ;
}