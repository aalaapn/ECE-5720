//Aalaap Narasipura (agn27)
//
//Problem 1
//

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> /* for uint64 definition */
#include <stdlib.h>
#include <time.h> /* for clock_gettime */
#include <math.h>

#define MAX_LENGTH  pow(2,26)
#define MIN_SIZE    2
#define BILLION 1000000000L

int* create_1D_array(){
  int j;
  int fillNum;
  int* arr = (int *)malloc(MAX_LENGTH * sizeof(int));
  for(j = 0; j < MAX_LENGTH; j++) {
          fillNum = 1;
          arr[j] = j;
      }
  return arr;
}

int main() {
  struct timespec start, end;
  uint64_t diff;
  int* A;
  A = create_1D_array();
  int h;
  int j;
  int i;
  int stride = 1;
  int K = 10;
  int n = MIN_SIZE;
  while(n != MAX_LENGTH){
    for(i=0; i!=(n-1); i++){
      while(stride < (n/2)){
        clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
        for(j=0; j<(stride*K); j++){
          for(h=0; h<n-1; h=h+stride){
          }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("elapsed time by method one = %llu nanoseconds\n", (long long unsigned int) diff);
        stride = stride *2;
      }
    }
    n = n*2;
  }
  return 0;
}
