//枚举数据类型

#include<stdio.h>
#include <time.h>

int main(){

    clock_t start = clock();  // ⏱️ 开始计时

    enum Color{red,yellow,bule,white,black};
    enum Color i,j,k,pri;
    int n,loop;
    n=0;
    for ( i = red; i <= black; i++)
    {
        for ( j = red; j <= black; j++)
        {
            if (j!=i)
            {
                for ( k = red; k <= black; k++)
                {
                    if ((k!=i) && (k!=j))
                    {
                        n++;
                        printf("%-4d",n);
                        //printf("%d %d %d\n",i,j,k);
                        for ( loop = 1; loop <= 3; loop++)
                        {
                            switch (loop)
                            {
                            case 1: pri=i;break;
                            case 2: pri=j;break;
                            case 3: pri=k;break;
                            default:break;
                            }
                            switch (pri)
                            {
                                case red:printf("%-10s","red");break;
                                case yellow:printf("%-10s","yellow");break;
                                case bule:printf("%-10s","bule");break;
                                case white:printf("%-10s","white");break;
                                case black:printf("%-10s","black");break;
                                default:break;
                            }
                        }
                        printf("\n"); 
                    }
                    
                }
                
            }
            
        }
        
    }
    printf("\nntotal:%d\n",n);

    clock_t end = clock();    // ⏱️ 结束计时

    // 计算耗时（单位：秒）
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n🕒 程序 CPU 执行时间: %.6f 秒\n", cpu_time_used);

    return 0;
}