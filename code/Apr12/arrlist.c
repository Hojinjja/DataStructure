#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		int arrlen ; //배열길이
		int size ; // 현재 리스트 요소 개수
		int first ; // 연결리스트의 첫번째 요소 인덱스
		char ** data ; // 인덱스의 value
		int * link ; // 데이터의 다음 요소를 가르킨다. 
	}
	arrlist_t ;


/******************
* arrlist 만들기 
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

	l->arrlen = capacity + 1 ; //0번 주소는 안쓰기로 약속했으므로, 크기는 +1로 잡아준다. - array 길이
	l->size = 0 ; // 초기 size는 0 
	l->first = 0 ; //시작점 인덱스도 0 // 1이 맞지 않나?? 원래 코드는 0 
	l->data = (char **) calloc(l->arrlen, sizeof(char *)) ; // 들어올 데이터 타입만큼의 크기 
	l->link = (int *) calloc(l->arrlen, sizeof(int)) ; // 
	memset(l->data, 0, l->arrlen * sizeof(char*)); // data 필드를 초기화 하는 부분 arrlen * sizeof(char*)으로 
	memset(l->link, 0, l->arrlen * sizeof(int)) ; // link 필드를 초기화 하는 부분 arrlen * sizeof(int) 만큼
	
	if (l->data == NULL || l->link == NULL) { // 제대로 할당이 이루어졌는지 확인하는 부분 , 만약 data or link 부분이 NULL이면 할당 실패. 
		free(l) ;
		return NULL ;
	}

	return l ; 
}


/*
* arrlist에 s를 집어 넣기. 
*/
int insert_arrlist (arrlist_t * l, char * s)
{
	if (s == NULL) // s가 NULL 인 경우.
		return 0 ;

	if (l->size == l->arrlen - 1) // full 난 경우. 
		return 0 ;

	// allocate an empty slot to store s
	int next = 1 ; // first의 다음인 1
	
	while (l->data[next] != NULL) { //넣을 공간이 비었는지 확인
		next++ ; // data의 next 인덱스가 NULL이 아니라면 next ++ 한다.  
	}
	l->data[next] = s ; // 비어있는 인덱스(next)를 발견하면 data[]에 넣는다.
	l->link[next] = 0 ; // 그 다음 값이 없다. next는 0이다. (NULL이 더 맞지 않나?)------------------------------ 

	/* TODO */ // 가장 마지막인 인덱스와 연결 - 링크값이 0인 경우를 찾아라 
	if (l->first == 0){ //싹 다 비어있는 경우 first가 아무도 가르키고 있지 않다. 
		l->first = next; // l의 first는 next가 된다. (그러면 next가 l의 first가 된다. ) 
	}
	else{
		int i;
		i=l->first;
		while(l->link[i] != 0){
			i=l->link[i]; 
		} //link[i]가 0이면 끝 , i가 마지막 element - 만약 link[i]가 비어있지 않다면, 가리키고 있는 다음요소의 인덱스를 반환함. 
		l->link[i]= next;
	}

	l->size++ ;
	return 1 ;
}

char * delete_arrlist (arrlist_t * l, char * s) //s를 찾아서 뺀다
{
	if (l->size == 0)
		return NULL ;

	int i, prev ; // prev를 사용해야함. 현재 탐색하고 있는 노드의 이전 노드
	prev= 0; // 초기값으로 prev=0
	i = l->first; // 초기값으로 i = l->first
/* TODO =뺄 것과 뺄 것의 앞을 찾아야함 */

	while(i !=0){
		if (strcmp(s,l->data[i])==0){ // 만약 s랑 i번째 인덱스의 data값이 같으면 break
			break; //즉 찾고있는 문자 s의 인덱스를 찾으면 반복 끝. 
		}
		prev = i; // 그리고 prev = i로 설정 -> 현재 탐색하고 있는 노드(i)가 prev가 되고
		i = l->link[i]; // i = link[i]로 설정. -> i는 다음 요소를 가리키게 됨. 
	}
	
	if (i==0){
		return NULL; // 그렇게 쭉 돌아서 i=0까지 오게되면 한 바퀴 다 돌았다는 뜻이므로, 찾고 있는 문자 s가 없다는 뜻이되니까 NULL 반환
	}
/*-----------------------------------*/

	char * r = l->data[i] ; // 
	l->data[i] = NULL ;

	if (i == l->first /*prev == 0*/) { // 삭제한 리스트가 첫번째 요소인 경우 (맨 앞을 삭제한 경우)
		l->first = l->link[i] ; // first는 i가 가리키고 있던 요소 (link[i])가 된다.
	}
	else { // 삭제한 노드가 첫번째 요소가 아닌 경우
		l->link[prev] = l->link[i] ; // 현재 가리키고 있는 (삭제할 노드 i )의 이전 노드(prev)는 현재 가리키고 있는 노드의 link(다음 요소)로 설정 
	}

	return r ;
}




void print_arrlist (arrlist_t * l)
{
	int i ;
	for (i = l->first ; i != 0 ; i = l->link[i]) { // link[i]로 계속해서 타고타고 가면서
		printf("%s ", l->data[i]) ; // data[i]를 출력한다. 
	}
	printf("\n") ;
}

void free_arrlist (arrlist_t * l) //arrlist를 free하는 경우
{
	free(l->data) ; //data 필드와
	free(l->link) ; // link 필드와
	free(l) ; // 리스트 자체 l을 free
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
