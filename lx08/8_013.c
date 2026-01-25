//14.将n个数按输入时顺序的逆序排列,用函数实现。

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long long * input_digit(int *number_count) {
    long long *numbers = NULL;
    int count = 0;
    int capacity = 10;

    numbers = malloc(capacity * sizeof(long long));
    if (!numbers) {
        fprintf(stderr, "初始内存分配失败！\n");
        *number_count = 0;
        return NULL;
    }

    char line[100];//输入临时缓冲区
    while (1) {
        printf("请输入第 %-2d 整数（直接回车或 Ctrl+D 结束）>> ",count+1);
        
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break; // EOF
        }

        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '\0') {
            break; // 空行
        }

        long long num;
        if (sscanf(line, "%lld", &num) != 1) {
            printf("无效输入，请输入整数！\n");
            continue;
        }

        if (count >= capacity) {
            capacity *= 2;
            long long *new_ptr = realloc(numbers, capacity * sizeof(long long));
            if (!new_ptr) {
                fprintf(stderr, "内存扩容失败！\n");
                // 释放已分配内存
                free(numbers);
                *number_count = 0;
                return NULL;
            }
            numbers = new_ptr;
        }
        numbers[count++] = num;
    }
    *number_count = count;
    return numbers;
}

void sort_digit(long long *digit,const int n){
    int i,j;
    long long temp;
    for (i = 0,j=n-1; i!=j; i++,j--)
    {
        temp=digit[i];
        digit[i]=digit[j];
        digit[j]=temp;
    }  
}

int main() {
    printf("请输入N个整数:\n\n");
    int number_count = 0;
    long long *digit = input_digit(&number_count);

    if (digit) {
        printf("获取了 %d 个有效数字:\n", number_count);
        for (int i = 0; i < number_count; i++) {
            printf("%lld ", digit[i]);
        }
        printf("\n");
    } else {
        printf("未获取任何有效数字。\n");
        free(digit);
        return 0;
    }
    printf("---------------------------------\n");
    sort_digit(digit,number_count);
    for (int i = 0; i < number_count; i++) {
        printf("%lld ", digit[i]);
    }
    printf("\n");
    free(digit);
    return 0;
}