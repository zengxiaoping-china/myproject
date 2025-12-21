//练习4-4：编写一个程序，判断2000年至2200年中哪些年份是闰年，并将闰年年份输出。

#include<stdio.h>

int main(){
    int count = 0;
    printf("\n\n====================== 判断2000年至2200年中哪些年份是闰年 并将闰年年份输出 ======================\n\n");
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
    for (int i = 2000; i < 2200; i++)
    {
        if(i % 4 ==0 && i % 100 != 0 || i % 400 == 0){
            printf("%d年时闰年  |  ",i);
            if(++count % 10 ==0) printf("\n\n");
        }
    }
    printf("\n\n");
    return 0;   
}