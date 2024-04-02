#include <stdio.h>
#include <stdlib.h>
#include "gstack.h" // gstack 헤더 파일을 포함합니다.

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
print_map () // 맵 출력하기
{
    int i, j ;

    for (i = 0 ; i < X + 2 ; i++)
        printf("==") ;
    printf("\n") ;
    for (i = 0 ; i < Y ; i++) {
        printf("==") ;
        for (j = 0 ; j < X ; j++) {
            if (m[i][j] == WALL) 
                printf("==") ;
            else if (m[i][j] == PATH) 
                printf("@@") ;
            else 
                printf("  ") ;
        }
        printf("==\n") ;
    }
    for (i = 0 ; i < X + 2 ; i++)
        printf("==") ;
    printf("\n") ;
}

void load_map(char * filename) // 맵 로드하기
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

int is_in_path(stack_t * xs, stack_t * ys, int nx, int ny) // 이미 경로가 스택에 있는지
{
    int i ;
    for (i = 0 ; i < get_size(xs) ; i++) {
        int x, y ;
        get_element(xs, i, &x) ; get_element(ys, i, &y) ;
        if (x == nx && y == ny) 
            return 1 ;
    }

    return 0 ;
}

void search () // 경로 찾기
{
    stack_t * xs = create_stack(400, sizeof(int)) ;
    stack_t * ys = create_stack(400, sizeof(int)) ;
    stack_t * ds = create_stack(400, sizeof(int)) ;
    int zero = 0; 
    int up = UP;

    push(xs, &zero) ;
    push(ys, &zero) ;
    push(ds, &up) ;
    

    while (is_empty(xs) == 0) {
        int x, y;
        int d ;
        pop(xs, &x) ; pop(ys, &y) ; pop(ds, &d) ;

        if (x == X - 1 && y == Y - 1) {
        int step = 1; // 단계 번호를 시작합니다.
        for (int i = 0 ; i < get_size(xs) ; i++) {
        int x, y ;
        get_element(xs, i, &x) ; get_element(ys, i, &y) ;
        
        m[y][x] = PATH;
        printf("Step %d: (%d,%d)\n", step++, y, x); // 단계 번호와 함께 경로 출력
    }
    return ;
}

        if (d == 4) {
            continue ;
        }

        int nx, ny ;
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
        push(xs, &x) ; push(ys, &y) ; 
        int next_direction = d + 1; 
        push(ds, &next_direction) ;

        if (0 <= nx && nx < X && 0 <= ny && ny < Y) {
            if (m[ny][nx] == 0) {
                if (is_in_path(xs, ys, nx, ny) == 0) {
                    push(xs, &nx) ; push(ys, &ny) ; push(ds, &zero) ;
                }
            }
        }
    }
}


int main ()
{
    load_map("maze2.txt") ;
    search() ;
    

    print_map() ;

    

    
    return EXIT_SUCCESS ;
}
