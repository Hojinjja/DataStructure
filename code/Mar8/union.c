#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct membership_t { //membership_t ���� (union)
	enum member_type {student, prof} type ;
	union { 
		long long student_number ; //�й�
		char office[20] ; //�ּ�
	} ;
} ;


struct person {
	char name[10] ; 
	int age ;
	struct membership_t membership ; //membership_t�� person�� �Ϻη� �д�. 
} ;


int main ()
{
	struct person shin ; //person ������ ��ü shin�� ����

	strcpy(shin.name, "Shin Hong") ; // shin.name�� "Shin Hong"���ڿ� ����
	shin.age = 38 ;
	shin.membership.type = prof ;
	strcpy(shin.membership.office, "316 S4-1") ;
	

	printf("%ld\n", sizeof(struct person)) ;

	return EXIT_SUCCESS ;
}
