//�����ϴ� �κ�

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int size ;
	} 
	stack_t ; // buffer~size ���� ����ü�� �����ؼ� stack_t�� �θ���� ��

stack_t * 
create_stack (int capacity, int unit) ;// ������ ũ��

void
delete_stack (stack_t * stack) ; // ���� ���� 

int 
push (stack_t * stack, void * elem) ; // push 

int
pop (stack_t * stack, void * elem) ; // pop

int 
is_empty (stack_t * stack) ; // empty���� (non_zero, 0)

int 
is_full (stack_t * stack) ; // full���� (non_zero , 0 )

int
get_size (stack_t * stack) ; // size ���ϱ�

int
get_element (stack_t * stack, int index, void * elem) ; // element ���ϱ�
