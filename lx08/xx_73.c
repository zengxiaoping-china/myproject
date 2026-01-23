//练习通过交换改变指针变量改变指针指向

#include<stdio.h>

int main(){
    int a=5,b=8;
    int *p1,*p2,*p;
    p1 = &a;
    p2 = &b;
    printf("\na = %lld b = %lld\n\n",a,b);
    printf("&a= %-10X &b = %-10X\n\n",&a,&b);
    printf("p1= %-10X p2 = %-10X\n\n",p1,p2);
    if (a<b)
    {
        p = p1,p1 = p2,p2=p;
        //p1 = &b,p2 = &a; //直接变更地址
    }
    printf("p1= %-10X p2 = %-10X\n\n",p1,p2);
    printf("max= %d min = %d\n\n",*p1,*p2);
    printf("a = %d b = %d\n",a,b);
}