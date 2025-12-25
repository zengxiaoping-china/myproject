//练习静态存储类别的变量和动态存储类别的变量

#include<stdio.h>

int main(){
    int f(int a);
    int a = 2;
    for (int i = 0; i < 3; i++)
    {
        printf("a+b+c = %d\n\n",f(a));
    }
}

int f(int a){
    auto int b = 0;
    static int c = 3; //静态存储类别的变量
    b =b + 1;
    c =c + 1;
    printf("a = %d \n",a);
    printf("b = %d \n",b);
    printf("c = %d \n",c);
    return(a+b+c);
}