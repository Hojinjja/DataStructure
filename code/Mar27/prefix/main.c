#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

typedef 
	enum { Number, Operator } 
	token_type ;

typedef  //union v �� token_type�� ����ü�� ���� token_t�� ����. 
	struct {
		union { // �� �� �� ū �޸𸮸� �Ҵ������ (�ϳ��� �޸𸮿� �ΰ��� Ÿ���� ǥ��)
			int num ;  //���� v.num�ϸ� 4byte �� 4byte ����
			char op ; // v.op�ϸ� 4byte �� 1byte�� ����  
		} v ;
		token_type type ;
	} 
	token_t ;

void
print_stack (stack_t * st)
{
	int i ;
	token_t t ;
	
	printf("[" ) ;
	for (i = 0 ; i < get_size(st); i++) {
		get_element(st, i, &t) ;
		if (t.type == Number)
			printf("(%d) ", t.v.num) ;
		else /* t.e.type == Operator */
			printf("<%c> ", t.v.op) ;
	}
	printf("]\n") ;
}

int
main () 
{
	stack_t * exp ;
	exp = create_stack(100, sizeof(token_t)) ;
	
	char buf[8] = { 0x0 } ;
	while (!(buf[0] == ';' && get_size(exp) == 1)) {
		print_stack(exp) ;

		if (get_size(exp) >= 3) {  // ���ÿ� 3�� �̻� ������
			token_t op, n1, n2 ; 
		// 3���� pop �Ѵ� �׷��� ���� ������ ����->����->������ �̹Ƿ�
			pop(exp, &n2) ; // ���� �� ���� �ִ� ����
			pop(exp, &n1) ; // �� ������ �ִ� ����
			pop(exp, &op) ; // �� ������ �ִ� ������

			if (n1.type == Number && n2.type == Number && op.type == Operator) {
				//������ 3���� ����-����-������ ������ ����� ����
				token_t res ;

				res.type = Number ;
				switch (op.v.op) {
					case '+':
						res.v.num = n1.v.num + n2.v.num ;
						break ;
					case '-':
						res.v.num = n1.v.num - n2.v.num ;
						break ;
					case '*':
						res.v.num = n1.v.num * n2.v.num ;
						break ;
					case '/':
						res.v.num = n1.v.num / n2.v.num ;
						break ;
				}
				push(exp, &res) ;
				continue ;
			}
			else { // ���� ����-����-������ ������ �ƴ϶�� ���� ����� ���� �ƴϹǷ� �ٽ� push�� ����ִ´�.
				push(exp, &op) ;
				push(exp, &n1) ;
				push(exp, &n2) ;
			}
		}
		
		scanf("%7s", buf) ; //���ۿ��� �ϳ��� �о�帰��

		if (buf[0] == ';') { // ���� �����ݷ��� ������ ������
			continue ;
		}
		else if (isdigit(buf[0])) { // ���� �о�� buf ���� ���ڶ��
			token_t tok ;
			tok.type = Number ;
			tok.v.num = atoi(buf) ; // ���ڷ� ����� atoi 
			push(exp, &tok) ;
		}
		else /* operator */ { // ���� �о�� buf ���� ���ڰ� �ƴϸ�, operator 
			token_t tok ;
			tok.type = Operator ;
			tok.v.op = buf[0] ;
			push(exp, &tok) ;
		}
	}

	token_t res ;
	pop(exp, &res) ;
	printf("%d\n", res.v.num) ;

	delete_stack(exp) ; // �����̸��� exp

	return EXIT_SUCCESS ;
}


