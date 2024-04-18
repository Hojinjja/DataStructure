#include <stdio.h>
#include <stdlib.h>
#include "gstack.h" // gstack ��� ������ �����մϴ�.

typedef
    enum { 
        UP, DOWN, LEFT, RIGHT, DONE 
    } 
    dir ;

enum cell {
    EMPTY, WALL, PATH
} ;

int X, Y ;
int m[20][20] ;

void
print_map () // �� ����ϱ�
{
    int i, j ;

    for (i = 0 ; i < X + 2 ; i++)
        printf("##") ; // �ܺ� 
    printf("\n") ;
    for (i = 0 ; i < Y ; i++) {
        printf("##") ; // ���� �ܺ�
        for (j = 0 ; j < X ; j++) {
            if (m[i][j] == WALL) 
                printf("==") ;
            else if (m[i][j] == PATH) 
                printf("@@") ;
            else 
                printf("  ") ;
        }
        printf("##\n") ; // ������ �ܺ�
    }
    for (i = 0 ; i < X + 2 ; i++)
        printf("##") ;// �Ʒ� �ܺ�
    printf("\n") ;
}

void load_map(char * filename) // �� �ε��ϱ�
{
    FILE * fp = fopen(filename, "r") ;
    fscanf(fp, "%d %d", &X, &Y) ;
    for (int i = 0 ; i < Y ; i++) {
        for (int j = 0 ; j < X ; j++) {
            fscanf(fp, "%d", &(m[i][j])) ;
        }
    }
    fclose(fp) ;
}

int is_in_path(stack_t * xs, stack_t * ys, int nx, int ny) // �̹� ��ΰ� ���ÿ� �ִ���
{
    int i ;
    for (i = 0 ; i < get_size(xs) ; i++) {
        int x, y ;
        get_element(xs, i, &x) ; get_element(ys, i, &y) ; //get_elem -> get_element, ���� �ּҷ�
        if (x == nx && y == ny) 
            return 1 ;
    }

    return 0 ;
}

void search () // ��� ã��
{
    stack_t * xs = create_stack(400, sizeof(int)) ; //gstack�̹Ƿ� ������ ũ�� ����.
    stack_t * ys = create_stack(400, sizeof(int)) ;
    stack_t * ds = create_stack(400, sizeof(int)) ;
    int zero = 0; //gstack�̹Ƿ� ���� ���� ����
    int up = UP; //gstack�̹Ƿ� ���� ���� ����

    push(xs, &zero) ; //push ���� �ּҰ�����
    push(ys, &zero) ;
    push(ds, &up) ; 
    

    while (is_empty(xs) == 0) {
        int x, y;
        int d ;
        pop(xs, &x) ; pop(ys, &y) ; pop(ds, &d) ; // pop ���� �ּҰ�����

        if (x == X - 1 && y == Y - 1) {
        // Step ����� ���� �Լ� 
        int step = 1; // step ����.
            for (int i = 0 ; i < get_size(xs) ; i++) {
                int x, y ;
                get_element(xs, i, &x) ; get_element(ys, i, &y) ; //get_elemnt�� �ٲ�, ���� �ּҰ�����
        
                 m[y][x] = PATH;
                 printf("Step %d: (%d,%d)\n", step++, y, x); // step�̶� ��� ��� 
            }
        return ;
        }

        if (d == 4) {
            continue ;
        }

        int nx, ny ; //nx = next_x , ny = next_y 
        switch (d) {
            case UP: {
                nx = x ;
                ny = y - 1 ;
                break ;
            }
            case DOWN: {
                nx = x ;
                ny = y + 1 ;
                break ; 
            }
            case LEFT: {
                nx = x - 1 ;
                ny = y ;
                break ; 
            }
            case RIGHT: {
                nx = x + 1 ;
                ny = y ;
                break ;
            }
        }
        push(xs, &x) ; push(ys, &y) ; //push ����, �ּҷ�.
        int next_direction = d + 1; //gstack�̹Ƿ�, ���� ���� ������ ���� �Ҵ�. 
        push(ds, &next_direction) ;

        if (0 <= nx && nx < X && 0 <= ny && ny < Y) { // �ܺ� �ȿ� �ִ� x,y ��ǥ���� Ȯ�� 
            if (m[ny][nx] == 0) {
                if (is_in_path(xs, ys, nx, ny) == 0) {
                    push(xs, &nx) ; push(ys, &ny) ; push(ds, &zero) ; //�ּ� ������, �ʱ� ���⵵ &zero�� ���� 
                }
            }
        }
    }
}


int main ()
{
    load_map("maze2.txt") ;
    search() ; // Step ����� �����ϱ� ���� ���� �ٲ�
    print_map() ;
    return EXIT_SUCCESS ;
}
