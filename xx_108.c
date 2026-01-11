//通过指向结构体变量的指针变量输出结构体变量中成员的信息。

#include<stdio.h>
#include<string.h>

int main(){
    struct Student
    {
        long int num;
        char name[20];
        char sex;
        float score;
    };
    
    struct Student stu;
    struct Student *p;
    p=&stu;

    stu.num = 10101;
    strcpy(stu.name,"ZengXiaoping");
    stu.sex = 'M';
    stu.score=96.50;
    //p->num = 10102;

    printf("Num:%ld\n",stu.num);
    printf("Name:%s\n",stu.name);
    printf("Sex:%c\n",stu.sex);
    printf("Score:%2.2f\n",stu.score);

    printf("------------------\n");

    printf("Num:%ld\n",(*p).num);
    printf("Name:%s\n",(*p).name);
    printf("Sex:%c\n",(*p).sex);
    printf("Score:%2.2f\n",p->score);

    return 0;
}