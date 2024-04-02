#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack_t * 
create_stack (int capacity, int unit) 
{
	stack_t * st = malloc(sizeof(stack_t)) ; // stact_t��ŭ malloc�ϱ�
	st->capacity = capacity ; // �Ķ���ͷ� �Ѿ�� capcity�� st.capacity ������
	st->unit = unit ; // �Ķ���ͷ� �Ѿ�� unit�� st.unit ������
	st->size = 0 ; // size ������ 0�� �ʱⰪ���� �Ѵ�. -> size�� size�� �� �ٲ���
	st->buffer = calloc(capacity, unit) ; // calloc���� capacity*unit ��ŭ�� ũ�⸸ŭ ���ӵ� �޸� ��� �Ҵ�. 
	return st ;
}

//malloc, calloc �� �� �޸𸮸� �������� �Ҵ�
//malloc�� ���� ����, �Ҵ�� �޸� �ʱ�ȭ x
//calloc�� �ΰ��� ���� (�޸� ����*����� ũ��), �Ҵ�� �޸� 0���� �ʱ�ȭ  ->malloc�ϰ� memset�� �Ͱ� ���� 

void
delete_stack (stack_t * st) 
{
	if (st->buffer != 0x0) //���� buffer�� null�� �ƴϸ� buffer�� free�Ѵ�. 
		free(st->buffer) ;
	free(st) ; // ���� ���۰� null�̸� free 
	//buffer�� ���� free�ϰ� stack�� free�Ѵ�. 
}

int 
push (stack_t * st, void * elem) //void(Ÿ���� ����) �����͸� �޴´� -> �޴� ����� Ÿ���� �� �־���. 
{								 //�׷��� ���⼭�� unit ������ Ȱ���Ѵ�. 
	if (is_full(st)) // ���� ������ ���� á�ٸ� return 0
		return 0 ;
	//else
	memcpy(st->buffer + ((st->size) * (st->unit)), elem, st->unit) ; // ---> �� �� ���� 
	//memcpy = �޸� ����  memcpy(�ٿ��ֱ��� �ּ�, ������ ������ �ּ�, ������ ������ ũ��)
	//elem�� ����Ű�� �޸𸮸� 
	//st->buffer�� ���� ������ size ��ġ�� �ִ� ��ġ�κ��� st->unit ũ�⸸ŭ �����մϴ�.
	st->size += 1 ; // �׸��� size�� ��ġ�� 1 �ø���.  
	return 1 ;
}

int
pop (stack_t * st, void * elem)
{
	if (is_empty(st)) // ���� ������ ����ٸ� return 0
		return 0 ;
	
	memcpy(elem, st->buffer + (st->size - 1) * st->unit, st->unit) ;
	// elem�� , st->buffer+(st->size-1)�� �ִ� �����, st->unit��ŭ ����
	// �� st�� buffer�� �� ���� �ִ� ���� elem�� ����
	st->size -= 1 ; // size�� -1 
	return 1 ;
}

int 
is_empty (stack_t * st) 
{
	return (st->size == 0) ; // ���� size ���� 0�̶�� return 0 
}

int 
is_full (stack_t * st) 
{
	return (st->size == st->capacity) ; // ���� size ���� capacity(�뷮) ���� ������ Ȯ�� 
	//���� ���ٸ� ��á�ٴ� �� 1 ��ȯ, �ƴϸ� 0 ��ȯ
}

int
get_size (stack_t * st) 
{
	return st->size ; // size���� ��ȯ 
}

int
get_element (stack_t * st, int index, void * elem) 
{
	if (st->size <= index) //�Ķ���ͷ� ���� index�� ���� size �� ���� �� ũ�� 
		return 0 ; // return 0

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	//elem�� st->buffer + index * st->unit�� �ִ� ����, st->unit��ŭ ����
	return 1 ; // �׸��� return 1
}
