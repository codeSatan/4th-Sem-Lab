/*
* Name: Suman Mondal
* Roll no: 001911001014
* BEIT UG-2
* Software Engineering Assignment 
* Question 2(i) 2(ii)
*/
 
#include <stdio.h>
#include <stdlib.h>

//global declarations
int **matrix;
char *string_bit;
int rows;
int columns;


//display of the matrix
void display()
{
    printf("Matrix with information embedded within: \n");
    
    for(int i = 0;i < rows;i++)
    {
        for(int j = 0;j < columns;j++)
        {
            printf(" %d ",matrix[i][j]);
        }
        printf("\n");
    }
}

//gets the bitstring entered by the user
void string_input(int bit)
{

    string_bit = (char *) malloc( rows * columns * bit * sizeof(char) );
    
    printf("ENTER YOUR BIT STRING: ");
    scanf("%s",string_bit);

}

//embedding the information into the given matrix
void encoder(int bits)
{

    int flag=0;
    for(int i = 0; i < rows; i++)
    {  

        for(int j = 0; j < columns; j++)
        {

            for(int k = bits - 1; k >= 0; k--)
            {
                if( ( matrix[i][j] & (1<<k) ) && *( string_bit + flag + bits-1-k ) == '0' )
                    matrix[i][j] -= (1<<k);
                else if( !( matrix[i][j] & (1<<k) ) && *( string_bit + flag + bits-1-k ) == '1' )
                    matrix[i][j] += (1<<k);
            }

            flag += bits;
        }
    }
}


int main()
{
    //entering the values of the matrix
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

    int LSB_bit;
    printf("\nEnter 1 for LSB hiding by 1 ");
    printf("\nEnter 2 for LSB hiding by 2 ");
    printf("\nEnter LSB value :");
    scanf("%d",&LSB_bit);

    string_input(LSB_bit);
    encoder(LSB_bit);
    display();
}

