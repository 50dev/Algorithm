#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void doSortingByDivideAndConquer(int *, int);
void doSortingInternal(int *, int, int);
void merge(int *, int, int ,int);

int main(void) {
    int arr[100];
    mix(arr, 100);
    //print input
    printArray(arr, 100);

    //do sorting
    doSortingByDivideAndConquer(arr, 100);

    //print output
    printArray(arr, 100);

    return 0;
}

void doSortingByDivideAndConquer(int *arr, int len) {
    doSortingInternal(arr, 0, len);
}

/**
 * arr : array
 * b : begin index included
 * e : end index excluded
 **/
void doSortingInternal(int *arr, int b, int e) {
    if(b == e-1) {
        return;
    }

    int m = (b+e)/2;
    doSortingInternal(arr, b, m);
    doSortingInternal(arr, m, e);
    merge(arr, b, m, e);
}

/**
 * arr : array
 * b : begin index included
 * m : medium index
 * e : end index excluded
 **/
void merge(int *arr, int b, int m, int e) {
    int loffset = b;
    int roffset = m;
    int len = e-b;
    int* t_array = (int*) malloc(sizeof(int)*len);

    int i = 0;
    while(loffset < m && roffset < e) {
        t_array[i++] = arr[loffset] <= arr[roffset]? 
            arr[loffset++] : arr[roffset++];
    }

    int remainIndex = roffset == e? loffset : roffset;
    while(i < len) {
        t_array[i++] = arr[remainIndex++];
    }

    //copy t_array to arr
    for(int n=0; n<len; n++) {
        arr[b+n] = t_array[n];
    }

    free(t_array);
}