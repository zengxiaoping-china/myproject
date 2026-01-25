#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <uchar.h> // 可选，但我们可以手动处理 UTF-8

// 辅助函数：判断一个 UTF-8 起始字节是否代表汉字
int is_chinese_char(unsigned char b1, unsigned char b2, unsigned char b3) {
    // 检查是否为 3 字节 UTF-8（汉字通常是 3 字节）
    if ((b1 & 0xF0) == 0xE0) {
        // 组合成 Unicode 码点
        unsigned int code = ((b1 & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F);
        // 汉字 Unicode 范围：U+4E00 ～ U+9FFF
        return (code >= 0x4E00 && code <= 0x9FFF);
    }
    return 0;
}

int main() {
    char *line = NULL;
    size_t len = 0;
    printf("请输入一行文字（可含中文）：");
    
    if (getline(&line, &len, stdin) == -1) {
        fprintf(stderr, "读取输入失败！\n");
        free(line);
        return -1;
    }

    // 移除换行符
    size_t text_len = strlen(line);
    if (text_len > 0 && line[text_len - 1] == '\n') {
        line[text_len - 1] = '\0';
        text_len--;
    }

    // 初始化计数器
    int chinese = 0, upper = 0, lower = 0, digit = 0, other = 0;

    for (size_t i = 0; i < text_len; ) {
        unsigned char c = (unsigned char)line[i];

        // ASCII 字符（0～127）
        if (c < 0x80) {
            if (isupper(c)) {
                upper++;
            } else if (islower(c)) {
                lower++;
            } else if (isdigit(c)) {
                digit++;
            } else if (c == ' ') {
                other++; // 或单独统计空格
            } else {
                other++;
            }
            i++; // 单字节
        }
        // UTF-8 多字节字符（可能是汉字）
        else if ((c & 0xE0) == 0xC0) {
            // 2 字节字符（如拉丁扩展、希腊字母等，非汉字）
            other++;
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0) {
            // 3 字节字符（可能是汉字）
            if (i + 2 < text_len) {
                unsigned char b1 = c;
                unsigned char b2 = (unsigned char)line[i + 1];
                unsigned char b3 = (unsigned char)line[i + 2];
                if (is_chinese_char(b1, b2, b3)) {
                    chinese++;
                } else {
                    other++;
                }
            } else {
                other++; // 不完整 UTF-8，视为其他
            }
            i += 3;
        }
        else if ((c & 0xF8) == 0xF0) {
            // 4 字节字符（如 emoji），视为其他
            other++;
            i += 4;
        }
        else {
            // 无效 UTF-8，跳过
            other++;
            i++;
        }
    }

    // 输出结果
    printf("\n统计结果：\n");
    printf("汉字: %d 个\n", chinese);
    printf("大写字母: %d 个\n", upper);
    printf("小写字母: %d 个\n", lower);
    printf("数字: %d 个\n", digit);
    printf("其他符号: %d 个\n", other);

    free(line);
    return 0;
}