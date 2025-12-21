//练习1-1：编写一个C程序，打印“这是一个C程序”，并计算两个整数的和，然后打印结果。

#include <stdio.h>

int main()
    {
        printf("\nThis is a C program\n\n");

        int a = 125, b = 236, sum = 0;
        sum = a + b;
        
        printf("sum is %d = %d + %d\n",sum,a,b);
        
        return 0;
    }