//Aalaap Narasipura (agn27)
//
//Problem 1
//
//Compile with the command:     gcc agn27_problem_1.c -o problem_1_output
//Then run with the command:    ./problem_1_output


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> /* for uint64 definition */
#include <stdlib.h>
#include <time.h> /* for clock_gettime */
#include <math.h>

#define MAX_LENGTH  pow(2,26)
#define MIN_SIZE    pow(2,10)
#define BILLION 1000000000L

float* create_1D_array(){
  int j;
  int fillNum;
  float* arr = (float *)malloc(MAX_LENGTH * sizeof(float));
  for(j = 0; j < MAX_LENGTH; j++) {
          fillNum = 1;
          arr[j] = j;
      }
  return arr;
}

int main() {
  struct timespec start, end;
  float diff;
  float* A;
  A = create_1D_array();
  int h;
  int j;
  int i;
  int stride;
  int K = 10;
  int n = MIN_SIZE;
  float temp;
  //FILE *fp;
  //fp = fopen("problem2outputasdfasdf.txt", "w+");
  for(n=MIN_SIZE; n<MAX_LENGTH; n=n*2){ //double the length of n
      for(stride = 1; stride<(n/2); stride = stride*2){ //double the length of the stride
        clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
        for(j=0; j<(K); j++){
          for(h=0; h<n-1; h=h+stride){
            temp = A[h];
          }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("%f,", (float) diff/(K));
      }
  printf("\n-------n-------\n");
  printf("---------------%d---------------\n", n);
  }
  //fclose(fp);
  printf("done\n");
  return 0;
}
