#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gqueue.h"
#include <ncurses.h>


typedef enum {
		closed, marked, open
	}
	cell_state ; // 열기전의 상태

typedef struct {
		int mined ; // mine이 있냐 없냐
		int num ; // 열었을 때 주변에 있는 mine의 개수. (0개이면 safe)
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
 * 파일 열어서 보드 기본 정보 (M,N,K)와 지뢰위치 저장하기.  
*/
void load_board (char * filename)
{
	FILE * fp ;
	if (!(fp = fopen(filename, "r"))) {
		fprintf(stderr, "Fail to open %s\n", filename) ;
		exit(EXIT_FAILURE) ;
	}

	if (fscanf(fp, "%d %d %d", &M, &N, &K) != 3) { // M,N,K 저장 -> 저장 제대로 됐으면 각각 1 return 
		fprintf(stderr, "File format error\n") ; //
		exit(EXIT_FAILURE) ;
	}

	/* TODO M,N,K 저장*/

	//지뢰 위치 저장
	for (int i = 0; i < K; i++) {
        int x, y;
        fscanf(fp, "%d %d", &y, &x);
        board[y][x].mined = 1;
		board[y][x].state = closed;
		// board[x][y].x = x;
		// board[x][y].y = y;
		printf("y:%d, x:%d, mine=%d\n", y,x, board[y][x].mined==1);
	
    }
	//지뢰 없는 칸의 초기 상태 저장
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
*주변 지뢰의 개수 8방향 탐색해서 업데이트
*/
void count_mine_around(){
	int dx[8] = {0,0,-1,1,-1,-1,1,1}; // 상,하,좌,우,왼대각,오른대각 
	int dy[8] = {1,-1,0,0,1,-1,1,-1}; // 상,하,좌,우,왼위,왼아래,오른위,오른아래

	for(int y=0; y<N; y++){
		for (int x=0; x<M; x++){
			if(board[y][x].mined){ // 검색하고 있는 칸이 지뢰이면 다음 칸 검색 
				continue;
			}
	
			int mine_count=0;
			for(int i=0; i<8; i++){
				int nx = x +dx[i];
				int ny = y +dy[i];
				//검색한 칸의 주변 8방향이 M,N안에 있고 MINE이면 MINE_COUNT ++
				if(nx>=0 && nx< M && ny>=0 && ny<N&& board[ny][nx].mined){
					mine_count +=1;
				}
			}board[y][x].num=mine_count;
				// printf("mine_count:%d ",mine_count);
				// printf("board[%d][%d].num=%d\n",x,y,board[y][x].num );			
		}
	}
	
}


// 지뢰가 아닌 칸의 개수 => M*N-K 개 
// 지뢰가 아닌 칸이 모두 열리거나, 지뢰 칸이 모두 MARKED이면 게임 끝
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
    // 모든 안전한 셀이 열렸거나 지뢰가 있는 셀만 표시되었을 때 종료
    return open_safe_cells_count == total_safe_cells && marked_mines_count == K;
}

void draw_board() {
    clear();  // 화면을 지웁니다.
    for (int row = 0; row < N; row++) {
        move(row, 0);  // 커서를 적절한 위치로 이동합니다.
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
    refresh();  // 화면 변경사항을 적용합니다.
}


void read_execute_userinput() {
    int y, x;
    char command[16];
    
    
    printw("> "); // ncurses를 사용해 입력 프롬프트를 출력
    echo();       // 사용자 입력을 화면에 보이도록 설정
    scanw("%15s %d %d", command, &y, &x); // ncurses의 scanw를 사용해 입력 받기
    noecho();     // 다시 에코를 끕니다.
    refresh();    // 화면을 갱신해 입력이 보이도록 합니다.

    

    if (strcmp(command, "open") == 1 && board[y][x].mined == 1) {
        if(board[y][x].mined == 0){
            board[y][x].state == open;
            refresh();
        }
        if(board[y][x].mined == 1){
            printw("LOSE!!\n");
            refresh();
            getch();  // 사용자로부터 키 입력을 대기(프로그램 종료 전)
            endwin(); // ncurses 세션을 종료
            exit(EXIT_FAILURE);
        }
    }

    if (strcmp(command, "q") ==0){
        exit(EXIT_FAILURE);
    }

    if (strcmp(command, "flag") == 0) {
        if (board[y][x].state == open) {
            return; // 이미 열린 칸에는 아무 작업도 수행하지 않음
        }
        board[y][x].state = (board[y][x].state == closed) ? marked : closed;
    } else if (strcmp(command, "open") == 0 && board[y][x].state == closed) {
        board[y][x].state == open;
    }
    draw_board(); // 보드를 다시 그립니다
}




	
	
int main(int argc, char **argv) {
    initscr();          // ncurses 세션을 시작합니다.
    cbreak();           // 버퍼링 없이 각 키를 즉시 사용 가능하게 합니다.
    noecho();           // 입력한 키를 화면에 표시하지 않습니다.

    if (argc != 2) {
        fprintf(stderr, "Invalid command: give a filename of board arrangement.\n");
        endwin();       // ncurses 세션을 종료합니다.
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
    refresh();          // 변경사항을 화면에 적용합니다.
    getch();            // 사용자로부터 키 입력을 대기합니다.
    endwin();           // ncurses 세션을 종료합니다.
    return 0;
}
//-lncurses













