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

    // ����Ʈ�� �� ��带 ��ȸ�ϸ鼭 �޸𸮸� �����մϴ�.
    while (node != NULL) {
        next_node = node->next; // ���� ��带 �ӽ÷� �����մϴ�.
        free(node); // ���� ����� �޸𸮸� �����մϴ�.
        node = next_node; // ���� ���� �̵��մϴ�.
    }
    // ����Ʈ ��ü�� �޸𸮸� �����մϴ�.
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
	 // ù ��° ��� �˻�
    if (l->first == NULL || l->first->n_elem == l->arr_cap) { // ���� ù��° ��尡 ����ְų�, �� �� ���
        // �� ��� ���� �� �ʱ�ȭ
        lalist_node_t *_new_node = malloc(sizeof(lalist_node_t));
        
        _new_node->arr = calloc(l->elem_size, l->arr_cap);
        _new_node->n_elem = 0;
        _new_node->next = l->first;
        l->first = _new_node;
    }

    // �迭 �� ��ҵ��� ���������� �̵�
    for (int i = l->first->n_elem; i > 0; i--) {
        memcpy((char *)l->first->arr + i * l->elem_size, 
               (char *)l->first->arr + (i - 1) * l->elem_size, 
               l->elem_size);
    }

    // �� ��� ����
    memcpy(l->first->arr, e, l->elem_size);

    // ��� �� ����
    l->first->n_elem++;
}

void lalist_insert_last(lalist_t * l, void * e) {
    lalist_node_t *current = l->first;
    lalist_node_t *last = NULL;

    // ����Ʈ�� ������ ��� ã��
    while (current != NULL) {
        last = current;
        current = current->next;
    }

    // ������ ��尡 NULL�̰ų� ��� ���� �ִ� �뷮�� �����ߴٸ� �� ��� �߰�
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

    // ������ ��忡 �� ��� �߰�
    memcpy((char *)last->arr + last->n_elem * l->elem_size, e, l->elem_size);
    last->n_elem++;
}
int lalist_insert_at(lalist_t *l, int index, void *e) {
    if (index < 0 || index > lalist_length(l)) {  // ������ �ε������� �˻�
        return -1;
    }

    if (l->first == NULL) {  // ����Ʈ�� ��������� �� ��带 ����
        l->first = malloc(sizeof(lalist_node_t));
        l->first->arr = calloc(l->arr_cap, l->elem_size);
        l->first->n_elem = 0;
        l->first->next = NULL;
    }

    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;
    int position = 0;

    // ������ ��ġ�� ã�� ���� ��ȸ
    while (current != NULL) {
        if (position <= index && index <= position + current->n_elem) {
            // ������ ��带 ã��.
            if (current->n_elem == l->arr_cap) {  // ��尡 ���� á�ٸ� �� ��� �߰�
                lalist_node_t *new_node = malloc(sizeof(lalist_node_t));
                new_node->arr = calloc(l->arr_cap, l->elem_size);
                new_node->n_elem = 0;
                new_node->next = current->next;
                current->next = new_node;
                // ������ �̵�
                int moveCount = (current->n_elem + 1) / 2; // ���� ����� ������ �� ���� �̵�
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

    // ���� ��忡�� ��Ҹ� ���������� �̵��Ͽ� �� ��Ҹ� ����
    for (int i = current->n_elem; i > index - position; --i) {
        memcpy((char *)current->arr + i * l->elem_size, (char *)current->arr + (i - 1) * l->elem_size, l->elem_size);
    }
    memcpy((char *)current->arr + (index - position) * l->elem_size, e, l->elem_size);
    current->n_elem++;

    return 0;
}



int lalist_remove_first(lalist_t *l, void *e) {
    if (l->first == NULL || l->first->n_elem == 0) {
        return -1; // ����Ʈ�� ��� �ְų� ù ��° ����� ��� ���� 0�� ��� ���� ��ȯ
    }

    // ù ��° ��Ҹ� e�� ����
    memcpy(e, l->first->arr, l->elem_size);

    // ù ��° ����� ��� �� ����
    l->first->n_elem--;

    if (l->first->n_elem == 0) {
        // ��Ұ� ��� �����Ǿ����� ù ��° ��带 �����ϰ� �޸� ����
        lalist_node_t *temp_node = l->first;
        l->first = l->first->next;
        free(temp_node->arr);
        free(temp_node);
    } else {
        // ��Ұ� �����ִٸ� �迭�� ��ҵ��� �������� �� ĭ�� �̵�
        memmove(l->first->arr, (char *)l->first->arr + l->elem_size, l->elem_size * l->first->n_elem);
        // �迭�� �� �κ��� �ʱ�ȭ
        memset((char *)l->first->arr + l->first->n_elem * l->elem_size, 0, l->elem_size);
    }

    return 0; // ���������� ��� ����
}



int
lalist_remove_last (lalist_t * l, void * e)
{
	/* TODO */
    if (l->first == NULL) {
        return -1; // ����Ʈ�� ��������� ���� ��ȯ
    }

    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

    // ����Ʈ�� ������ ��� ã��
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    memcpy(e, (char *)current->arr + (current->n_elem - 1) * l->elem_size, l->elem_size);
    current->n_elem--;

    // ��Ұ� �������� ������ ��� ����
    if (current->n_elem == 0) {
        if (previous) {
            previous->next = NULL;
        } else {
            l->first = NULL; // ����Ʈ�� ��尡 �ϳ��ۿ� �����ٸ� first�� NULL�� ����
        }
        free(current->arr);
        free(current);
    }

    return 0; // ���������� ��� ���� 
}

int
lalist_remove_at (lalist_t * l, int index, void * e)
{
	/* TODO */
    //�ε��� ������ �Ǻ�. 
    if (index < 0 || index > lalist_length(l)) {  // ������ �ε������� �˻�. 
        return -1;
    }
    int count = 0; // ��������� ī��Ʈ�� ��� �� (���� �ε���)
    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

    //������ ��� ã�� 
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
    lalist_node_t *node = l->first; // ����Ʈ�� ù ������ ����
    while (node != NULL) { // ��� ��带 ��ȸ
        for (int j = 0; j < node->n_elem; j++) { // �� ����� �迭�� ��� ��ҿ� ����
            void *element = (char *)node->arr + j * l->elem_size; // ����� �ּ� ���
            func(element); // ����� ���� �Լ� ����
        }
        node = node->next; // ���� ���� �̵�
    }
}

void 
lalist_info (lalist_t * l) // ä����
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
    if (!l || !l->first) return; // No nodes to pack

    lalist_node_t *current = l->first;
    lalist_node_t *next = current->next;

    while (current && next) {
        while (current->n_elem < l->arr_cap && next->n_elem > 0) {
            // Move the first element of the next node to the current node
            memcpy((char *)current->arr + current->n_elem * l->elem_size,
                   next->arr,
                   l->elem_size);
            current->n_elem++;

            // Shift all elements in the next node left
            memmove(next->arr,
                    (char *)next->arr + l->elem_size,
                    (next->n_elem - 1) * l->elem_size);
            next->n_elem--;

            // Clean the residual space in next node
            memset((char *)next->arr + next->n_elem * l->elem_size, 0, l->elem_size);
        }

        // If after transferring elements, next node is empty, remove it
        if (next->n_elem == 0) {
            current->next = next->next;
            free(next->arr);
            free(next);
            next = current->next; // Move to the next valid node
        } else {
            // Move to the next node to continue packing
            current = next;
            next = current->next;
        }
    }
}
    
    //ù��° �迭���� �� ������ �ִ��� Ȯ��. 
    //�� ������ �ִٸ� �� ������ �ڿ������� �� ĭ�� ������ ����. 
    //�׸��� ������� �� üũ��. 

    //���� �迭���� �� ������ �� ��ŭ ��Ҹ� ���� ����� �������� ����. 

    //���� �迭�� NULL�� �� ���� . 
