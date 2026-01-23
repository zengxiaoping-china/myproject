/*在全系1000名学生中举行慈善募捐,当总数达到10 万元时就结束,统计此时捐款的人数以及平均每人捐款的数目。*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define SUM 100000.0  // 定义募捐总额上限

// ================================
// 功能 1：获取 [min, max] 范围内的 double 实数
// ================================
double get_double_in_range(double min, double max) {
    char line[256];
    while (1) {
        if (!fgets(line, sizeof(line), stdin)) {
            fprintf(stderr, "输入失败（可能是 EOF）。\n");
            exit(EXIT_FAILURE);
        }

        // 去掉换行符
        line[strcspn(line, "\n")] = '\0';

        // 跳过前导空格
        char *start = line;
        while (isspace((unsigned char)*start)) start++;
        if (*start == '\0') {
            printf("❌ 输入不能为空。\n");
            continue;
        }

        // 转换
        char *end;
        errno = 0;
        double num = strtod(start, &end);

        // 检查是否完全未识别数字（如 "abc"）
        if (start == end) {
            printf("❌ 未检测到有效数字。\n");
            continue;
        }

        // 跳过尾随空格
        while (isspace((unsigned char)*end)) end++;
        if (*end != '\0') {
            printf("❌ 输入包含非法字符（仅允许数字、小数点、符号、e/E）。\n");
            continue;
        }

        // 检查溢出或特殊值
        if (errno == ERANGE) {
            printf("❌ 数值过大或过小，超出表示范围。\n");
            continue;
        }
        if (!isfinite(num)) {
            printf("❌ 不支持无穷大（inf）或非数值（NaN）。\n");
            continue;
        }

        // 检查用户指定范围
        if (num < min || num > max) {
            printf("❌ 金额不能为负，请重新输入: ");  // 因为 max 很大，通常只可能是负数
            continue;
        }

        return num;
    }
}

int main(){
    double amount,total = 0.0,aver;
    int i;
    for (i=1;i<=1000;i++)
    {
        printf("请输入第%d位同学的捐款数目（元，≥0）：",i);
        amount = get_double_in_range(0.0,DBL_MAX);
        total = total + amount;
        if (total >= SUM) break;
    }       
    aver = total / i;
    printf("\n\n捐款人数为:%d\n",i);
    printf("\n平均每人捐款数目为:%.2f\n\n",aver);   
}