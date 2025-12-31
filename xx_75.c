//练习指针变量作为函数参数改变调用函数中多个变量的值

#include<stdio.h>

void swap(int *p1,int *p2);
void exchange(int *p1,int *p2,int *p3);

int main(){
    int a,b,c;
    int *p1,*p2,*p3;
    printf("\n请输入三个整数：");
    scanf("%d %d %d",&a,&b,&c);
    p1=&a,p2=&b,p3=&c;
    exchange(p1,p2,p3);
    printf("\nmax = %d mid = %d min = %d\n",*p1,*p2,*p3);
    return 0;
}

void exchange(int *p1,int *p2,int *p3){
    if(*p1<*p2){
        swap(p1,p2);
    }
    if (*p2<*p3)
    {
        swap(p2,p3);
        if (*p1<*p2)
        {
            swap(p1,p2);
        }
    }
}

void swap(int *p1,int *p2){
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}