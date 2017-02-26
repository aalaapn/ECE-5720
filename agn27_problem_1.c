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
#include <math.h> /* for pow function */

#define BILLION 1000000000L //used to convert seconds to nano seconds

float** create_2D_int_array(int N, int k){
    int i, j; //iteration variables
    float fillNum; //number to store in array
    //allocating space for array
    float** arr = (float **)malloc(k * sizeof(float *));
    for (i=0; i<N; i++)
         arr[i] = (float*)malloc(N * sizeof(float));
         
    // fill up the array with random numbers
    for(i = 0; i < N; i++) {
        for(j = 0; j < k; j++) {
                fillNum = (float)(rand())/(float)(RAND_MAX); //random number generator
                arr[i][j] = fillNum;
            }
        }
    return arr;
    }

/*Row-wise method of iterating through the array*/
void centroid_method_1(float **array, float *c, int N, int k){
    int i;
    int j;
    float cf = 0;
    for(i=1; i!=N; i++){
        for(j=1; j!=k; j++){
          c[j]=c[j]+array[i][j]; //building up the c_k array
          //cf = cf+c[j]; 		 //summing up the values in c_k for the centroid value
        }
    }
}

/*column-wise method of iterating through the array*/
void centroid_method_2(float **array, float *c, int N, int k){
    int i;
    int j;
    float cf = 0;
    for(j=1; j!=k; j++){
        for(i=1; i!=N; i++){
            c[j]=c[j]+array[i][j]; //building up the c_k array
            //cf = cf+c[j];	       //summing up the values in c_k for the centroid value
        }
    }
}

int main(){
    //Variables used for timing
    struct timespec start, end;
    uint64_t diff;
    
    int N = 64;//pow(2,15);
    int k = 64;//pow(2,15);
    float **array;
    int i;
    int j;
    float c_one[k];
    float c_two[N];
    float c_one_f = 0;
    float c_two_f = 0;

    array = create_2D_int_array(N, k);

    for(j =1; j!=k; j++){
            c_one[j] = 0;
        }
    for(j =1; j!=N; j++){
            c_two[j] = 0;
        }
    printf("Method one\n");
    for(j=1; j!=15; j++){
    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    centroid_method_1(array, c_one, N, k);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("%llu\n", (long long unsigned int) diff);
    }

    printf("Method two\n");
    for(j=1; j!=15; j++){
    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    centroid_method_2(array, c_two, N, k);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("%llu\n", (long long unsigned int) diff);
}
    return 0;
}
