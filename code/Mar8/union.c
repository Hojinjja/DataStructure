#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct membership_t { //membership_t 정의 (union)
	enum member_type {student, prof} type ;
	union { 
		long long student_number ; //학번
		char office[20] ; //주소
	} ;
} ;


struct person {
	char name[10] ; 
	int age ;
	struct membership_t membership ; //membership_t를 person의 일부로 둔다. 
} ;


int main ()
{
	struct person shin ; //person 구조의 객체 shin을 생성

	strcpy(shin.name, "Shin Hong") ; // shin.name에 "Shin Hong"문자열 복사
	shin.age = 38 ;
	shin.membership.type = prof ;
	strcpy(shin.membership.office, "316 S4-1") ;
	

	printf("%ld\n", sizeof(struct person)) ;

	return EXIT_SUCCESS ;
}
