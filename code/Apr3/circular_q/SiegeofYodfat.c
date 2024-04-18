#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    int n,m;
    scanf("%d %d", &n, &m); //n=��� m=�ֱ� 
    gqueue_t * q = create_queue(n, sizeof(int));

    int i ; 
    for(i=1; i<=n; i++){
        enqueue(q,&i);
    }

    int turn = 0;    //�ε����� 0���� �����ϹǷ�
    while(get_size(q)>1){ //1�� ���� �� ���� �ݺ� 
        int curr;
        dequeue(q, &curr); //curr�� q���� dequeue
        
        if(turn<m-1){ // 0~m-1 ->m�ֱ�  
            enqueue(q,&curr); //�ֱ⿡ �������� �������� �ٽ� enqueue
            turn+=1;
        }
        else{
            turn =0; // �ֱ⿡ ���������� enqueue���ϰ� turn �ٽ� 0���� ����
        }
    }

    int answer;
    dequeue(q,&answer);
    printf("%d\n",answer);
}