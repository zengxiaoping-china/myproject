//练习

#include<stdio.h>

int main(){
    float average(float arr[10]);
    float score[10];
    float aver;
    int i;
    printf("\n请输入十个学生的成绩：");
    for ( i = 0; i < 10; i++)
    {
        scanf("%f",&score[i]);
    }
    aver = average(score);
    printf("\n十个学生的平均成绩是：%2.2f",aver);
    printf("\n");
}

float average(float arr[10]){
    int i;
    float sum = 0,aver;
    for ( i = 0; i < 10; i++)
    {
        sum = sum + arr[i];
    }
    aver = sum / 10;
    return(aver);
}