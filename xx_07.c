//练习7-3：编写一个程序，要求用户输入一个大于3的整数，然后判断该整数是否为素数，并给出相应的回答。

#include<stdio.h>

int main(){
    int n;
    int t=1;
    printf("\n\n请输入一个大于3的整数 由程序判断是否为一个素数 并给出回答\n\n");
    if(scanf("%d",&n) != 1){
        printf("输入无效！\n");
        return(1);
    }
    for (int i = 2; i*i <= n; i++)
    {
        if (n % i == 0){       
            t = 0;
            break;
        }        
    }
    if (t)
    {
        printf("\n\n%d是一个素数\n\n",n);
    }
    else{
        printf("\n\n%d不是一个素数\n\n",n);
    }
    
    return 0;
}