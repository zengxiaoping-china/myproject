//求 2/1、3/2、5/3、8/5...前20项之和；

#include<stdio.h>

int main(){
    double sum = 0.0;
    double num=2.0;
    double dem=1.0;
    int count=0;
    printf("\n");
    for (int i = 1; i <= 20; i++)
    {
        if (i!=20)
        {
            printf("%5.0f/%-5.0f + ",num,dem);
        }
        else{
            printf("%5.0f/%-5.0f",num,dem);
        }
        sum =sum + num / dem;
        int temp = num;
        num = dem +num;
        dem = temp;
        count++;
        if (count % 8 == 0)
        {
            printf("\n\n");
        }
        
    }
    printf(" = %10.5f",sum);
    printf("\n\nconunt = %d",count);
}