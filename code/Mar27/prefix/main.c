#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

typedef 
	enum { Number, Operator } 
	token_type ;

typedef  //union v 랑 token_type을 구조체로 만들어서 token_t로 만듦. 
	struct {
		union { // 둘 중 더 큰 메모리를 할당시켜줌 (하나의 메모리에 두개의 타입을 표현)
			int num ;  //만약 v.num하면 4byte 중 4byte 접근
			char op ; // v.op하면 4byte 중 1byte만 접근  
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

		if (get_size(exp) >= 3) {  // 스택에 3개 이상 들어오면
			token_t op, n1, n2 ; 
		// 3개를 pop 한다 그러면 보통 순서가 숫자->숫자->연산자 이므로
			pop(exp, &n2) ; // 스택 맨 위에 있던 숫자
			pop(exp, &n1) ; // 그 다음에 있던 숫자
			pop(exp, &op) ; // 그 다음에 있는 연산자

			if (n1.type == Number && n2.type == Number && op.type == Operator) {
				//꺼내온 3개가 숫자-숫자-연산자 순서면 계산을 진행
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
			else { // 만약 숫자-숫자-연산자 순서가 아니라면 아직 계산할 때가 아니므로 다시 push로 집어넣는다.
				push(exp, &op) ;
				push(exp, &n1) ;
				push(exp, &n2) ;
			}
		}
		
		scanf("%7s", buf) ; //버퍼에서 하나씩 읽어드린다

		if (buf[0] == ';') { // 만약 세미콜론이 읽히면 끝낸다
			continue ;
		}
		else if (isdigit(buf[0])) { // 만약 읽어온 buf 값이 숫자라면
			token_t tok ;
			tok.type = Number ;
			tok.v.num = atoi(buf) ; // 숫자로 만든다 atoi 
			push(exp, &tok) ;
		}
		else /* operator */ { // 만약 읽어온 buf 값이 숫자가 아니면, operator 
			token_t tok ;
			tok.type = Operator ;
			tok.v.op = buf[0] ;
			push(exp, &tok) ;
		}
	}

	token_t res ;
	pop(exp, &res) ;
	printf("%d\n", res.v.num) ;

	delete_stack(exp) ; // 스택이름이 exp

	return EXIT_SUCCESS ;
}


