//练习返回指针值的函数

#include<stdio.h>

int *search(int (*p)[4],int n);

int main(){
    int score[][4] = {{65,78,95,84},{78,95,85,64},{63,78,89,75}};
    int k,i;
    int *p;
    printf("请输入需要查询成绩的同学序号：");
    scanf("%d",&k);
    p=search(score,k);
    for ( i = 0; i < 4; i++)
    {
        printf("%d ",*(p+i));
    }
    return 0;
}

int *search(int (*p)[4],int n){
    int *result;
    int i;
    for ( i = 0; i < 3; i++)
    {
        if (i==n)
        {
            result = *(p+i);
            break;
        }
    }
    return(result);
}