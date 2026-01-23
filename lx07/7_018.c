//习题17.用递归法将一个整数n转换成字符串。例如,输入483,应输出字符串"483"。n的位数不确定,可以是任意位数的整数。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 辅助递归函数：将 n 转为字符串，追加到 buffer 中，返回写入的字符数
static int _num_to_str_recursive(long long n, char *buffer) {
    if (n == 0) {
        return 0; // 不写任何字符（由调用者处理 0 的情况）
    }
    
    int len = 0;
    if (n > 9) {
        // 先递归处理高位
        len = _num_to_str_recursive(n / 10, buffer);
    }
    // 写当前位
    buffer[len] = '0' + (n % 10);
    printf("n=%-10d len=%d buffer[%d]=%c\n",n,len,len,buffer[len]);
    return len + 1;
}

// 主函数：支持负数和零
char *num_to_string_recursive(long long n) {
    if (n == 0) {
        char *s = malloc(2);
        if (s) { s[0] = '0'; s[1] = '\0'; }
        return s;
    }

    int negative = (n < 0);
    if (negative) {
        n = -n; // 注意：对于 LLONG_MIN 需要特殊处理（见下方说明）
    }

    // 分配足够空间：最多 19 位数字 + 1 符号 + 1 '\0'
    char *str = malloc(25);
    if (!str) return NULL;

    int pos = 0;
    if (negative) {
        str[pos++] = '-';
    }

    // 递归填充数字部分
    int digits = _num_to_str_recursive(n, str + pos);
    str[pos + digits] = '\0';

    return str;
}

// 测试
int main() {
    long long nums[] = {12345678};
    for (int i = 0; i < 1; i++) {
        char *s = num_to_string_recursive(nums[i]);
        if (s) {
            printf("%lld → \"%s\"\n", nums[i], s);
            free(s);
        }
    }
    return 0;
}