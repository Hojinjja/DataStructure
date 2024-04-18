#include <stdlib.h>
#include "stack.h"

stack_t * 
create_stack (int capacity) 
{
	stack_t * stack = (stack_t *) malloc(sizeof(stack_t)) ; //���� �޸� �Ҵ�
	stack->capacity = capacity ; // ������ ����� �� �ִ� �ִ� ��� ��
	stack->size = 0 ; // ������ ������ �ִ� ����� �� 
	stack->buffer = (int *) calloc(capacity, sizeof(int)) ; // calloc���� capacity ũ���� int�迭�� �Ҵ��ϰ� buffer�� �Ҵ�.
	return stack ; 
}

void
delete_stack (stack_t * stack) 
{
	free(stack->buffer) ; // ���۸� ���� free�ϰ� 
	free(stack) ; // ������ free�Ѵ�
}

int 
push (stack_t * stack, int elem)
{
	if (is_full(stack)) // ���� ������ ��á���� push�� �ȵǹǷ� return 0
		return 0 ;
	
	stack->buffer[stack->size] = elem ; // buffer�� size(top)�� elem�� ����ְ�
	stack->size += 1 ; // size�� �� ĭ Ű���
	return 1 ; // ������� �Ϸ������� push �����̹Ƿ� return 1
}

int
pop (stack_t * stack, int * elem)
{
	if (is_empty(stack)) //������ ����ٸ� stack���� pop�Ұ� �����Ƿ� 
		return 0 ; // 0 ��ȯ
	
	//elem�� �����ͷ� ����Ǿ����Ƿ� *elem
	*elem = stack->buffer[stack->size - 1] ; // elem�� top�� ��ġ�ϴ� �� ������ ��Ҹ� �ְ�
	stack->size -= 1 ; //size�� �� ĭ ���δ�. 
	return 1;
}

int 
top (stack_t * stack, int * elem) //pop ó�� ��Ҹ� �����ϰ� ����� ���̴°� �ƴ϶�, Ȯ�θ�
{
	if (is_empty(stack)) 
		return 0 ;
	
	*elem = stack->buffer[stack->size - 1] ; // ������ top�� ��ġ�ϴ� �� ������ ��Ҹ� ����
	return 1;
}

int 
is_empty (stack_t * stack) 
{
	return (stack->size == 0) ; //����� 0�̶�� empty�̹Ƿ� 1 
}

int 
is_full (stack_t * stack) 
{
	return (stack->size == stack->capacity) ; //����� capacity�� ������ ��á�ٴ� �� 
}

int
get_size (stack_t * stack) 
{
	return stack->size ; // ������ size�� Ȯ��
}

int
get_elem (stack_t * stack, int index, int * elem)
{
	//����ó�� , index�� �����̰ų� ������� ������ return 0
	if (index < 0)
		return 0 ;
	if (stack->size <= index)
		return 0 ;

	//pop�� ���ۿ��� �������°Ű� , get_elem�� stack�� buffer���� index�� ��ġ�� ���� elem ��ġ�� �ִ°�. 
	*elem = stack->buffer[index] ; // buffer�� index�� ��ġ�ϴ� ��Ҹ� elem�� ��ȯ
	return 1 ;
}
