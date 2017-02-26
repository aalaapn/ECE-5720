#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> /* for clock_gettime */
#include <stdint.h> /* for uint64 definition */
#include <math.h>

#define BILLION 1000000000L //used to convert seconds to nano seconds


int** create_2D_int_array(int N, int k){
    time_t t;
    int i, j; //iteration variables
    int fillNum; //number to store in array
    //allocating space for array
    int** arr = (int **)malloc(k * sizeof(int *));
    for (i=0; i<N; i++)
         arr[i] = (int*)malloc(N * sizeof(int));
    srand(7);
    // fill up the array with random numbers
    for(i = 0; i < N; i++) {
        for(j = 0; j < k; j++) {
                fillNum = (int)(rand()/100000); //random number generator
                arr[i][j] = fillNum;
            }
        }
    return arr;
    }

void swapRow(int **array, int row1, int row2, int size){
    int i;
    int temp;
    for(i = 0; i<size; i++){
        temp = array[i][row1];
        array[i][row1] = array[i][row2];
        array[i][row2] = temp;
    }
}



int partition(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;

#pragma omp parallel for
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }   
    }   

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   

    return p + lt_n;
}

void quicksort(int * a, int p, int r)
{
    int div;

    if(p < r){ 
        div = partition(a, p, r);
#pragma omp parallel shared(a)
#pragma omp sections
        {   
#pragma omp section
            quicksort(a, p, div - 1); 
#pragma omp section
            quicksort(a, div + 1, r); 

        }
    }
}



int partition2(int * a, int p, int r)
{
    int lt[r-p];
    int gt[r-p];
    int i;
    int j;
    int key = a[r];
    int lt_n = 0;
    int gt_n = 0;
    for(i = p; i < r; i++){
        if(a[i] < a[r]){
            lt[lt_n++] = a[i];
        }else{
            gt[gt_n++] = a[i];
        }   
    }   

    for(i = 0; i < lt_n; i++){
        a[p + i] = lt[i];
    }   

    a[p + lt_n] = key;

    for(j = 0; j < gt_n; j++){
        a[p + lt_n + j + 1] = gt[j];
    }   

    return p + lt_n;
}

void quicksort2(int * a, int p, int r)
{
    int div;

    if(p < r){ 
        div = partition2(a, p, r); 
        quicksort2(a, p, div - 1); 
        quicksort2(a, div + 1, r); 

    }
}


int main(void){
    struct timespec start, end;
    uint64_t diff;

    int **a;
    int **b;
    int N = pow(2,15);
    a = create_2D_int_array(N,N);
    b = create_2D_int_array(N,N);

    printf("================\n");
    int i= 0;
    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    quicksort(a[i], 6, 9);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("%llu\n", (long long unsigned int) diff);


    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    quicksort2(b[i], 6, 9);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("%llu\n", (long long unsigned int) diff);

    printf("--------------\n");
    free(a);
    free(b);
    return 0;
}