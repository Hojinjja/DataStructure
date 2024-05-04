#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		int arrlen ; //�迭����
		int size ; // ���� ����Ʈ ��� ����
		int first ; // ���Ḯ��Ʈ�� ù��° ��� �ε���
		char ** data ; // �ε����� value
		int * link ; // �������� ���� ��Ҹ� ����Ų��. 
	}
	arrlist_t ;


/******************
* arrlist ����� 
*******************/
arrlist_t * create_arrlist (int capacity)
{
	if (capacity <= 0) {
		return NULL ;
	}

	arrlist_t * l = (arrlist_t *) malloc(sizeof(arrlist_t)) ;
	if (l == NULL) {
		return NULL ;
	}

	l->arrlen = capacity + 1 ; //0�� �ּҴ� �Ⱦ���� ��������Ƿ�, ũ��� +1�� ����ش�. - array ����
	l->size = 0 ; // �ʱ� size�� 0 
	l->first = 0 ; //������ �ε����� 0 // 1�� ���� �ʳ�?? ���� �ڵ�� 0 
	l->data = (char **) calloc(l->arrlen, sizeof(char *)) ; // ���� ������ Ÿ�Ը�ŭ�� ũ�� 
	l->link = (int *) calloc(l->arrlen, sizeof(int)) ; // 
	memset(l->data, 0, l->arrlen * sizeof(char*)); // data �ʵ带 �ʱ�ȭ �ϴ� �κ� arrlen * sizeof(char*)���� 
	memset(l->link, 0, l->arrlen * sizeof(int)) ; // link �ʵ带 �ʱ�ȭ �ϴ� �κ� arrlen * sizeof(int) ��ŭ
	
	if (l->data == NULL || l->link == NULL) { // ����� �Ҵ��� �̷�������� Ȯ���ϴ� �κ� , ���� data or link �κ��� NULL�̸� �Ҵ� ����. 
		free(l) ;
		return NULL ;
	}

	return l ; 
}


/*
* arrlist�� s�� ���� �ֱ�. 
*/
int insert_arrlist (arrlist_t * l, char * s)
{
	if (s == NULL) // s�� NULL �� ���.
		return 0 ;

	if (l->size == l->arrlen - 1) // full �� ���. 
		return 0 ;

	// allocate an empty slot to store s
	int next = 1 ; // first�� ������ 1
	
	while (l->data[next] != NULL) { //���� ������ ������� Ȯ��
		next++ ; // data�� next �ε����� NULL�� �ƴ϶�� next ++ �Ѵ�.  
	}
	l->data[next] = s ; // ����ִ� �ε���(next)�� �߰��ϸ� data[]�� �ִ´�.
	l->link[next] = 0 ; // �� ���� ���� ����. next�� 0�̴�. (NULL�� �� ���� �ʳ�?)------------------------------ 

	/* TODO */ // ���� �������� �ε����� ���� - ��ũ���� 0�� ��츦 ã�ƶ� 
	if (l->first == 0){ //�� �� ����ִ� ��� first�� �ƹ��� ����Ű�� ���� �ʴ�. 
		l->first = next; // l�� first�� next�� �ȴ�. (�׷��� next�� l�� first�� �ȴ�. ) 
	}
	else{
		int i;
		i=l->first;
		while(l->link[i] != 0){
			i=l->link[i]; 
		} //link[i]�� 0�̸� �� , i�� ������ element - ���� link[i]�� ������� �ʴٸ�, ����Ű�� �ִ� ��������� �ε����� ��ȯ��. 
		l->link[i]= next;
	}

	l->size++ ;
	return 1 ;
}

char * delete_arrlist (arrlist_t * l, char * s) //s�� ã�Ƽ� ����
{
	if (l->size == 0)
		return NULL ;

	int i, prev ; // prev�� ����ؾ���. ���� Ž���ϰ� �ִ� ����� ���� ���
	prev= 0; // �ʱⰪ���� prev=0
	i = l->first; // �ʱⰪ���� i = l->first
/* TODO =�� �Ͱ� �� ���� ���� ã�ƾ��� */

	while(i !=0){
		if (strcmp(s,l->data[i])==0){ // ���� s�� i��° �ε����� data���� ������ break
			break; //�� ã���ִ� ���� s�� �ε����� ã���� �ݺ� ��. 
		}
		prev = i; // �׸��� prev = i�� ���� -> ���� Ž���ϰ� �ִ� ���(i)�� prev�� �ǰ�
		i = l->link[i]; // i = link[i]�� ����. -> i�� ���� ��Ҹ� ����Ű�� ��. 
	}
	
	if (i==0){
		return NULL; // �׷��� �� ���Ƽ� i=0���� ���ԵǸ� �� ���� �� ���Ҵٴ� ���̹Ƿ�, ã�� �ִ� ���� s�� ���ٴ� ���̵Ǵϱ� NULL ��ȯ
	}
/*-----------------------------------*/

	char * r = l->data[i] ; // 
	l->data[i] = NULL ;

	if (i == l->first /*prev == 0*/) { // ������ ����Ʈ�� ù��° ����� ��� (�� ���� ������ ���)
		l->first = l->link[i] ; // first�� i�� ����Ű�� �ִ� ��� (link[i])�� �ȴ�.
	}
	else { // ������ ��尡 ù��° ��Ұ� �ƴ� ���
		l->link[prev] = l->link[i] ; // ���� ����Ű�� �ִ� (������ ��� i )�� ���� ���(prev)�� ���� ����Ű�� �ִ� ����� link(���� ���)�� ���� 
	}

	return r ;
}




void print_arrlist (arrlist_t * l)
{
	int i ;
	for (i = l->first ; i != 0 ; i = l->link[i]) { // link[i]�� ����ؼ� Ÿ��Ÿ�� ���鼭
		printf("%s ", l->data[i]) ; // data[i]�� ����Ѵ�. 
	}
	printf("\n") ;
}

void free_arrlist (arrlist_t * l) //arrlist�� free�ϴ� ���
{
	free(l->data) ; //data �ʵ��
	free(l->link) ; // link �ʵ��
	free(l) ; // ����Ʈ ��ü l�� free
}


int main ()
{
	arrlist_t * l = create_arrlist(30) ;

	insert_arrlist(l, "BAT") ;
	insert_arrlist(l, "CAT") ;
	insert_arrlist(l, "EAT") ;
	insert_arrlist(l, "FAT") ;
	insert_arrlist(l, "GAT") ;
	insert_arrlist(l, "HAT") ;
	insert_arrlist(l, "VAT") ;
	insert_arrlist(l, "WAT") ;

	delete_arrlist(l, "FAT") ;
	delete_arrlist(l, "VAT") ;

	print_arrlist(l) ;

	free_arrlist(l) ;

	return EXIT_SUCCESS ;
}
