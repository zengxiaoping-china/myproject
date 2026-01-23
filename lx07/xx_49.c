//练习一维数组作为函数参数使用

#include<stdio.h>

int main(){
    void sort(int arr[],int n);
    int arr[10];
    int i,n;
    n = sizeof(arr)/sizeof(arr[0]);
    printf("\n请输入%d个整数：",n);
    for(i=0; i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("\n输入的%d个整数是：",n);
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n\n");
    sort(arr,n);
    printf("%d个整数排序后是：",n);
    for ( i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}

void sort(int arr[],int n){
    int i,j,k,temp;
    for ( i = 0; i < n-1; i++)
    {
        for ( j = i+1; j < n; j++)
        {
            if(arr[j]<arr[i]){
                k = j;
            }
        }
        temp = arr[i],arr[i] = arr[k],arr[k] = temp;
    }
}