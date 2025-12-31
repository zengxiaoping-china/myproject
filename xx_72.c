//练习指针和指针变量

#include<stdio.h>

int main(){
    int a=5,b=8;
    int *pointer_1,*pointer_2;
    pointer_1 = &a;
    pointer_2 = &b;
    printf("\na = %-4d b = %-4d\n\n",a,b);
    printf("&a= %-10X &b = %-10X\n\n",&a,&b);
    printf("pointer_1= %-10X pointer_2 = %-10X\n\n",pointer_1,pointer_2);
    printf("pointer_1= %d pointer_2 = %d\n",*pointer_1,*pointer_2);
}