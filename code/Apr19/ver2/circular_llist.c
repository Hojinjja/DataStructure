#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct _llist_node_t {
		char * data ; // data
		struct _llist_node_t * next ; // 다음 노드를 가리키는 next 
	}
	llist_node_t ; // 노드 구조체

typedef 
	struct {
		llist_node_t * last ;  // 연결 리스트의 마지막 노드를 가리키는 노드 
	}
	llist_t ; // 링크드 리스트 구조체 (last 노드를 가리키게 만듦)

/*
* 링크드 리스트 만들기 
*/
llist_t * create_llist ()
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ; // llist_t 크기로 메모리 할당 
	l->last = NULL ; // last의 초기값은 NULL
	return l ; 
}

int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ; // 노드 'n' 만들기
	n->data = s ; //노드의 data 값은 s
	n->next = NULL ; // 노드의 next는 NULL
	
	if (l->last == NULL) { //만약 l->last가 NULL 이면 -> 첫번째 노드라면 
		l->last = n ; // l의 last는 'n'이 된다. -> 링크드 리스트의 마지막 노드(last) = n
		n->next = n ; // n의 next도 'n'이 된다. -> n의 next도 n -> 노드가 자기 하나 이므로 다음 노드 (next)도 자기 자신
		return 1 ;
	}

	// 만약 last가 NULL이 아니라면 -> 즉 링크드 리스트에 요소가 여러개 있다면, 
	llist_node_t * last; // last를 지정해주고 
	n->next = last->next ; // 방금 만든 노드 n의 다음 노드는(n->next) 기존의 마지막 노드 last의 next가 된다. 
	last->next = n ; // 그리고 기존의 last의 next는 새로 추가된 노드 n이 된다. 
	last = n ; // 이제 모든걸 설정 해줬으므로 새로운 last는 n이 된다. 

	return 1 ;
}

/*
* 특정 문자열 s를 l리스트 에서 삭제하기 
*/
char * delete_llist (llist_t * l, char * s) 
{
	llist_node_t * i ; // 노드 i 
	llist_node_t * prev ;  // 현재 노드의 이전 노드 prev 

	if (l->last == NULL) // last도 NULL 인 경우, 즉 리스트가 비어있는 경우. 
		return NULL ;

	int found = 0 ; // 찾았냐 못찾았냐 상태를 나타내는 변수 found 
	prev = l->last ; // prev(이전) 노드는 리스트(l)의 마지막 노드 (last)
	i = l->last->next ; // i는 리스트 (l)의 마지막 노드(last)의 다음 (next)노드 
	do {
		if (strcmp(i->data, s) == 0) { // 찾는 문자열이 있으면
			found = 1 ; // found를 1로 설정하고 break
			break ;
		}
		prev = i ; // prev (이전)노드는 i로 설정. 
		i = i->next ; // i는 i->next로
	} while (i != l->last->next) ; // i가 리스트 (l)의 last->next가 아닐 때 까지 (last->next = 첫번째 노드)

	if (found == 0) // 만약 found가 0인 채로 끝났으면 지우려는 문자열을 못찾았다는 뜻. 
		return NULL ;

	char * r ;
	r = i->data ; // r에 i번째 인덱스의 data를 담고 

	if (i == l->last) { //마지막 노드를 삭제한 경우 
		if (l->last == l->last->next) { // l->last랑 l->last->next 랑 같은 경우 (즉 하나 남은 경우 ) -> 그 중에서도 하나 남은 노드를 삭제한 경우. 
			l->last = NULL ; // 하나 남은 걸 삭제했으므로 리스트(l)의 last는 NULL -> 노드가 하나도 없음.  
		}
		else { // 마지막 노드를 삭제했지만 하나 남은 상황은 아닌 경우
			prev->next = l->last->next ; // 이전 노드 (prev)의 next는 리스트의 첫 번 째 노드
			l->last = prev ; // 그리고 last요소는 현재 삭제한 노드의 이전 노드 (prev)가 된다. 
		}
	}
	else { // 마지막 노드를 삭제하지 않은 경우. 
		prev->next = i->next ; // prev의 next (이전 노드의 next = 현재 노드의 next) - > 현재 노드가 삭제되니까 이전이랑(prev)랑 현재 노드의 next랑 이어줌. 
	}
	free(i) ; // 설정 다 해줬으니까 i는 free 시킨다.  ==> i->data를 NULL 로 따로 설정할 필요 없음. free(i)로 해결

	return r ;
}

void print_llist (llist_t * l) // 아직 안끝남.
{
	if (l->last == NULL)
		return ;

	llist_node_t * i = l->last->next;  // i의 초기값을 리스트의 last->next( 즉 처음 노드 )로 설정해놓고 
	do {
		printf("%s",i->data);
		i=i->next;
	}while (i != l->last->next);
	printf("\n") ;
}

void free_llist (llist_t * l)
{
	/*TODO < 아직*/
	llist_node_t * i ;
	for (i = l->last->next ; i != NULL ; ) {
		llist_node_t * current = i;
		i=i->next;
		free(current);
	}
	free(i);
}


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
