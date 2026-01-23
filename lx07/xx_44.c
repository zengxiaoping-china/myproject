//练习使用函数递归方法和传统循环方法计算n！

#include<stdio.h>

long long f(int n); //函数递归法计算阶乘
long long factorial(int n); // 传统循环方法计算阶乘

int main(){
    int n;
    printf("\n请输入n的值：");
    scanf("%d",&n);
    printf("\n== 函数递归法 ========================================\n\n");

    // 递归方法计算阶乘
    long long result1 = f(n);
    if(result1 != -1) { // 使用-1表示错误，成功时显示结果
        printf("\n递归方法：%d! = %lld\n\n", n, result1);
    }
    
    printf("== 传统循环法 ========================================\n\n");
    // 传统方法计算阶乘
    long long result2 = factorial(n);
    if(result2 != -1) { // 使用-1表示错误，成功时显示结果
        printf("\n传统方法：%d! = %lld\n", n, result2);
    }
    
    return 0;
}

long long f(int n){
    long long c;  // 改为long long
    if(n < 0){
        printf("错误：n<0 数字不能小于0\n\n");
        return -1; // 使用-1表示错误
    }else if (n >= 21)  // 修正：long long能安全计算到20!
    {
        printf("错误：计算%d!时，由于阶乘值超出long long数据类型范围发生溢出！\n\n", n);
        return -1;
    }
    if(n == 0 || n == 1){
        c = 1;
    }
    else{
        c = f(n-1) * n;
    }
    printf("n = %-2d  %d! = %-20lld\n", n,n,c);  // 使用%lld，增加宽度
    return c;
}

//扩展：传统方法计算n的阶乘
long long factorial(int n){
    int i;
    long long c = 1;
    if(n < 0){
        printf("错误：n<0 数字不能小于0\n");
        return -1;
    }else if (n >= 21)  // 修正：long long能安全计算到20!
    {
        printf("错误：计算%d!时，由于阶乘值超出long long数据类型范围发生溢出！\n", n);
        return -1;
    }
    
    if(n == 0 || n == 1) {
        printf("%lld", c);  // 使用%lld
        return c; 
    }
    
    printf("计算过程：");
    for(i = 1; i <= n; i++) {
        c = c * i;
        if(i != n) {
            printf("%d x ", i);
            if(i % 10 == 0) printf("\n\n          "); // 调整换行格式
        } else {
            printf("%d", i);
        }
    }
    printf(" = %lld\n", c);  // 使用%lld
    return c;
}