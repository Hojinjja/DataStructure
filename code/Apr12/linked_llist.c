#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef 
	struct _llist_node_t { //���ȣ���� ���� _list_node_t�� ���� <�߿�?>
		char * data ; //�����͸� ����Ű�� ������.
		struct _llist_node_t * next ; // ���� ��带 ����Ű�� ������. (�߿�)������ ������ ������ָ� ������ ����� �ȵ�.->���Ѵ�� �߻���.)
	}
	llist_node_t ;


typedef 
	struct {
		llist_node_t * first ; // �� ó�� ��� 
		int size ; // ��ũ�� ����Ʈ�� ������ (���� �� �ִ� ����� ����)
	}
	llist_t ;

/*
* ��ũ�� ����Ʈ ���� �� �ʱ�ȭ
*/
llist_t * create_llist () 
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ; // l�� ũ��� sizeof(llist_t)�� 
	l->first = NULL ; //first�� NULL
	l->size = 0 ; // size�� 0���� �ʱ�ȭ 
	return l ; 
}


/*
* ��� �ϳ� ���� ��ũ�� ����Ʈ ���� �߰��ϱ�. 
*/
int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ;
	//node 'n' �ϳ� ����� (data/next)
	n->data = s ; // data�� s�� 
	n->next = NULL ; // next�� NULL�� (���� ��Ұ� ���� �����Ƿ�)
	
	//ù ����� ��� (size==0 or first==0)
	if (l->first == NULL) {
		l->first = n ;
		l->size=1;
		return 1 ;
	}

	/* TODO - ù ��尡 �ƴ� ���
	��� 1 -> �������谡 �߿��� ���.
	.*/
	llist_node_t *last = l->first; // last ��带 ����°� �ƴ϶�(�׳� �̸��� last) last�� �ĺ��� ���� first�� �־��ش�.
	while(last->next !=NULL){ // ���� ����Ʈ�� ���� ã�� (next�� null �϶����� �ݺ�)
		last=last->next; //ã�Ҵٸ� last�� last->next. �� ��带 ��� �Ѿ. 
	}
	last->next = n; // ����� ���� ã�Ҵٸ� last�� next�� n 

	/*��� 2 =���� ���谡 �߿�ġ �ʾ� first �տ� �������°��
	n->next = l->first;
	l->first=n;
	l->size++;
	*/

	return 1 ;
}


/*
* Ư�� ������ �ε����� �����ϱ� 
*/
char * delete_llist (llist_t * l, char * s) //Ư�� ���ڸ� ������ 
{
	llist_node_t * i ;
	llist_node_t * prev = NULL; //���� ����� next �κ��� ����� �ϱ� ������ , ���� ��带 �˾ƾ��Ѵ�.
	//�׸��� ������� �����Ͱ� �ִ� ��带 free ���ش�. 
	//���� ��Ȳ1) prev�� �������� �ʴ� ��� -> first�� '������� ����� next'�� ������ �Ѵ�.

	for (i = l->first ; i != NULL ; i = i->next) { //first�� ����ؼ� i�� null�϶�����.. i�� ������ ��� �Ѿ.
		if (strcmp(i->data, s) == 0) { //������� Ư�� ���ڿ� i ����� data�� ������ Ȯ��. ������ ����
			break ;			//cf) strcmp���� (int���� �� -> '-' ���� )
		} 
		prev=i; // ���� ������ ����� data�� ������� ���ڿ� s�� �ٸ��ٸ� ���� �˻��ϰ� �ִ� �ε��� i�� prev��.
	}

	if (i == NULL) // ���� i�� ������ �� ��� (������ ����� next�� NULL)
		return NULL ; // ã�� ���ڰ� ���ٴ� ���̹Ƿ� NULL ��ȯ 

/* ���� �����Ϸ��� ���� s�� ã�� ���*/
	char * r ;
	r= i->data; // r�� i�� �����͸� ��� (ã������ ���ڿ�)
	if(i== l->first){ // i�� ù��° ���(first) ���ٸ� 
		l->first = i->next; // first�� i�� next�� �ȴ�
	}
	else{ // �����Ϸ��� ����� �ε����� ù��° ��Ұ� �ƴ϶�� 
		prev->next = i->next; //���� ��� ���� ��� (prev)�� next�� ���� ���(i)�� next�� �̾���. 
	}
	free(i); // �׸��� i��° ��带 free����,

	return r ;
}


void print_llist (llist_t * l) // ��ũ�� ����Ʈ ����ϱ�
{
	llist_node_t * i ; //��� i�� �����ϰ� 
	for (i = l->first ; i != NULL ; i = i->next) { // i�� NULL�� �� �� ���� next�� �ѱ�
		printf("%s ", i->data) ; // i�� ����Ǿ��ٸ�, i->data�� ��� 
	}
	printf("\n") ;
}

void free_llist (llist_t * l) //list ��ü�� ��带 �� ������ ��. 
{
	/*TODO*/
	llist_node_t * i ;
	for (i = l->first ; i != NULL ; ) { // ����Ʈ (l)�� ������ ��ȸ�ϸ� (NULL����)
		llist_node_t * current = i; // current ��带 �����Ͽ� ���� ��� i�� �־�ΰ� 
		i=i->next; // i�� ���� ���� �ѱ����
		free(current); //  ���� ���� free ��Ų��. 
	}
	free(i);
}

/*****/

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
