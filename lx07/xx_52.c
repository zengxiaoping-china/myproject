#include<stdio.h>

float Min = 0,Max = 0;
int main(){
    float average(float arr[],int n);
    float array[10];
    float aver;
    printf("\n请输入十个学生的成绩：");
    for (int i = 0; i < 10; i++)
    {
        scanf("%f",&array[i]);
    }
    printf("\n\n您输入的十个学生的成绩是：");
    for (int i = 0; i < 10; i++)
    {
        printf("%2.2f ",array[i]);
    }
    printf("\n\n");
    aver = average(array,10);
    printf("Min = %2.2f\n\n",Min);
    printf("Max = %2.2f\n\n",Max);
    printf("Aver = %2.2f\n",aver);
}

float average(float arr[],int n){
    int i;
    float aver,temp = 0;
    Max=arr[0];
    Min=arr[0];
    for ( i = 1; i < n; i++)
    {
        if (Max<arr[i])
        {
            Max = arr[i];
        }
        if (Min>arr[i])
        {
            Min = arr[i];
        }
        temp=temp+arr[i];     
    }
    aver = (temp + arr[0]) / n;
    return(aver);
}