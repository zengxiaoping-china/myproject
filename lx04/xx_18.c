//输人4个整数，要求按由小到大的顺序输出。

#include <stdio.h>
int main() {
    int a, b, c, d;
    int temp;

    // 输入4个整数
    printf("请输入4个整数：");
    scanf("%d %d %d %d", &a, &b, &c, &d);
/*
    // 使用冒泡排序法对4个整数进行排序
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3 - i; j++) {
            if (*( &a + j) > *( &a + j + 1)) {
                // 交换
                temp = *( &a + j);
                *( &a + j) = *( &a + j + 1);
                *( &a + j + 1) = temp;
            }
        }
    }
    */

    // 使用简单的比较和交换方法对4个整数进行排序
    if (a > b) { temp = a; a = b; b = temp; }
    if (a > c) { temp = a; a = c; c = temp; }
    if (a > d) { temp = a; a = d; d = temp; }
    if (b > c) { temp = b; b = c; c = temp; }
    if (b > d) { temp = b; b = d; d = temp; }
    if (c > d) { temp = c; c = d; d = temp; }
    // 输出排序后的结果
    printf("按由小到大的顺序输出：%d %d %d %d\n", a, b, c, d);

    return 0;
}