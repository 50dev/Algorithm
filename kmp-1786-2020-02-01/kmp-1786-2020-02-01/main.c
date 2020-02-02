//
//  main.c
//  kmp-1786-2020-02-01
//
//  Created by 민수강 on 2020/02/01.
//  Copyright © 2020 민수강. All rights reserved.
//

//찾기 - https://www.acmicpc.net/problem/1786

#include <stdio.h>

#define MAX_LEN 1000000
// [0] [1]...[MAX_LEN] + '\n' + \0'
#define ARR_SIZE MAX_LEN+3

char T[ARR_SIZE];
char P[ARR_SIZE];
int pi[ARR_SIZE];
//n: T index, m: P indexs
int n;
int m;

int ans[ARR_SIZE];

int length(char *in) {
    int len = 0;
    while(*in != '\0' && *in != '\n') {
        in++;
        len++;
    }
    
    return len;
}

void getPi() {
    //P : src index, j: compare index
    int i=1, j=2;
    
    while(j <= m) {
        if(P[i] == P[j]) {
            pi[j] = pi[j-1]+1;
            i++; j++;
        }else if(i == 1) {
            pi[j] = 0;
            j ++;
        } else {
            i = 1;
        }
    }
}

void kmp() {
    getPi();
    
//    printf("pi: ");
//    for(int i=1; i<=m; i++) {
//        printf("%d ", pi[i]);
//    }
//    printf("\n");
    
    //i : T index, j : P index
    int i = 1, j = 1;

    while(i <= n) {
        if(T[i] == P[j]) {
            if(j == m) {
                //matched
                ans[++ans[0]] = i - m  + 1;
                
                //next
                i++;
                j = pi[j] + 1;
            } else {
                i++;
                j++;
            }
        } else {
            if(j == 1) {
                i++;
            } else {
                j = pi[j-1] + 1;
            }
        }
    }
    
    printf("%d\n", ans[0]);
    if(ans[0] > 0) {
        for(int i=1; i<ans[0]; i++) {
            printf("%d ", ans[i]);
        }
        
        printf("%d\n", ans[ans[0]]);
    }
    
}

int main(int argc, const char * argv[]) {

    //init
    for(int i=0; i<ARR_SIZE; i++) {
        T[i] = 0;
        P[i] = 0;
        pi[i] = 0;
        ans[i] = 0;
    }
    
    fgets(T+1, MAX_LEN+1, stdin);
    fgets(P+1, MAX_LEN+1, stdin);
    
    n = length(T+1);
    m = length(P+1);
    
//    printf("T(%d): %s", n, T+1);
//    printf("P(%d): %s", m, P+1);
    
    kmp();
    
    return 0;
}
