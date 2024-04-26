#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gqueue.h"
#include <ncurses.h>


typedef enum {
		closed, marked, open
	}
	cell_state ; // �������� ����

typedef struct {
		int mined ; // mine�� �ֳ� ����
		int num ; // ������ �� �ֺ��� �ִ� mine�� ����. (0���̸� safe)
		cell_state state ; 
	}
	cell_t  ; 

// typedef struct {
// 	int x;
// 	int y;
// } cell_coordinate ;


int M, N, K ;
cell_t board[16][16] = {{ {0, 0, 0} }} ; // 0,0,0 (mined,num,state) ?? ??? 

/*
 * ���� ��� ���� �⺻ ���� (M,N,K)�� ������ġ �����ϱ�.  
*/
void load_board (char * filename)
{
	FILE * fp ;
	if (!(fp = fopen(filename, "r"))) {
		fprintf(stderr, "Fail to open %s\n", filename) ;
		exit(EXIT_FAILURE) ;
	}

	if (fscanf(fp, "%d %d %d", &M, &N, &K) != 3) { // M,N,K ���� -> ���� ����� ������ ���� 1 return 
		fprintf(stderr, "File format error\n") ; //
		exit(EXIT_FAILURE) ;
	}

	/* TODO M,N,K ����*/

	//���� ��ġ ����
	for (int i = 0; i < K; i++) {
        int x, y;
        fscanf(fp, "%d %d", &y, &x);
        board[y][x].mined = 1;
		board[y][x].state = closed;
		// board[x][y].x = x;
		// board[x][y].y = y;
		printf("y:%d, x:%d, mine=%d\n", y,x, board[y][x].mined==1);
	
    }
	//���� ���� ĭ�� �ʱ� ���� ����
	for (int x=0; x<M ; x++){
		for(int y=0; y<M; y++){
			if(board[y][x].mined!=0){
				board[y][x].state=closed;
				// board[x][y].x=x;
				// board[x][y].y=y;
			}
		}

	}
	fclose(fp) ;
}

/*
*�ֺ� ������ ���� 8���� Ž���ؼ� ������Ʈ
*/
void count_mine_around(){
	int dx[8] = {0,0,-1,1,-1,-1,1,1}; // ��,��,��,��,�޴밢,�����밢 
	int dy[8] = {1,-1,0,0,1,-1,1,-1}; // ��,��,��,��,����,�޾Ʒ�,������,�����Ʒ�

	for(int y=0; y<N; y++){
		for (int x=0; x<M; x++){
			if(board[y][x].mined){ // �˻��ϰ� �ִ� ĭ�� �����̸� ���� ĭ �˻� 
				continue;
			}
	
			int mine_count=0;
			for(int i=0; i<8; i++){
				int nx = x +dx[i];
				int ny = y +dy[i];
				//�˻��� ĭ�� �ֺ� 8������ M,N�ȿ� �ְ� MINE�̸� MINE_COUNT ++
				if(nx>=0 && nx< M && ny>=0 && ny<N&& board[ny][nx].mined){
					mine_count +=1;
				}
			}board[y][x].num=mine_count;
				// printf("mine_count:%d ",mine_count);
				// printf("board[%d][%d].num=%d\n",x,y,board[y][x].num );			
		}
	}
	
}


// ���ڰ� �ƴ� ĭ�� ���� => M*N-K �� 
// ���ڰ� �ƴ� ĭ�� ��� �����ų�, ���� ĭ�� ��� MARKED�̸� ���� ��
int is_terminated() {
    int open_safe_cells_count = 0;
    int marked_mines_count = 0;
    int total_safe_cells = M * N - K;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (board[y][x].state == open) {
                open_safe_cells_count++;
            }
            if (board[y][x].state == marked && board[y][x].mined) {
                marked_mines_count++;
            }
        }
    }
    // ��� ������ ���� ���Ȱų� ���ڰ� �ִ� ���� ǥ�õǾ��� �� ����
    return open_safe_cells_count == total_safe_cells && marked_mines_count == K;
}

void draw_board() {
    clear();  // ȭ���� ����ϴ�.
    for (int row = 0; row < N; row++) {
        move(row, 0);  // Ŀ���� ������ ��ġ�� �̵��մϴ�.
        for (int col = 0; col < M; col++) {
            if (board[row][col].state == closed) {
                printw("* ");
            } else if (board[row][col].state == open) {
                printw("%d ", board[row][col].num);
            } else if (board[row][col].state == marked) {
                printw("F ");
            }
        }
        printw("\n");
    }
    refresh();  // ȭ�� ��������� �����մϴ�.
}


void read_execute_userinput() {
    int y, x;
    char command[16];
    
    
    printw("> "); // ncurses�� ����� �Է� ������Ʈ�� ���
    echo();       // ����� �Է��� ȭ�鿡 ���̵��� ����
    scanw("%15s %d %d", command, &y, &x); // ncurses�� scanw�� ����� �Է� �ޱ�
    noecho();     // �ٽ� ���ڸ� ���ϴ�.
    refresh();    // ȭ���� ������ �Է��� ���̵��� �մϴ�.

    

    if (strcmp(command, "open") == 1 && board[y][x].mined == 1) {
        if(board[y][x].mined == 0){
            board[y][x].state == open;
            refresh();
        }
        if(board[y][x].mined == 1){
            printw("LOSE!!\n");
            refresh();
            getch();  // ����ڷκ��� Ű �Է��� ���(���α׷� ���� ��)
            endwin(); // ncurses ������ ����
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp(command, "q") ==0){
        exit(EXIT_FAILURE);
    }

    if (strcmp(command, "flag") == 0) {
        if (board[y][x].state == open) {
            return; // �̹� ���� ĭ���� �ƹ� �۾��� �������� ����
        }
        board[y][x].state = (board[y][x].state == closed) ? marked : closed;
    } else if (strcmp(command, "open") == 0 && board[y][x].state == closed) {
        board[y][x].state == open;
    }
    draw_board(); // ���带 �ٽ� �׸��ϴ�
}




	
	
int main(int argc, char **argv) {
    initscr();          // ncurses ������ �����մϴ�.
    cbreak();           // ���۸� ���� �� Ű�� ��� ��� �����ϰ� �մϴ�.
    noecho();           // �Է��� Ű�� ȭ�鿡 ǥ������ �ʽ��ϴ�.

    if (argc != 2) {
        fprintf(stderr, "Invalid command: give a filename of board arrangement.\n");
        endwin();       // ncurses ������ �����մϴ�.
        return EXIT_FAILURE;
    }

    load_board(argv[1]);
    printf("col:%d, row:%d, mine:%d\n", M, N, K);

    while (!is_terminated()) {
        count_mine_around();
        draw_board();
        read_execute_userinput();
    }

    printw("WIN!!\n");
    refresh();          // ��������� ȭ�鿡 �����մϴ�.
    getch();            // ����ڷκ��� Ű �Է��� ����մϴ�.
    endwin();           // ncurses ������ �����մϴ�.
    return 0;
}
//-lncurses













