#include <stdio.h>
#include <ctype.h> // ���� �Ǻ��� ���� isdigit �Լ�
#include "stack.h"

// �������� �켱���� ��ȯ
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// �������� �켱������ ���ϰ� ���ÿ��� ���� ǥ������� �ű�� �Լ�
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


// ���� ǥ����� ���� ǥ������� ��ȯ
void infix_to_postfix(const char* infix, char* postfix) {
    stack_t* op_stack = create_stack(100, sizeof(char));
    int p_idx = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isdigit(token)) { // ���ڴ� �ٷ� ����� �߰�
            postfix[p_idx++] = token;
        } else if (token == '(') { // ���� ��ȣ�� ���ÿ� Ǫ��
            push(op_stack, &token);
        } else if (token == ')') { // �ݴ� ��ȣ�� ������ ���� ��ȣ�� ���� ������ pop
            char top_op;
            pop(op_stack, &top_op);
            while (top_op != '(') {
                postfix[p_idx++] = top_op;
                pop(op_stack, &top_op);
            }
        } else { // ������ ó��
            process_operator(op_stack, token, postfix, &p_idx);
        }
    }

    // ���ÿ� ���� ��� �����ڸ� pop
    while (!is_empty(op_stack)) {
        char top_op;
        pop(op_stack, &top_op);
        postfix[p_idx++] = top_op;
    }
    postfix[p_idx] = '\0'; // ���ڿ� ����
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
