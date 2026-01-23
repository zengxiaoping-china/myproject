//习题 2.输入n 个字符串,按由小到大的顺序输出。

#include<stdio.h>
#include<string.h>

void string_sort(char *p[],int n);
void string_print(char *p[],int n);

int main(){
    int n=3,i=0;
    char str[10][256];
    printf("\n请输入%d个字符串，然后对其进行排序\n\n",n);
    while (i<n)
    {
        printf("请输入第 %d 个字符串（按回车结束）：",i+1);
        if (fgets(str[i], sizeof(str[i]), stdin) == NULL) {
        printf("输入错误。\n");
        return 1;
        }
        
        str[i][strcspn(str[i], "\n")] = '\0'; // 去掉换行符
        i++;
    }

    char *string[10];
    for ( i = 0; i < n; i++)
    {
        string[i]=str[i];
    }
    
    string_sort(string,n);
    string_print(string,n);
    return 0;
}

void string_sort(char *p[],int n){
    char *temp;
    int i,j,k;
    for ( i = 0; i < n; i++)
    {
        k=i;
        for ( j = 1+i;j<n; j++)
        {
            if (strcmp(*(p+k),*(p+j))>0)
            {
                k=j;
            }
        }
        if(k!=i)
        {
            temp=*(p+k),*(p+k)=*(p+i),*(p+i)=temp;
        }
        
    }
}

void string_print(char *p[],int n){
    int i;
    printf("\n对%d个字符串按从小到大排序后：\n\n",n);
    for ( i = 0; i < n; i++)
    {
        printf("%s\n",*(p+i));
    }
}