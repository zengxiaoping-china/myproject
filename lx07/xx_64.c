//写一个函数,将两个字符串连接。

#include<stdio.h>
#include<string.h>

int str_conn(char str1[],const char str2[]);

int main(){
    char str1[256];
    char str2[256];
    printf("\n请输入第一个字符串：");
    // 安全读取一行输入
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    // 去掉换行符
    str1[strcspn(str1, "\n")] = '\0';
    printf("\n你输入的第一个字符串是：%s\n",str1);

    printf("\n请输入第二个字符串：");
    // 安全读取一行输入
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    // 去掉换行符
    str2[strcspn(str2, "\n")] = '\0';
    printf("\n你输入的第二个字符串是：%s\n",str2);

    if(str_conn(str1,str2)){
        printf("\n两个字符串连接后是：%s\n",str1);
    }
    else
    {
        printf("\n错误：连接后可能产生溢出错误，所以不能在源字符串基础上进行直接连接\n");
    }
    return 0;
}

int str_conn(char str1[],const char str2[]){
    int i,j;
    int len1=strlen(str1);
    int len2=strlen(str2);
    //int min_len=len1>len2?len2:len1;
    if (len1+len2 >= 256)
    {  
        return 0;
    }
    for ( i = len1,j = 0; i < 256; i++)
    {
        str1[i]=str2[j];
        if(j>=len2) break;
        j++;
    }
    str1[len1 + len2] = '\0'; // 必须加结束符！
    return 1;  
}