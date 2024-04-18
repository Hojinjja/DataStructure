#include <stdio.h>
#include <ctype.h> // 숫자 판별을 위한 isdigit 함수
#include "stack.h"

// 연산자의 우선순위 반환
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 연산자의 우선순위를 비교하고 스택에서 후위 표기식으로 옮기는 함수
void process_operator(stack_t* op_stack, char op, char* postfix, int* p_idx) {
    char top_op;

    while (!is_empty(op_stack)) {
        get_element(op_stack, get_size(op_stack) - 1, &top_op);
        if (precedence(top_op) >= precedence(op)) {
            pop(op_stack, &top_op);
            postfix[(*p_idx)++] = top_op;
        } else {
            break;
        }
    }
    push(op_stack, &op);
}


// 중위 표기식을 후위 표기식으로 변환
void infix_to_postfix(const char* infix, char* postfix) {
    stack_t* op_stack = create_stack(100, sizeof(char));
    int p_idx = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isdigit(token)) { // 숫자는 바로 결과에 추가
            postfix[p_idx++] = token;
        } else if (token == '(') { // 여는 괄호는 스택에 푸시
            push(op_stack, &token);
        } else if (token == ')') { // 닫는 괄호를 만나면 여는 괄호를 만날 때까지 pop
            char top_op;
            pop(op_stack, &top_op);
            while (top_op != '(') {
                postfix[p_idx++] = top_op;
                pop(op_stack, &top_op);
            }
        } else { // 연산자 처리
            process_operator(op_stack, token, postfix, &p_idx);
        }
    }

    // 스택에 남은 모든 연산자를 pop
    while (!is_empty(op_stack)) {
        char top_op;
        pop(op_stack, &top_op);
        postfix[p_idx++] = top_op;
    }
    postfix[p_idx] = '\0'; // 문자열 종료
    delete_stack(op_stack);
}

int main() {
    char infix[] = "3+(2*5)-(1/4)";
    char postfix[100];

    infix_to_postfix(infix, postfix);
    printf("Infix: %s\n", infix);
    printf("Postfix: %s\n", postfix);

    return 0;
}
