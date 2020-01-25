    // KMP 알고리즘 https://www.acmicpc.net/problem/1786

    #include <stdio.h>
    #include <string.h>

    #define MAX_LEN 1000001

    void printArray(int *arr, int len) {
        for(int i=0; i<len; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    void buildPi(char *P, int *pi) {
        int pLen = (int)strlen(P) - 1;
        pi[0] = 0;
        //i : 첫번째 offset, j: 두번째 offset
        int i = 0, j = 1;
        while(j < pLen) {
            if(P[i] == P[j]) {
                pi[j] = pi[j-1]+1;
                i++;
            } else {
                i=0;
            }
            j++;
        }
    }

    int kmp(char *T, char *P, int *pi, int *out) {
        int tLen = (int)strlen(T) - 1;
        int pLen = (int)strlen(P) - 1;
        if(pLen > tLen) {
            return -1;
        }

        int i = 0;
        int j = 0;
        while(i < tLen) {
           if(T[i] != P[j]) {
              if(j == 0) {
                  i++;
              } else {
                  j = pi[j-1];
              }
           } else {
               if(j == pLen-1) {
                   //matched
                    out[++out[0]] = i - pLen + 1 + 1;

                   //reset
                   j = pi[j];
                   i++;
               } else {
                   i++;
                   j++;
               }
           }
        }
        return 0;
    }

    int out[MAX_LEN+1];
    char T[MAX_LEN];
    char P[MAX_LEN];

    int main() {
        fgets(T, MAX_LEN, stdin);
        fgets(P, MAX_LEN, stdin);
    //    printf("T: %s\n", T);
    //    printf("P: %s\n", P);

        //find pi
        int pi[MAX_LEN];
        buildPi(P, pi);

        //Test : print pi
    //    printArray(pi, 100);

        //kmp
        kmp(T, P, pi, out);

        printf("%d\n",out[0]);
        printArray(out+1, out[0]);

        return 0;
    }
