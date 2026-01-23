//用筛选法求100以内的素数
#include <stdio.h>
int main() {
    int n = 100;
    int is_prime[101]; // 用于标记素数，1表示是素数，0表示不是素数
    int i, j;

    // 初始化数组，假设所有数都是素数
    for (i = 2; i <= n; i++) {
        is_prime[i] = 1;
    }

    // 筛选法找出素数
    for (i = 2; i * i <= n; i++) {
        if (is_prime[i]) { // 如果i是素数
            for (j = i * i; j <= n; j += i) {
                is_prime[j] = 0; // 标记i的倍数不是素数
            }
        }
    }

    // 输出100以内的素数
    printf("100以内的素数有：\n");
    for (i = 2; i <= n; i++) {
        if (is_prime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}