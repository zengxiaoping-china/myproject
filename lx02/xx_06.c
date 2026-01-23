//练习题06-打印九九乘法表

#include<stdio.h>

int main(){

    printf("\n\n=================== 打印九九乘法表 ======================\n\n");
    int i;
    int j;
    for ( i = 1; i < 10; i++)
    {
        for ( j = 1; j <= i; j++)
        {
            printf("%d X %d = %d  ",j,i,i*j);
        }
        printf("\n");
    }
    printf("\n\n=================== 打印完毕 ======================\n\n");    
    return 0;
}