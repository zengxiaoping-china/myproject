//


#include<stdio.h>
#define N 3

struct Student
{
    long int num;
    char name[20];
    float srcoe[3];
    float aver;
};

void input(struct Student stu[]);
struct Student max(struct Student stu[]);
void print(struct Student stu);

int main(){
    struct Student stu[N];
    struct Student *p=stu;
    input(p);
    printf("\n--------------------\n");
    printf("平均成绩最高的是：\n");
    print(max(p));
    return 0;
}

void input(struct Student stu[]){
    int i,j;
    float sum;
    for ( i = 0; i < N; i++)
    {
        printf("请输入第%d个学生的学号：",i+1);
        scanf("%ld",&stu[i].num);
        printf("请输入第%d个学生的姓名：",i+1);
        scanf("%s",stu[i].name);
        for ( j = 0; j < N; j++)
        {
            printf("请输入第%d个学生的第%d门成绩：",i+1,j+1);
            scanf("%f",&stu[i].srcoe[j]);
        }
        sum=0;
        for ( j = 0; j < N; j++)
        {
            sum=sum+stu[i].srcoe[j];
        }
        stu[i].aver=sum/N;
    }
}

struct Student max(struct Student stu[]){
    int i,max=0;
    for ( i = 1; i < N; i++)
    {
        if (stu[max].aver<stu[i].aver)
        {
            max=i;
        }
    }
    return(stu[max]);
}

void print(struct Student stu){
    int i;
    printf("Num:%ld\n",stu.num);
    printf("Name:%s\n",stu.name);
    printf("Srcoe:");
    for (i = 0; i < N; i++)
    {
        printf("%2.2f ",stu.srcoe[i]);
    }
    printf("\n");
    printf("Aver:%2.2f\n",stu.aver);
}