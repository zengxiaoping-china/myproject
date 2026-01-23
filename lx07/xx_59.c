//求方程ax^2+bx+c=0的根,用3个函数分别求当: b^2-4ac大于0.等于0和小于0时的根并输出结果。从主函数输人a,b,c的值。

#include <stdio.h>
#include <math.h>

void f1(double a, double b, double delta, double *x1, double *x2);
void f2(double a, double b, double *x1, double *x2);
void f3(void);

int main() {
    double a, b, c, delta, x1, x2;
    printf("\n请分别输入一元二次方程 ax^2+bx+c=0 中 a,b,c 的值：");
    scanf("%lf %lf %lf", &a, &b, &c);

    // ===== 智能打印方程 =====
    printf("\n\n你输入的方程是：");

    // 打印 ax^2 项
    if (a == 1) {
        printf("x^2");
    } else if (a == -1) {
        printf("-x^2");
    } else {
        printf("%.0lfx^2", a);
    }

    // 打印 bx 项
    if (b > 0) {
        if (b == 1) {
            printf("+x");
        } else {
            printf("+%.0lfx", b);
        }
    } else if (b < 0) {
        if (b == -1) {
            printf("-x");
        } else {
            printf("%.0lfx", b);  // 负数自带减号
        }
    }
    // 如果 b == 0，跳过不打印

    // 打印常数项 c
    if (c > 0) {
        printf("+%.0lf", c);
    } else if (c < 0) {
        printf("%.0lf", c);  // 负数自带减号
    }
    // 如果 c == 0，跳过

    printf("=0\n");
    // ======================

    if (a == 0) {
        printf("错误：a 不能为 0（不是二次方程）\n");
        return 0;
    }

    delta = b * b - 4 * a * c;

    if (delta > 0) {
        f1(a, b, delta, &x1, &x2);
        printf("\n两个不等实根：X1 = %.2lf, X2 = %.2lf\n", x1, x2);
    } else if (delta == 0) {
        f2(a, b, &x1, &x2);
        printf("\n一个重根：X1 = X2 = %.2lf\n", x1);
    } else {
        f3();
    }
    return 0;
}

void f1(double a, double b, double delta, double *x1, double *x2) {
    *x1 = (-b + sqrt(delta)) / (2 * a);
    *x2 = (-b - sqrt(delta)) / (2 * a);
}

void f2(double a, double b, double *x1, double *x2) {
    *x1 = *x2 = -b / (2 * a);
}

void f3(void) {
    printf("\n该方程无实数根（判别式 < 0）。\n");
}