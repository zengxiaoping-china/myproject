//练习通过指针引用数组

#include<stdio.h>

int main(){
    int array[10]={1,2,3,4,5,6,7,8,9,10};
    int *p;
    //p=&array[0];
    p=array;
    for (int i = 0; i < 10; i++)
    {
        //printf("%d ",array[i]);
        //printf("%d ",*(array+i));
        printf("%d ",*(p+i));
    }
    
}