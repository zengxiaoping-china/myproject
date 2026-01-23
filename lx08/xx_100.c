//习题9.写一函数,将一个3X3的整型矩阵转置。

#include<stdio.h>

void transpose_matrix(int src[][3], int dest[][3], int rows, int cols);

int main(){
    int rows=3,cols=3;
    int array_src[3][3];
    int array_dest[3][3];
    int *p,i;
    p=array_src[0];

    //初始化
    for ( i = 0; i < 9; i++,p++)
    {
        *p=i+1;
    }

    //整型矩阵转置
    transpose_matrix(array_src,array_dest,rows,cols);
    
    //输出原整形矩阵
    printf("\n原整形矩阵\n");
    p=array_src[0];
    for ( i = 0; i < 9; i++,p++)
    {
        printf("%d ",*p);
        if((i+1)%3==0) printf("\n");
    }

    //输出转置后的整形矩阵
    printf("\n转置后的整形矩阵\n");
    p=array_dest[0];
    for ( i = 0; i < 9; i++,p++)
    {
        printf("%d ",*p);
        if((i+1)%3==0) printf("\n");
    }
}

void transpose_matrix(int src[][3], int dest[][3], int rows, int cols){
    int *p1,*p2,i,j,temp;
    p1=src[0];
    p2=dest[0];
    for ( i = 0; i < rows*cols; i++)
    {
        *p2=*p1;
        p1++;
        p2++;
    }
    for ( i = 0; i < rows; i++)
    {
        for ( j = i+1; j < cols; j++)
        {
            temp=dest[i][j];
            dest[i][j]=dest[j][i];
            dest[j][i]=temp;
        }   
    }
    
}