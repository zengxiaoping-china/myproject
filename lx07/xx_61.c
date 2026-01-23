//写一个函数,使给定的一个3X3的二维整型数组转置,即行列互换。

#include<stdio.h>

void transpose(int arr[][3]);
void transpose_new(int arr[][3]);

int main(){
    int array[3][3] = {{25,41,36},{45,84,23},{63,92,78}};
    int i,j;
    printf("\n给定下面3x3的二维整形数组，要求对其进行数组转置（行列互换）\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 3; j++)
        {
            printf("%2d ",array[i][j]);
        }
        printf("\n");
    }
    transpose_new(array);
    printf("\n这个3x3的二维整形数组进行数组转置（行列互换）后如下\n\n");
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 3; j++)
        {
            printf("%2d ",array[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void transpose(int arr[][3]){
    int array[3][3];
    int i,j;
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 3; j++)
        {
            array[j][i] = arr[i][j];
        }
    }
    for ( i = 0; i < 3; i++)
    {
        for ( j = 0; j < 3; j++)
        {
            arr[i][j] = array[i][j];
        }
    }
}

void transpose_new(int arr[][3]){
    int i,j,temp = 0;
    for ( i = 0; i < 3; i++)
    {
        for ( j = i+1; j < 3; j++)
        {
            temp = arr[i][j];
            arr[i][j] = arr[j][i];
            arr[j][i] = temp;
        }
    }
}