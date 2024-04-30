#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gqueue.h"
#include <time.h>
#include "scoreboard.h"

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

	if (fscanf(fp, "%d %d %d", &N, &M, &K) != 3) { 
		fprintf(stderr, "File format error\n") ; 
		exit(EXIT_FAILURE) ;
	}

	/* TODO M,N,K ����*/

	//���� ��ġ ����
	for (int i = 0; i < K; i++) {
        int x, y;
        fscanf(fp, "%d %d", &y, &x);
        board[y][x].mined = 1;
		board[y][x].state = closed;
	
    }
	//���� ���� ĭ�� �ʱ� ���� ����
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
						
		}
	}
	
}


void draw_board() {
    
    int col, row;
    // ������ ��� �׵θ� ���
    printf("a/b-");
    for (col = 0; col < M; col++) {
        printf("%d-", col);
    }
    printf("\n");

    // �� ��ȣ�� ���� ���� ���
    for (row = 0; row < N; row++) {
        printf("%d ", row); // �� ��ȣ ���
        for (col = 0; col < M; col++) {
            if (col == 0) printf("| ");// �׵θ� 
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

    // ������ �ϴ� �׵θ� ���
    printf("   ");
    for (col = 0; col < M; col++) {
        printf("-%d", col);
    }
    printf("\n");
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
    return open_safe_cells_count == total_safe_cells || marked_mines_count == K;
}

void read_execute_userinput() {
    printf("> command : (open/flag/hint) a b \n");
    printf("> ");
    //refresh();
    char command[16];
    int y, x;

    scanf("%15s %d %d", command, &y, &x);

    // ù ��°�� ���� üũ: �Էµ� ��ġ�� �������� Ȯ��
    if (strcmp(command, "open") == 0 && board[y][x].mined == 1) {
        printf("LOSE!!\n");
        exit(EXIT_FAILURE); // ���ڰ� �ִ� ���� ������ �ϸ� ���� ����
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
        // ���ڰ� �ƴ� ���� ����
        gqueue_t *cells_to_bomb = create_queue(M * N, sizeof(int)*2);
        int initial_cell[2] = {y, x};  // y�� x �ε����� �迭�� ����
        enqueue(cells_to_bomb, initial_cell); //

        while (!is_empty(cells_to_bomb)) {
            int current_cell[2];
            dequeue(cells_to_bomb, current_cell);
            int cy = current_cell[0], cx = current_cell[1];

            // �̹� ���� �ְų�, ���ڰ� �ִ� ��� �ǳʶٱ�
            if (board[cy][cx].state != closed || board[cy][cx].mined) continue;

            // �� ���¸� �������� ����
            board[cy][cx].state = open;

            // ���ڰ� 0�̸� �ֺ� ���� ����
            if (board[cy][cx].num == 0) {
                int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
                int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

                for (int d = 0; d < 8; d++) {
                    int nx = cx + dx[d];
                    int ny = cy + dy[d];

                    // ���� �����̰� ���� �����̸� ���ڰ� �ƴ� ���� ť�� �߰�
                    if (nx >= 0 && nx < M && ny >= 0 && ny < N && board[ny][nx].state == closed && !board[ny][nx].mined) {
                         int new_cell[2] = {ny, nx};
                        enqueue(cells_to_bomb, new_cell);
                    }
                }
            }
        }
        delete_queue(cells_to_bomb); // ť �޸� ����
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


