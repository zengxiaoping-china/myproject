//输入一个整数，计算1到该整数的累加和

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

// 函数声明：计算 1 到 z 的累加和
int test(int z);

int main() {
    int a;
    char buffer[256];  // 用于存储用户输入的一行

    while (1) {  // 循环直到用户输入合法整数
        printf("请输入一个整数：\n");

        // 安全读取一行输入
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // 如果遇到 EOF（如 Ctrl+Z / Ctrl+D），退出程序
            printf("输入结束，程序退出。\n");
            return 1;
        }

        // 去掉换行符（如果存在）
        buffer[strcspn(buffer, "\n")] = '\0';

        // 跳过首尾空格后判断是否为空
        char* start = buffer;
        while (*start == ' ' || *start == '\t') start++;
        if (*start == '\0') {
            printf("❌ 输入为空，请重新输入。\n\n");
            continue;
        }

        // 尝试将字符串转换为 long 类型整数
        char* endptr;
        errno = 0;  // 重置错误标志
        long val = strtol(start, &endptr, 10);  // 十进制转换

        // 检查转换是否成功
        if (errno == ERANGE) {
            // 数值超出 long 范围（如 999999999999999999999）
            printf("❌ 数值太大或太小，超出整数范围，请重新输入。\n\n");
            continue;
        }

        if (endptr == start) {
            // 没有任何数字被解析（如输入 "abc"）
            printf("❌ 输入的不是整数，请重新输入。\n\n");
            continue;
        }

        // 检查是否有多余字符（如 "123abc" 或 "12.5"）
        while (*endptr == ' ' || *endptr == '\t') endptr;  // 允许尾部空格
        if (*endptr != '\0') {
            printf("❌ 输入包含非法字符（如小数点或字母），请只输入整数。\n\n");
            continue;
        }

        // 检查是否在 int 范围内（因为你的变量是 int）
        if (val < INT_MIN || val > INT_MAX) {
            printf("❌ 数值超出 int 类型范围（%d ~ %d），请重新输入。\n\n", INT_MIN, INT_MAX);
            continue;
        }

        // 转换成功！赋值给 a 并跳出循环
        a = (int)val;
        break;
    }

    // 调用函数计算累加和
    int sum = test(a);
    printf("1+2+3+.....+%d=%d\n", a, sum);

    return 0;
}

// 计算 1 到 z 的累加和（注意：如果 z 是负数，当前逻辑会返回 0）
int test(int z) {
    // 可选：处理负数情况（通常累加从 1 开始，负数无意义）
    if (z < 0) {
        printf("⚠️ 注意：输入为负数，累加和定义为 0。\n");
        return 0;
    }

    int sum = 0;
    for (int i = 1; i <= z; i++) {  // 修正：从 1 开始（原代码从 0 开始，多加了 0）
        sum += i;
    }
    return sum;
}