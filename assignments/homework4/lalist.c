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
    int position = 0;

    // ������ ��ġ�� ã�� ���� ��ȸ
    while (current != NULL) {
        if (position <= index && index <= position + current->n_elem) {
            if (current->n_elem == l->arr_cap) {  // ������ ��尡 ���� á�ٸ�
                // �� ��� ����
                lalist_node_t *new_node = malloc(sizeof(lalist_node_t));
                new_node->arr = calloc(l->arr_cap, l->elem_size);
                new_node->n_elem = 0;
                new_node->next = current->next;
                current->next = new_node;

                // ���� ����� ������ ��Ҹ� �� ����� ù ��° ��ġ�� �̵�
                memcpy(new_node->arr, (char *)current->arr + (current->n_elem - 1) * l->elem_size, l->elem_size);
                new_node->n_elem = 1;
                current->n_elem--; // ���� ��忡�� ������ ��� ����
            }

            // ���� ��忡�� ��Ҹ� ���������� �̵��Ͽ� �� ��Ҹ� ����
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

    return -1; // ���� ��ġ�� ã�� ���� ���
}




int 
lalist_remove_first (lalist_t * l, void * e)
{
	/* TODO */ 
    // �迭�� ��� ����ִ� ���. 
    if(l->first ==NULL) {
        return 0;
    }

    //ù ��° ��� e�� ����.
    memcpy(e,l->first->arr, l->elem_size);
    //ù ��° ����� ��� �� 1 ����
    l->first->n_elem -=1; 

    //��Ұ� ���� ���� ���� ��� ��� ����. 
    if(l->first->n_elem == 0){
        lalist_node_t * temp_node = l->first;
        l->first = l->first->next;
        free(temp_node->arr);
        free(temp_node);
    }
    //����� �迭�� ��Ұ� ����������, �迭�� �����ִ� ��ҵ� �� ĭ �� ������ ����. 
    else{
        memmove(l->first->arr, (char*) l->first->arr + l->elem_size, l->first->n_elem * l->elem_size);
    }



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


///??
void lalist_pack(lalist_t *l) { // ?
    lalist_node_t * current = l->first;
    lalist_node_t * previous = NULL; 

    while (current != NULL) {
        int empty_space = l->arr_cap - current->n_elem; // ���� �迭�� �� �ڸ�
        if (empty_space > 0) {
            int filled_index = 0; // �տ������� ä���� �ε���
            // �� �ڸ��� ã�� ������ ��ҵ��� �� ĭ�� �ű�ϴ�.
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

    
    //ù��° �迭���� �� ������ �ִ��� Ȯ��. 
    //�� ������ �ִٸ� �� ������ �ڿ������� �� ĭ�� ������ ����. 
    //�׸��� ������� �� üũ��. 

    //���� �迭���� �� ������ �� ��ŭ ��Ҹ� ���� ����� �������� ����. 

    //���� �迭�� NULL�� �� ���� . 
