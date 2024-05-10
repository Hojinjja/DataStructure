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
	l->first = malloc(sizeof(lalist_node_t)) ;
	l->first->arr = calloc(elem_size, arr_cap) ;
	l->first->n_elem = 0 ;
	l->first->next = NULL ;

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

void lalist_pack(lalist_t *l) {
    lalist_node_t *current = l->first;

    while (current != NULL) {
        int empty_space = l->arr_cap - current->n_elem; // 현재 배열의 빈 공간

        if (empty_space > 0 && current->next != NULL) { // 빈 공간이 있고 다음 노드가 있는 경우
            lalist_node_t *next_node = current->next; // 다음 노드

            int filled_index = 0; // 현재 노드에서 빈 공간 뒤에서부터 채워질 인덱스

            // 빈 공간 뒤에 있는 요소들을 한 칸씩 앞으로 이동
            for (int i = 0; i < next_node->n_elem; i++) {
                memcpy((char *)current->arr + (empty_space + filled_index) * l->elem_size, 
                       (char *)next_node->arr + i * l->elem_size, 
                       l->elem_size);
                filled_index++;
            }

            // 다음 노드의 요소들을 이동했으므로 요소 수 갱신
            current->n_elem += filled_index;
            next_node->n_elem -= filled_index;

            // 빈 공간 뒤에 있는 요소들을 이동했으므로 다음 노드에서 요소들을 당긴다.
            memmove(next_node->arr, (char *)next_node->arr + filled_index * l->elem_size, 
                    next_node->n_elem * l->elem_size);

            // 다음 노드의 빈 공간 초기화
            memset((char *)next_node->arr + next_node->n_elem * l->elem_size, 
                   0, (l->arr_cap - next_node->n_elem) * l->elem_size);

            // 만약 다음 노드의 요소가 없으면 다음 노드를 삭제하고 메모리를 해제한다.
            if (next_node->n_elem == 0) {
                current->next = next_node->next;
                free(next_node->arr);
                free(next_node);
            }
        }

        current = current->next; // 다음 노드로 이동
    }
}



void lalist_insert_first(lalist_t *l, void *e) {
    // 첫 번째 노드가 비어 있거나 가득 찬 경우 새 노드를 생성하고 추가
    if (l->first == NULL || l->first->n_elem == l->arr_cap) {
        lalist_node_t *_new_node = malloc(sizeof(lalist_node_t));
        _new_node->arr = calloc(l->arr_cap, l->elem_size);
        _new_node->n_elem = 0;
        _new_node->next = l->first;
        l->first = _new_node;
    }

    // 요소를 삽입하기 위해 배열의 모든 요소를 오른쪽으로 이동
    for (int i = l->first->n_elem; i > 0; i--) {
        memcpy((char *)l->first->arr + i * l->elem_size,
               (char *)l->first->arr + (i - 1) * l->elem_size,
               l->elem_size);
    }

    // 새 요소를 삽입
    memcpy(l->first->arr, e, l->elem_size);

    // 요소 수 갱신
    l->first->n_elem++;
}

void lalist_insert_last(lalist_t *l, void *e) {
    lalist_node_t *current = l->first;

    // 리스트의 마지막 노드 찾기
    while (current != NULL && current->next != NULL) {
        current = current->next;
    }

    // 마지막 노드가 없거나 가득 찬 경우 새 노드 생성
    if (current == NULL || current->n_elem == l->arr_cap) {
        lalist_node_t *new_node = malloc(sizeof(lalist_node_t));
        new_node->arr = calloc(l->arr_cap, l->elem_size);
        new_node->n_elem = 0;
        new_node->next = NULL;

        if (current == NULL) {
            l->first = new_node;
        } else {
            current->next = new_node;
        }

        current = new_node;
    }

    // 요소를 삽입
    memcpy((char *)current->arr + current->n_elem * l->elem_size, e, l->elem_size);
    current->n_elem++;
}

int lalist_insert_at(lalist_t *l, int index, void *e) {
    if (index < 0 || index > lalist_length(l)) {
        return -1; // 적절한 인덱스가 아닌 경우 실패 반환
    }

    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;
    int position = 0;

    // 삽입할 위치를 찾기 위해 순회
    while (current != NULL) {
        if (position <= index && index <= position + current->n_elem) {
            // 현재 노드가 가득 찬 경우 새 노드 생성
            if (current->n_elem == l->arr_cap) {
                lalist_node_t *new_node = malloc(sizeof(lalist_node_t));
                new_node->arr = calloc(l->arr_cap, l->elem_size);
                new_node->n_elem = 0;
                new_node->next = current->next;
                current->next = new_node;

                // 데이터 이동
                int moveCount = (current->n_elem + 1) / 2;
                memcpy(new_node->arr, (char *)current->arr + (current->n_elem - moveCount) * l->elem_size, moveCount * l->elem_size);
                new_node->n_elem = moveCount;
                current->n_elem -= moveCount;
            }
            break;
        }
        position += current->n_elem;
        previous = current;
        current = current->next;
    }

    // 현재 노드에서 요소를 오른쪽으로 이동하여 새 요소 삽입
    for (int i = current->n_elem; i > index - position; i--) {
        memcpy((char *)current->arr + i * l->elem_size, (char *)current->arr + (i - 1) * l->elem_size, l->elem_size);
    }
    memcpy((char *)current->arr + (index - position) * l->elem_size, e, l->elem_size);
    current->n_elem++;

    return 0;
}

int lalist_remove_first(lalist_t *l, void *e) {
    if (l->first == NULL || l->first->n_elem == 0) {
        return -1; // 리스트가 비어 있거나 첫 번째 노드의 요소 수가 0인 경우 실패 반환
    }

    // 첫 번째 요소를 e에 복사
    memcpy(e, l->first->arr, l->elem_size);

    // 첫 번째 노드의 요소 수 감소
    l->first->n_elem--;

    if (l->first->n_elem == 0) {
        // 요소가 모두 삭제되었으면 첫 번째 노드를 삭제하고 메모리 해제
        lalist_node_t *temp_node = l->first;
        l->first = l->first->next;
        free(temp_node->arr);
        free(temp_node);
    } else {
        // 요소가 남아있다면 배열의 요소들을 왼쪽으로 한 칸씩 이동
        memmove(l->first->arr, (char *)l->first->arr + l->elem_size, l->elem_size * l->first->n_elem);
        // 배열의 끝 부분을 초기화
        memset((char *)l->first->arr + l->first->n_elem * l->elem_size, 0, l->elem_size);
    }

    return 0; // 성공적으로 요소 제거
}

int lalist_remove_last(lalist_t *l, void *e) {
    if (l->first == NULL) {
        return -1; // 리스트가 비어 있으면 실패 반환
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

int lalist_remove_at(lalist_t *l, int index, void *e) {
    if (index < 0 || index > lalist_length(l)) {
        return -1; // 적절한 인덱스가 아닌 경우 실패 반환
    }

    int count = 0; // 현재까지의 카운트한 요소 수 (현재 인덱스)
    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

    // 삭제할 노드 찾기
    while (current != NULL && count + current->n_elem <= index) {
        count += current->n_elem;
        previous = current;
        current = current->next;
    }

    memcpy(e, (char *)current->arr + (index - count) * l->elem_size, l->elem_size);
    memset((char *)current->arr + (index - count) * l->elem_size, 0, l->elem_size);
    current->n_elem -= 1;

    if (current->n_elem == 0) {
        // 요소가 없으면 노드 삭제
        if (previous) {
            previous->next = current->next;
        } else {
            l->first = NULL;
        }
        free(current->arr);
        free(current);
    }

    return 0;
}
