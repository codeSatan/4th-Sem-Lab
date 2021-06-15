/*
* Name: Suman Mondal
* Roll no: 001911001014
* BEIT UG-2
* Software Engineering Assignment 
* Question 1
*/

#include <stdio.h>
#include <stdlib.h>

//global declarations
int **matrix;
int ***resultant_matrix;
int rows;
int columns;

void bitplanes();
void display();

int main()
{
    //entering the Matrix whose bit plane is to be found
    printf("Enter the dimensions of the matrix in form of row and columns\n");
    scanf("%d%d",&rows, &columns);

    matrix = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++)
    {
        matrix[i]=(int*)malloc(columns * sizeof(int));
    }    
    printf("Enter your Matrix:\n");
    for(int i = 0;i<rows;i++)
    {
        for(int j =0; j<columns; j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }

    bitplanes();
    display();

    return 0;
}


void bitplanes()
{
    //declaration of 3D matrix
    resultant_matrix = (int***)malloc( 8 * sizeof(int**));

    for(int i = 0;i < 8;i++)
    {
        resultant_matrix[i] = (int**)malloc( 8 * sizeof(int*));
    }
    for(int i = 0;i < 8;i++)
    {
        for(int j = 0;j < 8;j++)
        {
           resultant_matrix[i][j] = (int*)malloc( 8 * sizeof(int));    
        }
    }

    //formation of the bit planes using Bit shifting
    for(int i = 0; i < 8;i++)
    {
        for(int j = 0;j < rows;j++)
        {
            for(int k = 0;k < columns;k++)
            {
                resultant_matrix[i][j][k] = ((1<<i)&matrix[j][k]) ? (1<<i) : 0;
            }
        }
    }
}

void display()
{
    //display of the resultant bitplanes
    for(int i = 0;i < 8;i++)
    {       
        printf("\n%dth BITPLANE : \n",i);
        for(int j = 0;j < rows;j++)
        {
            for(int k = 0;k < columns;k++)
            {
                printf(" %d ",resultant_matrix[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}