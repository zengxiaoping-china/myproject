//练习指向函数的指针变量作为函数参数

#include<stdio.h>

int max(int x,int y){
    int z;
    z = x>y?x:y;
    return(z);
}

int min(int x,int y){
    int z;
    z = x<y?x:y;
    return(z);
}

int add(int x,int y){
    int z;
    z = x+y;
    return(z);
}

int fun(int (*p1)(int,int),int (*p2)(int,int),int (*p3)(int,int),int a,int b,int n){
    int result;
    switch (n)
    {
    case 1:
        result = (*p1)(a,b);
        break;
    case 2:
        result = (*p2)(a,b);
        break;
    case 3:
        result = (*p3)(a,b);
        break;
    default:
        printf("\n\n输入选择错误！\n");
        return -1;
    }
    return(result);
}

int main(){
    int a,b,n,result;
    int (*p1)(int,int);
    int (*p2)(int ,int);
    int (*p3)(int ,int);
    p1= max,p2=min,p3=add;
    printf("\n请输入两个整数a和b：");
    scanf("%d %d",&a,&b);
    printf("\na = %d b = %d",a,b);
    printf("\n\n请选择求他们的最大值（输入1），最小值（输入2），求和（输入3）:");
    scanf("%d",&n);
    result = fun(p1,p2,p3,a,b,n);
    if(result != -1) printf("\n结果是：%d\n",result);
    return 0;
}

