#include <stdlib.h>
#include <string.h>
#include "queue.h"

gqueue_t * 
create_queue (int capacity, int unit) 
{
	gqueue_t * queue = (gqueue_t *) malloc(sizeof(gqueue_t)) ;
    queue->unit = unit; //ť�� ����� ����� ũ�� 
	queue->front = 0; // ť�� �� �� �ε��� 
    queue->rear = 0; // ť�� �� �� �ε���
	queue->capacity = capacity ; // ť�� ������ �� �ִ� �ִ� ����� ��.
	queue->size = 0 ; // ť�� �� �ִ� ����� �� 
	queue->buffer =  calloc(capacity, unit) ; // ���� ��Ҹ� �����ϴµ� ���Ǵ� �޸� ���� 
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

	// buffer+ (rear(�ε���)*unit) -> ���ο� ��Ҹ� ������� ���� �ּ� ��� 
	// buffer ������ + (rear���� * unit�� ũ�⸸ŭ)
	// elem�� ��ġ���� unit ũ�� ��ŭ (�̶� elem�� ������ �̸� elem , �����Ͱ� �ƴϸ� &elem)
	memcpy((queue->buffer)+(queue->rear)*(queue->unit), elem, queue->unit); //word ������ ����
    
	//ť�� �������� ������ �� �ֵ���, rear+1�� rear ��ġ�� �ϳ� �ڷ� �ű�� ���� �ִ� �뷮 �̻��� ��� �ٽ� 0���� ������.
	queue->rear = (queue->rear +1) % queue->capacity;
    queue->size +=1;
	return 1 ;
}

int
dequeue (gqueue_t * queue, void * elem)
{
	if (is_empty(queue)) 
		return 0 ;
	
	//elem�� buffer+(front*unit)�� ��ġ���� unit��ŭ ���� -> elem�� dequeue�� �� ����
	memcpy(elem, (queue->buffer) + (queue->front)*(queue->unit), queue->unit);
	
	//front�� ��ġ�� 1ĭ �ڷ� �ű�, ���� ť ������ ���� %capacity �ؼ� capacity ũ�� �̻��̸� �ٽ� �ε��� 0����
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

	//elem�� front �� ����. (buffer+(front*unit))�� ��ġ���� unitũ�� ��ŭ �޸� ����
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
	//queue�� size(ť�� �� ���� ��)�� capacity(ť�� �� �� �ִ� ���� �ִ� ��)�� ������ 1
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

	//index= front�� index�� i��ŭ ���ؼ� % capacity�ϸ� -> ���� ť������ �ε����� ���� 
	int index = (queue->front +i) % queue->capacity;

	//elem�� ������ index�� ����ִ� ���� ����
	memcpy(elem, queue->buffer+queue->front*index+queue->unit, queue->unit);
	return 1 ;
}