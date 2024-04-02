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

int row (int cell)
{
    return cell / 8 ; 
}

int col (int cell)
{
    return cell % 8;
}
// 나이트 이동경로 넣을 스택 생성
int knight_travel()
{
    int board[8][8];
    int c,r; 

    
    
}

// 나이트 이동경로 계산 (하나씩 돌려봐서)

//이미 경로가 스택에 있는지 확인 



// 경로 출력하기 






//경로 찾기 


//