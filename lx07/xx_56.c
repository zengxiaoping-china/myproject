#include<stdio.h>
#include ".h\test.h" //注意包含了自定义的头文件

int A;

int main(){
    int b = 3,c,d,m;
    printf("enter the number a and its power m:\n");
    scanf("%d %d",&A,&m);
    c = A * b;
    printf("%d * %d = %d\n",A,b,c);
    d = power(m);
    printf("%d ** %d = %d",A,m,d);
    return 0;
}