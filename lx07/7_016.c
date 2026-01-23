//习题16.写一个函数,输入一个十六进制数,输出相应的十进制数。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int is_valid_hex_string(const char *string){
    if(!string || !*string) return 0;

    // 跳过空白（可选）
    while (isspace((unsigned char)*string)) string++;

    // 支持 0x 或 0X 前缀
    if (string[0] == '0' && (string[1] == 'x' || string[1] == 'X')) {
        string += 2;
        if (!*string) return 0; // 只有 "0x" 不行
    }

    // 检查剩余字符是否都是十六进制字符
    while (*string) {
        if (!isxdigit((unsigned char)*string)) 
            return 0;
        string++;
    }
    return 1;
}

//手写将十六进制数转换成十进制数的函数
unsigned int hex_to_dec(const char *hex) {
    unsigned int result = 0;
    int i = 0;

    // 跳过空格
    while (isspace((unsigned char)hex[i])) i++;

    // 处理 0x 前缀
    if (hex[i] == '0' && (hex[i+1] == 'x' || hex[i+1] == 'X')) {
        i += 2;
    }

    // 逐位转换
    for (; hex[i] != '\0'; i++) {
        char c = hex[i];
        int digit;

        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c >= 'A' && c <= 'F')
            digit = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f')
            digit = c - 'a' + 10;
        else
            return -1; // 非法字符

        result = result * 16 + digit;
    }
    return result;
}

int main(){
    char input[256];
    char *endptr;
    unsigned long value;
    printf("请输入一个十六进制数：");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // 去掉换行

    // 方法1：先验证格式
    if (!is_valid_hex_string(input)) {
        printf("❌ 不是合法的十六进制格式！\n");
        return 1;
    }

    // 方法2：直接转换 + 错误检查（更简洁）
    value = strtoul(input, &endptr, 16);

    // 检查是否完全转换
    if (*endptr != '\0') {
        printf("❌ 包含非法字符: '%s'\n", endptr);
        return 1;
    }

    printf("✅ 转换成功！\n");
    printf("十六进制输入: %s\n", input);
    printf("对应的十进制值: %lu\n", value);
    printf("验证（输出为十六进制）: 0x%lX\n", value);

    return 0;
}

