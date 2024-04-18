#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		int arrlen ;
		int size ;
		int first ;
		char ** data ;
		int * link ;
	}
	arrlist_t ;

arrlist_t * create_arrlist (int capacity)
{
	if (capacity <= 0) {
		return NULL ;
	}

	arrlist_t * l = (arrlist_t *) malloc(sizeof(arrlist_t)) ;
	if (l == NULL) {
		return NULL ;
	}
	l->arrlen = capacity + 1 ; //0번 주소는 안쓰기로 약속했으므로, 크기는 +1로 잡아준다. 
	l->size = 0 ;
	l->first = 0 ; //시작점 인덱스
	l->data = (char **) calloc(l->arrlen, sizeof(char *)) ;
	l->link = (int *) calloc(l->arrlen, sizeof(int)) ;
	memset(l->data,0,l->arrlen*sizeof(char*));
	memset(l->link, 0, l->arrlen * sizeof(int)) ; //초기화 0으로 
	if (l->data == NULL || l->link == NULL) {
		free(l) ;
		return NULL ;
	}

	return l ; 
}

int insert_arrlist (arrlist_t * l, char * s)
{
	if (s == NULL)
		return 0 ;

	if (l->size == l->arrlen - 1)
		return 0 ;

	//allocate an empty slot to store 's'
	int next = 1 ;
	while (l->data[next] != NULL) { //넣을 공간이 비었는지 
		next++ ;
	}
	l->data[next] = s ;
	l->link[next] = 0 ; // 그 다음 값이 없다. 0번 인덱스 가리키게

	/* TODO */ // 가장 마지막인 인덱스와 연결 - 링크값이 0인 경우를 찾아라 
	if (l->first == 0){ //싹 다 비어있는 경우
		l->first = next;
	}
	else{
		int i;
		// for (i= l->first ; l->link[i] !=0; i = l->link[i]); 
		i=l->first;
		while(l->link[i] != 0){
			i=l->link[i]; 
		} //link[i]가 0이면 끝 , i가 마지막 element 
		l->link[i]= next;
	}

	l->size++ ;

	return 1 ;
}

char * delete_arrlist (arrlist_t * l, char * s) //s를 찾아서 뺀다
{
	if (l->size == 0)
		return NULL ;

	int i, prev ;
	prev= 0;
	i = l->first;
/* TODO =뺄 것과 뺄 것의 앞을 찾아야함 */

	while(i !=0){
		if (strcmp(s,l->data[i])==0){
			break;
		}
		prev = i;
		i = l->link[i];
	}
	if (i==0){
		return NULL;
	}
/*-----------------------------------*/

		
	

	char * r = l->data[i] ;
	l->data[i] = NULL ;

	if (i == l->first/*prev == 0*/) {
		l->first = l->link[i] ;
	}
	else {
		l->link[prev] = l->link[i] ;
	}

	return r ;
}

void print_arrlist (arrlist_t * l)
{
	int i ;
	for (i = l->first ; i != 0 ; i = l->link[i]) {
		printf("%s ", l->data[i]) ;
	}
	printf("\n") ;
}

void free_arrlist (arrlist_t * l)
{
	free(l->data) ;
	free(l->link) ;
	free(l) ;
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
