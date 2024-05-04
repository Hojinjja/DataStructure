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

    // ������ ��尡 NULL�̸� �� ��带 ù ���� �߰�
    if (last == NULL) {
        l->first = malloc(sizeof(lalist_node_t));
        l->first->arr = calloc(l->elem_size, l->arr_cap);
        l->first->n_elem = 0;
        l->first->next = NULL;
        last = l->first;
    } else if (last->n_elem == l->arr_cap) {
        // ������ ����� �迭�� ���� á�ٸ� �� ��� �߰�
        last->next = malloc(sizeof(lalist_node_t));
        last->next->arr = calloc(l->elem_size, l->arr_cap);
        last->next->n_elem = 0;
        last->next->next = NULL;
        last = last->next;
    }

    // �� ��Ҹ� ������ ����� �迭�� �߰�
    memcpy((char *)last->arr + last->n_elem * l->elem_size, e, l->elem_size);

    // ��� �� ����
    last->n_elem++;
}

int
lalist_insert_at (lalist_t * l, int index, void * e)
{
	if (index < 0 || index > lalist_length(l)) {  // ������ �ε������� �˻�. 
        return -1;
    }

    int count = 0; // ��������� ī��Ʈ�� ��� �� (���� �ε���)
    lalist_node_t *current = l->first;
    lalist_node_t *previous = NULL;

	// �̹� ��� ��尡 �� �� ���.
   if (current->n_elem == l->arr_cap) {
    lalist_node_t *new_node = malloc(sizeof(lalist_node_t));  // �� ��� ����
    new_node->arr = calloc(l->elem_size, l->arr_cap);        // �� �迭 �Ҵ�
    new_node->n_elem = 0;                                    // �ʱ� ��� ���� 0
    new_node->next = current->next;                          // �� ��带 ���� ��� �ڿ� ����
    current->next = new_node;                                // ���� ����� ���� ��带 �� ���� ����
    current = new_node;                                      // ������ ��带 �� ���� ����
	}

    // ������ ��� ã�� ->index�� �˸´� ��� ã�� (current�� NULL�̰ų�, index�� ��ġ�� �ִ� ��忡 �����ϸ� �ݺ� ��)
    while (current != NULL && count + current->n_elem <= index) {
        count += current->n_elem;
        previous = current;
        current = current->next;
    }

	// ��带 ã�Ƽ� ������ ���µ�, ��尡 ���� ���.
    if (current == NULL) {  // �� ��尡 �ʿ��� ��� -����Ʈ�� ���� �� ���, �� �������� �ִµ� ������ ��尡 �� �� ���
        current = malloc(sizeof(lalist_node_t));
        current->arr = calloc(l->elem_size, l->arr_cap);
        current->n_elem = 0;
        current->next = NULL;
        //
		if (previous != NULL) {
            previous->next = current;
        } else { // �ƿ� �� ��� 
            l->first = current;
        }
    }

	

    // �迭 �� ��ҵ��� ���������� �̵�
    for (int i = current->n_elem; i > index - count; i--) {
        memcpy((char *)current->arr + i * l->elem_size, 
               (char *)current->arr + (i - 1) * l->elem_size, 
               l->elem_size);
    }

    // �� ��� ����
    memcpy((char *)current->arr + (index - count) * l->elem_size, e, l->elem_size);

    // ��� �� ����
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

void
lalist_pack (lalist_t * l) // ������ ��� ���� �� ������. 
{
	/* TODO */
}
