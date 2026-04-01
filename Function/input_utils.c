#include "input_utils.h"
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 清空输入缓冲区
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 安全 fgets：自动处理 NULL 和去除换行符
char* safe_fgets(char *buffer, int max_len, FILE *stream) {
    if (fgets(buffer, max_len, stream) == NULL) {
        buffer[0] = '\0';
        return NULL;
    }
    // 去掉末尾换行符
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}

// 输入正整数（带范围校验）
int input_positive_int(const char *prompt, int min_val, int max_val) {
    char line[100];
    while (1) {
        printf("%s", prompt);
        if (safe_fgets(line, sizeof(line), stdin) == NULL) {
            clear_input_buffer();
            printf("输入失败，请重试。\n");
            continue;
        }

        if (line[0] == '\0') {
            printf("输入不能为空！\n");
            continue;
        }

        char *endptr;
        long val = strtol(line, &endptr, 10);

        // 检查是否完全转换（无非法字符）
        if (*endptr != '\0') {
            printf("请输入一个有效的整数！\n");
            continue;
        }

        if (val < min_val || val > max_val) {
            printf("输入超出范围！请输入 %d 到 %d 之间的整数。\n", min_val, max_val);
            continue;
        }

        return (int)val;
    }
}

// 输入非空字符串
void input_nonempty_string(const char *prompt, char *output, size_t output_size) {
    char line[512]; // 足够大的临时缓冲区
    while (1) {
        printf("%s", prompt);
        if (safe_fgets(line, sizeof(line), stdin) == NULL) {
            clear_input_buffer();
            printf("输入失败，请重试。\n");
            continue;
        }

        if (line[0] == '\0') {
            printf("输入不能为空！\n");
            continue;
        }

        if (strlen(line) >= output_size) {
            printf("输入太长！最多 %zu 个字符。\n", output_size - 1);
            continue;
        }

        strcpy(output, line);
        return;
    }
}

// 从指定字符集中选择一个字符（不区分大小写）
char input_char_from_options(const char *prompt, const char *valid_chars) {
    char line[10];
    while (1) {
        printf("%s", prompt);
        if (safe_fgets(line, sizeof(line), stdin) == NULL) {
            clear_input_buffer();
            printf("输入失败，请重试。\n");
            continue;
        }

        if (strlen(line) != 1) {
            printf("请输入单个字符！\n");
            continue;
        }

        char c = line[0];
        // 转为大写比较（假设 valid_chars 是大写）
        char upper_c = (char)toupper((unsigned char)c);
        const char *p = valid_chars;
        while (*p) {
            if (upper_c == *p) {
                return upper_c; // 返回大写统一格式
            }
            p++;
        }

        printf("无效输入！请选择以下之一：%s\n", valid_chars);
    }
}