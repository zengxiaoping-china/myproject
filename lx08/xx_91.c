//练习动态内存分配与指向它指针变量

#include<stdio.h>
#include<stdlib.h>

void chech(int *p,int n){
    printf("\n\n不及格的成绩：");
    for (int i = 0; i < n; i++)
    {
        if (*(p+i)<60)
        {   
            printf("%d ",*(p+i));
        }    
    }
}

int main(){
    int *pt,i,n;
    n=5;
    printf("\n请输入需要输入成绩的同学人数：");
    scanf("%d",&n);
    pt = (int *)malloc(n*sizeof(int));
    printf("\n输入%d个学生的成绩：",n);
    for ( i = 0; i < n; i++)
    {
        scanf("%d",pt+i);
    }
    printf("\n输入的%d个学生的成绩是：",n);
    for (int i = 0; i < n; i++)
    {  
        printf("%d ",*(pt+i));
    }
    chech(pt,n);
    free(pt);
    return 0;
}