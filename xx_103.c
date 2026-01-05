//18.编一程序,输入月份号,输出该月的英文月名。例如,输入 3,则输出"March",要求用指针数组处理。

#include<stdio.h>

int main(){
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int n,i;
    printf("请输入月份数字：");
    scanf("%d",&n);
    if (n<1 || n>12)
    {
        printf("输入的月份错误！");
        return 0;
    }
    
    for ( i = 0; i < 12; i++)
    {
        if (n==i+1)
        {
            printf("您输入的%d月份的英语单词是：%s",n,months[i]);
        }
        
    }
    return 0;
}