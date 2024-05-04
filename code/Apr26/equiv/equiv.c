#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"

int n_elements = 0 ; //element ����
int n_pairs = 0 ; // �׷��� ��

intlist_t ** equiv ; // intlist�� equiv

void find_equiv_class ()
{
	int * checked ; // üũ �ߴ��� ���ߴ���
	int n_checked = 0 ; // � üũ�ߴ���
	int i, j ; 

	checked = (int *) calloc(n_elements, sizeof(int)) ; // checked�� n_elements ���� ��ŭ sizeof(int) �޸� �Ҵ�
	
	for (i = 0 ; i < n_elements ; i++) { // element�� ������ŭ
		checked[i] = 0 ; // checked���� ��� 0���� ����
	}

	n_checked = 0 ; 
	while (n_checked < n_elements) { // n_checked(üũ�� ����)�� n_element(����� �� )���� ���� ���� -> ���� Ȯ�ε��� ���� ���� ã��. 
		
		intlist_t * a_class = intlist_create() ; // a_class�� �����ϰ� (intlist��)

		for (i = 0 ; i < n_elements ; i++) { // for ������ ����Ͽ� a_class�� �� ���ҿ� ���� ����� �ٸ� ���Ҹ� ã�´�. 
			if (checked[i] == 0) { // ���� i�� check ���ΰ� 0�̶�� (üũ�� ������ �ʾҴٸ�)
				intlist_add(a_class, i) ; // a_class�� �������
				checked[i] = 1 ; //�׸��� i�� üũ ���θ� 1�� �ٲٰ�
				n_checked++ ; // üũ�� ����� ������ 1 ���� ��Ŵ
				break ;
			}
		}

		i = 0 ; // �ٽ� i�� 0���� �����ϰ�
		while (i < intlist_len(a_class)) { // a_class�� ���� ��ŭ
			int e1 ; 
			intlist_get(a_class, i, &e1) ; // a_class�� i��° ���Ҹ� e1�� ����
			for (j = 0 ; j < intlist_len(equiv[e1]) ; j++) { //e1�� �����ϴ� equiv[e1]�� �� ���ҿ� ���� �ݺ� 
				int e2 ;
				intlist_get(equiv[e1], j, &e2) ; // equiv[e1]���� j ��° ���� ������ ->equiv[1]�̶�� �ϸ� 1�� ���õ� ������� ���ҵ��� ����.
				if (checked[e2] == 0) { // ���� üũ�� �Ǿ����� �ʴٸ�
					intlist_add(a_class, e2) ; // e2�� a_class�� �ְ�
					checked[e2] = 1 ; //e2�� üũ ���θ� 1�� �ٲ�
					n_checked++ ; //�׸��� üũ�� ���� ����
				}
			}
			i++ ; // �������� i++
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
