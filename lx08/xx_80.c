//练习指向二维数组的指针变量

#include<stdio.h>

float average(float *p,int n); //函数声明（求N个学生所有课程的平均成绩的函数）

float search(float (*p)[4],int i); //函数声明（输出第N个学生所有课程成绩及总成绩的函数）

void search_2(float (*p)[4]);//函数声明（找出所有凡是有一门成绩不及格的同学，并输入他们的所有课程成绩的函数）

float aver,sum;

int main(){
    float score[3][4] = {{87,69,89,75},{52,89,95,56},{85,58,96,68}};

    aver = average(*score,12);

    printf("\naverage = %5.2f\n\n",aver);

    sum = search(score,2);

    printf("\n\nsearch = %5.2f\n\n",sum);

    search_2(score);
}

//求N个学生所有课程的平均成绩的函数
float average(float *p,int n){
    float sum = 0,aver;
    float *p_end = p+n-1;
    for (; p <= p_end; p++)
    {
        sum = sum + *p;
    }
    aver = sum / n;
    return(aver);
}

//输出第N个学生所有课程成绩及总成绩的函数
float search(float (*p)[4],int n){
    float sum=0;
    int i;
    for ( i = 0; i < 4; i++)
    {
        printf("%5.2f ",*(*(p+n)+i));
        sum = sum + *(*(p+n)+i);
    }
    return(sum);
}

//找出所有凡是有一门成绩不及格的同学，并输入他们的所有课程成绩的函数
void search_2(float (*p)[4]){
    float sum=0;
    int i,j;
    for ( i = 0; i < 3; i++)
    {
        int k=0;
        for ( j = 0; j < 4; j++)
        {
            if (*(*(p+i)+j)<60)
            {
                k=1;
            }        
        }
        if(k){
           printf("序号是%d的同学所有课程的成绩是：",i);
           for ( j = 0; j < 4; j++)
            {
                printf("%5.2f ",*(*(p+i)+j));
            } 
            printf("\n\n");
        }
    }
}