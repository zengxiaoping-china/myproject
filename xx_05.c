#include<stdio.h>

// 1. 定义分数结构体
struct Fraction {
    int num;  // 分子（简写）
    int den;  // 分母（简写）
    };

    // 2. 打印分数的函数
void print_fraction(struct Fraction f) {
    if (f.den == 1) {
        printf("%d", f.num);
    } else {
        printf("%d/%d", f.num, f.den);
    }
    }

/*
int main(){

    int sum = 0;
    int i;
    for (i = 10; i >= 1; i--)
    {
        if (i % 2 ==0)
        {
            printf("%d + ",i);
            sum = sum + i;
        }
        else if (i != 1)       
        {
            printf("%d - ",i);
            sum = sum - i;
        }
        else{
            printf("%d",i);
            sum = sum - i;
        }
    }
    printf(" = %d",sum);
    return 0;
}
*/
int main() {
    double sum = 0.0;
    
    printf("\n计算：\n\n");

    for (int k = 1; k <= 8; k++) {
        double term = 1.0 / k;

        // 第一项不加符号前缀，后续项根据正负加 '+' 或 '-'
        if (k == 1) {
            printf("1");               // 第一项是 1
            sum += term;
        } else {
            if (k % 2 == 0) {
                // 偶数项：负数
                printf(" - 1/%d", k);
                sum -= term;
            } else {
                // 奇数项：正数
                printf(" + 1/%d", k);
                sum += term;
            }
        }

        // 每行打印 10 项，避免一行太长（可选美化）
        if (k % 10 == 0) {
            printf("\n");
        }
    }

    // 如果最后一行不满 10 项，补一个换行
    if (100 % 10 != 0) {
        printf("\n");
    }

    printf("= %.15f\n", sum);

    return 0;
}