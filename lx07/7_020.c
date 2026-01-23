//使用 C 语言递归函数：计算 n 阶勒让德多项式 Pn(x) 

#include <stdio.h>

/*
 * 递归函数：计算 n 阶勒让德多项式 Pn(x)
 * 参数：n - 阶数, x - 变量值
 * 返回值：Pn(x) 的结果 (double 类型)
 */
double legendre(int n, double x) {
    // 基准情况 (Base Case)：n = 0
    if (n == 0) {
        return 1.0;
    }
    // 基准情况 (Base Case)：n = 1
    else if (n == 1) {
        return x;
    }
    // 递归情况 (Recursive Case)：n >= 2
    else {
        // 公式：Pn(x) = [ (2n-1) * x * Pn-1(x) - (n-1) * Pn-2(x) ] / n
        double term1 = (2 * n - 1) * x * legendre(n - 1, x);
        double term2 = (n - 1) * legendre(n - 2, x);
        return (term1 - term2) / n;
    }
}

int main() {
    int n;
    double x;

    // 输入提示
    printf("请输入阶数 n 和变量 x 的值 (例如: 2 3.5): ");

    // 读取用户输入
    if (scanf("%d %lf", &n, &x) != 2) {
        printf("输入错误！\n");
        return 1;
    }

    // 检查阶数是否为非负整数
    if (n < 0) {
        printf("阶数 n 不能为负数！\n");
        return 1;
    }

    // 调用函数并输出结果
    double result = legendre(n, x);
    printf("P%d(%.2f) = %.6f\n", n, x, result);

    return 0;
}