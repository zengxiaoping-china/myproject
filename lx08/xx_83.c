//练习指向函数的指针

#include<stdio.h>

int max(int x,int y);
int min(int x,int y);

int main(){
    int a,b,d;
    int (*p)(int,int);
    printf("请输入两个整数：");
    scanf("%d %d",&a,&b);
    printf("\na = %d b = %d\n\n",a,b);
    printf("请选择两个数中的最大值还是最小值\n\n");
    printf("求最大值选1 求最小值选2\n\n");
    printf("请输入你的选择：");
    scanf("%d",&d);
    switch (d)
    {
    case 1:
        p = max;
        break;
    case 2:
        p = min;
        break;
    default:
        printf("输入的选择错误！");
        return 1;
    }
    printf("\n结果：%d\n",(*p)(a,b));
    return 0;
}

int max(int x,int y){
    int z;
    if (x<y)
    {
        z = y;
    }else{
        z = x;
    }
    return(z);   
}

int min(int x,int y){
    int z;
    z = x<y?x:y;
    return(z);
}