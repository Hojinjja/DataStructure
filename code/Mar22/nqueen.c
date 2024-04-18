#include <stdio.h>
#include <stdlib.h>
#include "stack.h" 

// ü���ǿ� ���� ��ġ��Ű�µ� �����ϸ�, �� ��ġ�� ���ÿ� �ִ� �ڵ� 

int row (int cell)
{
	return cell / 8 ;
}

int col (int cell)
{
	return cell % 8 ;
}

int is_feasible (stack_t * queens) //�浹�ϴ��� Ȯ�� -> �浹�� 0, �浹 x �� 1 
{
	int board[8][8] ;
	int c, r ;

	for (r = 0 ; r < 8 ; r++) { // y�࿡ �ش��ϴ� r
		for (c = 0 ; c < 8 ; c++) { // x�࿡ �ش��ϴ� c �� ���Ͽ�
			board[r][c] = 0 ; // �� �ڸ��� 0���� �ʱ�ȭ
		}
	}

	for (int i = 0 ; i < get_size(queens) ; i++) { //����(queen) �����ŭ �ݺ�
		int cell ;
		get_elem(queens, i, &cell) ; // queens ������ i��° �ε��� ���� cell�� ����
		
		int r = row(cell) ;
		int c = col(cell) ;
	
		if (board[r][c] != 0) { //���� r,c�� 0�� �ƴ϶�� -> �̹� �� �ڸ��� ���� �����Ѵٸ�
			return 0 ; // return 0
		}

		int x, y ;
		for (y = 0 ; y < 8 ; y++) {
			board[y][c] = 1 ; // (c,r)�� ���� ��ġ���� �� x���� c�̰� �� �������� ��� 1
		}
		for (x = 0 ; x < 8 ; x++) { 
			board[r][x] = 1 ; // (c,r)�� ���� ��ġ���� �� y���� r�̰� �� �������� ��� 1
		}

		y = r + 1 ; x = c + 1 ; // ������ �� �밢��
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y += 1 ; x += 1 ;
		}

		y = r + 1 ; x = c - 1 ; // ���� �� �밢��
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y += 1 ; x -= 1 ;
		}

		y = r - 1 ; x = c + 1 ; // ������ �Ʒ� �밢��
		while (0 <= y && y < 8 && 0 <= x && x < 8) {
			board[y][x] = 1 ;
			y -= 1 ; x += 1 ;
		}

		y = r - 1 ; x = c - 1 ; // ���� �Ʒ� �밢��
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

	push(queens, 0) ; // ���� 0��° ĭ�� �� ��ġ 
	while (!is_empty(queens)) { // ������ ��� ���� �ʴٸ� ����ؼ� �ݺ�
		int latest_queen ;
		top(queens, &latest_queen) ;

		if (latest_queen == 64) { // ���� ������ ���� ��ġ�� 64���(������ ĭ)
			pop(queens, &latest_queen) ; //  ��ġ�� ��(64�� ��ġ��)�� ���ÿ��� �����Ѵ�. 
			if (!is_empty(queens)) {  // ���� ������ ������� �ʴٸ�
				pop(queens, &latest_queen) ; // ���� �ϳ� �� ���ϰ�
				push(queens, latest_queen + 1) ; // �� ���� ���� ĭ�� ��ġ��Ų��
			}
			else { // ���� ������ ����ٸ� break (�� ����)
				break ;
			}
			continue ; // ���� ������ ���� ��ġ�� 64�� �ƴϸ� �׳� �ǳʶٰ� 
		}

		if (is_feasible(queens)) { // is_feasible�� 1�̶�� �浹x �̹Ƿ� 
			
			if (get_size(queens) == 8) { // ���� ����(queens)�� ũ�Ⱑ 8�� ��á�ٸ�
				for (int i = 0 ; i < 8 ; i++) {	
					int queen ;
					get_elem(queens, i, &queen) ; // �� ���� ��ġ�� queen�� �����ϰ�
					printf("%d ", queen) ; // ���� ��ġ�� ����Ʈ�Ѵ�.
				}
				printf("\n") ;
				//return 0 ;

				//���� ����� ���� ã�� ���� �ڵ�
				int lastest_queen ;
				pop(queens, &latest_queen) ; // ���� �������� ��ġ�� ���� ��ġ�� latest_queen�� �����ϰ� 
				push(queens, latest_queen + 1) ; // latest_queen+1�� ��ġ���Ѻ���. 
			}
			else { // ���� ������ ũ�Ⱑ 8�� �� ���� �ʾҴٸ� 
				int latest_queen ;
				top(queens, &latest_queen) ; // �������� ��ġ�� ���� ��ġ�� latest_queen�� �����ϰ�
				push(queens, latest_queen + 1) ; // ���� ���� latest_queen+1�� ��ġ�Ѵ� 
			}

		}else { // ���� ������ �浹�Ѵٸ� 
			int lastest_queen ; 
			pop(queens, &latest_queen) ; // ������ ���� pop�ϰ�
			push(queens, latest_queen + 1) ; // �� ���� ������ ��ġ +1�� push�Ѵ�
		}

	}
	delete_stack(queens) ;

	return EXIT_FAILURE ;
}

