#include <stdio.h>
#include <stdlib.h>
// #include <omp.h>
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
    srand(9);
    // fill up the array with random numbers
    for(i = 0; i < N; i++) {
        for(j = 0; j < k; j++) {
                fillNum = (int)(rand()/100000); //random number generator
                arr[i][j] = fillNum;
            }
        }
    return arr;
    }

    //function to print out items in the array
    void printArray(int **array, int N, int k){
        printf("------array-begin--------\n");
        int i;
        int j;
        int *temp;
        int largest = 0;
        int lIndex = 0;
            for(i=0; i<N; i++){
                for(j=0; j<k; j++){
                printf("%d ", array[i][j]);
                if(array[i][j]>largest){
                    largest = array[i][j];
                    lIndex = i;
                }
            }
            printf("\n");
        }
            printf("------array-end--------\n");
    }

void sort(int **arr, int N){
  int row,col, iter;
  row =N;
  col = N;
  int i,j,k=0,x,temp;
  for(iter = 0; iter<N; iter++){
    k=iter;
    for(i=iter;i<row;i++){
      for(j=i+1;j<row;j++){
        if(arr[i][k] > arr[j][k]){
          for(x=iter;x<N;x++){
            temp=arr[i][x];
            arr[i][x]=arr[j][x];
            arr[j][x]=temp;
          }
        }
      }
    }
  }
}


void sortOMP(int **arr, int N){
  int row,col, iter;
  row =N;
  col = N;
  int i,j,k=0,x,temp;
#pragma omp parallel shared(arr, N,)
  for(iter = 0; iter<N; iter++){
    k=iter;
    #pragma omp parallel
    for(i=iter;i<row;i++){
    #pragma omp parallel
      for(j=i+1;j<row;j++){
        if(arr[i][k] > arr[j][k]){
        #pragma omp parallel
          for(x=iter;x<N;x++){
            temp=arr[i][x];
            arr[i][x]=arr[j][x];
            arr[j][x]=temp;
          }
        }
      }
    }
  }
}


int main(void){
    struct timespec start, end;
    uint64_t diff;

    int **a;
    int **arr;
    //array dimensions
    int N[11];
    int k[11];
    int power;
    for(power = 3; power<14; power++){
        N[power-3] = (int)(pow(2,power));
        k[power-3] = (int)(pow(2,power));
    }

    for(power = 0; power<11; power++){
      arr = create_2D_int_array(N[power], k[power]);
        clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
        //sortOMP(arr, N[power]);
        sort(arr, N[power]);
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("%llu\n", (long long unsigned int) diff);
        free(arr);
    }
    printf("--------------\n");
    return 0;
}
