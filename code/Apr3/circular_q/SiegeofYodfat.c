#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    int n,m;
    scanf("%d %d", &n, &m); //n=사람 m=주기 
    gqueue_t * q = create_queue(n, sizeof(int));

    int i ; 
    for(i=1; i<=n; i++){
        enqueue(q,&i);
    }

    int turn = 0;    //인덱스는 0부터 시작하므로
    while(get_size(q)>1){ //1개 남을 때 까지 반복 
        int curr;
        dequeue(q, &curr); //curr에 q에서 dequeue
        
        if(turn<m-1){ // 0~m-1 ->m주기  
            enqueue(q,&curr); //주기에 도달하지 못했으면 다시 enqueue
            turn+=1;
        }
        else{
            turn =0; // 주기에 도달했으면 enqueue안하고 turn 다시 0으로 돌림
        }
    }

    int answer;
    dequeue(q,&answer);
    printf("%d\n",answer);
}