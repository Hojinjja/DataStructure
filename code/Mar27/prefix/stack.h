//정의하는 부분

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int size ;
	} 
	stack_t ; // buffer~size 등을 구조체로 정의해서 stack_t로 부르기로 함

stack_t * 
create_stack (int capacity, int unit) ;// 스택의 크기

void
delete_stack (stack_t * stack) ; // 스택 삭제 

int 
push (stack_t * stack, void * elem) ; // push 

int
pop (stack_t * stack, void * elem) ; // pop

int 
is_empty (stack_t * stack) ; // empty인지 (non_zero, 0)

int 
is_full (stack_t * stack) ; // full인지 (non_zero , 0 )

int
get_size (stack_t * stack) ; // size 구하기

int
get_element (stack_t * stack, int index, void * elem) ; // element 구하기
