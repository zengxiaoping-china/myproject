//写一个函数,输人一行字符,将此字符串中最长的单词输出。

#include<stdio.h>
#include<string.h>

int main(){
    char str[256];
    int i,j=0,k=0,max=0;
    printf("\n请输入一行字符串：");
    // 安全读取一行输入
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
    }
    // 去掉换行符
    str[strcspn(str, "\n")] = '\0';
    printf("\n输入的有效字符串是：%s\n\n",str);

    for ( i = 0; str[i] !='\0'; i++)
    {
        if (str[i] !=' '|| str[i+1] =='\0')
        {   
            j++;
            if (str[i+1] =='\0')
            {
                //printf("j = %d\n",j);
                if (j>max){
                    max = j;
                    //printf("max = %d\n",max);
                    k=i+1;
                }
            }    
        }
        else
        {
            //printf("j = %d\n",j);
            if (j>max)
            {
                max = j;
                //printf("max = %d\n",max);
                k=i;
            }
            j = 0;
        }
    }
    //printf("k = %d\n\n",k);
    printf("字符串中最长的第一个单词是：");
    for ( i = k-max; i < k; i++)
    {
        printf("%c",str[i]);
    }
    printf("\n");
    return 0;
}