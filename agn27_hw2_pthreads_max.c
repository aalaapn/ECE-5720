/**
Aalaap Narasipura
2-24-2017
Homework 2: pthread_max

//compile instructions
compile with command gcc -pthread agn27_hw2_pthreads_max.c -o agn27_hw2_pthreads_max_out
the run with ./agn27_hw2_pthreads_max_out
**/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h> /* for uint64 definition */
#include <stdlib.h>
#include <time.h> /* for clock_gettime */
#include <math.h> /* for pow function */
#include <pthread.h>

#define BILLION 1000000000L //used to convert seconds to nano seconds
#define NUM_THREADS 12

struct thread_data{
    int **array;
    int c;
    int n;
    int start_index;
};


struct thread_data thread_data_array[NUM_THREADS];

int** create_2D_int_array(int N, int k){
    time_t t; //time used for generating random values
    int i, j; //iteration variables
    int fillNum; //number to store in array
    srand(7);

    //allocating space for array
    int** arr = (int **)malloc(k * sizeof(int *));
    for (i=0; i<N; i++)
         arr[i] = (int*)malloc(N * sizeof(int));
         
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

//function to swap row i and j
void swapRow(int **array, int i, int j){
    int *temp;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//function to swap item (i,j) and (a,b)
void swapItem(int **array, int i, int  j, int a, int b){
    int temp;
    temp = array[i][j];
    array[i][j] = array[a][b];
    array[a][b] = temp;
}


void *findLargestAndSwap(void *threadarg){
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;

    int **array = my_data->array;
    int c = my_data->c;
    int n = my_data-> n;
    int start_index = my_data->start_index;

    int i;
    int largeIndex = 0;
    int largeValue = 0;
    for(i = start_index; i<n; i++){
        if(abs(array[i][c])>abs(largeValue)){
            largeValue = array[i][c];
            largeIndex = i;
        }
    }
    swapItem(array, start_index, c, largeIndex, c);
    pthread_exit(NULL);
}

int main(){
    //Variables used for timing
    struct timespec start, end;
    uint64_t diff;

    //array dimensions
    int N[11];
    int k[11];
    int power;
    for(power = 3; power<14; power++){
        N[power-3] = (int)(pow(2,power));
        k[power-3] = (int)(pow(2,power));
    }
    
    //pthread stuff
    pthread_t threads[NUM_THREADS];   /*thread handles are defined*/
    int err;
    long t;
    pthread_attr_t attr;
    void *status;

    //array creation and print
    int **array;

    //breaking up the work and sorting the threads
    int reps;
    int numberOfRepsPerThread;
    int threadColumnStart = 0;

    //thread creation and sorting
    int j;
    int i;
    int numThreads = NUM_THREADS;

    for(power = 0; power<11; power++){
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        // printf("n is: %d, time is:", N[power]);
        array = create_2D_int_array(N[power], k[power]);
        numberOfRepsPerThread = (int)(N[power]/NUM_THREADS);
        clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
        
        for(i=0; i<N[power]-1; i++){
            threadColumnStart = i;
            numberOfRepsPerThread = (int)((N[power]-i)/numThreads);
                for(t= 0; t<numThreads; t++){
                    thread_data_array[t].array = array;
                    thread_data_array[t].c = threadColumnStart+i;
                    thread_data_array[t].n = k[power];
                    thread_data_array[t].start_index = i;
                    err = pthread_create(&threads[t], NULL, findLargestAndSwap, (void *)&thread_data_array[t]); 
                    if (err){ break;
                   }
                   threadColumnStart = threadColumnStart + numberOfRepsPerThread;
                }
        }
        
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
        printf("%llu\n", (long long unsigned int) diff);
        free(array);
    }
     pthread_exit(NULL);
}
