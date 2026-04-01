#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NAME_LENGHT 20
#define FILE_NAME "students.txt"

typedef struct 
{
    int id;
    float chinese;
    float math;
    float english;
    float avargrade;
    char name[NAME_LENGHT];
}Stu;

int main(){
    FILE *fp=NULL;
    Stu stu[5];
    int i;
    float avargrade = 0;

    printf("请输入五个学生的信息：学生号，学生名字，语文成绩，数学成绩，英语成绩\n\n");
    
    for ( i = 0; i < 5; i++)
    {
        printf("请输入第%d个学生资料：",i+1);
        scanf("%d %s %f %f %f",&stu[i].id,stu[i].name,&stu[i].chinese,&stu[i].math,&stu[i].english);
        stu[i].avargrade = (stu[i].chinese+stu[i].math+stu[i].english) / 3;
    }
    

    if((fp=fopen(FILE_NAME,"w"))==NULL)
    {
        printf("打开文件失败！程序立即退出\n");
        exit(0);
    }

    for ( i = 0; i < 5; i++)
    {
        fprintf(fp,"%d|%s|%.2f|%.2f|%.2f|%.2f\n",stu[i].id,stu[i].name,stu[i].chinese,stu[i].math,stu[i].english,stu[i].avargrade);
    }
    printf("学生信息已经保存到文件%s",FILE_NAME);
    fclose(fp);

    return 0;  
}

