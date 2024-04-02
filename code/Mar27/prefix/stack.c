#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack_t * 
create_stack (int capacity, int unit) 
{
	stack_t * st = malloc(sizeof(stack_t)) ; // stact_t만큼 malloc하기
	st->capacity = capacity ; // 파라미터로 넘어온 capcity를 st.capacity 값으로
	st->unit = unit ; // 파라미터로 넘어온 unit을 st.unit 값으로
	st->size = 0 ; // size 값으로 0을 초기값으로 한다. -> size을 size로 다 바꾸자
	st->buffer = calloc(capacity, unit) ; // calloc으로 capacity*unit 만큼의 크기만큼 연속된 메모리 블록 할당. 
	return st ;
}

//malloc, calloc 둘 다 메모리를 동적으로 할당
//malloc은 단일 인자, 할당된 메모리 초기화 x
//calloc은 두개의 인자 (메모리 개수*요소의 크기), 할당된 메모리 0으로 초기화  ->malloc하고 memset한 것과 같음 

void
delete_stack (stack_t * st) 
{
	if (st->buffer != 0x0) //만약 buffer가 null이 아니면 buffer를 free한다. 
		free(st->buffer) ;
	free(st) ; // 만약 버퍼가 null이면 free 
	//buffer를 먼저 free하고 stack을 free한다. 
}

int 
push (stack_t * st, void * elem) //void(타입이 없는) 포인터를 받는다 -> 받는 대상의 타입이 안 주어짐. 
{								 //그래서 여기서는 unit 정보를 활용한다. 
	if (is_full(st)) // 만약 스택이 가득 찼다면 return 0
		return 0 ;
	//else
	memcpy(st->buffer + ((st->size) * (st->unit)), elem, st->unit) ; // ---> 좀 더 볼것 
	//memcpy = 메모리 복사  memcpy(붙여넣기할 주소, 복사할 데이터 주소, 복사할 데이터 크기)
	//elem이 가리키는 메모리를 
	//st->buffer에 현재 스택의 size 위치에 있는 위치로부터 st->unit 크기만큼 복사합니다.
	st->size += 1 ; // 그리고 size의 위치를 1 올린다.  
	return 1 ;
}

int
pop (stack_t * st, void * elem)
{
	if (is_empty(st)) // 만약 스택이 비었다면 return 0
		return 0 ;
	
	memcpy(elem, st->buffer + (st->size - 1) * st->unit, st->unit) ;
	// elem에 , st->buffer+(st->size-1)에 있는 대상을, st->unit만큼 복사
	// 즉 st의 buffer의 맨 위에 있는 값을 elem에 복사
	st->size -= 1 ; // size값 -1 
	return 1 ;
}

int 
is_empty (stack_t * st) 
{
	return (st->size == 0) ; // 만약 size 값이 0이라면 return 0 
}

int 
is_full (stack_t * st) 
{
	return (st->size == st->capacity) ; // 만약 size 값이 capacity(용량) 값과 같은지 확인 
	//만약 같다면 꽉찼다는 뜻 1 반환, 아니면 0 반환
}

int
get_size (stack_t * st) 
{
	return st->size ; // size값을 반환 
}

int
get_element (stack_t * st, int index, void * elem) 
{
	if (st->size <= index) //파라미터로 들어온 index의 값이 size 값 보다 더 크면 
		return 0 ; // return 0

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	//elem에 st->buffer + index * st->unit에 있는 값을, st->unit만큼 복사
	return 1 ; // 그리고 return 1
}
