#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"

int n_elements = 0 ; //element 개수
int n_pairs = 0 ; // 그룹의 수

intlist_t ** equiv ; // intlist인 equiv

void find_equiv_class ()
{
	int * checked ; // 체크 했는지 안했는지
	int n_checked = 0 ; // 몇개 체크했는지
	int i, j ; 

	checked = (int *) calloc(n_elements, sizeof(int)) ; // checked는 n_elements 개수 만큼 sizeof(int) 메모리 할당
	
	for (i = 0 ; i < n_elements ; i++) { // element의 개수만큼
		checked[i] = 0 ; // checked들을 모두 0으로 세팅
	}

	n_checked = 0 ; 
	while (n_checked < n_elements) { // n_checked(체크된 개수)가 n_element(요소의 수 )보다 작을 동안 -> 아직 확인되지 않은 원소 찾기. 
		
		intlist_t * a_class = intlist_create() ; // a_class를 생성하고 (intlist임)

		for (i = 0 ; i < n_elements ; i++) { // for 루프를 사용하여 a_class의 각 원소에 대해 연결된 다른 원소를 찾는다. 
			if (checked[i] == 0) { // 만약 i의 check 여부가 0이라면 (체크가 되있지 않았다면)
				intlist_add(a_class, i) ; // a_class에 집어넣음
				checked[i] = 1 ; //그리고 i의 체크 여부를 1로 바꾸고
				n_checked++ ; // 체크된 요소의 개수를 1 증가 시킴
				break ;
			}
		}

		i = 0 ; // 다시 i를 0으로 세팅하고
		while (i < intlist_len(a_class)) { // a_class의 길이 만큼
			int e1 ; 
			intlist_get(a_class, i, &e1) ; // a_class의 i번째 원소를 e1에 저장
			for (j = 0 ; j < intlist_len(equiv[e1]) ; j++) { //e1에 대응하는 equiv[e1]의 각 원소에 대해 반복 
				int e2 ;
				intlist_get(equiv[e1], j, &e2) ; // equiv[e1]에서 j 번째 원소 가져옴 ->equiv[1]이라고 하면 1과 관련된 등가관계인 원소들이 있음.
				if (checked[e2] == 0) { // 만약 체크가 되어있지 않다면
					intlist_add(a_class, e2) ; // e2를 a_class에 넣고
					checked[e2] = 1 ; //e2의 체크 여부를 1로 바꿈
					n_checked++ ; //그리고 체크한 개수 증가
				}
			}
			i++ ; // 다했으면 i++
		}

		for (i = 0 ; i < intlist_len(a_class) ; i++) {
			int e ;
			intlist_get(a_class, i, &e) ;
			printf("%d ", e) ;
		}
		printf("\n") ;

		intlist_free(a_class) ;
	}

}



int main ()
{
	FILE * fp = fopen("data", "r") ;
	int i, j ;


	fscanf(fp, "%d %d", &n_elements, &n_pairs) ;

	equiv = (intlist_t **) calloc(n_elements, sizeof(intlist_t *)) ;

	for (i = 0 ; i < n_elements ; i++) {
		equiv[i] = intlist_create() ;
	}
	
	for (i = 0 ; i < n_pairs ; i++) {
		int a, b ;
		fscanf(fp, "%d %d", &a, &b) ;
		
		intlist_add(equiv[a], b) ;
		intlist_add(equiv[b], a) ;
	}

	find_equiv_class() ;

	free(equiv) ;
	fclose(fp) ;

	return EXIT_SUCCESS ;
}
