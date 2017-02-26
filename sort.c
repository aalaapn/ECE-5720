#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h> /* for clock_gettime */
#include <stdint.h> /* for uint64 definition */
#include <math.h>

#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define MIN(A, B) (((A) > (B)) ? (B) : (A))
#define UP 0
#define DOWN 1
#define BILLION 1000000000L //used to convert seconds to nano seconds



int m;

void swap(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void bitonic_sort_seq(int start, int length, int *seq, int flag)
{
    int i;
    int split_length;

    if (length == 1)
        return;

    if (length % 2 !=0 )
    {
        printf("error\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
    for (i = start; i < start + split_length; i++)
    {
        if (flag == UP)
        {
            if (seq[i] < seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
        else
        {
            if (seq[i] > seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
    }

    bitonic_sort_seq(start, split_length, seq, flag);
    bitonic_sort_seq(start + split_length, split_length, seq, flag);
}

void bitonic_sort_par(int start, int length, int *seq, int flag)
{
    int i;
    int split_length;

    if (length == 1)
        return;

    if (length % 2 !=0 )
    {
        printf("The length of a (sub)sequence is not divided by 2.\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
#pragma omp parallel for shared(seq, flag, start, split_length) private(i)
    for (i = start; i < start + split_length; i++)
    {
        if (flag == UP)
        {
            if (seq[i] < seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
        else
        {
            if (seq[i] > seq[i + split_length])
                swap(&seq[i], &seq[i + split_length]);
        }
    }
    #pragma omp sections
    if (split_length > m)
    {
        // m is the size of sub part-> n/numThreads
        bitonic_sort_par(start, split_length, seq, flag);
        bitonic_sort_par(start + split_length, split_length, seq, flag);
    }

    return;
}


main()
{
    int i, j;
    int n;
    int flag;
    int *seq;
    int *seq2;

    //Variables used for timing
    struct timespec start, end;
    uint64_t diff;

    double startTime, elapsedTime; /* for checking/testing timing */
    double clockZero = 0.0;

    int numThreads,id;
    n = 16;
    seq = (int *) malloc (n * sizeof(int));
    seq2 = (int *) malloc (n * sizeof(int));

    int fill;
    for (i = 0; i < n; i++){
        fill = rand()/10000000;
        seq[i] = fill;
        seq2[i] = fill;
    }

    // start


    numThreads =  omp_get_max_threads();

    // making sure input is okay
    if ( n < numThreads * 2 )
    {
        printf("The size of the sequence is less than 2 * the number of processes.\n");
        exit(0);
    }

    // bitonic sort
    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    bitonic_sort_par(0, n, seq, UP);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("parallel: %llu\n", (long long unsigned int) diff);

    clock_gettime(CLOCK_MONOTONIC, &start); /* mark start time */
    bitonic_sort_seq(0, n, seq2, UP);
    clock_gettime(CLOCK_MONOTONIC, &end);
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
    printf("seqential %llu\n", (long long unsigned int) diff);

    //end


    free(seq);
}