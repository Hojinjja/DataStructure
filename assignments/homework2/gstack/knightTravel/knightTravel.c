#include <stdio.h>
#include <stdlib.h>
#include "gstack.h"

//방향 설정 
typedef
    enum{
        UP_RIGHT,UP_LEFT,DOWN_RIGHT,DOWN_LEFT,
        RIGHT_UP,RIGHT_DOWN,LEFT_UP,LEFT_DOWN
    }
    dir ; 



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
    int up_right = UP_RIGHT;

    push(xs, &zero) ;
    push(ys, &zero) ;
    push(ds, &up_right) ;
    

    while (is_empty(xs) == 0) {
        int x, y;
        int d ;
        pop(xs, &x) ; pop(ys, &y) ; pop(ds, &d) ;
        return ;
    


        if (d == 9) {
            continue ;
        }

        int nx, ny ;
        switch (d) {
            case UP_RIGHT: {
                nx = x + 1 ;
                ny = y + 2 ;
                break ;
            }
            case UP_LEFT: {
                nx = x - 1;
                ny = y + 2 ;
                break ; 
            }
            case RIGHT_UP: {
                nx = x + 2 ;
                ny = y + 1 ;
                break ; 
            }
            case LEFT_DOWN: {
                nx = x + 2 ;
                ny = y - 1;
                break ;
            }case LEFT_UP: {
                nx = x + 2 ;
                ny = y - 1;
                break ;
            }case RIGHT_DOWN: {
                nx = x + 2 ;
                ny = y - 1;
                break ;
            }case DOWN_LEFT: {
                nx = x + 2 ;
                ny = y - 1;
                break ;
            }case DOWN_RIGHT: {
                nx = x + 2 ;
                ny = y - 1;
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



// 나이트 이동경로 넣을 스택 생성
// 나이트 이동경로 계산 (하나씩 돌려봐서)

//이미 경로가 스택에 있는지 확인 

// 경로 출력하기 

//경로 찾기 

//