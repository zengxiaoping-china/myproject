//练习指针变量作为函数参数

#include<stdio.h>
#include<stdint.h>

void swap(int *p1,int *p2);

int main(){
    int a=235,b=425;
    //printf("\n请输入两个整数：");
    //scanf("%d %d",&a,&b);
    int *pointer_1,*pointer_2;
    pointer_1 = &a;
    pointer_2 = &b;
    uintptr_t addr_1 = (uintptr_t)pointer_1;
    uintptr_t addr_2 = (uintptr_t)pointer_1;
    printf("\np1 = %llX p2 = %llX\n",pointer_1,pointer_2);
    printf("\np1 = %p p2 = %p\n",pointer_1,pointer_2);
    printf("\np1 = %o p2 = %o\n",pointer_1,pointer_2);
    if (a<b)
    {
        swap(pointer_1,pointer_2);
    }
    printf("\np1 = %lld p2 = %lld\n",pointer_1,pointer_2);
    printf("\nmax = %d min = %d\n",a,b);
    //*pointer_1 =52;
    pointer_1 = pointer_1 - 1; //指针变量算术运算测试
    printf("\np1 = %lld p2 = %lld\n",pointer_1,pointer_2);
    printf("\nmax = %d\n",*pointer_1);
}

//通过指针交换的函数
void swap(int *p1,int *p2){
    int temp;
    temp = *p1;
    *p1 = * p2;
    *p2 = temp;
}