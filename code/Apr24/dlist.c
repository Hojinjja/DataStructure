#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"

//���� ���� ����Ʈ -> �� ��尡 �ڽ��� "����" ���� "����" ��带 ����Ű�� �����͸� ������ �ִ� ���� ����Ʈ
dlist_t * // node ����ü �� �ϳ��� dlist_t
dlist_alloc (int unit) 
{
	dlist_t * l = (dlist_t *) malloc(sizeof(dlist_t)) ; //dlist_t�� ũ�⸸ŭ malloc()�Ͽ� �޸� �Ҵ�
	l->left = l  ;	 // ����� ������ l
	l->right = l ; // ����� �����ʵ� l -> �� �ڽ��� ������ ���� �� �ڱ� �ڽ��� ����Ŵ (���� ���� �ڽ� �ϳ� ���̴ϱ� )
	l->element = malloc(sizeof(int)) ; // ���� ���� ����Ʈ�� �� ��ҿ� ����� �������� ũ�⸦ �����ϱ� ���� �޸𸮸� �Ҵ���. ->element�� intũ�� ��ŭ �޸� �Ҵ��.
	int * u = (int *) l->element ; // ������ u�� element�� �Ҵ��� �޸��� �ּҸ� �˷���. 
	*u = unit ; // �׸��� �� �ּҿ� unit�� ������� (unit�� ��ũ�� ����Ʈ�� ������� ��� value)

	return l ;
}

// dlist_free ��Ű��
void
dlist_free (dlist_t * l)
{
	node_t * curr ; //current ���
	node_t * next ; //next ���

	curr = l->right ; // current ���� l�� right (l �� ��ü�� ����̴ϱ� �Ⱦ��� l->right�� first �����)
	while (curr != l) { // current ��尡 'l'�� �ƴ� �� ���� (�� ���� ���Ƽ� curr�� l�̸� �ѹ��� ���Ҵٴ� ��)
		next = curr->right ; // next ���� ���� ����� ���� ��� (curr->right) ���� ��� �Ѱܳ���
		free(curr->element) ; // ���� ����� element (�Ҵ��� �޸�)�� free
		free(curr) ; // ���� ��嵵 free
		curr = next ; // �׸��� �Ʊ� �Ѱܳ��� next ��带 ���� ��� (curr)�� �����س���
	}
	free(l->element) ; // �� ���� �� �������� l�� element free�ϱ� 
	free(l) ; // ���������� l�� free �ϱ� 
}


//dlist�� ���� ���ϱ� 
int 
dlist_length (dlist_t * l) 
{ 
	int len = 0 ; // ���̸� ��Ÿ���� ���� len�� ����

	node_t * curr = l->right ; // curr ����� �ʱⰪ���� l->right (ù��° ���)�� �ϰ�
	while (curr != l) { // curr ��尡 l�� �ƴ� ���� (�� ���� ���Ƽ� curr�� ����� �Ǳ� ������)
		len += 1 ; // len�� 1 ������Ű��
		curr = curr->right ;  // curr ����� ��ġ�� curr�� ���� ���� �ű�
	}
	return len ; 
}

//left�� right ���̿� ��带 �߰��ϴ� ��� (left - new - right)
void 
dlist_insert (node_t * left, void * e, int unit)
{
	node_t * _new = (node_t *) malloc(sizeof(node_t)) ; // ���� ���� ��� _new�� ����� ������� node_t ũ��� �Ѵ�. ->��ũ�� ����Ʈ�� ����°� dlist_t ũ���
	_new->element = malloc(unit) ; // �׸��� _new->element���� unitũ�� ��ŭ malloc �����ش�
	memcpy(_new->element, e, unit) ; // e�� ����Ű�� �޸𸮿��� ���� �����Ͽ� unit ũ�⸸ŭ�� �����͸� _new->element�� ����Ű�� �޸� ��ġ�� ����. 
//-> ex) e�� ���ڿ��� ��Ÿ���� ������ , unit�� ���ڿ��� ���̶�� memcpy�� _new->element ��ġ�� e ���ڿ��� unit ũ�⸸ŭ �����Ѵ�. 
	node_t * right = left->right ; // right ���� left ����� right�̴�.

	_new->left = left ; // ���ο� ����� left�� left ����̰� 
	_new->right = right ; // ���ο� ����� right�� right ����̴�.

	left->right = _new ; // left ����� right�� ���ο� ��尡 �ǰ�
	right->left = _new ; // right ����� left�� ���ο� ��尡 �ȴ�. 
}

// ��ũ�� ����Ʈ�� �� ���� insert �� ���
void
dlist_insert_first (dlist_t * l, void * e)
{
	dlist_insert(l, e, *((int *)(l->element))) ; // insert ��� 
	// l�� �� �ʿ� e(������)�� l->element�� �ִ� �� ��ŭ insert�Ѵ�. 
	// dlist_insert(node_t * left , void * e , int unit) -> left�� right ���̿� ������� (left �ڿ� ����)
}

//��ũ�� ����Ʈ�� �� �ڿ� insert �� ���
void 
dlist_insert_last (dlist_t * l, void * e)
{
	dlist_insert(l->left, e, *((int *)(l->element))) ; 
	// l�� left (�� ������ ��忡), e�� �����͸� , l->element�� �ִ� �� ��ŭ insert �Ѵ�. 
	// l->left (������ ���) �ڿ� �ִ´�. 
}


//��ũ�� ����Ʈ�� ��� ����
int
dlist_remove (dlist_t * l, node_t * n)
{
	if (l->left == l) // l�� left�� �ٽ� l�� �Ǵ� ��� (��尡 �ϳ��� ���°��)
		return 0 ;

	n->left->right = n->right ; // (�����Ϸ��� ��� n�� left)�� right�� ,  n�� right�� 
	n->right->left = n->left ; // (�����Ϸ��� ��� n�� right)�� left�� , n�� left��
// -> ������� ����� ���ʰ� �������� �̾��ִ� �۾�

	free(n->element) ; // �� �̾��ְ� ���� n�� element ���� free ���ְ�
	free(n) ; // n�� free�Ѵ�. 
	return 1 ;
}

//�� �� �κ��� ���� 
int 
dlist_remove_first (dlist_t * l, void * e)
{
	if (l->right == l) // ����Ʈ�� ��� �ִ� ���
		return 0 ;

	memcpy(e, l->right->element, *((int *)(l->element))) ; //e���ٰ� l�� right�� element�� ����
	dlist_remove(l, l->right) ; // ����Ʈ (l) �� l->right( ù ��� )�� ����
	return 0 ;
}

int
dlist_remove_last (dlist_t * l, void * e)
{
	if (l->left == l) 
		return 1 ;

	memcpy(e, l->left->element, *((int *)(l->element))) ; // e�� ������ ���(����Ʈ(l)�� left)�� element�� �ְ�
	dlist_remove(l, l->left) ; // l�� ���� (������ ��带 �����Ѵ�.)
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
	n=l->right ; //ù��° ��� 
	int i = 0;
	for (i=0; i <index ; i++){ // �Է��� �ε��� ���� �̵�
		n = n->right;
		if (n == l){
			return 0; 
		}
	}

	memcpy(e, n->element, *((int*)l->element)); // e���ٰ� n��° �ε����� element�� �������
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
 
	node_t * n = l->right ; // ��� n�� �ʱⰪ�� l->right�̰� 
	int i = 0 ;  // int i�� �ʱⰪ�� 0

	for (i = 0 ; i < index ; i++) { // i�� �ε��� ��ġ���� �̵���Ŵ,
		n = n->right ;
		if (n == l) {
			return 0 ;
		}
	}

	n->left->right = n->right ; // (n->left)����� right = ���� ���(n)�� right
	n->right->left = n->left ; // (n->right)����� left = ���� ��� (n)�� left
// �̰͵� ������� ����� ���ʰ� �������� �̾��ִ� �۾�
	free(n->element) ; // n�� element�� free���ְ�
	free(n) ; // n�� free ����
	return 1 ;
}

int 
dlist_append (dlist_t * l1, dlist_t * l2)
/*
 * add all elements in ``l2`` to ``l1``, in their order in ``l2``.
 * return the number of added elements.
 */

{	
	// ��ũ�� ����Ʈ l2�� ��� ��Ҹ� l1 �ڿ� �߰��ϴ� �Լ�.
	/*TODO*/
	
	node_t * i2; // ��� i2 �������ְ� 

	for(i2 = l2->right; i2 !=l2 ; i2 = i2->right){ // i2��尡 l2->right(l2 ����� ù��° ���)���� ���� , i2�� l2�� �ƴ� ������ (�� l2�� �� ���� ����)
		// dlist_insert_last(l1, i2->element);
		node_t * _new = malloc(sizeof(node_t)); // _new ��带 �������ְ� �޸� �Ҵ�. 
		_new->element = malloc(sizeof(*((int*)(l2->element)))) ;  // _new ����� element �κ��� l2->element�� �ִ� ������
		memcpy(_new->element, i2->element, *((int*)l2->element) ); // _new ����� element�� i2�� element�� ���� ����. 

		_new->left = l1->left; // new ����� left�� , l1 ����Ʈ�� ������ ���� ����
		_new->right = l1; // new ����� right�� l1 ����� ����Ű�� �ȴ�. 

		l1->left->right = _new; // l1�� left (l1�� ������ ���)�� right�� ���ο� ��� _new�� �ְ�
		l1->left = _new; // l1�� left (������ ���)�� _new �̴�. 

	} ; 
}


