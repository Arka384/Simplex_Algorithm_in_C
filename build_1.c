/*
    build_1:
        all equations should be given in generalized form.Currently for maximization problems only.

        1. all index of matrix and array will start from 1
           table matrix is the main table of allocations

        2. input() function makes the initial table too.
           the initial allocation will always use last variables as cb and cj

    After second try the initial table is completed and it is done along with the input function
    so while taking input the initial table is done. with zj-cj too.

*/

#include<stdio.h>
#include<stdlib.h>
#define size 10

float table[size][size]={0};
float cj[size]={0}, zj_cj[size]={0}, min_ratio[size]={0};
int N,C;    //n = number of variables, C = number of constraints
int n;  //actual number of columns in the table

void input(void);
void print_all(void);
void print_table(void);
void find_zjcj(void);   //function which calculates zj-cj row

int main()
{
    input();
    print_table();
}


void find_zjcj()
{
    int i,j,k=1;    //k is zj-cj array size
    float zj=0.0;
    
    for(j=5;j<=n;j++)
    {
        for(i=1;i<=C;i++)
            zj = zj + table[i][1]*table[i][j];    //calculating zj
        zj_cj[k] = zj - cj[k];
        k++;
    }
}

void input()
{   //makes the initial table too (table 1)
    int i,j,x;
    printf("\nEnter the number of variables: ");
    scanf("%d",&N);
    printf("\nEnter the number of constraints: ");
    scanf("%d", &C);

    n = N+4;    //actual number of columns

    printf("\nEnter the Maximization problem:\n");  //directly into cj
    for(i=1;i<=N;i++)
    {
        printf("\nCoefficient for variable x%d: ",i);
        scanf("%f", &cj[i]);
    }
    
    printf("\nNow enter the constraints: ");    //directly into table
    for(i=1;i<=C;i++)   
    {
        printf("\nEnter constraint %d",i);  
        for(j=5;j<=n;j++)   //first 4 columns are preserved
        {                   //variables start from column 5
            printf("\nCoefficient of x%d: ",j-4);
            fflush(stdin);
            scanf("%f", &table[i][j]);
        }
        printf("\nWhich equals to = ");
        scanf("%f", &table[i][4]);
    }
    
    for(i=1,j=1;i<=C;i++)
    {
        x = N-C+i;
        table[i][1] = cj[x];
        table[i][2] = x;
        table[i][3] = x;
    }

    find_zjcj();    //calling this to complete initial table
}

void print_table()
{
    int i,j;
    printf("\nCB\tB\txb\tb");
    for(i=1;i<=N;i++)
        printf("\ta%d",i);
    printf("\n");
    for(i=1;i<=C;i++)   
    {
        for(j=1;j<=n;j++)
            printf("%.1f\t", table[i][j]);
        printf("\n");
    }
    printf("\t\tzj-cj\t\t");
    for(i=1;i<=N;i++)
        printf("%.1f\t",zj_cj[i]);
}

void print_all()
{
    int i,j;
    printf("\nMax Z = ");
    for(i=1;i<=N;i++)
        printf(" %.1f ", cj[i]);
    printf("\nSubject to, \n");
    for(i=1;i<=C;i++)   
    {
        for(j=1;j<=n;j++)
            printf(" %.1f ", table[i][j]);
        printf("\n");
    }
}