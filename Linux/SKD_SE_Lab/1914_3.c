/*
* Name: Suman Mondal
* Roll no: 001911001014
* BEIT UG-2
* Software Engineering Assignment 
* Question 3
*/

#include<stdio.h>
#include<stdlib.h>

//Global declarations
int **matrix;
int rows;
int columns;
char* string_bit;
const int LSB_bit = 2; //constant value

//finding the embedded information
void find_message()
{
    int flag = 0;
    //string declaration
    string_bit = (char*)malloc( 3 * 3 * LSB_bit *sizeof(char));
    for(int  i = 0;i < rows; i++)
    {
        for(int j = 0;j < columns; j++)
        {
            for(int  k = LSB_bit-1; k >= 0; k--)
            {
                if(matrix[i][j] & (1<<k) )
                {
                    *( string_bit + flag + LSB_bit-k-1) = '1';
                }
                else
                {
                    *( string_bit + flag + LSB_bit-k-1) = '0';
                }
            }
            flag += LSB_bit;
        }
    } 
}

int main()
{
    //matrix whose information is to be found
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

    find_message();

    //printing of the string
    printf("INFORMATION EMBEDDED IN MATRIX :  \n");
    printf("%s\n", string_bit);

    return 0;
}