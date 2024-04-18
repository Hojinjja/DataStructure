#include <stdio.h>
#include <stdlib.h>
#include "chstack.h"

int 
is_balanced (char * buf) //buf�� �޴´�
{
	stack_t * left = create_stack(256) ;

	for (int i = 0 ; buf[i] != '\0' ; i++) { //i�� 0���� ~ buf[i]�� ���ڿ��� ������� ������ ���� 
		
		//buf�� main�Լ��� ���ǵ� char�� ����Ʈ
		//���� ��ȣ ������ left ���ÿ� push
		if (buf[i] == '(' || buf[i] == '[' || buf[i] == '{' || buf[i] == '<') {
			push(left, buf[i]) ;
		}

		//�ݴ� ��ȣ ������ 
		else if (buf[i] == ')' || buf[i] == ']' || buf[i] == '}' || buf[i] == '>') {
			
			int r ; 	
			char top ;

			// r= pop�� ����/����
			// (0=������ �����.)
			// (1=������ ���ִ�) -> �������� top�� left���� pop�� �� �ֱ�. 
			r = pop(left, &top) ; 
			
			if (r == 0) { //r=0�� ��� -> ������ ����ִ�. (delete_stack)
				delete_stack(left) ;
				return 0 ; // ����
			}

			//buf[i](������ �ε���)�� ')'���� ��ȣ�ε�, top���� '('�� �ƴ϶�� ����
			if (buf[i] == ')' && top != '(') {
				delete_stack(left) ; //���� ����
				return 0 ;
			}

			//buf[i](������ �ε���)�� '}'���� ��ȣ�ε�, top���� '{'�� �ƴ϶�� ����			
			if (buf[i] == '}' && top != '{') {
				delete_stack(left) ; //���� ����
				return 0 ;
			}
			//buf[i](������ �ε���)�� ']'���� ��ȣ�ε�, top���� '['�� �ƴ϶�� ����			
			if (buf[i] == ']' && top != '[') {
				delete_stack(left) ;
				return 0 ;
			}
			//buf[i](������ �ε���)�� '>'���� ��ȣ�ε�, top���� '>'�� �ƴ϶�� ����			
			if (buf[i] == '>' && top != '<') {
				delete_stack(left) ;
				return 0 ;
			}

		}
		else {
			//unreachable
			// skip it over if it is the other case.
		}
	}

	if (get_size(left)) { // ���� get_size(left)�� ���� 0�� �ƴϸ� delete
		delete_stack(left) ;
		return 0 ;
	}
	
	delete_stack(left) ;
	return 1 ;
}


int 
main ()
{
	char buf[256] ;

	scanf("%255s", buf) ;

	if (is_balanced(buf)) {
		printf("balanced.\n") ;
	}
	else {
		printf("not balanced.\n") ;
	}

	return EXIT_SUCCESS ;
}
