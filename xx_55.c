//函数中声明外部变量

#include<stdio.h>

int main(){
    int max();
    extern int A,B,C;
    printf("\nPlease enter integer three number:");
    scanf("%d %d %d",&A,&B,&C);
    printf("\nMax number is:%d\n",max());
    return 0;
}
int A,B,C;

int max(){
    int m;
    m = A>B?A:B;
    m = C>m?C:m;
    return(m);
}