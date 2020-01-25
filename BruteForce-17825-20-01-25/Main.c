// 주사위 윷놀이 - https://www.acmicpc.net/problem/17825

#include <stdio.h>
#include <string.h>

//위치 1~20
int r1[21] = {
    20,
    2, 4, 6, 8, 10,
    12, 14, 16, 18, 20,
    22, 24, 26, 28, 30,
    32, 34, 36, 38, 40,
};

//31~37
int r2[8] = {
    7,
    13, 16, 19, 25,
    30, 35, 40,
};

//51~56
int r3[7] = {
    6,
    22, 24, 25,
    30, 35, 40,
};

//71~77
int r4[8] = {
    7,
    28, 27, 26, 25,
    30, 35, 40,
};

int in[11];
int player[4];
int mark[100];

/**
 * i : player index
 * c : 현재 숫자 횟수
**/
int next(int i, int c) {
    if(c > 10) {
        return 0;
    }
    //주사위 숫자
    int n = in[c];
    int pos = player[i];
    int pt = 0;
    //도착 여부 확인
    if(pos >= 0) {
        //이동
        if(pos == 5) {
            pos = 30;
        } else if(pos == 10) {
            pos = 40;
        } else if(pos == 15) {
            pos = 50;
        } 
        
        pos += n;

        if(mark[pos] == 1) {
            //이동 불가
        } else {
            //이동
            mark[player[i]] = 0;
            
            if((i > 20 && i <30)
            ||(i > 37 && i < 50)
            ||(i > 56 && i < 70)
            ||(i > 77 && i < 90)
            ) {
                //도착
                player[i] = -1;
            } else {
                //위치 갱신
                mark[pos] = 1;
                player[i] = pos;

                //포인트 갱신
                if(i > 70) {
                    pt = r4[pos-70];
                } else if(i > 50) {
                    pt = r3[pos-50];
                } else if(i > 30) {
                    pt = r2[pos-30];
                } else {
                    pt = r1[pos];
                }
            }
        }
    }

    //포인트
    int max = 0;
    for(int i=0; i<4; i++) {
        int sum = next(i, c+1);
        max = sum > max? sum : max;
    };

    return max+pt; 
}


int main(void) {
    //init
    memset(player, 0x00, sizeof(int)*4);
    memset(mark, 0x00, sizeof(int)*100);

    for(int i=1; i<=10; i++) {
        scanf("%d", &in[i]);
    }

    for(int i=1; i<=10; i++) {
        printf("%d ", in[i]);
    }
    printf("\n");

    int max = 0;
    for(int i=0; i<4; i++) {
        int temp = next(i, 1);
        max = temp > max ? temp : max; 
    }

    printf("%d\n", max);

    return 0;
}