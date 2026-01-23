//有n个学生的信息(包括学号、姓名、成绩),要求按照成绩的高低顺序输出

#include<stdio.h>

struct Student
{
    int num;
    char name[20];
    float score;
};

int main(){
    struct Student student[5]={10101,"Wang",85.0,10102,"Zeng",75.0,10103,"Sun",92.5,10104,"Zhu",63.5,10105,"Huang",79.0,};
    const int n=5;
    int i,j,k;
    struct Student temp;
    //选择法排序
    for ( i = 0; i < n-1; i++)
    {
        k=i;
        for ( j = i+1; j < n; j++)
        {
            if (student[j].score>student[k].score)
            {
                k=j;
            }  
        }
        if (k!=i)
        {
            temp=student[k],student[k]=student[i],student[i]=temp;
        }
        
    }

    for ( i = 0; i < n; i++)
    {
        printf("Num:%6d\n",student[i].num);
        printf("Name:%s\n",student[i].name);
        printf("Score:%2.2f\n",student[i].score);
        printf("---------------------\n");
    }
    return 0;
}