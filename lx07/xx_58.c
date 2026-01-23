//写两个函数,分别求两个整数的最大公约数和最小公倍数,用主函数调用这两个函数,并输出结果。两个整数由键盘输人。

#include<stdio.h>
int gcd(int a,int b);
int lcm(int a,int b);

int main(){
    int a,b;
    printf("\n");
    printf("请输入两个整数：");
    scanf("%d %d",&a,&b);
    if(a ==0 || b==0){
        printf("错误：输入的两个整数不能是0");
        return 0;
    }
    printf("\n%-2d 和 %-2d 的最大公约数是：%-2d\n\n",a,b,gcd(a,b));
    printf("%-2d 和 %-2d 的最小公倍数是：%-2d\n",a,b,lcm(a,b));
}

//求两个整数的最大公约数函数
int gcd(int a,int b){
    int i,gcd_value,min;
    a = a<0?-a:a; //转换成绝对值
    b = b<0?-b:b; //转换成绝对值
    min = a<b?a:b;
    gcd_value = 1;
    for ( i = 1; i <= min; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            gcd_value = i;
        }     
    }
    return(gcd_value);
}

//求两个整数的最小公倍数
int lcm(int a,int b){
    int i,lcm_value,max;
    a = a<0?-a:a; //转换成绝对值
    b = b<0?-b:b; //转换成绝对值
    lcm_value = a*b;
    max = a>b?a:b;
    for ( i = max; i <= a*b; i++)
    {
        if(i % a == 0 && i % b ==0)
        {
            lcm_value = i;
            break;
        }
    }
    return(lcm_value);
}