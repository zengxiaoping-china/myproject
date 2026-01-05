//练习字符指针作为函数参数

#include<stdio.h>
#include<string.h>

void copy_string(char *p1,char *p2);

int main(){

    char string_one[500];

    char string_two[500];

    printf("\n请输入一个字符串：");

    // 安全读取一行输入
    if (fgets(string_one, sizeof(string_one), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    // 去掉换行符
    string_one[strcspn(string_one, "\n")] = '\0';

    char *str1,*str2;

    str1=string_one;

    str2=string_two;

    copy_string(str1,str2);

    printf("\n复制后的字符串是：%s\n",string_two);

    return 0;
}

void copy_string(char *p1,char *p2){

    for (; *p1 != '\0'; p1++,p2++)
    {
        *p2 = *p1;
    }
    *p2='\0';
}