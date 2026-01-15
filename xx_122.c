//读取二进制文件

#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

struct Student_type
{
    char name[10];
    int num;
    int age;
    char addr[15];
};


void print(FILE *fp){
    struct Student_type stu[SIZE];
    int i;
    for ( i = 0; i < SIZE; i++)
    {
        fread(&stu[i],sizeof(struct Student_type),1,fp);
        printf("%-10s %4d %4d %-15s\n",stu[i].name,stu[i].num,stu[i].age,stu[i].addr);
    }    
}

int main(){
    FILE *fp;
    if ((fp=fopen("stu.dat","rb"))==NULL)
    {
        printf("打开文件错误！\n");
        exit(0);
    }
    print(fp);
    fclose(fp);
    return 0;  
}
