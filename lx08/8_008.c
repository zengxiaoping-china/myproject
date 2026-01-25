//11.在主函数中输入10 个等长的字符串。用另一函数对它们排序。然后在主函数输出这10 个已排好序的字符串。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STR_NUM 10

int input_strings(char strings[][256]){
    for ( int i = 0; i < STR_NUM; i++)
    {
        printf("请输入第 %d 行: ", i + 1);
        if (fgets(strings[i],sizeof(strings[i]),stdin)==NULL)
        {
            if (feof(stdin)) {
                fprintf(stderr, "\n输入提前结束（EOF）。\n");
            } else {
                fprintf(stderr, "读取输入失败！\n");
            }
            return -1;
        }
        strings[i][strcspn(strings[i], "\n")] = '\0'; // 去掉换行
    }
    return 0; 
}

void sort_string(char *str_pt[]){
    char *temp;
    for (int i = 0; i < STR_NUM-1; i++)
    {
        int k=i;
        for (int j = 1+i; j <STR_NUM ; j++)
        {
            if (strcmp(str_pt[j],str_pt[k])<0)//升序
            {
                k=j;
            }
        }
        if (k!=i)
        {
            temp=str_pt[k];
            str_pt[k]=str_pt[i];
            str_pt[i]=temp;
        }
    }
    
}

void print_string(char *str_pt[]){
    for (int i = 0; i < STR_NUM; i++)
    {
        printf("%s\n",str_pt[i]);
    }
}

int main(){
    char strings[STR_NUM][256];
    char *str_pt[STR_NUM];
    for ( int i = 0; i < STR_NUM; i++)
    {
        str_pt[i]=strings[i];
    }

    if (input_strings(strings) != 0) {
        fprintf(stderr, "获取字符串失败！\n");
        return 0;
    }
    sort_string(str_pt);
    print_string(str_pt);
    return 0;
}