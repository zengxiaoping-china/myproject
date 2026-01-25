//获取任意大小字符串的函数（使用完后需要手动释放内存存储空间）

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_line_dynamic() {
    size_t capacity = 64;          // 初始容量
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (!buffer) return NULL;

    int c;
    while ((c = fgetc(stdin)) != EOF && c != '\n') {
        if (length + 1 >= capacity) {
            // 扩容（例如翻倍）
            capacity *= 2;
            char *new_buffer = realloc(buffer, capacity);
            if (!new_buffer) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
        }
        buffer[length++] = (char)c;
    }
    buffer[length] = '\0';
    return buffer;
}

int main() {
    printf("请输入一行文字：");
    char *line = read_line_dynamic();
    if (!line) {
        fprintf(stderr, "读取输入失败！\n");
        return -1;
    }

    printf("你输入的内容是：\"%s\"\n", line);
    printf("字符串长度：%zu\n", strlen(line));

    free(line);
    return 0;
}