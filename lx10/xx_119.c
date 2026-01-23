//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){ 
    FILE *fp;
    char str[3][10],temp[10];
    int i,j,k,n=3;
    for ( i = 0; i < n; i++)
    {
        printf("请输入第%d字符串：",i+1);
        fgets(str[i], sizeof(str[i]), stdin);
        str[i][strcspn(str[i], "\n")] = '\0';
    }
    //用选择排序法对字符串进行排序（升序）
    for ( i = 0; i < n-1; i++)
    {
        k=i;
        for ( j = i+1; j < n; j++)
        {
            if (strcmp(str[k],str[j])>0)
            {
                k=j;
            }    
        }
        if (k!=i)
        {
            strcpy(temp,str[i]),strcpy(str[i],str[k]),strcpy(str[k],temp);
        }
    }
    //打开磁盘文件
    if ((fp=fopen("D:\\myproject\\string.dat","w"))==NULL)
    {
        printf("文件打开错误！\n");
        exit(0);
    }
    //将字符串写入磁盘文件
    printf("将字符串写入文件\n");
    for ( i = 0; i < n; i++)
    {
        fputs(str[i],fp);
        fputs("\n",fp);
        printf("%s\n",str[i]);
    }
    return 0;
}