//练习使用指针引用数组作为函数参数

#include<stdio.h>

void swap(int *x,int *y);
void inv(int *arr,int n);
void inv_new(int *arr,int n);

int main(){
    int array[10]={1,2,3,4,5,6,7,8,9,10};
    int i,n=10;
    printf("\n");
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n====================\n");
    inv(array,n);
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n====================\n");
    inv_new(array,n);
    for ( i = 0; i < n; i++)
    {
        printf("%d ",array[i]);
    }  
}

void inv(int *arr,int n){
    int i,j;
    for ( i = 0,j=n-1; i <= (n-1)/2; i++,j--)
    {
        //printf("i=%d j=%d\n",i,j);
        swap(arr+i,arr+j);
    }
}

void inv_new(int *arr,int n){
    int *i,*j,*p,m=(n-1)/2;
    i=arr,j=arr+n-1,p=arr+m;
    for (; i <= p; i++,j--)
    {
        swap(i,j);
    } 
}

void swap(int *x,int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y= temp;
}