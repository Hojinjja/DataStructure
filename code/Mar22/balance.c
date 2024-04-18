#include <stdio.h>
#include <stdlib.h>
#include "chstack.h"

int 
is_balanced (char * buf) //buf를 받는다
{
	stack_t * left = create_stack(256) ;

	for (int i = 0 ; buf[i] != '\0' ; i++) { //i는 0부터 ~ buf[i]의 문자열이 비어있지 않을때 까지 
		
		//buf는 main함수에 정의된 char형 리스트
		//여는 괄호 만나면 left 스택에 push
		if (buf[i] == '(' || buf[i] == '[' || buf[i] == '{' || buf[i] == '<') {
			push(left, buf[i]) ;
		}

		//닫는 괄호 만나면 
		else if (buf[i] == ')' || buf[i] == ']' || buf[i] == '}' || buf[i] == '>') {
			
			int r ; 	
			char top ;

			// r= pop의 성공/실패
			// (0=스택이 비었다.)
			// (1=스택이 차있다) -> 차있으면 top에 left에서 pop한 값 넣기. 
			r = pop(left, &top) ; 
			
			if (r == 0) { //r=0인 경우 -> 스택이 비어있다. (delete_stack)
				delete_stack(left) ;
				return 0 ; // 실패
			}

			//buf[i](마지막 인덱스)가 ')'닫힌 괄호인데, top값이 '('이 아니라면 실패
			if (buf[i] == ')' && top != '(') {
				delete_stack(left) ; //스택 삭제
				return 0 ;
			}

			//buf[i](마지막 인덱스)가 '}'닫힌 괄호인데, top값이 '{'이 아니라면 실패			
			if (buf[i] == '}' && top != '{') {
				delete_stack(left) ; //스택 삭제
				return 0 ;
			}
			//buf[i](마지막 인덱스)가 ']'닫힌 괄호인데, top값이 '['이 아니라면 실패			
			if (buf[i] == ']' && top != '[') {
				delete_stack(left) ;
				return 0 ;
			}
			//buf[i](마지막 인덱스)가 '>'닫힌 괄호인데, top값이 '>'이 아니라면 실패			
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

	if (get_size(left)) { // 만약 get_size(left)의 값이 0이 아니면 delete
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
