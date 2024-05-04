#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

//이중 연결 리스트 -> 각 노드가 자신의 "이전" 노드와 "다음" 노드를 가리키는 포인터를 가지고 있는 연결 리스트
dlist_t * // node 구조체 중 하나인 dlist_t
dlist_alloc (int unit) 
{
	dlist_t * l = (dlist_t *) malloc(sizeof(dlist_t)) ; //dlist_t의 크기만큼 malloc()하여 메모리 할당
	l->left = l  ;	 // 노드의 왼쪽은 l
	l->right = l ; // 노드의 오른쪽도 l -> 즉 자신의 오른쪽 왼쪽 다 자기 자신을 가리킴 (현재 노드는 자신 하나 뿐이니까 )
	l->element = malloc(sizeof(int)) ; // 이중 연결 리스트의 각 요소에 저장될 데이터의 크기를 저장하기 위해 메모리를 할당함. ->element에 int크기 만큼 메모리 할당됨.
	int * u = (int *) l->element ; // 포인터 u에 element에 할당한 메모리의 주소를 알려줌. 
	*u = unit ; // 그리고 그 주소에 unit을 집어넣음 (unit은 링크드 리스트에 집어넣을 요소 value)

	return l ;
}

// dlist_free 시키기
void
dlist_free (dlist_t * l)
{
	node_t * curr ; //current 노드
	node_t * next ; //next 노드

	curr = l->right ; // current 노드는 l의 right (l 그 자체는 헤더이니까 안쓰고 l->right가 first 노드임)
	while (curr != l) { // current 노드가 'l'이 아닐 때 동안 (즉 돌고 돌아서 curr이 l이면 한바퀴 돌았다는 뜻)
		next = curr->right ; // next 노드는 현재 노드의 다음 노드 (curr->right) 다음 노드 넘겨놓고
		free(curr->element) ; // 현재 노드의 element (할당한 메모리)를 free
		free(curr) ; // 현재 노드도 free
		curr = next ; // 그리고 아까 넘겨놓은 next 노드를 현재 노드 (curr)로 설정해놓기
	}
	free(l->element) ; // 한 바퀴 다 돌았으면 l의 element free하기 
	free(l) ; // 마지막으로 l도 free 하기 
}


//dlist의 길이 구하기 
int 
dlist_length (dlist_t * l) 
{ 
	int len = 0 ; // 길이를 나타내는 변수 len을 설정

	node_t * curr = l->right ; // curr 노드의 초기값으로 l->right (첫번째 노드)로 하고
	while (curr != l) { // curr 노드가 l이 아닌 동안 (즉 돌고 돌아서 curr이 헤더가 되기 전까지)
		len += 1 ; // len을 1 증가시키고
		curr = curr->right ;  // curr 노드의 위치를 curr의 다음 노드로 옮김
	}
	return len ; 
}

//left와 right 사이에 노드를 추가하는 경우 (left - new - right)
void 
dlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ; // 새로 넣은 노드 _new를 만들고 사이즈는 node_t 크기로 한다. ->링크드 리스트를 만드는건 dlist_t 크기로
	_new->element = malloc(unit) ; // 그리고 _new->element에는 unit크기 만큼 malloc 시켜준다
	memcpy(_new->element, e, unit) ; // e가 가리키는 메모리에서 부터 시작하여 unit 크기만큼의 데이터를 _new->element가 가리키는 메모리 위치로 복사. 
//-> ex) e가 문자열을 나타내는 포인터 , unit이 문자열의 길이라면 memcpy로 _new->element 위치에 e 문자열을 unit 크기만큼 복사한다. 
	node_t * right = left->right ; // right 노드는 left 노드의 right이다.

	_new->left = left ; // 새로운 노드의 left는 left 노드이고 
	_new->right = right ; // 새로운 노드의 right는 right 노드이다.

	left->right = _new ; // left 노드의 right는 새로운 노드가 되고
	right->left = _new ; // right 노드의 left는 새로운 노드가 된다. 
}

// 링크드 리스트의 앞 쪽이 insert 할 경우
void
dlist_insert_first (dlist_t * l, void * e)
{
	dlist_insert(l, e, *((int *)(l->element))) ; // insert 사용 
	// l의 앞 쪽에 e(데이터)를 l->element에 있는 값 만큼 insert한다. 
	// dlist_insert(node_t * left , void * e , int unit) -> left와 right 사이에 집어넣음 (left 뒤에 넣음)
}

//링크드 리스트의 맨 뒤에 insert 할 경우
void 
dlist_insert_last (dlist_t * l, void * e)
{
	dlist_insert(l->left, e, *((int *)(l->element))) ; 
	// l의 left (맨 마지막 노드에), e의 데이터를 , l->element에 있는 값 만큼 insert 한다. 
	// l->left (마지막 노드) 뒤에 넣는다. 
}


//링크드 리스트의 노드 삭제
int
dlist_remove (dlist_t * l, node_t * n)
{
	if (l->left == l) // l의 left가 다시 l이 되는 경우 (노드가 하나도 없는경우)
		return 0 ;

	n->left->right = n->right ; // (삭제하려는 노드 n의 left)의 right를 ,  n의 right로 
	n->right->left = n->left ; // (삭제하려는 노드 n의 right)를 left를 , n의 left로
// -> 지우려는 노드의 왼쪽과 오른쪽을 이어주는 작업

	free(n->element) ; // 다 이어주고 나서 n의 element 먼저 free 해주고
	free(n) ; // n을 free한다. 
	return 1 ;
}

//맨 앞 부분을 삭제 
int 
dlist_remove_first (dlist_t * l, void * e)
{
	if (l->right == l) // 리스트가 비어 있는 경우
		return 0 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ; //e에다가 l의 right의 element를 복사
	dlist_remove(l, l->right) ; // 리스트 (l) 의 l->right( 첫 요소 )를 삭제
	return 0 ;
}

int
dlist_remove_last (dlist_t * l, void * e)
{
	if (l->left == l) 
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ; // e에 마지막 노드(리스트(l)의 left)의 element를 넣고
	dlist_remove(l, l->left) ; // l의 왼쪽 (마지막 노드를 삭제한다.)
	return 1 ;
}

int 
dlist_get (dlist_t * l, int index, void * e)
/* 
 * copies the data at the given index ``index``, if exists, to ``e``, and returns 1.
 * if not exists, return 0.
 */
{
	/* TODO */
	if (index <0 ){
		return 0;
	}
	
	node_t * n ;
	n=l->right ; //첫번째 노드 
	int i = 0;
	for (i=0; i <index ; i++){ // 입력한 인덱스 까지 이동
		n = n->right;
		if (n == l){
			return 0; 
		}
	}

	memcpy(e, n->element, *((int*)l->element)); // e에다가 n번째 인덱스의 element를 집어넣음
	return 1;
}

int 
dlist_remove_at (dlist_t * l, int index)
/*
 * removes the node at the given index ``index``, if exists, and returns 1.
 * if not exists, return 0.
 */
{
	if (index < 0)
		return 0 ;
 
	node_t * n = l->right ; // 노드 n의 초기값은 l->right이고 
	int i = 0 ;  // int i의 초기값은 0

	for (i = 0 ; i < index ; i++) { // i를 인덱스 위치까지 이동시킴,
		n = n->right ;
		if (n == l) {
			return 0 ;
		}
	}

	n->left->right = n->right ; // (n->left)요소의 right = 현재 노드(n)의 right
	n->right->left = n->left ; // (n->right)요소의 left = 현재 노드 (n)의 left
// 이것도 지우려는 노드의 왼쪽과 오른쪽을 이어주는 작업
	free(n->element) ; // n의 element를 free해주고
	free(n) ; // n도 free 해줌
	return 1 ;
}

int 
dlist_append (dlist_t * l1, dlist_t * l2)
/*
 * add all elements in ``l2`` to ``l1``, in their order in ``l2``.
 * return the number of added elements.
 */

{	
	// 링크드 리스트 l2의 모든 요소를 l1 뒤에 추가하는 함수.
	/*TODO*/
	
	node_t * i2; // 노드 i2 선언해주고 

	for(i2 = l2->right; i2 !=l2 ; i2 = i2->right){ // i2노드가 l2->right(l2 노드의 첫번째 요소)에서 부터 , i2는 l2가 아닐 때까지 (즉 l2를 한 바퀴 돌아)
		// dlist_insert_last(l1, i2->element);
		node_t * _new = malloc(sizeof(node_t)); // _new 노드를 생성해주고 메모리 할당. 
		_new->element = malloc(sizeof(*((int*)(l2->element)))) ;  // _new 노드의 element 부분은 l2->element에 있는 사이즈
		memcpy(_new->element, i2->element, *((int*)l2->element) ); // _new 노드의 element에 i2의 element를 집어 넣음. 

		_new->left = l1->left; // new 노드의 left는 , l1 리스트의 마지막 노드와 같음
		_new->right = l1; // new 노드의 right는 l1 헤더를 가리키게 된다. 

		l1->left->right = _new; // l1의 left (l1의 마지막 노드)의 right에 새로운 노드 _new를 넣고
		l1->left = _new; // l1의 left (마지막 노드)도 _new 이다. 

	} ; 
}


