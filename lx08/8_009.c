//动态内存版本

//11.在主函数中输入N个字符串。用另一函数对它们排序。然后在主函数输出这N个已排好序的字符串。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 函数：动态读取字符串，返回字符串数组，通过 count 返回数量
char (*input_strings(int *count))[256] {
    int capacity = 5; // 初始容量
    *count = 0;

    // 分配初始内存：capacity 行，每行 256 字节
    char (*string)[256] = malloc(capacity * sizeof(*string));
    if (!string) {
        fprintf(stderr, "初始内存分配失败！\n");
        return NULL;
    }

    char line[256]; // 临时缓冲区
    while (1) {
        printf("请输入字符串（直接回车或 Ctrl+D 结束）: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            // 遇到 EOF（如 Ctrl+D / Ctrl+Z）
            break;
        }

        // 去掉换行符
        line[strcspn(line, "\n")] = '\0';

        // 如果输入空行，也结束
        if (line[0] == '\0') {
            break;
        }

        // 检查是否需要扩容
        if (*count >= capacity) {
            capacity *= 2;
            char (*new_string)[256] = realloc(string, capacity * sizeof(*string));
            if (!new_string) {
                fprintf(stderr, "内存扩容失败！\n");
                free(string);
                return NULL;
            }
            string = new_string;
        }

        // 复制到动态数组
        strcpy(string[*count], line);
        (*count)++;
    }

    // 可选：缩小到实际大小（避免浪费）
    if (*count > 0 && *count < capacity) {
        char (*trimmed)[256] = realloc(string, *count * sizeof(*string));
        if (trimmed) {
            string = trimmed;
        }
    }

    return string;
}

void sort_string(char **str_pt,int n){
    char *temp;
    for (int i = 0; i < n-1; i++)
    {
        int k=i;
        for (int j = 1+i; j <n ; j++)
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

void print_string(char **str_pt,int n){
    for (int i = 0; i < n; i++)
    {
        printf("%s\n",str_pt[i]);
    }
}

int main() {
    int count = 0;
    char (*strings)[256] = input_strings(&count);

    if (!strings || count == 0) {
        printf("无有效输入。\n");
        return 0;
    }

    char **str_pt = malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++) {
        str_pt[i] = strings[i];
    }

    sort_string(str_pt, count);
    print_string(str_pt, count);

    free(str_pt);
    free(strings);
    return 0;
}

