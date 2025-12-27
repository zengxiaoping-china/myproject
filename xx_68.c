//写一个函数,输人一个4位数字,要求输出这4个数字字符,但每两个数字间空-个空格。如输人1990,应输出“1 9 9 0”。

#include<stdio.h>
#include<math.h>

int main(){
    int i,j,num;
    int ch_arr[10];
    printf("\n请输入一个4位整数：");
    scanf("%d",&num);
    if(num>=10000 || num<1000){
        printf("\n错误：输入的整数不是4位整数\n");
        return 1;
    }

    //将整数中的每一个数字转换成整形数组元素
    int digits[4];
    int temp = num;
    // 从个位开始提取（逆序）
    for (int i = 3; i >= 0; i--) {
        digits[i] = temp % 10;
        temp /= 10;
    }
    
    //打印整形数组所有元素（查看转换情况）
    for ( i = 0; i < 4; i++)
    {
        printf("%d\n",digits[i]);
    }

    printf("================================\n");//打印分割线方便观察

    //将整形数组转换成字符数组
    for ( i = 0; i < 4; i++)
    {
        ch_arr[i]=digits[i]+'0';
    }

    //输出字符数组（字符中间用空格隔开）
    for ( i = 0; i < 4; i++)
    {
        printf("%c",ch_arr[i]);
        if (i<3)
        {
            printf(" ");
        }
    }
    return 0;  
}