

#include<stdio.h>

struct Student
{
    int num;
    char name[20];
    char sex;
    float score;
    int age;
};

int main(){
    struct Student stu[5]={
        {10101,"Zeng",'M',95.50,12},
        {10102,"Sun",'M',69.00,17},
        {10103,"Zhu",'S',85.50,15},
        {10104,"Wang",'M',79.00,18},
        {10105,"Huang",'M',87.50,14}
    };

    struct Student *p;
    printf(" NUM    NAME       SEX    SCORE   AGE\n");
    for ( p = stu; p < stu+5; p++)
    {
        printf("%d   %-6s      %c     %2.2f   %d\n",p->num,p->name,p->sex,p->score,p->age);
    }
    
}
