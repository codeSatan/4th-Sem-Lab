/*
 * Name: Suman Mondal
 * Roll: 001911001014
 * Class: IT-UG2,2nd Year, 2nd Semester
 * Software Engineering Lab Soln.

Showing the characteristics of the device on which this program has been executed on using mpstat command:
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ mpstat
Linux 4.4.0-18362-Microsoft (DESKTOP-JI3FIB5)   04/02/21        _x86_64_        (8 CPU)

16:07:09     CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
16:07:09     all    7.00    0.00    8.39    0.00    1.50    0.00    0.00    0.00    0.00   83.11

To execute the source code in Linux commandline use command:
gcc 14_Suman_Mondal.c -lpthread


"8 THREADS WERE USED:"
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ gcc 14_Suman_Mondal.c -o suman -lpthread
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ ./suman 8 1600 0
Total time taken by the operation is 8.477610 seconds 

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

"1 THEAD WAS USED:"
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ gcc 14_Suman_Mondal.c -o suman -lpthread
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ ./suman 1 1600 0
Total time taken by the operation is 44.908974 seconds

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


OUTPUT (checking for display)
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ gcc 14_Suman_Mondal.c -lpthread
suman_mondal@DESKTOP-JI3FIB5:~/Linux/UR_SE_Lab$ ./a.out 4 4 1
Total time taken by the operation is 0.1495 seconds

Matrix A: 
1       1       1       0
1       0       0       1
0       0       1       1
0       0       1       1

Matrix B: 
0       1       1       0
1       1       1       0
0       0       0       1
0       1       1       0

Matrix C: 
1       2       2       1
0       2       2       0
0       1       1       1
0       1       1       1

*/


//header files needed
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define U_INT unsigned int              //macros 

//Global matrices
U_INT **matrixA;
U_INT **matrixB;
U_INT **matrixC;

//to find the minimum
int min(int a, int b)
{
    return ((a<b)?a:b); 
}

//to display the matrices
void displayMatrix(U_INT **matrix,int n)
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

//childThread function and parallel matrix multiplication 
void *childThread(void *arg_arr)
{
    int *arr_param = (int*)arg_arr;
    int blockNo = arr_param[0];
    int dimension = arr_param[1];
    int blockSize = arr_param[2];

     for (int i = blockNo * blockSize;
         i < min((blockNo + 1) * blockSize, dimension); i++) {
        for (int j = 0; j < dimension; j++) {
            matrixC[i][j] = 0;
            for (int k = 0; k < dimension; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

//main method
int main(int args, char *arr[])
{
    //checking the number of arguments and if they are only 3 arguments
    if(args !=4)
    {
        printf("Please check the number of arguments\n");
        exit(-1);
    }
    
    //initialisation using the entries by the user
    int noOfThreads = atoi(arr[1]);
    int dimension = atoi(arr[2]);
    int display = atoi(arr[3]);

    //check condition for if the number of threads are more than the dimensions 
    noOfThreads = min(noOfThreads,dimension);
    
    //matrix initialisation
    matrixA = (U_INT**)malloc(dimension *sizeof(U_INT*));
    matrixB = (U_INT**)malloc(dimension *sizeof(U_INT*));
    matrixC = (U_INT**)malloc(dimension *sizeof(U_INT*));

    for (int i = 0; i < dimension; i++) {
        matrixA[i] = (U_INT *)malloc(dimension * sizeof(U_INT));
        matrixB[i] = (U_INT *)malloc(dimension * sizeof(U_INT));
        matrixC[i] = (U_INT *)malloc(dimension * sizeof(U_INT));
    }

    for(int i=0; i<dimension; i++)
    {
        for(int j=0; j<dimension; j++)
        {
            //randomly assigned with 0s and 1s
            matrixA[i][j] = rand()%2;
            matrixB[i][j] = rand()%2;
        }
    }

    //start of the timer
    struct timeval time1;
    gettimeofday(&time1, NULL);

    //creation of threads
    pthread_t threadID[noOfThreads];

    for (int i =0; i<noOfThreads; i++)
    {
        int *threadParameters =(int *)malloc(3 * sizeof(int*));
        threadParameters[0] = i;                        //block number
        threadParameters[1] = dimension;                //dimension
        threadParameters[2] = dimension/noOfThreads;    //blocksize
        int ret_val = pthread_create(&threadID[i], NULL, childThread, (void *)threadParameters);
        if (ret_val != 0) printf("Error in thread creation");
    }
    
    //joining of the threads
    for (int i = 0; i < noOfThreads; i++)
    {
        pthread_join(threadID[i], NULL); 
    }

    //end of the timer
    struct timeval time2;
    gettimeofday(&time2, NULL);

    long ms =
        (time2.tv_sec * 1000000 + time2.tv_usec) - (time1.tv_sec * 1000000 + time1.tv_usec);
    long s = ms/1000000;
    ms = ms%1000000;
    printf("Total time taken by the operation is %ld.%ld seconds\n\n",s,ms);
    
    //matrix display if needed
    if(display == 1)
    {
        printf("\nMatrix A: \n");
        displayMatrix(matrixA, dimension);
        printf("\nMatrix B: \n");
        displayMatrix(matrixB, dimension);
        printf("\nMatrix C: \n");
        displayMatrix(matrixC, dimension);
    }
    return 0;
}