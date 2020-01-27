//
//  main.c
//  dice-17825-20-01-27
//
//  Created by 민수강 on 2020/01/27.
//  Copyright © 2020 민수강. All rights reserved.
//

// 주사위 윷놀이 - https://www.acmicpc.net/problem/17825

#include <stdio.h>

#define INPUT_LEN 10

//20
int r1[19] = {
    2, 4, 6, 8, 10,
    12, 14, 16, 18, 20,
    22, 24, 26, 28, 30,
    32, 34, 36, 38,
};

//3
int r2[3] = {
    13, 16, 19,
};

//2
int r3[2] = {
    22, 24,
};

//3
int r4[3] = {
    28, 27, 26,
};

//4
int r5[4] = {
    25, 30, 35, 40,
};

// r1 : 1~20 + 5
// r2 : 31~33
// r3 : 41~42
// r4 : 51~53
// r5 : 61~64 + 5

int map[100];
int visited[100];

//player position
int player[4];
int dice[11];

void init() {
    for(int i=0; i<100; i++) {
        map[i] = 0;
        visited[i] = 0;
    }
    
    for(int i=0; i<4; i++) {
        player[i] = 0;
    }
    
    for(int i=0; i<11; i++) {
        dice[i] = 0;
    }
    
    for(int i=0; i<19; i++) {
        map[1+i] = r1[i];
    }
    
    for(int i=0; i<3; i++) {
        map[31+i] = r2[i];
    }
    
    for(int i=0; i<2; i++) {
        map[41+i] = r3[i];
    }
    
    for(int i=0; i<3; i++) {
        map[51+i] = r4[i];
    }
    
    for(int i=0; i<4; i++) {
        map[61+i] = r5[i];
    }
}

int move(int current, int d) {
    if(current == 5) {
        current = 30;
    } else if(current == 10) {
        current = 40;
    } else if(current == 15) {
        current = 50;
    }
    
    int next = current + d;
    if(next >= 20 && next <= 30) {
        next = next - 20 + 64;
    } else if(next >= 34 && next <= 40) {
        next = next - 34 + 61;
    } else if(next >= 43 && next <= 50) {
        next = next - 43 + 61;
    } else if(next >=54 && next <= 60) {
        next = next - 54 + 61;
    }
    
    return next;
}

/**
 c : 주사위 횟수
 p : 현재 포인트
 */


int maxPoint = 0;
int maxTracking[11];
int tracking[11];
int lastPlayer[4];

int getPoint(int c, int p) {
    //주사위 10번이 넘어갔을 때
    if(c > INPUT_LEN) {
        //for test
        if(p > maxPoint) {
            maxPoint = p;
            for(int i=1; i<=10; i++) {
                maxTracking[i] = tracking[i];
            }
            
            for(int i=0; i<4; i++) {
                lastPlayer[i] = player[i];
            }
        }
        return p;
    }
    
    //모든 플레이어의 경우의 수 찾기
    int maxPoint = 0;
    for(int i=0; i<4; i++) {
        tracking[c] = i;
        //초기값
        int currentPosition = player[i];
        int nextPosition = currentPosition;
        int nextPoint = p;
        
        //현재 플레이어는 도착해 있지 않은가?
        int enableMove = 0;
        if(currentPosition == 0
           || map[currentPosition] != 0) {
            int temp = move(currentPosition, dice[c]);
            
            //이동할 수 있는 곳인가?
            //:: 도착지점 또는 다른 플레이어가 존재하지 않는가?
            if(map[temp] == 0
                    || visited[temp] == 0) {
                nextPosition = temp;
                
                //이동
                visited[currentPosition] = 0;
                visited[nextPosition] = 1;
                player[i] = nextPosition;
                nextPoint += map[nextPosition];
                enableMove = 1;
            }
        }
  
        if(enableMove) {
            int subOptimal = getPoint(c+1, nextPoint);
            maxPoint = (subOptimal > maxPoint)? subOptimal : maxPoint;
            
            //recover
            visited[nextPosition] = 0;
            visited[currentPosition] = 1;
            player[i] = currentPosition;
        }
    }

    return maxPoint;
}

int main(int argc, const char * argv[]) {
    init();
    
    for(int i=1; i<=INPUT_LEN; i++) {
        scanf("%d", &dice[i]);
    };
    
//    for(int i=1; i<=INPUT_LEN; i++) {
//        printf("%d ", dice[i]);
//    }
    
//    printf("\n");
    
    int answer = getPoint(1, 0);
    
    printf("%d\n", answer);
    
    //for test
//    printf("%d\n", maxPoint);
//    for(int i=1; i<=INPUT_LEN; i++) {
//        printf("%d ", maxTracking[i]);
//    }
//    printf("\n");
//
//    for(int i=0; i<4; i++) {
//        printf("%d ", lastPlayer[i]);
//    }
//    printf("\n");
    
    return 0;
}
