#include <stdlib.h>
#include "stack.h"

stack_t * 
create_stack (int capacity) 
{
	stack_t * stack = (stack_t *) malloc(sizeof(stack_t)) ; //스택 메모리 할당
	stack->capacity = capacity ; // 스택이 허용할 수 있는 최대 요소 수
	stack->size = 0 ; // 스택이 가지고 있는 요소의 수 
	stack->buffer = (int *) calloc(capacity, sizeof(int)) ; // calloc으로 capacity 크기의 int배열을 할당하고 buffer에 할당.
	return stack ; 
}

void
delete_stack (stack_t * stack) 
{
	free(stack->buffer) ; // 버퍼를 먼저 free하고 
	free(stack) ; // 스택을 free한다
}

int 
push (stack_t * stack, int elem)
{
	if (is_full(stack)) // 만약 스택이 꽉찼으면 push가 안되므로 return 0
		return 0 ;
	
	stack->buffer[stack->size] = elem ; // buffer의 size(top)에 elem을 집어넣고
	stack->size += 1 ; // size를 한 칸 키운다
	return 1 ; // 여기까지 완료했으면 push 성공이므로 return 1
}

int
pop (stack_t * stack, int * elem)
{
	if (is_empty(stack)) //스택이 비었다면 stack에서 pop할게 없으므로 
		return 0 ; // 0 반환
	
	//elem이 포인터로 선언되었으므로 *elem
	*elem = stack->buffer[stack->size - 1] ; // elem에 top에 위치하는 맨 마지막 요소를 넣고
	stack->size -= 1 ; //size를 한 칸 줄인다. 
	return 1;
}

int 
top (stack_t * stack, int * elem) //pop 처럼 요소를 추출하고 사이즈를 줄이는게 아니라, 확인만
{
	if (is_empty(stack)) 
		return 0 ;
	
	*elem = stack->buffer[stack->size - 1] ; // 스택의 top에 위치하는 맨 마지막 요소를 넣음
	return 1;
}

int 
is_empty (stack_t * stack) 
{
	return (stack->size == 0) ; //사이즈가 0이라면 empty이므로 1 
}

int 
is_full (stack_t * stack) 
{
	return (stack->size == stack->capacity) ; //사이즈가 capacity와 같으면 꽉찼다는 뜻 
}

int
get_size (stack_t * stack) 
{
	return stack->size ; // 현재의 size를 확인
}

int
get_elem (stack_t * stack, int index, int * elem)
{
	//예외처리 , index가 음수이거나 사이즈보다 작으면 return 0
	if (index < 0)
		return 0 ;
	if (stack->size <= index)
		return 0 ;

	//pop은 버퍼에서 빼버리는거고 , get_elem은 stack의 buffer에서 index에 위치한 값을 elem 위치에 넣는것. 
	*elem = stack->buffer[index] ; // buffer의 index에 위치하는 요소를 elem에 반환
	return 1 ;
}
