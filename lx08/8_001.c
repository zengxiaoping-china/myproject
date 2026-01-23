//用指向指针的指针的方法对5个字符串进行排序并输出

#include<stdio.h>
#include<string.h>

#define NUM 5
#define MAX_LED 100

//辅助函数：输入字符串到二维数组
void input_string(char strings[][MAX_LED]){
    printf("请输入%d个字符串：",NUM);
    for (int i = 0; i < NUM; i++)
    {
        // 读取字符串到二维数组中
        fgets(strings[i],MAX_LED,stdin);
        // 去除 fgets 可能读取的换行符
        strings[i][strcspn(strings[i], "\n")] = 0;
    }
}

//辅助函数：对字符串进行排序
void string_sort(char **p){
    char *temp;
    int i,j;
    for ( i = 0; i < NUM-1; i++)
    {
        for ( j = 0; j < NUM-1-i; j++)
        {
            if (strcmp(*(p+j),*(p+j+1))>0)
            {
                temp=*(p+j);
                *(p+j)=*(p+j+1);
                *(p+j+1)=temp;
            }    
        }
    }   
}

//辅助函数：打印字符串
void print_string(char **p){
    for (int i = 0; i < NUM; i++)
    {
        printf("%s\n",*(p+i));
    }   
}

int main(){
    char strings[NUM][MAX_LED];
    char *str[NUM];
    char **p;
    input_string(strings);
    for (int i = 0; i < NUM; i++)
    {
        str[i]=strings[i];
    }
    p=str;
    string_sort(p);
    printf("\n=======排序后的字符串=======\n");
    print_string(p);
    return 0;
}

