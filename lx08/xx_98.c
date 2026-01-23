//7.有一字符串,包含n 个字符。写一函数,将此字符串中从第m 个字符开始的全部字符复制成为另一个字符串。

#include<stdio.h>
#include<string.h>

int string_copy(char *str,char *str_new,int m);

int main(){
    char string[256];
    char string_new[256];
    int m=50;
    printf("\n请输入一个字符串：");
    if (fgets(string,sizeof(string),stdin)==NULL)
    {
        printf("输入错误\n");
        return 1;
    }
    string[strcspn(string,"\n")] ='\0';

    if(string_copy(string,string_new,m))
    {
        printf("新字符串：%s",string_new);
    }
    return 0;
}

int string_copy(char *str,char *str_new,int m){
    int i,length;
    for ( i = 0; str[i]!='\0'; i++)
    {
        length=i+1;
    }
    if(m>length)
    {
        printf("错误,m大于字符串长度");
        return 0;
    }
    for ( i = 0; str[m-1+i] !='\0'; i++)
    {
        str_new[i]=str[m-1+i];
    }
    return 1;
}