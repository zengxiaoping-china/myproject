//定义共用体，对共用体中的成语进行赋值，访问共用体的成员

#include<stdio.h>
#include<string.h>

union Date
{
    int i;
    float f;
    char str[20];
};

int main(){
    union Date date;
    date.i=25;
    //date.f=12.85;
    //strcpy(date.str,"测试数据");

    printf("date.i = %d\n",date.i);
    //printf("date.f = %2.2f\n",date.f);
    //printf("date.str = \"%s\"\n",date.str);

    return 0;
}