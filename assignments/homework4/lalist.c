#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lalist.h"

lalist_t * 
lalist_alloc (int arr_cap, int elem_size) 
{
	lalist_t * l = malloc(sizeof(lalist_t)) ;
	l->arr_cap = arr_cap ;
	l->elem_size = elem_size ;
	l->first = NULL;
	/*
	l->first = malloc(sizeof(lalist_node_t)) ;
	l->first->arr = calloc(elem_size, arr_cap) ;
	l->first->n_elem = 0 ;
	l->first->next = NULL ;
	*/
	return l ;
}

void
lalist_free (lalist_t * l)
{
	/* TODO */
}

int 
lalist_length (lalist_t * l)
{
	int n = 0 ;
	lalist_node_t * i ;
	for (i = l->first ; i != NULL ; i = i->next) {
		n += i->n_elem ;
	}
	return n ;
}

void
lalist_insert_first (lalist_t * l, void * e)
{
	 // 첫 번째 노드 검사
    if (l->first == NULL || l->first->n_elem == l->arr_cap) { // 만약 첫번째 노드가 비어있거나, 꽉 찬 경우
        // 새 노드 생성 및 초기화
        lalist_node_t *_new_node = malloc(sizeof(lalist_node_t));
        _new_node->arr = calloc(l->elem_size, l->arr_cap);
        _new_node->n_elem = 0;
        _new_node->next = l->first;
        l->first = _new_node;
    }

    // 배열 내 요소들을 오른쪽으로 이동
    for (int i = l->first->n_elem; i > 0; i--) {
        memcpy((char *)l->first->arr + i * l->elem_size, 
               (char *)l->first->arr + (i - 1) * l->elem_size, 
               l->elem_size);
    }

    // 새 요소 삽입
    memcpy(l->first->arr, e, l->elem_size);

    // 요소 수 갱신
    l->first->n_elem++;
}

void lalist_insert_last(lalist_t * l, void * e) {
    lalist_node_t *current = l->first;
    lalist_node_t *last = NULL;

    // 리스트의 마지막 노드 찾기
    while (current != NULL) {
        last = current;
        current = current->next;
    }

    // 마지막 노드가 NULL이면 새 노드를 첫 노드로 추가
    if (last == NULL) {
        l->first = malloc(sizeof(lalist_node_t));
        l->first->arr = calloc(l->elem_size, l->arr_cap);
        l->first->n_elem = 0;
        l->first->next = NULL;
        last = l->first;
    } else if (last->n_elem == l->arr_cap) {
        // 마지막 노드의 배열이 가득 찼다면 새 노드 추가
        last->next = malloc(sizeof(lalist_node_t));
        last->next->arr = calloc(l->elem_size, l->arr_cap);
        last->next->n_elem = 0;
        last->next->next = NULL;
        last = last->next;
    }

    // 새 요소를 마지막 노드의 배열에 추가
    memcpy((char *)last->arr + last->n_elem * l->elem_size, e, l->elem_size);

    // 요소 수 갱신
    last->n_elem++;
}

int
lalist_insert_at (lalist_t * l, int index, void * e)
{
	if (index < 0 || index > lalist_length(l)) {  // 적절한 인덱스인지 검사. 
        return -1;
    }

    int count = 0; // 현재까지의 카운트한 요소 수 (현재 인덱스)
    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

	// 이미 모든 노드가 꽉 찬 경우.
   if (current->n_elem == l->arr_cap) {
    lalist_node_t *new_node = malloc(sizeof(lalist_node_t));  // 새 노드 생성
    new_node->arr = calloc(l->elem_size, l->arr_cap);        // 새 배열 할당
    new_node->n_elem = 0;                                    // 초기 요소 수는 0
    new_node->next = current->next;                          // 새 노드를 현재 노드 뒤에 연결
    current->next = new_node;                                // 현재 노드의 다음 노드를 새 노드로 설정
    current = new_node;                                      // 삽입할 노드를 새 노드로 변경
	}

    // 적절한 노드 찾기 ->index에 알맞는 노드 찾기 (current가 NULL이거나, index의 위치가 있는 노드에 도착하면 반복 끝)
    while (current != NULL && count + current->n_elem <= index) {
        count += current->n_elem;
        previous = current;
        current = current->next;
    }

	// 노드를 찾아서 끝까지 갔는데, 노드가 꽉찬 경우.
    if (current == NULL) {  // 새 노드가 필요한 경우 -리스트가 완전 빈 경우, 맨 마지막에 넣는데 마지막 노드가 꽉 찬 경우
        current = malloc(sizeof(lalist_node_t));
        current->arr = calloc(l->elem_size, l->arr_cap);
        current->n_elem = 0;
        current->next = NULL;
        //
		if (previous != NULL) {
            previous->next = current;
        } else { // 아예 빈 경우 
            l->first = current;
        }
    }

	

    // 배열 내 요소들을 오른쪽으로 이동
    for (int i = current->n_elem; i > index - count; i--) {
        memcpy((char *)current->arr + i * l->elem_size, 
               (char *)current->arr + (i - 1) * l->elem_size, 
               l->elem_size);
    }

    // 새 요소 삽입
    memcpy((char *)current->arr + (index - count) * l->elem_size, e, l->elem_size);

    // 요소 수 갱신
    current->n_elem++;
    return 0;
}

int 
lalist_remove_first (lalist_t * l, void * e)
{
	/* TODO */
}

int
lalist_remove_last (lalist_t * l, void * e)
{
	/* TODO */
}

int
lalist_remove_at (lalist_t * l, int index, void * e)
{
	/* TODO */
}


void lalist_apply(lalist_t * l, void (* func)(void * e)) {
    lalist_node_t *node = l->first; // 리스트의 첫 노드부터 시작
    while (node != NULL) { // 모든 노드를 순회
        for (int j = 0; j < node->n_elem; j++) { // 각 노드의 배열의 모든 요소에 대해
            void *element = (char *)node->arr + j * l->elem_size; // 요소의 주소 계산
            func(element); // 사용자 정의 함수 적용
        }
        node = node->next; // 다음 노드로 이동
    }
}

void 
lalist_info (lalist_t * l) // 채점용
{
	lalist_node_t * i ;
	int j = 0 ;
	printf("========\n") ;
	for (i = l->first, j = 0 ; i != NULL ; i = i->next, j++) {
		printf(" - node %d : %d elements\n", j, i->n_elem) ;
	}
	printf("========\n") ;
}

void
lalist_pack (lalist_t * l) // 마지막 노드 빼고 다 꽉차게. 
{
	/* TODO */
}
