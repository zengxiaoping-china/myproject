//定义共用体，对共用体中的成语进行赋值，访问共用体的成员

#include<stdio.h>
#include<string.h>

union Date
{
    int i;
    float f;
    char str[30];
};

int main(){
    union Date date;
    
    date.i=25;
    printf("date.i = %d \n\n",date.i);

    date.f=23.56;
    printf("date.f = %.2f \n\n",date.f);

    strcpy(date.str,"这是一个C程序");
    printf("date.str = \"%s\"\n",date.str);

    return 0;
}