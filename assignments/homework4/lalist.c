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

void lalist_free(lalist_t *l) {
    lalist_node_t *node = l->first;
    lalist_node_t *next_node = NULL;

    // 리스트의 각 노드를 순회하면서 메모리를 해제합니다.
    while (node != NULL) {
        next_node = node->next; // 다음 노드를 임시로 저장합니다.
        free(node); // 현재 노드의 메모리를 해제합니다.
        node = next_node; // 다음 노드로 이동합니다.
    }
    // 리스트 자체의 메모리를 해제합니다.
    free(l);
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

    // 마지막 노드가 NULL이거나 요소 수가 최대 용량에 도달했다면 새 노드 추가
    if (last == NULL || last->n_elem >= l->arr_cap) {
        lalist_node_t *new_node = malloc(sizeof(lalist_node_t));
        new_node->arr = calloc(l->elem_size, l->arr_cap);
        new_node->n_elem = 0;
        new_node->next = NULL;
        if (last == NULL) {
            l->first = new_node;
        } else {
            last->next = new_node;
        }
        last = new_node;
    }

    // 적절한 노드에 새 요소 추가
    memcpy((char *)last->arr + last->n_elem * l->elem_size, e, l->elem_size);
    last->n_elem++;
}

int lalist_insert_at(lalist_t *l, int index, void *e) {
    if (index < 0 || index > lalist_length(l)) {  // 적절한 인덱스인지 검사
        return -1;
    }

    if (l->first == NULL) {  // 리스트가 비어있으면 새 노드를 생성
        l->first = malloc(sizeof(lalist_node_t));
        l->first->arr = calloc(l->arr_cap, l->elem_size);
        l->first->n_elem = 0;
        l->first->next = NULL;
    }

    lalist_node_t *current = l->first;
    int position = 0;

    // 삽입할 위치를 찾기 위해 순회
    while (current != NULL) {
        if (position <= index && index <= position + current->n_elem) {
            if (current->n_elem == l->arr_cap) {  // 삽입할 노드가 가득 찼다면
                // 새 노드 생성
                lalist_node_t *new_node = malloc(sizeof(lalist_node_t));
                new_node->arr = calloc(l->arr_cap, l->elem_size);
                new_node->n_elem = 0;
                new_node->next = current->next;
                current->next = new_node;

                // 현재 노드의 마지막 요소를 새 노드의 첫 번째 위치로 이동
                memcpy(new_node->arr, (char *)current->arr + (current->n_elem - 1) * l->elem_size, l->elem_size);
                new_node->n_elem = 1;
                current->n_elem--; // 현재 노드에서 마지막 요소 제거
            }

            // 현재 노드에서 요소를 오른쪽으로 이동하여 새 요소를 삽입
            for (int i = current->n_elem; i > index - position; --i) {
                memcpy((char *)current->arr + i * l->elem_size, (char *)current->arr + (i - 1) * l->elem_size, l->elem_size);
            }
            memcpy((char *)current->arr + (index - position) * l->elem_size, e, l->elem_size);
            current->n_elem++;

            return 0;
        }
        position += current->n_elem;
        current = current->next;
    }

    return -1; // 삽입 위치를 찾지 못한 경우
}




int 
lalist_remove_first (lalist_t * l, void * e)
{
	/* TODO */ 
    // 배열이 모두 비어있는 경우. 
    if(l->first ==NULL) {
        return 0;
    }

    //첫 번째 요소 e에 복사.
    memcpy(e,l->first->arr, l->elem_size);
    //첫 번째 노드의 요소 수 1 감소
    l->first->n_elem -=1; 

    //요소가 남아 있지 않은 경우 노드 제거. 
    if(l->first->n_elem == 0){
        lalist_node_t * temp_node = l->first;
        l->first = l->first->next;
        free(temp_node->arr);
        free(temp_node);
    }
    //지우고도 배열에 요소가 남아있으면, 배열에 남아있는 요소들 한 칸 씩 앞으로 당긴다. 
    else{
        memmove(l->first->arr, (char*) l->first->arr + l->elem_size, l->first->n_elem * l->elem_size);
    }



}

int
lalist_remove_last (lalist_t * l, void * e)
{
	/* TODO */
    if (l->first == NULL) {
        return -1; // 리스트가 비어있으면 실패 반환
    }

    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

    // 리스트의 마지막 노드 찾기
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    memcpy(e, (char *)current->arr + (current->n_elem - 1) * l->elem_size, l->elem_size);
    current->n_elem--;

    // 요소가 남아있지 않으면 노드 삭제
    if (current->n_elem == 0) {
        if (previous) {
            previous->next = NULL;
        } else {
            l->first = NULL; // 리스트에 노드가 하나밖에 없었다면 first도 NULL로 설정
        }
        free(current->arr);
        free(current);
    }

    return 0; // 성공적으로 요소 제거 
}

int
lalist_remove_at (lalist_t * l, int index, void * e)
{
	/* TODO */
    //인덱스 적절성 판별. 
    if (index < 0 || index > lalist_length(l)) {  // 적절한 인덱스인지 검사. 
        return -1;
    }
    int count = 0; // 현재까지의 카운트한 요소 수 (현재 인덱스)
    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

    //삭제할 노드 찾기 
    while(current != NULL && count + current ->n_elem <=index){
        count += current -> n_elem; 
        previous = current ; 
        current = current->next;
    }
    memcpy(e, (char *)current->arr + (index - count) * l->elem_size, l->elem_size);
    memset((char *)current->arr + (index - count) * l->elem_size, 0, l->elem_size);
    current->n_elem -= 1; 
    if(current->n_elem == 0){
        if(previous){
            previous->next = current->next;
        }
        else{
            l->first = NULL;
        }
        free(current->arr);
        free(current);
    }

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


///??
void lalist_pack(lalist_t *l) { // ?
    lalist_node_t * current = l->first;
    lalist_node_t * previous = NULL; 

    while (current != NULL) {
        int empty_space = l->arr_cap - current->n_elem; // 현재 배열의 빈 자리
        if (empty_space > 0) {
            int filled_index = 0; // 앞에서부터 채워질 인덱스
            // 빈 자리를 찾아 앞으로 요소들을 한 칸씩 옮깁니다.
            for (int i = 0; i < current->n_elem; i++) {
                    if (*(int *)((char *)current->arr + i * l->elem_size) != 0)
                    memcpy((char *)current->arr + filled_index * l->elem_size, (char *)current->arr + i * l->elem_size, l->elem_size);
                    filled_index++;
                }
            }
            
        }
    current = l->first;
    while (current != NULL){
        lalist_node_t * previous = NULL;


        }
    }

    
    //첫번째 배열부터 빈 공간이 있는지 확인. 
    //빈 공간이 있다면 빈 공간의 뒤에서부터 한 칸씩 앞으로 당긴다. 
    //그리고 빈공간의 수 체크함. 

    //다음 배열에서 빈 공간의 수 만큼 요소를 이전 요소의 마지막에 넣음. 

    //다음 배열이 NULL일 때 까지 . 
