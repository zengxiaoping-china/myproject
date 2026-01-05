#include<stdio.h>

void num_swap(int *arr,int n,int m);

int main(){
    int n,m,i;
    m=3;
    n=10;
    int array[100];
    printf("\n请输入%d个整数：",n);
    for (i = 0; i < n; i++)
    {
        scanf("%d",&array[i]);
    }
    printf("\n您输入的%d个整数是：",n);
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }
    num_swap(array,n,m);
    printf("\n\n%d个整数交换后是：",n);
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
    return 0;
}

void num_swap(int *arr,int n,int m){
    int i;
    int temp[100];
    for ( i = 0; i < m; i++)
    {
        temp[i]=arr[n-m+i];
    }
    for ( i = 0; i < n-m; i++)
    {
        arr[n-1-i]=arr[n-m-1-i];
    }
    for ( i = 0; i < m; i++)
    {
        arr[i]=temp[i];
    }
}