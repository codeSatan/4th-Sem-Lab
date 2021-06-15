/*
 * Name: Ronak Sanpui
 * Roll: 001911001042
 * Class: IT-UG2,2nd Year, 2nd Semester
 * Software Engineering Lab Soln.
 */

/*

suman_mondal@DESKTOP-JI3FIB5:~/Linux$ gcc ronak.c -o ronak -pthread
suman_mondal@DESKTOP-JI3FIB5:~/Linux$ ./ronak 8 1600 0
Operation took 8.477610 `secs (8 threads)

13:36:35     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:36:36     all   97.49    0.00    1.82    0.00    0.68    0.00    0.00    0.00    0.00    0.00
13:36:36       0   89.19    0.00    7.21    0.00    3.60    0.00    0.00    0.00    0.00    0.00
13:36:36       1   95.41    0.00    2.75    0.00    1.83    0.00    0.00    0.00    0.00    0.00
13:36:36       2  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:36       3   99.07    0.00    0.93    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:36       4   96.36    0.00    3.64    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:36       5  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:36       6  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:36       7  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00

13:36:36     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:36:37     all   95.76    0.00    3.85    0.00    0.40    0.00    0.00    0.00    0.00    0.00
13:36:37       0   87.00    0.00   10.00    0.00    3.00    0.00    0.00    0.00    0.00    0.00
13:36:37       1   98.95    0.00    1.05    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:37       2  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:37       3  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:37       4   92.47    0.00    7.53    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:37       5   94.57    0.00    5.43    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:37       6   96.74    0.00    3.26    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:36:37       7   96.74    0.00    3.26    0.00    0.00    0.00    0.00    0.00    0.00    0.00

suman_mondal@DESKTOP-JI3FIB5:~/Linux$ ./ronak 1 1600 0
Operation took 44.908974 `secs
suman_mondal@DESKTOP-JI3FIB5:~/Linux$

13:41:52     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
13:41:53     all   14.25    0.00    4.75    0.00    2.44    0.00    0.00    0.00    0.00   78.56
13:41:53       0    2.91    0.00    6.80    0.00    3.88    0.00    0.00    0.00    0.00   86.41
13:41:53       1    2.94    0.00    1.96    0.00    0.00    0.00    0.00    0.00    0.00   95.10
13:41:53       2    4.95    0.00    3.96    0.00    1.98    0.00    0.00    0.00    0.00   89.11
13:41:53       3    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:41:53       4  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
13:41:53       5    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00  100.00
13:41:53       6    5.26    0.00   21.05    0.00   12.28    0.00    0.00    0.00    0.00   61.40
13:41:53       7    0.00    0.00    1.98    0.00    0.00    0.00    0.00    0.00    0.00   98.02

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define u_int unsigned int

// Global matrices
u_int **mat1;
u_int **mat2;
u_int **mat3;

void *threadFunction(void *args);  // Function executed by child thread
void displayMatrix(u_int **matrix,
                   int dimension);  // Function to Display matrix
u_int min(u_int a, u_int b);        // min function for unsigned int

int main(int argc, char *argv[]) {
    // Arguement Validation
    if (argc != 4) {
        printf("Please execute with proper arguements");
        exit(-1);
    }

    // Getting required paramteres from args.
    int noOfThreads = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    int dispFactor = atoi(argv[3]);

    noOfThreads = min(dimension, noOfThreads);

    // Initailizing array
    mat1 = (u_int **)malloc(dimension * sizeof(u_int *));
    mat2 = (u_int **)malloc(dimension * sizeof(u_int *));
    mat3 = (u_int **)malloc(dimension * sizeof(u_int *));

    for (int i = 0; i < dimension; i++) {
        mat1[i] = (u_int *)malloc(dimension * sizeof(u_int));
        mat2[i] = (u_int *)malloc(dimension * sizeof(u_int));
        mat3[i] = (u_int *)malloc(dimension * sizeof(u_int));
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            mat1[i][j] = rand() % 2;
            mat2[i][j] = rand() % 2;
        }
    }

    // Displaying matrix 1 and 2
    if (dispFactor == 1) {
        printf("Matrix A:\n");
        displayMatrix(mat1, dimension);
        printf("Matrix B:\n");
        displayMatrix(mat2, dimension);
    }

    // getting begining gettimeofday()
    struct timeval t1;
    gettimeofday(&t1, NULL);

    // Thread creation
    pthread_t tId[noOfThreads];

    for (int i = 0; i < noOfThreads; i++) {
        int *threadParams = (int *)malloc(sizeof(int) * 3);
        threadParams[0] = dimension;                // dimensopn
        threadParams[1] = dimension / noOfThreads;  // no. of blocks
        threadParams[2] = i;                        // blockNum
        int status =
            pthread_create(&tId[i], NULL, threadFunction, (void *)threadParams);
        if (status != 0) printf("Error in thread creation");
    }

    for (int i = 0; i < noOfThreads; i++) {
        pthread_join(tId[i], NULL);  // joining of threads
    }

    // getting ending gettimeofday()
    struct timeval t2;
    gettimeofday(&t2, NULL);

    // Displaying resultant matrix
    if (dispFactor == 1) {
        printf("Resultant matrix:\n");
        displayMatrix(mat3, dimension);
    }
    long ms =
        (t2.tv_sec * 1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec);
    long s = ms / 1000000;
    ms %= 1000000;
    printf("Operation took %ld.%ld `secs\n", s, ms);
    return 0;
}

// Function executed by child thread
void *threadFunction(void *args) {
    int *params = (int *)args;
    int dimension = params[0];
    int blockSize = params[1];
    int blockNum = params[2];

    for (int i = blockNum * blockSize;
         i < min((blockNum + 1) * blockSize, dimension); i++) {
        for (int j = 0; j < dimension; j++) {
            mat3[i][j] = 0;
            for (int k = 0; k < dimension; k++) {
                mat3[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

// Function to Display matrix
void displayMatrix(u_int **matrix, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// min function for unsigned int
u_int min(u_int a, u_int b) {
    if (a > b)
        return b;
    else
        return a;
}