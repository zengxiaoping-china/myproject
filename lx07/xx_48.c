//练习一维数组作为函数参数使用

#include<stdio.h>

int main(){
    float average(float arr[],int n);
    float score1[5] = {85,79.5,92,68,82};
    float score2[10] = {89,68,75,92.5,95,63,74,86,83,56};
    float aver1,aver2;
    int n1 = sizeof(score1) / sizeof(score1[0]);
    int n2 = sizeof(score2) / sizeof(score2[0]);
    aver1 = average(score1,n1);
    aver2 = average(score2,n2);
    printf("\n");
    printf("第一班级（5 名同学）的平均成绩是：%2.2f \n\n",aver1);
    printf("第二班级（10名同学）的平均成绩是：%2.2f \n\n",aver2);
}

float average(float arr[],int n){
    float sum = arr[0],aver;
    int i;
    for (i = 1; i < n; i++)
    {
        sum = sum + arr[i];
    }
    aver = sum / n;
    return(aver);
}