#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct _llist_node_t {
		char * data ; // data
		struct _llist_node_t * next ; // ���� ��带 ����Ű�� next 
	}
	llist_node_t ; // ��� ����ü

typedef 
	struct {
		llist_node_t * last ;  // ���� ����Ʈ�� ������ ��带 ����Ű�� ��� 
	}
	llist_t ; // ��ũ�� ����Ʈ ����ü (last ��带 ����Ű�� ����)

/*
* ��ũ�� ����Ʈ ����� 
*/
llist_t * create_llist ()
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ; // llist_t ũ��� �޸� �Ҵ� 
	l->last = NULL ; // last�� �ʱⰪ�� NULL
	return l ; 
}

int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ; // ��� 'n' �����
	n->data = s ; //����� data ���� s
	n->next = NULL ; // ����� next�� NULL
	
	if (l->last == NULL) { //���� l->last�� NULL �̸� -> ù��° ����� 
		l->last = n ; // l�� last�� 'n'�� �ȴ�. -> ��ũ�� ����Ʈ�� ������ ���(last) = n
		n->next = n ; // n�� next�� 'n'�� �ȴ�. -> n�� next�� n -> ��尡 �ڱ� �ϳ� �̹Ƿ� ���� ��� (next)�� �ڱ� �ڽ�
		return 1 ;
	}

	// ���� last�� NULL�� �ƴ϶�� -> �� ��ũ�� ����Ʈ�� ��Ұ� ������ �ִٸ�, 
	llist_node_t * last; // last�� �������ְ� 
	n->next = last->next ; // ��� ���� ��� n�� ���� ����(n->next) ������ ������ ��� last�� next�� �ȴ�. 
	last->next = n ; // �׸��� ������ last�� next�� ���� �߰��� ��� n�� �ȴ�. 
	last = n ; // ���� ���� ���� �������Ƿ� ���ο� last�� n�� �ȴ�. 

	return 1 ;
}

/*
* Ư�� ���ڿ� s�� l����Ʈ ���� �����ϱ� 
*/
char * delete_llist (llist_t * l, char * s) 
{
	llist_node_t * i ; // ��� i 
	llist_node_t * prev ;  // ���� ����� ���� ��� prev 

	if (l->last == NULL) // last�� NULL �� ���, �� ����Ʈ�� ����ִ� ���. 
		return NULL ;

	int found = 0 ; // ã�ҳ� ��ã�ҳ� ���¸� ��Ÿ���� ���� found 
	prev = l->last ; // prev(����) ���� ����Ʈ(l)�� ������ ��� (last)
	i = l->last->next ; // i�� ����Ʈ (l)�� ������ ���(last)�� ���� (next)��� 
	do {
		if (strcmp(i->data, s) == 0) { // ã�� ���ڿ��� ������
			found = 1 ; // found�� 1�� �����ϰ� break
			break ;
		}
		prev = i ; // prev (����)���� i�� ����. 
		i = i->next ; // i�� i->next��
	} while (i != l->last->next) ; // i�� ����Ʈ (l)�� last->next�� �ƴ� �� ���� (last->next = ù��° ���)

	if (found == 0) // ���� found�� 0�� ä�� �������� ������� ���ڿ��� ��ã�Ҵٴ� ��. 
		return NULL ;

	char * r ;
	r = i->data ; // r�� i��° �ε����� data�� ��� 

	if (i == l->last) { //������ ��带 ������ ��� 
		if (l->last == l->last->next) { // l->last�� l->last->next �� ���� ��� (�� �ϳ� ���� ��� ) -> �� �߿����� �ϳ� ���� ��带 ������ ���. 
			l->last = NULL ; // �ϳ� ���� �� ���������Ƿ� ����Ʈ(l)�� last�� NULL -> ��尡 �ϳ��� ����.  
		}
		else { // ������ ��带 ���������� �ϳ� ���� ��Ȳ�� �ƴ� ���
			prev->next = l->last->next ; // ���� ��� (prev)�� next�� ����Ʈ�� ù �� ° ���
			l->last = prev ; // �׸��� last��Ҵ� ���� ������ ����� ���� ��� (prev)�� �ȴ�. 
		}
	}
	else { // ������ ��带 �������� ���� ���. 
		prev->next = i->next ; // prev�� next (���� ����� next = ���� ����� next) - > ���� ��尡 �����Ǵϱ� �����̶�(prev)�� ���� ����� next�� �̾���. 
	}
	free(i) ; // ���� �� �������ϱ� i�� free ��Ų��.  ==> i->data�� NULL �� ���� ������ �ʿ� ����. free(i)�� �ذ�

	return r ;
}

void print_llist (llist_t * l) // ���� �ȳ���.
{
	if (l->last == NULL)
		return ;

	llist_node_t * i = l->last->next;  // i�� �ʱⰪ�� ����Ʈ�� last->next( �� ó�� ��� )�� �����س��� 
	do {
		printf("%s",i->data);
		i=i->next;
	}while (i != l->last->next);
	printf("\n") ;
}

void free_llist (llist_t * l)
{
	/*TODO < ����*/
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
