#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <limits.h>

// ================================
// 功能 1：获取 [min, max] 范围内的 double 实数
// ================================
double get_double_in_range(double min, double max) {
    char line[256];
    while (1) {
        printf("请输入一个实数 (%.6g ~ %.6g): ", min, max);
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
            printf("❌ %.6g 不在有效范围 [%.6g, %.6g] 内。\n", num, min, max);
            continue;
        }

        return num;
    }
}

// ================================
// 功能 2：安全地将 double 转为 int（向零取整）
// ================================
int safe_double_to_int_trunc(double x) {
    // 先检查是否在 int 范围内
    if (x < (double)INT_MIN || x > (double)INT_MAX) {
        fprintf(stderr, "❌ 错误：%.6g 超出 int 范围 [%d, %d]\n", x, INT_MIN, INT_MAX);
        exit(EXIT_FAILURE);
    }
    // 强制转换（向零取整）
    return (int)x;
}

// ================================
// 可选：安全四舍五入转 int
// ================================
int safe_double_to_int_round(double x) {
    double rx = round(x);
    if (rx < (double)INT_MIN || rx > (double)INT_MAX) {
        fprintf(stderr, "❌ 错误：%.6g 四舍五入后超出 int 范围\n", x);
        exit(EXIT_FAILURE);
    }
    return (int)rx;
}

// ================================
// 主函数：演示用法
// ================================
int main() {
    // 示例 1：获取 0.0 到 100.0 之间的实数
    double value = get_double_in_range(0.0, 100.0);
    printf("\n✅ 您输入的实数是: %.6f\n", value);

    // 示例 2：安全转换为整数（截断）
    int truncated = safe_double_to_int_trunc(value);
    printf("➡️  向零取整（截断）: %d\n", truncated);

    // 示例 3：安全转换为整数（四舍五入）
    int rounded = safe_double_to_int_round(value);
    printf("➡️  四舍五入: %d\n", rounded);

    // 示例 4：如果你只需要整数部分（且确定范围安全）
    // 比如题目要求“不多于5位正整数”，但你用浮点输入
    printf("\n--- 另一个场景：模拟输入整数（但用浮点函数） ---\n");
    double integer_input = get_double_in_range(1.0, 99999.0);
    
    // 因为 1~99999 在 int 范围内，可安全转换
    int as_integer = safe_double_to_int_trunc(integer_input);
    printf("输入的整数是: %d\n", as_integer);

    return 0;
}