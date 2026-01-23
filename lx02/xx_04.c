//练习4-4：编写一个程序，判断year_min年至year_max年中哪些年份是闰年，并将闰年年份输出。

#include<stdio.h>

int main(){
    int count = 0;
    int year_min,year_max;
    printf("\n");
    printf("请输入起始年份：");
    scanf("%d",&year_min);
    printf("\n");
    printf("请输入结束年份：");
    scanf("%d",&year_max);
    printf("\n\n======================================================== 判断%d年至%d年中哪些年份是闰年 并将统计闰年数量 ========================================================\n\n",year_min,year_max);
    /*
    for (int i = 2000; i <= 2500; i++)
    {
        if(i % 4 == 0){     
            if(i % 100 != 0){     
                printf("%d年是闰年 |  ",i);
                if (++count % 10 == 0) printf("\n\n");
            }
            else if (i % 400 == 0)
            {
                printf("%d年是闰年 |  ",i);
                if (++count % 10 == 0) printf("\n\n");
            }          
        }
    }
        */
    for (int i = year_min; i <= year_max; i++)
    {
        if(i % 4 ==0 && i % 100 != 0 || i % 400 == 0){
            count++;
            printf("%d年时闰年",i);
            if(count % 10!=0 && (i+4)<=year_max) printf("  |  ");
            if(count % 10 ==0) printf("\n\n");
        }
    }
    if(count % 10 !=0) printf("\n\n");
    printf("这期间一共有 %d 个闰年\n\n",count);
    return 0;   
}