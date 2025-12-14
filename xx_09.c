#include<stdio.h>

int main()
{
    printf("\n\n输入10个整数，输出其中最大的一个整数\n\n");
    int num;
    int max_num;
    for (int i = 1; i <= 10; i++)
    {
        while (1) {
        printf("请您输入第%d个整数：", i);
            if (scanf("%d", &num) == 1) {
                break; // 成功，跳出 while
            } else {
                printf("输入无效！请重新输入。\n");
                // 清空输入缓冲区
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        }
        if (i == 1)
        {
            max_num = num;
        }
        else if (num > max_num)
        {
            max_num = num;       
        }
    }
    printf("这10个整数中最大的数是：%d\n",max_num);
    return 0;
}
