
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
void printArray(float **array, int N, int k){
    int i;
    int j;
    for(j=1; j!=k; j++){
        for(i=1; i!=N; i++){
            printf("%f ", array[i][j]);
        }
        printf("\n");
    }
}

int main(){
    //Variables used for timing
    struct timespec start, end;
    uint64_t diff;
    
    int N = 3;//pow(2,15);
    int k = 3;//pow(2,15);
    float **array;
    int i;
    int j;
    float c_one[k];
    float c_two[N];
    float c_one_f = 0;
    float c_two_f = 0;

    array = create_2D_int_array(N, k);

    printArray(array, N, k);
}