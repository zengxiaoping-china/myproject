#include<stdio.h>
#include<math.h>
int main(){
    int sign=1;
    double pi=0.0,term=1.0,j=1.0;
    do  
    {
        pi=pi+term;
        j=j+2;
        sign=-sign;   
        term=sign/j;
    } while (fabs(term)>=1e-8);
    pi=4*pi;
    printf("\nj=%2d\n",(int)j/2);
    printf("\n圆周率=%10.8f\n",pi);
    int i=1;
    return 0;
}