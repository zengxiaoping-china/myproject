//写一个函数,使输人的一个字符串按反序存放,在主函数中输人和输出字符串。

#include<stdio.h>
#include <string.h>

void reverse_string(char string[]);

int main(){
    char string[256];
    int i;
    printf("\n请输入一个字符串：");
    // 安全读取一行输入
    if (fgets(string, sizeof(string), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    // 去掉换行符
    string[strcspn(string, "\n")] = '\0';
    printf("\n输入的字符串是:%s\n",string);
    reverse_string(string);
    printf("\n输出反序字符串：%s\n",string);
    return 0;
}

void reverse_string(char string[]){
    int i;
    char temp;
    int len = strlen(string); //获取字符串长度
    for ( i = 0; i<len/2; i++)
    {
        temp = string[i];
        string[i] = string[len-1-i];
        string[len-1-i] = temp;
    }
}