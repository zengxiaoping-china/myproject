#include<stdio.h>

int count_one_bits(unsigned value){
    int ones,i=0;
    int bits[100];
     printf("value=");
    for (ones=0;  value!=0; value = value >> 1,i++)
    {
        if (value % 2 !=0)
        {
            ones++;
            bits[i]=1;  
        }
        else
        {
            bits[i]=0;
        }
    }

    for ( int j = i-1; j >= 0; j--)
    {
        printf("%d",bits[j]);
    }
    printf("\n");
    return ones;
}

int main(){
    long long value=0;
    int count;
    printf("\n请输入一个正整数：");
    scanf("%lld",&value);
    count = count_one_bits(value);
    printf("count = %d\n\n",count);

    value=value>>3;
    count = count_one_bits(value);
    printf("count = %d\n\n",count);

    return 0; 
}