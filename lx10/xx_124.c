#include<stdio.h>


int main(){
    char str[100];
    FILE *fp = fopen("file.txt", "w+");
    if (fp == NULL)
    {
        printf("Failed to create file\n");
        return 1; // 返回一个非零值表示错误
    }
    char str1[100] = "This is a sample text";
    fprintf(fp, "%s\n", str1);

    // 移动文件指针到文件开头
    fseek(fp, 0, SEEK_SET);

    // 读取文件内容
    fgets(str, sizeof(str), fp);
    printf("Read from file: %s", str);

    //写入内容
    fseek(fp,7,SEEK_SET);
    fputs(" C Programming Langauge ",fp);

    // 移动文件指针到文件开头
    fseek(fp, 0, SEEK_SET);

    // 再次读取文件内容
    char str3[100];
    fgets(str3,100,fp);
    fclose(fp);

    printf("%s\n",str3);
    
    return 0;
}