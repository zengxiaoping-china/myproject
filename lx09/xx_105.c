//输入两个学生的学号、姓名和成绩,输出成绩较高的学生的学号、姓名和成绩

#include<stdio.h>

int main(){
    struct Student
    {
        int num;
        char name[20];
        float score;
    };

    struct Student student1,student2;

    printf("\n请输入第一个学生的学号、名字、成绩：");
    scanf("%d %s %f",&student1.num,student1.name,&student1.score);
    printf("您输入的第一个学生的学号是：%d,名字是：%s,成绩是：%2.2f\n\n",student1.num,student1.name,student1.score);

    printf("请输入第二个学生的学号、名字、成绩：");
    scanf("%d %s %f",&student2.num,student2.name,&student2.score);
    printf("您输入的第二个学生的学号是：%d,名字是：%s,成绩是：%2.2f\n\n",student2.num,student2.name,student2.score);
   
    if (student1.score > student2.score)
    {
        printf("第一个学生的学号是：%d,名字是：%s,成绩是：%2.2f\n",student1.num,student1.name,student1.score);
    }
    else if (student1.score < student2.score)
    {
        printf("第二个学生的学号是：%d,名字是：%s,成绩是：%2.2f\n",student2.num,student2.name,student2.score);
    }
    else{
        printf("第一个学生的学号是：%d,名字是：%s,成绩是：%2.2f\n\n",student1.num,student1.name,student1.score);
        printf("第二个学生的学号是：%d,名字是：%s,成绩是：%2.2f\n",student2.num,student2.name,student2.score);
    }
      
}