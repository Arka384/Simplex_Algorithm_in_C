/*
    build_2:
        taking input and making initial table is done in build_1.

    updates:
        keyvalue structure the location of the key value for the current table.

        now only one iteration is done 
        after the initial table the code checks the values of zj-cj and finds the keyvalue 
        for the first table.
        this logic or code will be applied after each creation of new table 
        after changing the rows and columns

        the next update is going to be for transffering the rows and columns of the keyvalue.

*/

#include<stdio.h>
#include<stdlib.h>
#define SIZE 10
#define BIGNUM 9999

float table[SIZE][SIZE]={0};
float cj[SIZE]={0}, zj_cj[SIZE]={0}, min_ratio[SIZE]={0};
int N,C;    //n = number of variables, C = number of constraints
int n;  //actual number of columns in the table

typedef struct element{
    int row;
    int col;
}element;
element keyVal; //for key value

void input(void);
void print_all(void);
void print_table(void);
void find_zjcj(void);   //function which calculates zj-cj row
int check_zjcj(void);
void get_min_ratio(void);

int main()
{
    input();    //makes the initial table too
                //  find_zjcj() is called within it
    print_table();

    if(check_zjcj())  //this will be false when optimal solution has been obtained
    {
        get_min_ratio();
        printf("\nkey element = %f\n", table[keyVal.row][keyVal.col]);
    }


}

int check_zjcj()
{
    int i,flag=0;
    float min = BIGNUM;
    
    for(i=1;i<=N;i++)
    {
        if(zj_cj[i] < 0 )
            flag = 1;   //means contains negetive element
        if(zj_cj[i] < min)
        {
            min = zj_cj[i];
            keyVal.col = i+4; //column index of the key element
        }
    }
    return flag;   //means the problem is solved
}

void get_min_ratio()
{
    int i,j;
    float min = BIGNUM;

    for(i=1;i<=C;i++)
    {
        min_ratio[i] = table[i][4] / table[i][keyVal.col];
    }
    i--; //now i contains the size of min_ration[]

    for(j=1;j<=i;j++)
    {
        if(min_ratio[j] < min && min_ratio[j]!=0 && min_ratio[j] > 0)
        {
            min = min_ratio[j];
            keyVal.row = j;
        }
    }
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