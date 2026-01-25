//习题10.写一个函数,输入一行字符,将此字符串中最长的单词输出。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

void is_string_long_word(const char str[], char result[], size_t result_size) {
    if (result_size == 0) {
        return; // 无法存储结果
    }

    int max_len = 0;
    char temp[256];
    int temp_len = 0;

    // 初始化结果为空
    result[0] = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            if (temp_len < (int)sizeof(temp) - 1) {
                temp[temp_len++] = str[i];
            }
        } else {
            // 遇到非字母，处理当前单词
            if (temp_len > 0) {
                temp[temp_len] = '\0'; // 终止字符串
                if (temp_len > max_len) {
                    max_len = temp_len;
                    // 安全复制：确保不溢出 result
                    if (max_len < (int)result_size) {
                        strcpy(result, temp);
                    } else {
                        strncpy(result, temp, result_size - 1);
                        result[result_size - 1] = '\0';
                    }
                }
                temp_len = 0; // 重置
            }
        }
    }

    // 处理字符串以字母结尾的情况（如 "hello"）
    if (temp_len > 0) {
        temp[temp_len] = '\0';
        if (temp_len > max_len) {
            if (temp_len < (int)result_size) {
                strcpy(result, temp);
            } else {
                strncpy(result, temp, result_size - 1);
                result[result_size - 1] = '\0';
            }
        }
    }
}

//获取任意大小字符串的函数（使用完后需要手动释放内存存储空间）
char* input_string(){
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (!buffer) return NULL;

    int c;
    while ((c = fgetc(stdin))!=EOF && c!='\n')
    {
        if (length + 1 >= capacity)
        {
            capacity = capacity*2;
            char *new_buffer=realloc(buffer,capacity);
            if (!new_buffer)
            {
                fprintf(stderr,"开辟新的动态内存存储空间失败！");
                free(buffer);
                return NULL;
            }
            buffer=new_buffer;
        }
        buffer[length++]=(char)c;
    }
    buffer[length]='\0';
    return buffer;
}

int main(){
    printf("请输入一行文字：");
    char *line=input_string();
    if (!line)
    {
        fprintf(stderr, "读取输入失败！\n");
        return -1;
    }
    char result[256];
    size_t result_size=sizeof(result);
    is_string_long_word(line,result,result_size);
    printf("最长的单词是：%s\n",result);
    free(line);
    return 0;
}