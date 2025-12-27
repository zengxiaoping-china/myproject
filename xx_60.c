//写一个判素数的函数,在主函数输人一个整数,输出是否为素数的信息。

#include<stdio.h>
#include<math.h>

int is_prime(int a);

int main(){
    int a;
    printf("\n请输入一个整数：");
    scanf("%d",&a);
    printf("\n");
    if(is_prime(a)==1) printf("%d是素数\n",a);
    if(is_prime(a)!=1) printf("%d不是素数\n",a);
    return 0;
}

int is_prime(int a){
    int i;
    if(a<=1)
    {  
        return 0;
    }
    if (a==2)
    {
        return 1;
    } 
    if (a % 2 == 0)
    {
        return 0;
    }
    for ( i = 3;i*i <= a; i=i+2)
    {
            if (a % i == 0)
            {
                return 0;
            }            
    }
    return 1;
}