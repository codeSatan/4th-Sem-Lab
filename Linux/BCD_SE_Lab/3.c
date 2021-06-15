/*
* Name: Suman Mondal
* Roll no: 001911001014
* BEIT UG-2
* Software Engineering Assignment 
* Question 3
*/

//to run enter in the terminal: gcc 3.c -lm 

//To find the secret information via lagrange interpolation method


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//struct body of Point
struct Point {
    int x;
    int y;
};

int *getSecret(int k);
void display(int *coefficients, int k);
int getFofX(int *coefficients, int k, int x);
struct Point *getpairs(int *secret_data, int k, int n);
void randomPoints(struct Point *pairs, int n);
int *findSolution(struct Point *pairs, int k);
double findDeterminant(double **a, int n);

//driver code
int main() 
{
    int k;
    printf("Enter k (number of secret integers):\n");
    scanf("%d", &k);

    if (k <= 0) 
    {
        printf("k should be positive!\n");
        return EXIT_FAILURE;
    }

    //calling function
    int *secret = getSecret(k);
    display(secret, k);

    int n;

    //to be distributed to n persons
    printf("Enter n (number of persons to distribute information to):\n");
    scanf("%d", &n);
    
    if (n < k) {
        printf("n should be greater than k!\n");
        return EXIT_FAILURE;
    }

    struct Point *points = getpairs(secret, k, n);
    printf("\nPrintng the %d points\n", n);
    for (int i = 0; i < n; i++) {
        printf("( %d , %d )\n", points[i].x, points[i].y);
    }

    // for selecting k random pairs we shuffle the array of pairs
    // and select the first k pairs
    randomPoints(points, n);

    int *newData = findSolution(points, k);
    
    printf("\nPrintng the %d retrived secret integers:\n", k);
    for (int i = 0; i < k; i++) 
    {
        printf("%d\n", newData[i]);
    }
}

// input k secret integers
int *getSecret(int k) 
{
    int *data = (int *)malloc(sizeof(int) * k);
    printf("Enter the %d  non-negative integers:\n", k);
    int z = 0;
    for (int i = 0; i < k; i++) 
    {
        scanf("%d", &data[i]);
        if (data[i] < 0) {
            printf("All secret integers should be non-negative!\n");
            exit(EXIT_FAILURE);
        }
        z = z | data[i]; 
    }
    if (z == 0) 
    {
        printf("Atleast one of the secret integers should be greater than 0!\n");
        exit(EXIT_FAILURE);
    }
    return data;
}

// print the polynomial formed
void display(int *coefficients, int k)
{
    printf("\nPolynomial formed from secret integers :\n");
    printf("f(x) = ");
    for (int i = 0; i < k; i++) {
        printf("%d(x^%d)%s", coefficients[i], i, (i < k - 1) ? " + " : "\n\n");
    }
}

// get F(X)
int getFofX(int *coefficients, int k, int x) {
    int sum = 0;
    int powerOfx = 1;
    for (int i = 0; i < k; i++, powerOfx *= x) {
        sum += (coefficients[i] * powerOfx);
    }
    return sum;
}

// form array of pairs to be distributed
struct Point *getpairs(int *secret_data, int k, int n) {
    struct Point *pairs = (struct Point *)malloc(sizeof(struct Point) * n);
    for (int x = 1; x <= n; x++)
     {
        int y = getFofX(secret_data, k, x);
        pairs[x - 1].x = x;
        pairs[x - 1].y = y;
    }
    return pairs;
}

// shuffle the array of pairs
void randomPoints(struct Point *pairs, int n)
 {
    // seed random number generator with current time
    srand(time(NULL));
    for (int i = 1; i < n; i++) 
    {
        int r = rand() % (i + 1);
        struct Point temp = pairs[i];
        pairs[i] = pairs[r];
        pairs[r] = temp;
    }
}

int *findSolution(struct Point *pairs, int k) 
{
    printf("\nPrintng the %d pairs\n", k);
    for (int i = 0; i < k; i++) 
    {
        printf("( %d , %d )\n", pairs[i].x, pairs[i].y);
    }

    int *secret_data = (int *)malloc(sizeof(int) * k);
    double **denom = (double **)malloc(sizeof(double *) * k);
    double **num = (double **)malloc(sizeof(double *) * k);
    for (int i = 0; i < k; i++) 
    {
        denom[i] = (double *)malloc(sizeof(double) * k);
        num[i] = (double *)malloc(sizeof(double) * k);
    }

    int n = k - 1;

    for (int i = 0; i <= n; i++) denom[n][i] = 1;
    for (int i = n - 1; i >= 0; i--) 
    {
        for (int j = 0; j <= n; j++) 
        {
            denom[i][j] = denom[i+1][j] * pairs[j].x;
        }
    }

    double det_denom = findDeterminant(denom, k);

    for (int i = 0; i <= n; i++) 
    {
        secret_data[i] = pow(-1, n - i);
        for (int j = 0; j <= n; j++) num[0][j] = pairs[j].y;

        for (int ii = n; ii > 0; ii--) 
        {
            for (int jj = 0; jj <= n; jj++) 
            {
                if (n - ii < i) 
                {
                    num[ii][jj] = pow(pairs[jj].x, n - ii);
                } 
                else  
                {
                    num[ii][jj] = pow(pairs[jj].x, n - ii + 1);
                }
            }
        } 
        double det_num = findDeterminant(num, k);
        secret_data[i] *= det_num;
        secret_data[i] /= det_denom;
    }

    // free the matrices
    for (int i = 0; i < k; i++) 
    {
        free(denom[i]);
        free(num[i]);
    }

    free(denom);
    free(num);
    return secret_data;
}

double findDeterminant(double **a, int n) 
{
    int i, j, j1, j2;
    double det = 0;
    double **m = NULL;

    if (n < 1) 
    { 
        printf("Determinant() on matrix od size less than 1 called!\n");
        return EXIT_FAILURE;
    } 
    else if (n == 1) 
    { 
        det = a[0][0];
    }
    else if (n == 2)
    {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
    } 
    else 
    {
        det = 0;
        for (j1 = 0; j1 < n; j1++) 
        {
            m = malloc((n - 1) * sizeof(double *));
            for (i = 0; i < n - 1; i++) m[i] = malloc((n - 1) * sizeof(double));
            for (i = 1; i < n; i++) 
            {
                j2 = 0;
                for (j = 0; j < n; j++) 
                {
                    if (j == j1) continue;
                    m[i - 1][j2] = a[i][j];
                    j2++;
                }
            }
            det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * findDeterminant(m, n - 1);
            for (i = 0; i < n - 1; i++) free(m[i]);
            free(m);
        }
    }
    return (det);
}