#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int *arr, int len) {
    for(int i=0; i<len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *arr, int i, int j) {
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void mix(int *arr, int len) {
    for(int i=0; i<len; i++) {
        arr[i] = i+1;
    }

    //initialize random number
    srand(time(NULL));

    for(int i=0; i<len; i++) {
        int r = rand() % len;
        swap(arr, i, r);
    }
}