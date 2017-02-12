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

#define BILLION 1000000000L

float** create_2D_int_array(int N, int k){
    int i, j;
    float fillNum;
    float** arr = (float **)malloc(k * sizeof(float *));
    for (i=0; i<N; i++)
         arr[i] = (float*)malloc(N * sizeof(float));
    // initilize seed
    srand(time(NULL));
    // fill up..
    for(i = 0; i < N; i++) {
        for(j = 0; j < k; j++) {
                fillNum = (float)(rand())/(float)(RAND_MAX);
                arr[i][j] = fillNum;
            }
        }
    return arr;
    }

float centroid_method_1(float **array, float *c, int N, int k){
    int i;
    int j;
    float cf = 0;
    for(i=1; i!=N; i++){
        for(j=1; j!=k; j++){
          c[j]=c[j]+array[i][j];
          cf = cf+c[j];
        }
    }
    return cf;
}

float centroid_method_2(float **array, float *c, int N, int k){
    int i;
    int j;
    float cf = 0;
    for(j=1; j!=N; j++){
        for(i=1; i!=k; i++){
            c[j]=c[j]+array[i][j];
            cf = cf+c[j];
        }
    }
    return cf/N;
}

int main(){
    struct timespec start, end;
    uint64_t diff;
    int N = pow(2,15);
    int k = pow(2,15);
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

    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    c_one_f = centroid_method_1(array, c_one, N, k);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time by method one = %llu nanoseconds\n", (long long unsigned int) diff);

    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    c_two_f = centroid_method_2(array, c_two, N, k);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("elapsed time by method two = %llu nanoseconds\n", (long long unsigned int) diff);
    return 0;
}
