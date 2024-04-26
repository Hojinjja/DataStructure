#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef = llist_node_t 
//struct = _llist_nodet_t
typedef 
	struct _llist_node_t { //재귀호출을 위해 _list_node_t를 써줌 <중요?>
		char * data ; //데이터를 가르키는 포인터.
		struct _llist_node_t * next ; // 다음 노드를 가르키는 포인터. (중요)포인터 형식을 안잡아주면 사이즈 계산이 안됨.->무한대로 발산함.)
	}
	llist_node_t ;

typedef 
	struct {
		llist_node_t * first ;
		int size ;
	}
	llist_t ;


llist_t * create_llist () 
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ;
	l->first = NULL ;
	l->size = 0 ;
	return l ; 
}

int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ;
	//node 하나 만들기 (data/next)
	n->data = s ;
	n->next = NULL ;
	
	//첫 노드인 경우 (size==0 or first==0)
	if (l->first == NULL) {
		l->first = n ;
		l->size=1;
		return 1 ;
	}

	/* TODO - 첫 노드가 아닌 경우
	방법 1 -> 순서관계가 중요한 경우.
	.*/
	llist_node_t *last = l->first; // last 노드를 만드는게 아니라(그냥 이름이 last) last의 후보로 먼저 first를 넣어준다.
	while(last->next !=NULL){ // 현재 리스트의 끝을 찾아 (next가 null 일때까지 반복)
		last=last->next; //찾았다면 last는 last->next. 즉 노드를 계속 넘어감. 
	}
	last->next = n; // 노드의 끝을 찾았다면 last의 next는 n 

	/*방법 2 =순서 관계가 중요치 않아 first 앞에 껴버리는경우
	n->next = l->first;
	l->first=n;
	l->size++;
	*/

	return 1 ;
}


char * delete_llist (llist_t * l, char * s) //특정 문자를 지워라 
{
	llist_node_t * i ;
	llist_node_t * prev = NULL; //이전 노드의 next 부분을 떼어내야 하기 때문에 , 이전 노드를 알아야한다.
	//그리고 지우려는 데이터가 있는 노드를 free 해준다. 
	//예외 상황1) prev가 존재하지 않는 경우 -> first가 '지우려는 노드의 next'를 가지게 한다.

	for (i = l->first ; i != NULL ; i = i->next) { //first를 출발해서 i가 null일때까지..
		if (strcmp(i->data, s) == 0) { //지우려는 특정 문자와 i 노드의 data와 같은지 확인. 
			break ;			//cf) strcmp에서 int형식 비교 -> '-' 빼기 
		} 
		prev=i;
	}

	if (i == NULL)
		return NULL ;

/* TODO */
	char * r ;
	r= i->data;
	if(i== l->first){
		l->first = i->next;
	}else{
		prev->next = i->next;
	}
	free(i);

	return r ;
}

void print_llist (llist_t * l)
{
	llist_node_t * i ;
	for (i = l->first ; i != NULL ; i = i->next) {
		printf("%s ", i->data) ;
	}
	printf("\n") ;
}

void free_llist (llist_t * l) //list 전체의 노드를 다 날리는 것. 
{
	/*TODO*/
	llist_node_t * i ;
	for (i = l->first ; i != NULL ; ) {
		llist_node_t * current = i;
		i=i->next;
		free(current);
	}
	free(i);
}

/*****/

int main ()
{
	llist_t * l = create_llist() ;

	insert_llist(l, "BAT") ;
	insert_llist(l, "CAT") ;
	insert_llist(l, "EAT") ;
	insert_llist(l, "FAT") ;
	insert_llist(l, "GAT") ;
	insert_llist(l, "HAT") ;
	insert_llist(l, "VAT") ;
	insert_llist(l, "WAT") ;


	delete_llist(l, "FAT") ;
	delete_llist(l, "VAT") ;

	print_llist(l) ;

	free_llist(l) ;

	return EXIT_SUCCESS ;
}
