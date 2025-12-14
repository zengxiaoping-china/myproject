#include<stdio.h>

int main(){
    int deno;
    int sign;
    double sum;
    double term;
    sum =1.0;
    sign=1;
    printf("\t1");
    for ( deno = 2; deno <= 100; deno++)
    {
        sign=sign*-1;
        term=sign*(1.0/deno);
        sum=sum+term;
        if (sign==-1)
        {
            printf("\t-\t");
        }
        else{
            printf("\t+\t");
        } 
        printf("1/%d",deno);
        if (deno % 10 == 0)
        {
            printf("\n\n");
        }           
    }
    printf("\t=%.15f\n\n",sum);
    return 0;
}