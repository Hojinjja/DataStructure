#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef 
	struct _llist_node_t { //재귀호출을 위해 _list_node_t를 써줌 <중요?>
		char * data ; //데이터를 가르키는 포인터.
		struct _llist_node_t * next ; // 다음 노드를 가르키는 포인터. (중요)포인터 형식을 안잡아주면 사이즈 계산이 안됨.->무한대로 발산함.)
	}
	llist_node_t ;


typedef 
	struct {
		llist_node_t * first ; // 맨 처음 요소 
		int size ; // 링크드 리스트의 사이즈 (현재 들어가 있는 요소의 개수)
	}
	llist_t ;

/*
* 링크드 리스트 생성 및 초기화
*/
llist_t * create_llist () 
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ; // l의 크기는 sizeof(llist_t)로 
	l->first = NULL ; //first는 NULL
	l->size = 0 ; // size는 0으로 초기화 
	return l ; 
}


/*
* 노드 하나 만들어서 링크드 리스트 끝에 추가하기. 
*/
int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ;
	//node 'n' 하나 만들기 (data/next)
	n->data = s ; // data는 s로 
	n->next = NULL ; // next는 NULL로 (다음 요소가 아직 없으므로)
	
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


/*
* 특정 문자의 인덱스를 삭제하기 
*/
char * delete_llist (llist_t * l, char * s) //특정 문자를 지워라 
{
	llist_node_t * i ;
	llist_node_t * prev = NULL; //이전 노드의 next 부분을 떼어내야 하기 때문에 , 이전 노드를 알아야한다.
	//그리고 지우려는 데이터가 있는 노드를 free 해준다. 
	//예외 상황1) prev가 존재하지 않는 경우 -> first가 '지우려는 노드의 next'를 가지게 한다.

	for (i = l->first ; i != NULL ; i = i->next) { //first를 출발해서 i가 null일때까지.. i는 옆으로 계속 넘어감.
		if (strcmp(i->data, s) == 0) { //지우려는 특정 문자와 i 노드의 data와 같은지 확인. 같으면 종료
			break ;			//cf) strcmp에서 (int형식 비교 -> '-' 빼기 )
		} 
		prev=i; // 만약 현재의 노드의 data가 지우려는 문자열 s와 다르다면 현재 검사하고 있는 인덱스 i는 prev로.
	}

	if (i == NULL) // 만약 i가 끝까지 간 경우 (마지막 요소의 next는 NULL)
		return NULL ; // 찾는 문자가 없다는 뜻이므로 NULL 반환 

/* 만약 삭제하려는 문자 s를 찾은 경우*/
	char * r ;
	r= i->data; // r에 i의 데이터를 담고 (찾으려는 문자열)
	if(i== l->first){ // i가 첫번째 요소(first) 였다면 
		l->first = i->next; // first는 i의 next가 된다
	}
	else{ // 삭제하려는 요소의 인덱스가 첫번째 요소가 아니라면 
		prev->next = i->next; //현재 노드 이전 노드 (prev)의 next는 현재 노드(i)의 next로 이어짐. 
	}
	free(i); // 그리고 i번째 노드를 free해줌,

	return r ;
}


void print_llist (llist_t * l) // 링크드 리스트 출력하기
{
	llist_node_t * i ; //노드 i를 선언하고 
	for (i = l->first ; i != NULL ; i = i->next) { // i가 NULL이 될 때 까지 next로 넘김
		printf("%s ", i->data) ; // i가 선언되었다면, i->data를 출력 
	}
	printf("\n") ;
}

void free_llist (llist_t * l) //list 전체의 노드를 다 날리는 것. 
{
	/*TODO*/
	llist_node_t * i ;
	for (i = l->first ; i != NULL ; ) { // 리스트 (l)의 끝까지 순회하며 (NULL까지)
		llist_node_t * current = i; // current 노드를 선언하여 현재 노드 i를 넣어두고 
		i=i->next; // i는 다음 노드로 넘긴다음
		free(current); //  현재 노드는 free 시킨다. 
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
