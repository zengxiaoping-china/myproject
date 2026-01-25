//习题8.输入一行文字,找出其中大写字母、小写字母、空格、数字以及其他字符各有多少。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//获取任意大小字符串的函数（使用完后需要手动释放内存存储空间）
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

int main(){
    char string[1024];
    printf("请输入一行文字：");
    if (fgets(string,sizeof(string),stdin)==NULL)
    {
        fprintf(stderr,"输入的字符串错误！");
        return -1;
    }
    string[strcspn(string,"\n")]='\0';//去除换行符

    int upper_count = 0;
    int lower_count = 0;
    int digit_count = 0;
    int space_count = 0;
    int other_count = 0;

    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i]>='0' && string[i]<='9')
        {
            digit_count++;
        }else if (string[i]>='a'&&string[i]<='z')
        {
            lower_count++;
        }else if (string[i]>='A'&&string[i]<='Z')
        {
            upper_count++;
        }else if (string[i]==' ')
        {
            space_count++;
        }else
        {
            other_count++;
        }    
    }
    
    printf("\n=======这行其中大写字母、小写字母、空格、数字以及其他字符各有多少=======\n\n");
    printf("大写字母数量：%d\n\n",upper_count);
    printf("小写字母数量：%d\n\n",lower_count);
    printf("空格数量：%d\n\n",space_count);
    printf("数字数量：%d\n\n",digit_count);
    printf("其他字符数量：%d\n",other_count);

    return 0;
}