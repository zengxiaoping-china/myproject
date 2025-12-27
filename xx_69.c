//写一个函数,输人一个N(N<10)位正整数,要求输出这N个数字字符,但每两个数字间空-个空格。如输人1990,应输出“1 9 9 0”。

#include<stdio.h>

//获取整数位数的函数
int count_digits(int n) {
    if (n == 0) return 1;  // 特殊情况：0 是 1 位
    
    int count = 0;
    while (n != 0) {
        count++;
        n = n / 10;  // 去掉最后一位
    }
    return count;
}

int main(){
    int i,n,num;
    char ch_arr[12];
    printf("\n请输入一个N(N<10)位正整数：");
    scanf("%d",&num);
    n = count_digits(num); //获取输入的整数位数
    if(n>=10 || num<=0){
        printf("\n错误：输入的整数不在1到9位正整数范围内\n");
        return 1;
    }

    //将整数中的每一个数字转换成整形数组元素
    int digits[10];
    int temp = num;
    // 从个位开始提取（逆序）
    for (int i = n-1; i >= 0; i--) {
        digits[i] = temp % 10;
        temp /= 10;
    }
    
    //打印整形数组所有元素（查看转换情况）
    for ( i = 0; i < n; i++)
    {
        printf("%d\n",digits[i]);
    }

    printf("================================\n");//打印分割线方便观察

    //将整形数组转换成字符数组
    for ( i = 0; i < n; i++)
    {
        ch_arr[i]=digits[i]+'0';
    }

    //输出字符数组（字符中间用空格隔开）
    for ( i = 0; i < n; i++)
    {
        printf("%c",ch_arr[i]);
        if (i<n-1)
        {
            printf(" ");
        }
    }
    return 0;  
}