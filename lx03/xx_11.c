//练习11-1：编写一个程序，提示用户输入一元二次方程的系数a、b和c，然后计算并显示该方程的两个实数根。

#include<stdio.h>
#include<math.h>

int main(){
    double a,b,c,disc,p,q,x1,x2;
    scanf("%lf%lf%lf",&a,&b,&c);
    printf("%lf %lf %lf\n",a,b,c);
    disc = b*b-4*a*c;
    printf("disc = %lf\n",disc);
    p = -b/(2.0*a);
    printf("p = %lf\n",p);
    q = sqrt(disc)/(2.0*a);
    printf("q = %lf\n",q);
    x1 = p+q;
    x2 = p-q;
    
    printf("x1=%7.2f\nx2=%7.2f\n",x1,x2);

    return 0;
}