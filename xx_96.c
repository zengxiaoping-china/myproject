//习题5.有n个人围成一圈,顺序排号。从第1个人开始报数(从1到3报数),凡报到3的人退出圈子,问最后留下的是原来第几号的那位。

#include<stdio.h>

int main(){
    int i,n=5,count=n,k=0,j=0;
    int array[100];
    for ( i = 0; i < n; i++)
    {
        array[i]=1;
    }
    for (i=1;count>1;i++)
    {
        if (array[j])
        {
            k++;
            if(k==3)
            {
            array[j]=0;
            count--;
            k=0;
            }
        }
        j = (j + 1) % n;  // ✅ 关键：始终循环移动，用取模避免越界       
    }
    for ( i = 0; i < n; i++)
    {
        if (array[i]==1)
        {
            printf("\n最后留下来的是原来第%d号的那位\n",i+1);
            break;
        }
        
    }
   return 0; 
}