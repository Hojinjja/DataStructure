#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gqueue.h"
#include <time.h>
#include "scoreboard.h"

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

	if (fscanf(fp, "%d %d %d", &N, &M, &K) != 3) { 
		fprintf(stderr, "File format error\n") ; 
		exit(EXIT_FAILURE) ;
	}

	/* TODO M,N,K 저장*/

	//지뢰 위치 저장
	for (int i = 0; i < K; i++) {
        int x, y;
        fscanf(fp, "%d %d", &y, &x);
        board[y][x].mined = 1;
		board[y][x].state = closed;
	
    }
	//지뢰 없는 칸의 초기 상태 저장
	for (int x=0; x<M ; x++){
		for(int y=0; y<M; y++){
			if(board[y][x].mined!=0){
				board[y][x].state=closed;
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
						
		}
	}
	
}


void draw_board() {
    
    int col, row;
    // 보드의 상단 테두리 출력
    printf("a/b-");
    for (col = 0; col < M; col++) {
        printf("%d-", col);
    }
    printf("\n");

    // 행 번호와 보드 내용 출력
    for (row = 0; row < N; row++) {
        printf("%d ", row); // 행 번호 출력
        for (col = 0; col < M; col++) {
            if (col == 0) printf("| ");// 테두리 
            if (board[row][col].state == closed) {
                printf("* ");
            } else if (board[row][col].state == open) {
                printf("%d ", board[row][col].num);
            } else if (board[row][col].state == marked) {
                printf("F ");
            }
            
        }
        printf("\n");
    }

    // 보드의 하단 테두리 출력
    printf("   ");
    for (col = 0; col < M; col++) {
        printf("-%d", col);
    }
    printf("\n");
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
    return open_safe_cells_count == total_safe_cells || marked_mines_count == K;
}

void read_execute_userinput() {
    printf("> command : (open/flag/hint) a b \n");
    printf("> ");
    //refresh();
    char command[16];
    int y, x;

    scanf("%15s %d %d", command, &y, &x);

    // 첫 번째로 지뢰 체크: 입력된 위치가 지뢰인지 확인
    if (strcmp(command, "open") == 0 && board[y][x].mined == 1) {
        printf("LOSE!!\n");
        exit(EXIT_FAILURE); // 지뢰가 있는 셀을 열려고 하면 게임 종료
    }

    if (strcmp(command, "flag") == 0  ) {
        if(board[y][x].state == marked){
            board[y][x].state = closed;
        }else if(board[y][x].state == closed){
            board[y][x].state = marked;
        }else{
            printf(" already opened\n\n");
            return ;
        }; 
    }
    if (strcmp(command, "hint") == 0) {
         if (board[y][x].mined == 1) {
        printf("\nHint: (%d, %d) is mined.\n", y, x);
        } else {
        printf("\nHint: (%d, %d), there is no mine.\n", y, x);
         }
        getchar();
        return;
    }
	else if (strcmp(command, "open") == 0 && board[y][x].state == closed) {
        // 지뢰가 아닌 셀을 열기
        gqueue_t *cells_to_bomb = create_queue(M * N, sizeof(int)*2);
        int initial_cell[2] = {y, x};  // y와 x 인덱스를 배열에 저장
        enqueue(cells_to_bomb, initial_cell); //

        while (!is_empty(cells_to_bomb)) {
            int current_cell[2];
            dequeue(cells_to_bomb, current_cell);
            int cy = current_cell[0], cx = current_cell[1];

            // 이미 열려 있거나, 지뢰가 있는 경우 건너뛰기
            if (board[cy][cx].state != closed || board[cy][cx].mined) continue;

            // 셀 상태를 열림으로 변경
            board[cy][cx].state = open;

            // 숫자가 0이면 주변 셀도 열기
            if (board[cy][cx].num == 0) {
                int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
                int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

                for (int d = 0; d < 8; d++) {
                    int nx = cx + dx[d];
                    int ny = cy + dy[d];

                    // 범위 내부이고 닫힌 상태이며 지뢰가 아닌 셀만 큐에 추가
                    if (nx >= 0 && nx < M && ny >= 0 && ny < N && board[ny][nx].state == closed && !board[ny][nx].mined) {
                         int new_cell[2] = {ny, nx};
                        enqueue(cells_to_bomb, new_cell);
                    }
                }
            }
        }
        delete_queue(cells_to_bomb); // 큐 메모리 해제
    }
    system("clear");
}
	
	
int main (int argc, char ** argv)
{
	if (argc != 2) {
		fprintf(stderr, "Invalid command: give a filename of board arrangement.\n") ;
		return EXIT_FAILURE ;
	}

	load_board(argv[1]) ;
	printf("col:%d, row:%d, mine:%d\n", M,N,K);
	
    time_t start_time = time(NULL);


	 while (!is_terminated()) {
        count_mine_around();
        draw_board();
        read_execute_userinput();
    }

    time_t end_time = time(NULL);
    record_and_display_timer("scoreboard.txt", start_time, end_time);

	printf("WIN!!\n");
}


