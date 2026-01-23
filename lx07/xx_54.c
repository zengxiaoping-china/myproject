#include<stdio.h>

int main(){
    int f(int n);
    int n,sum=0;
    printf("\n请输入一个整数：");
    scanf("%d",&n);
    printf("\n");
    for (int i = 2; i <= n; i++)
    {
        sum=f(i);
    }  
    printf("\n%d 的阶乘值是：%4d\n",n,sum);

}

int f(int n){
    static int f = 1;
    printf("%-2d x %-2d = ",f,n);
    f = f * n;
    printf("%-2d\n",f);
    return(f);
}