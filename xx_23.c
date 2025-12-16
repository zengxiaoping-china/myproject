/*
给一个不多于5位的正整数,要求:

①求出它是几位数;

②分别输出每- .位数字;

③按逆序输出各位数字,例如原数为321,应输出123.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_valid_number(void) {
    char line[100];
    long num;
    char *end;

    while (1) {
        printf("\n请输入一个不多于5位的正整数 (1-99999): ");
        if (!fgets(line, sizeof(line), stdin)) {
            printf("读取输入失败。\n");
            exit(1);
        }

        // 去掉换行符
        line[strcspn(line, "\n")] = '\0';

        // 跳过前导空格
        char *start = line;
        while (isspace((unsigned char)*start)) start++;
        if (*start == '\0') {
            printf("输入不能为空。\n");
            continue;
        }

        // 转换
        num = strtol(start, &end, 10);

        // 检查是否转换成功且无多余字符
        if (*end != '\0') {
            printf("输入包含非法字符。\n");
            continue;
        }

        if (num < 1 || num > 99999) {
            printf("数字必须在 1 到 99999 之间。\n");
            continue;
        }

        return (int)num;
    }
}

int main() {
    int num;
    int digits[5];
    int count = 0;

    num = get_valid_number();

    // 提取各位数字并存储在数组中
    while (num > 0 && count < 5) {
        digits[count] = num % 10;
        num /= 10;
        count++;
    }

    // 输出位数
    printf("\n该数是 %d 位数。\n\n", count);

    // 输出各位数字
    printf("各位数字分别是: ");
    for (int i = count - 1; i >= 0; i--) {
        printf(" %d", digits[i]);
    }
    printf("\n\n");

    // 输出逆序数字
    printf("逆序输出各位数字: ");
    for (int i = 0; i < count; i++) {
        printf(" %d", digits[i]);
    }
    printf("\n\n");

    return 0;
}