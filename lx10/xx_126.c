// 该程序实现在文件中查找字符串并插入新字符串

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("file.txt", "r+");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1; // 返回一个非零值表示错误
    }

    // 读取文件的全部内容
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *file_content = (char *)malloc(file_size + 1);
    if (file_content == NULL) {
        printf("Memory allocation failed\n");
        fclose(fp);
        return 1;
    }
    fread(file_content, 1, file_size, fp);
    file_content[file_size] = '\0'; // 确保字符串以 null 结尾

    // 定义要查找的字符串和要插入的字符串
    char *search_str = "This";
    char *insert_str = "Insert this ";
    long insert_size = strlen(insert_str);

    // 查找字符串的位置
    char *pos = strstr(file_content, search_str);
    if (pos == NULL) {
        printf("Search string not found\n");
        free(file_content);
        fclose(fp);
        return 1;
    }

    // 计算插入位置
    long insert_pos = pos - file_content + strlen(search_str); // 在找到的字符串后面插入

    // 扩展文件内容以腾出空间
    char *new_content = (char *)malloc(file_size + insert_size + 1);
    if (new_content == NULL) {
        printf("Memory allocation failed\n");
        free(file_content);
        fclose(fp);
        return 1;
    }

    // 将原文件内容的一部分复制到新内容
    memcpy(new_content, file_content, insert_pos);
    // 插入新内容
    memcpy(new_content + insert_pos, insert_str, insert_size);
    // 将剩余的原文件内容复制到新内容
    memcpy(new_content + insert_pos + insert_size, file_content + insert_pos, file_size - insert_pos);
    new_content[file_size + insert_size] = '\0'; // 确保字符串以 null 结尾

    // 打开文件以写入新内容
    rewind(fp); // 将文件指针移动到文件开头
    fwrite(new_content, 1, file_size + insert_size, fp);

    // 清理内存并关闭文件
    free(file_content);
    free(new_content);
    fclose(fp);

    return 0;
}
