//练习函数嵌套调用

#include<stdio.h>

int main(){
    int a,b,c,d;
    int max;
    int max4(int a,int b,int c,int d);
    printf("\n请输入四个整数：");
    scanf("%d %d %d %d",&a,&b,&c,&d);
    max = max4(a,b,c,d);
    printf("\n最大值是：%d\n",max);
    return 0;
}
//函数max4实现四个数中的最大值
int max4(int a,int b,int c,int d){
    int m;
    int max2(int a,int b);
    m = max2(a,b);
    m = max2(m,c);
    m = max2(m,d);
    return m;
}
//函数max2实现两个数中的最大值
int max2(int a,int b){
    if(a>=b){
        return a;
    }
    else{
        return b;
    }
}

//代码精简版本
/*
int main(){
    int a,b,c,d,max;
    int max4(int a,int b,int c,int d);
    printf("\n请输入四个整数：");
    scanf("%d %d %d %d",&a,&b,&c,&d);
    max = max4(a,b,c,d);
    printf("\n最大值是：%d\n",max);
    return 0;
}

int max4(int a,int b,int c,int d){
    int max2(int a,int b);
    return max2(max2(max2(a,b),c),d);
}

int max2(int a,int b){
    return(a>=b?a:b);
}
*/