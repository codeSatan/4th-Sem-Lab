/*
* Name: Suman Mondal
* Roll no: 001911001014
* BEIT UG-2
* Software Engineering Assignment 
* Question 1
*/

//to run enter in the terminal: g++ 1.cpp

//Program to solve a transportation problem using Vogels Aprroximation Method

//header files
#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<stdlib.h>
#define MAX 50

using namespace std;
enum boolean{FALSE,TRUE};

//class declarations
class voggelsmethod
{
	//class data members
    int data[MAX][MAX];
    int requered[MAX];
    int capacity[MAX];
    int allocation[MAX][MAX];
    int no_of_rows,no_of_columns,no_of_allocation;

	//member functions
    public:
	void lcmethod();
	void setColumn(int no){no_of_columns=no;};
	void setRow(int no){no_of_rows=no;}
	void getData();
	void getCapacity();
	void getRequiredValue();
	void makeAllocation();
	boolean checkValue(int [],int);
	int getMinVal(int [],int);
	int getTotalMinVal(int [],int,int);
	int getMinValsPos(int,int [],int);
	void display();
	int getPanalty(int [],int);
};

//calculating the LC
void voggelsmethod::lcmethod()
{
	int  j ;
    for(int i=0;i<MAX;i++)
	{
		capacity[i]=0;
		requered[i]=0;
		for(int j=0;j<MAX;j++)
		{
		    data[i][j]=0;
		    allocation[i][j]=0;
		}
	}
    no_of_rows=no_of_columns=no_of_allocation=0;
}

//calculating the penalty
int voggelsmethod::getPanalty(int array[],int no)
{
    int i,j,temp;
    for(i=0;i<no;i++)
		for(j=i+1;j<no;j++)
	    	if(array[i]>array[j])
			{
				temp=array[i];
				array[i]=array[j];
				array[j]=temp;
	    	}
    return array[1]-array[0];
}

//to calculate the min value
int voggelsmethod::getMinVal(int array[],int no)
{
    int min=array[0];
    for(int i=0;i<no;i++)
	if(array[i]<min)
	    min=array[i];
    return min;
}

//to get the position of the minimum variable
int voggelsmethod::getMinValsPos(int value,int temp_data[],int no)
{
    int k;
    for(int i=0;i<no;i++)
	if(temp_data[i]==value)
	    return i;
    return -1;
}

//find the total
int voggelsmethod::getTotalMinVal(int array[],int n,int value)
{
    int no=0;
    for(int i=0;i<n;i++)
	if(array[i]==value)
		no++;
    return no;
}

//checking for value
boolean voggelsmethod::checkValue(int arr[],int no)
{
    for(int i=0;i<no;i++)
	if(arr[i]!=0)
	    return FALSE;
    return TRUE;
}

//copy the array
void arrayCopy(int start,int end,int array1[],int start1,int array2[])
{
    for(int i=start,j=start1;i<end;i++,j++)
	array2[j]=array1[i];
}

//finding the total
int getTotal(int array[],int no){
    int sum=0;
    for(int i=0;i<no;i++)
	sum+=array[i];
    return sum;
}

//copy the matrix
void copy2DArray(int startRow,int startCol,int endRow,int endCol,int array[][MAX],int start1Row,int start1Col,int ans[][MAX])
{
    for(int i=startRow,k=start1Row;i<endRow;i++,k++)
	for(int j=startCol,l=start1Col;j<endCol;j++,l++)
	    ans[k][l]=array[i][j];
}

//getting the maximum value
int getMaxVal(int array[MAX],int no)
{
    int max=0;
    for(int i=0;i<no;i++)
	if(array[i]>max)
	    max=array[i];
    return max;
}

//getting the maximum value position
int getMaxValPos(int array[MAX],int no,int value)
{
    for(int i=0;i<no;i++)
	if(value==array[i])
	    return i;
    return -1;
}

//making the allocations
void voggelsmethod::makeAllocation()
{
    int i=0,j=0,min,total_min;
    int temp_requered[MAX]={0};
    int temp_capacity[MAX]={0};
    int temp_data[MAX][MAX]={0};
    int position[MAX];
    int dataPos[MAX];
    int sum_of_cap,sum_of_req;
    sum_of_cap=getTotal(capacity,no_of_rows);
    sum_of_req=getTotal(requered,no_of_columns);
    if(sum_of_cap!=sum_of_req)
	{
		if(sum_of_cap>sum_of_req)
		{
	    	for(j=0;j<no_of_rows;j++)
				data[j][no_of_columns]=0;
	    	requered[no_of_columns]=sum_of_cap-sum_of_req;
	    	no_of_columns++;
		}
		else
		{
	    	for(j=0;j<no_of_columns;j++)
				data[no_of_rows][j]=0;
	    	capacity[no_of_rows]=sum_of_req-sum_of_cap;
	    	no_of_rows++;
		}
    }
    i=j=0;

    arrayCopy(0,no_of_rows,capacity,0,temp_capacity);
    arrayCopy(0,no_of_columns,requered,0,temp_requered);
    copy2DArray(0,0,no_of_rows,no_of_columns,data,0,0,temp_data);


    int rowPanalty[MAX]={0};
    int colPanalty[MAX]={0};
    int panaltyData[MAX]={0},n=0;

    while(!checkValue(temp_capacity,no_of_rows) || !checkValue(temp_requered,no_of_columns))
	{
		for(i=0;i<no_of_rows;i++)
		{
	    	arrayCopy(0,no_of_columns,temp_data[i],0,panaltyData);
	    	if(temp_capacity[i]!=0)
				rowPanalty[i]=getPanalty(panaltyData,no_of_columns);
	    	else
			rowPanalty[i]=0;
		}
		for(i=0;i<no_of_columns;i++)	
		{
	    	for(j=0;j<no_of_rows;j++)
				panaltyData[j]=temp_data[j][i];
	    	if(requered[i]!=0)
				colPanalty[i]=getPanalty(panaltyData,no_of_rows);
	    	else
				colPanalty[i]=0;
		}
		int maxRowPanalty=getMaxVal(rowPanalty,no_of_rows);
		int maxColPanalty=getMaxVal(colPanalty,no_of_columns);
		int maxPanRow[MAX]={0};
		int maxPanCol[MAX]={0};
		if(maxRowPanalty>maxColPanalty)
		{
	    	i=getMaxValPos(rowPanalty,no_of_rows,maxRowPanalty);
	    	for(j=0;j<no_of_columns;j++)
				maxPanRow[j]=temp_data[i][j];
	    	min=getMinVal(maxPanRow,no_of_columns);
	    	j=getMinValsPos(min,maxPanRow,no_of_columns);
		}
		else
		{
	    	j=getMaxValPos(colPanalty,no_of_columns,maxColPanalty);
	    	for(i=0;i<no_of_rows;i++)
			maxPanCol[i]=temp_data[i][j];
	    	min=getMinVal(maxPanCol,no_of_rows);
	    	i=getMinValsPos(min,maxPanCol,no_of_rows);
		}

		if(temp_capacity[i]>temp_requered[j])
		{
	    	allocation[i][j]=temp_requered[j];
	    	for(int k=0;k<no_of_rows;k++)
				temp_data[k][j]=9999;
	    	temp_capacity[i]-=temp_requered[j];
	    	temp_requered[j]=0;
		}
		else if(temp_capacity[i]<temp_requered[j])
		{
	    	allocation[i][j]=temp_capacity[i];
	    	for(int k=0;k<no_of_columns;k++)
				temp_data[i][k]=9999;
	    	temp_requered[j]-=temp_capacity[i];
	    	temp_capacity[i]=0;
		}
		else
		{
	    	int k;
	    	allocation[i][j]=temp_capacity[i];
	    	for(k=0;k<no_of_rows;k++)
			temp_data[k][j]=9999;
	    	for(k=0;k<no_of_columns;k++)
				temp_data[i][k]=9999;
	    	temp_requered[j]=temp_capacity[i]=0;
		}
		n++;
    }
    no_of_allocation=n;
}

//getting capacity
void voggelsmethod::getCapacity()
{
    cout<<"Enter capacity for each source : \n";
    for(int i=0;i<no_of_rows;i++)
	{
		cout<<"s"<<i+1<<" : ";
		cin>>capacity[i];
    }
}

//getting the required value for each destination
void voggelsmethod::getRequiredValue()
{
    cout<<"Enter required unit value for each destination : \n";
    for(int i=0;i<no_of_columns;i++)
	{
		cout<<"d"<<i+1<<" : ";
		cin>>requered[i];
    }
}

//to display
void voggelsmethod::display()
{
    int i;
    cout<<"\nGiven data :\n";
    cout<<setw(9);
    for(i=0;i<no_of_columns;i++)
        cout<<"D"<<i+1<<setw(4);
    cout<<setw(5)<<"cap"<<endl<<setw(0);
    for(i=0;i<no_of_rows;i++)
	{
        cout<<setw(3)<<"S"<<i+1;
        for(int j=0;j<no_of_columns;j++)
            cout<<setw(5)<<data[i][j];
        cout<<setw(5)<<capacity[i]<<endl;
    }
    cout<<setw(4)<<"req";
    for(i=0;i<no_of_columns;i++)
        cout<<setw(5)<<requered[i];

    cout<<"\n\n After allocation :\n";
    for(i=0;i<no_of_rows;i++)
	{
        for(int j=0;j<no_of_columns;j++)
		{
            if(allocation[i][j]!=0)
                cout<<setw(5)<<data[i][j]<<"*"<<setw(2)<<allocation[i][j];
            else
                cout<<setw(8)<<data[i][j];
        }
        cout<<endl;
    }
    int k=0,sum=0;
    for(i=0;i<no_of_rows;i++)
	{
        for(int j=0;j<no_of_columns;j++)
		{
            if(allocation[i][j]!=0)
			{
                cout<<"("<<data[i][j]<<" * "<<allocation[i][j]<<")";
                if(k < no_of_allocation-1)
				{
                    cout<<"+";
                    k++;
                }
                sum+=data[i][j]*allocation[i][j];
            }
        }
    }
    cout<<"\nanswer : "<<sum;
}

//getting the data
void voggelsmethod::getData(){
    cout<<"Enter source to destination data:"<<endl;
    for(int i=0;i<no_of_rows;i++)
	{
        cout<<"Enter "<<i<<"th row : ";
        for(int j=0;j<no_of_columns;j++){
            cin>>data[i][j];
        }
    }
}

//driver code
int main()
{
	//creating object of the class
    voggelsmethod v;

    int r,c;
    cout<<"Enter no of Rows : ";
    cin>>r;
    cout<<"Enter no of columns : ";
    cin>>c;

	//calling the functions
    v.setColumn(c);
    v.setRow(r);

	//to get the data to work on
    v.getData();
    v.getCapacity();
    v.getRequiredValue();
    v.makeAllocation();

	//display
    v.display();
    return 0;
} 
