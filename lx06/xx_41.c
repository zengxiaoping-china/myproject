//要求输出1~n^2的自然数(限奇数)构成的魔方阵。
#include <stdio.h>
int main() {
    int n;
    printf("请输入魔方阵的阶数 n (奇数): ");
    scanf("%d", &n);

    if (n % 2 == 0) {
        printf("魔方阵要求阶数为奇数！\n");
        return 1;
    }

    int magic_square[99][99] = {0}; // 假设 n 不超过 99
    int num = 1;
    int i = 0, j = n / 2; // 从第一行中间开始放置数字

    while (num <= n * n) {
        magic_square[i][j] = num; // 放置数字
        num++;
        int new_i = (i - 1 + n) % n; // 向上移动一行
        int new_j = (j + 1) % n;     // 向右移动一列

        if (magic_square[new_i][new_j] != 0) { // 如果位置已被占用
            i = (i + 1) % n; // 向下移动一行
        } else {
            i = new_i;
            j = new_j;
        }
    }

    // 输出魔方阵
    printf("输出 %d 阶魔方阵：\n", n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d ", magic_square[i][j]);
        }
        printf("\n");
    }

    return 0;
}