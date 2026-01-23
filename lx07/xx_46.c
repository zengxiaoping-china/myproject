#include<stdio.h>

int main(){
    int max(int x,int y);
    int arr[10],m,i,n;
    printf("\n请输入十个整数：");
    for(i=0;i<10;i++){
        scanf("%d",&arr[i]);
    }
    for(i=1,m=arr[0],n=0;i<10;i++){
        if(max(m,arr[i])>m){
            m = max(m,arr[i]);
            n = i;
        }
    }
    printf("\n十个整数中最大的数字是：%d",m);
    printf("\n\n最大的数字%d的位置是：%d",m,n+1);
    printf("\n");
    return 0;
}

int max(int x,int y){
    return(x > y ? x : y);
}