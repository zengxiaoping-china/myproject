//习题17.将一个整数n转换成字符串。例如,输入483,应输出字符串"483"。n的位数不确定,可以是任意位数的整数。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//求整数的位数的函数
int count_digits(long long n){
    if(n==0) return 1;
    if(n<0) n=-n;
    int count =0;
    while (n)
    {
        count++;
        n=n/10;
    }
    return(count);
}

//将整数转换成字符串的函数
char * num_to_string(long long n){
    if(n==0){
        char *s = malloc(2);
        if(s){s[0]='0';s[1]='\0';}
        return s;
    }
    
    int negative=(n<0);
    if(negative){n=-n;}

    int len=count_digits(n);

    char *str=malloc(len+negative+1);
    if(!str) return NULL;

    int i=len+negative;
    str[i]='\0';
    i--;

    while (n)
    {
        str[i]='0'+ (n%10);
        n=n/10;
        i--;
    }
    if (negative)
    {
        str[i]='-';
    }
    return(str);
}

int main(){
    long long n;
    int len;
    printf("============将一个整数转换成字符串============\n\n");
    printf("请输入一个任意位数的整数：");
    scanf("%lld",&n);
    char *string=num_to_string(n);
    if (string) {
        printf("字符串: %s\n", string); // 输出 "-12345"
        free(string); // ⚠️ 别忘了释放！
    }
    return 0;
}