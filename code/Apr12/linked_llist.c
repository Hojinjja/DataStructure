#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef = llist_node_t 
//struct = _llist_nodet_t
typedef 
	struct _llist_node_t { //���ȣ���� ���� _list_node_t�� ���� <�߿�?>
		char * data ; //�����͸� ����Ű�� ������.
		struct _llist_node_t * next ; // ���� ��带 ����Ű�� ������. (�߿�)������ ������ ������ָ� ������ ����� �ȵ�.->���Ѵ�� �߻���.)
	}
	llist_node_t ;

typedef 
	struct {
		llist_node_t * first ;
		int size ;
	}
	llist_t ;


llist_t * create_llist () 
{
	llist_t * l = (llist_t *) malloc(sizeof(llist_t)) ;
	l->first = NULL ;
	l->size = 0 ;
	return l ; 
}

int insert_llist (llist_t * l, char * s)
{
	llist_node_t * n = (llist_node_t *) malloc(sizeof(llist_node_t)) ;
	//node �ϳ� ����� (data/next)
	n->data = s ;
	n->next = NULL ;
	
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


char * delete_llist (llist_t * l, char * s) //Ư�� ���ڸ� ������ 
{
	llist_node_t * i ;
	llist_node_t * prev = NULL; //���� ����� next �κ��� ����� �ϱ� ������ , ���� ��带 �˾ƾ��Ѵ�.
	//�׸��� ������� �����Ͱ� �ִ� ��带 free ���ش�. 
	//���� ��Ȳ1) prev�� �������� �ʴ� ��� -> first�� '������� ����� next'�� ������ �Ѵ�.

	for (i = l->first ; i != NULL ; i = i->next) { //first�� ����ؼ� i�� null�϶�����..
		if (strcmp(i->data, s) == 0) { //������� Ư�� ���ڿ� i ����� data�� ������ Ȯ��. 
			break ;			//cf) strcmp���� int���� �� -> '-' ���� 
		} 
		prev=i;
	}

	if (i == NULL)
		return NULL ;

/* TODO */
	char * r ;
	r= i->data;
	if(i== l->first){
		l->first = i->next;
	}else{
		prev->next = i->next;
	}
	free(i);

	return r ;
}

void print_llist (llist_t * l)
{
	llist_node_t * i ;
	for (i = l->first ; i != NULL ; i = i->next) {
		printf("%s ", i->data) ;
	}
	printf("\n") ;
}

void free_llist (llist_t * l) //list ��ü�� ��带 �� ������ ��. 
{
	/*TODO*/
	llist_node_t * i ;
	for (i = l->first ; i != NULL ; ) {
		llist_node_t * current = i;
		i=i->next;
		free(current);
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
