#include<stdio.h>

int main() {
    int i,n,num1,num2; 
    double sum =0.0; 
    for(i = 1; i <= 40; i++) {
        if(i < 3) {
            n=1;
            num1=n;
            num2=n;
        }
        else {
            n = num1 + num2;
            num1 = num2;
            num2 = n;
        }
        sum = sum + n;
        printf("%10d ", n);
        if(i % 10 == 0) {
            printf("\n\n");
        }
    }
    //补换行
    if(i % 10 != 1) {
        printf("\n\n");
    }
    printf("sum = %10.0f\n", sum);
    return 0;
}