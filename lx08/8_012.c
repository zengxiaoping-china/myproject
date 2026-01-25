#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 函数修改：由调用者传入 result 缓冲区
void find_longest_word(const char str[], char result[], size_t result_size) {
    int max_len = 0;
    char temp[256];
    int temp_len = 0;

    // 确保 result 初始为空
    if (result_size > 0) {
        result[0] = '\0';
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) { // ✅ 正确判断字母
            if (temp_len < (int)sizeof(temp) - 1) {
                temp[temp_len++] = str[i];
            }
        } else {
            // 遇到非字母，检查是否是最长单词
            if (temp_len > max_len) {
                max_len = temp_len;
                temp[temp_len] = '\0';
                // 安全复制到 result
                if (max_len < (int)result_size) {
                    strcpy(result, temp);
                } else {
                    strncpy(result, temp, result_size - 1);
                    result[result_size - 1] = '\0';
                }
            }
            temp_len = 0; // 重置临时缓冲区
        }
    }

    // 处理字符串以字母结尾的情况
    if (temp_len > max_len) {
        temp[temp_len] = '\0';
        if (temp_len < (int)result_size) {
            strcpy(result, temp);
        } else {
            strncpy(result, temp, result_size - 1);
            result[result_size - 1] = '\0';
        }
    }
}

// 使用示例
int main() {
    char input[] = "Hello, this is a test string with supercalifragilisticexpialidocious!";
    char longest[256];

    find_longest_word(input, longest, sizeof(longest));
    printf("最长单词: %s\n", longest); // 输出: supercalifragilisticexpialidocious
    return 0;
}