#include <stdio.h>
#include <stdlib.h>
#include "stack.h" 

// 체스판에 퀸을 배치시키는데 성공하면, 그 위치를 스택에 넣는 코드 

int row (int cell)
{
	return cell / 8 ;
}

int col (int cell)
{
	return cell % 8 ;
}

int is_feasible (stack_t * queens) //충돌하는지 확인 -> 충돌시 0, 충돌 x 시 1 
{
	int board[8][8] ;
	int c, r ;

	for (r = 0 ; r < 8 ; r++) { // y축에 해당하는 r
		for (c = 0 ; c < 8 ; c++) { // x축에 해당하는 c 에 대하여
			board[r][c] = 0 ; // 각 자리를 0으로 초기화
		}
	}

	for (int i = 0 ; i < get_size(queens) ; i++) { //스택(queen) 사이즈만큼 반복
		int cell ;
		get_elem(queens, i, &cell) ; // queens 스택의 i번째 인덱스 값을 cell에 저장
		
		int r = row(cell) ;
		int c = col(cell) ;
	
		if (board[r][c] != 0) { //만약 r,c가 0이 아니라면 -> 이미 그 자리에 퀸이 존재한다면
			return 0 ; // return 0
		}

		int x, y ;
		for (y = 0 ; y < 8 ; y++) {
			board[y][c] = 1 ; // (c,r)에 퀸이 위치했을 때 x축은 c이고 그 수직으로 모두 1
		}
		for (x = 0 ; x < 8 ; x++) { 
			board[r][x] = 1 ; // (c,r)에 퀸이 위치했을 때 y축은 r이고 그 수평으로 모두 1
		}

		y = r + 1 ; x = c + 1 ; // 오른쪽 위 대각선
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y += 1 ; x += 1 ;
		}

		y = r + 1 ; x = c - 1 ; // 왼쪽 위 대각선
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y += 1 ; x -= 1 ;
		}

		y = r - 1 ; x = c + 1 ; // 오른쪽 아래 대각선
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y -= 1 ; x += 1 ;
		}

		y = r - 1 ; x = c - 1 ; // 왼쪽 아래 대각선
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y -= 1 ; x -= 1 ;
		}

	}

	return 1;
}


int main ()
{
	stack_t * queens = create_stack(8) ;

	push(queens, 0) ; // 먼저 0번째 칸에 퀸 배치 
	while (!is_empty(queens)) { // 스택이 비어 있지 않다면 계속해서 반복
		int latest_queen ;
		top(queens, &latest_queen) ;

		if (latest_queen == 64) { // 만약 마지막 퀸의 위치가 64라면(마지막 칸)
			pop(queens, &latest_queen) ; //  배치한 퀸(64에 위치한)을 스택에서 제거한다. 
			if (!is_empty(queens)) {  // 만약 스택이 비어있지 않다면
				pop(queens, &latest_queen) ; // 퀸을 하나 더 팝하고
				push(queens, latest_queen + 1) ; // 그 퀸을 다음 칸에 배치시킨다
			}
			else { // 만약 스택이 비었다면 break (해 없음)
				break ;
			}
			continue ; // 만약 마지막 퀸의 위치가 64가 아니면 그냥 건너뛰고 
		}

		if (is_feasible(queens)) { // is_feasible이 1이라면 충돌x 이므로 
			
			if (get_size(queens) == 8) { // 만약 스택(queens)의 크기가 8로 꽉찼다면
				for (int i = 0 ; i < 8 ; i++) {	
					int queen ;
					get_elem(queens, i, &queen) ; // 각 퀸의 위치를 queen에 추출하고
					printf("%d ", queen) ; // 퀸의 위치를 프린트한다.
				}
				printf("\n") ;
				//return 0 ;

				//다음 경우의 수를 찾기 위한 코드
				int lastest_queen ;
				pop(queens, &latest_queen) ; // 가장 마지막에 배치한 퀸의 위치를 latest_queen에 저장하고 
				push(queens, latest_queen + 1) ; // latest_queen+1에 배치시켜본다. 
			}
			else { // 만약 스택의 크기가 8로 꽉 차지 않았다면 
				int latest_queen ;
				top(queens, &latest_queen) ; // 마지막에 위치한 퀸의 위치를 latest_queen에 저장하고
				push(queens, latest_queen + 1) ; // 다음 퀸을 latest_queen+1에 배치한다 
			}

		}else { // 만약 퀸끼리 충돌한다면 
			int lastest_queen ; 
			pop(queens, &latest_queen) ; // 마지막 퀸을 pop하고
			push(queens, latest_queen + 1) ; // 그 퀸을 마지막 위치 +1에 push한다
		}

	}
	delete_stack(queens) ;

	return EXIT_FAILURE ;
}

