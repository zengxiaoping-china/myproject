//6.写一函数,求一个字符串的长度。在 main 函数中输入字符串,并输出其长度。

#include<stdio.h>
#include<string.h>

int string_length(char *str);

int main(){
    char string[256];

    int length;

    printf("\n请输入一个字符串：");

    if(fgets(string,sizeof(string),stdin)==NULL)
    {
        printf("输入错误。\n");
        return 1;
    }
    string[strcspn(string, "\n")] = '\0'; // 去掉换行符

    length = string_length(string);

    printf("字符串长度是：%d",length);
    
    return 0;
}

int string_length(char *str){
    int length,i;
    for ( i = 0; str[i] != '\0'; i++)
    {
        length = i+1;
    }
    return(length);
}