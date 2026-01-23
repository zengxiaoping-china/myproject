//写一个函数,输人一行字符,将此字符串中最长的单词输出。

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 256
#define MAX_WORDS   50  // 假设一行最多50个单词

int main() {
    char str[MAX_STR_LEN];
    int word_starts[MAX_WORDS];  // 记录每个最长单词的起始下标
    int max_len = 0;             // 最长单词的长度
    int count = 0;               // 最长单词的个数

    // === 第一步：安全读入字符串 ===
    printf("\n请输入一行字符串：");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    str[strcspn(str, "\n")] = '\0';  // 去掉换行符
    printf("\n输入的有效字符串是：%s\n\n", str);

    // === 第二步：第一遍遍历 —— 找出最大单词长度 ===
    int i = 0;
    while (str[i] != '\0') {
        // 跳过非字母字符
        while (str[i] != '\0' && !isalpha(str[i])) {
            i++;
        }

        int start = i;
        // 统计当前单词长度
        while (str[i] != '\0' && isalpha(str[i])) {
            i++;
        }

        int curr_len = i - start;
        if (curr_len > 0 && curr_len > max_len) {
            max_len = curr_len;
        }
    }

    // 如果没找到任何单词
    if (max_len == 0) {
        printf("未找到任何单词。\n");
        return 0;
    }

    // === 第三步：第二遍遍历 —— 记录所有长度为 max_len 的单词起始位置 ===
    i = 0;
    count = 0;
    while (str[i] != '\0' && count < MAX_WORDS) {
        // 跳过非字母
        while (str[i] != '\0' && !isalpha(str[i])) {
            i++;
        }

        int start = i;
        while (str[i] != '\0' && isalpha(str[i])) {
            i++;
        }

        int curr_len = i - start;
        if (curr_len == max_len) {
            word_starts[count] = start;
            count++;
        }
    }

    // === 第四步：输出所有最长单词 ===
    printf("最长单词长度为 %d，共有 %d 个：\n\n", max_len, count);
    for (int j = 0; j < count; j++) {
        printf("%d. ", j + 1);
        for (int k = 0; k < max_len; k++) {
            putchar(str[word_starts[j] + k]);
        }
        printf("\n\n");
    }

    return 0;
}