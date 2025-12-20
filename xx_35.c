//比较三个字符串，输出按字典序最大的字符串

#include<stdio.h>
#include<string.h>

int main()
{
    char str[3][20];
    char string[20];
    int i,j;
    printf("请输入3个字符串：\n");
    for(i=0;i<3;i++)
    {
        printf("第 %d 个字符串: ",i+1);
        fgets(str[i], sizeof(str[i]), stdin); // 安全读取一行输入
        str[i][strcspn(str[i], "\n")] = '\0'; // 去掉换行符
    }
    for(i=0;i<2;i++)
    {
        if(strcmp(str[i],str[i+1]) > 0)
        {
            strcpy(string,str[i]);
        }
    }
    printf("按字典序最大的字符串是：%s\n",string);
    return 0;
}