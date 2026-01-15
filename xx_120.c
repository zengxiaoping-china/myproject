//读取文件

#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    char str[3][10];
    int i=0;
    if ((fp=fopen("D:\\myproject\\string.dat","r"))==NULL)
    {
        printf("打开文件错误！\n");
        exit(0);
    }
    while (fgets(str[i],10,fp)!=NULL)
    {
        printf("%s",str[i]);
        i++;
    }
    fclose(fp);
    return 0;
}