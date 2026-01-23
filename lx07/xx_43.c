//练习递归函数求学生年龄

#include<stdio.h>

int main(){
    int age(int n);
    int n;
    printf("\n请输入学生的序号：");
    scanf("%d",&n);
    printf("\n第%d个学生的年龄是：%d\n",n,age(n));
}

int age(int n){
    int c;
    if(n==1){
        c = 10;
        printf("c = %d n=%d\n",c,n);
    }
    else{
        c = age(n-1)+2;
        printf("c = %d n=%d\n",c,n);
    }
    return c;
}