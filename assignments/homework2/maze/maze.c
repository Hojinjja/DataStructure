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
        printf("##") ; // 외벽 
    printf("\n") ;
    for (i = 0 ; i < Y ; i++) {
        printf("##") ; // 왼쪽 외벽
        for (j = 0 ; j < X ; j++) {
            if (m[i][j] == WALL) 
                printf("==") ;
            else if (m[i][j] == PATH) 
                printf("@@") ;
            else 
                printf("  ") ;
        }
        printf("##\n") ; // 오른쪽 외벽
    }
    for (i = 0 ; i < X + 2 ; i++)
        printf("##") ;// 아래 외벽
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
        get_element(xs, i, &x) ; get_element(ys, i, &y) ; //get_elem -> get_element, 인자 주소로
        if (x == nx && y == ny) 
            return 1 ;
    }

    return 0 ;
}

void search () // 경로 찾기
{
    stack_t * xs = create_stack(400, sizeof(int)) ; //gstack이므로 사이즈 크기 지정.
    stack_t * ys = create_stack(400, sizeof(int)) ;
    stack_t * ds = create_stack(400, sizeof(int)) ;
    int zero = 0; //gstack이므로 따로 변수 설정
    int up = UP; //gstack이므로 따로 변수 설정

    push(xs, &zero) ; //push 인자 주소값으로
    push(ys, &zero) ;
    push(ds, &up) ; 
    

    while (is_empty(xs) == 0) {
        int x, y;
        int d ;
        pop(xs, &x) ; pop(ys, &y) ; pop(ds, &d) ; // pop 인자 주소값으로

        if (x == X - 1 && y == Y - 1) {
        // Step 출력을 위한 함수 
        int step = 1; // step 시작.
            for (int i = 0 ; i < get_size(xs) ; i++) {
                int x, y ;
                get_element(xs, i, &x) ; get_element(ys, i, &y) ; //get_elemnt로 바꿈, 인자 주소값으로
        
                 m[y][x] = PATH;
                 printf("Step %d: (%d,%d)\n", step++, y, x); // step이랑 경로 출력 
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
        push(xs, &x) ; push(ys, &y) ; //push 인자, 주소로.
        int next_direction = d + 1; //gstack이므로, 다음 방향 변수도 따로 할당. 
        push(ds, &next_direction) ;

        if (0 <= nx && nx < X && 0 <= ny && ny < Y) { // 외벽 안에 있는 x,y 좌표인지 확인 
            if (m[ny][nx] == 0) {
                if (is_in_path(xs, ys, nx, ny) == 0) {
                    push(xs, &nx) ; push(ys, &ny) ; push(ds, &zero) ; //주소 연산자, 초기 방향도 &zero로 설정 
                }
            }
        }
    }
}


int main ()
{
    load_map("maze2.txt") ;
    search() ; // Step 출력을 먼저하기 위해 순서 바꿈
    print_map() ;
    return EXIT_SUCCESS ;
}
