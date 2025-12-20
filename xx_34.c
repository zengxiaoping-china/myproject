//统计一个字符串中的单词个数

#include <stdio.h>
#include <string.h>
#include <ctype.h>  // 如果你后续要用 isspace()

int main() {
    char string[100];
    int i, num = 0, in_word = 0;
    char c;

    // 安全读取一行输入
    printf("请输入一条语句：");
    if (fgets(string, sizeof(string), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    // 去掉换行符
    string[strcspn(string, "\n")] = '\0';

    for (i = 0; string[i] != '\0'; i++) {
        c = string[i];
        if (c == ' ') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            num++;
        }
    }

    printf("%s 这条语句一共有 = %d 个单词\n", string, num);
    return 0;
}