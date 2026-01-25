//动态内存分配版本 自动扩容，无需预设上限（如 256）

//16.输入一个字符串,内有数字和非数字字符，例如:A123x456 17960?302tab5876
//将其中连续的数字作为一个整数,依次存放到一数组a 中。例如,123 放在 a[0],456 放在a[1]....统计共有多少个整数,并输出这些数。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_arr(long long *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld\n", arr[i]);
    }
}

void string_search_num(char str[]) {
    // 动态数组：初始容量
    int capacity = 10;  // 初始可存 10 个数字
    int count = 0;      // 当前已存数字个数

    // 动态分配：存储数字字符串（每个最多 19 位 + '\0'，我们分配 25 字节足够）
    char **string_num = malloc(capacity * sizeof(char *));
    if (!string_num) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }

    long long *arr = malloc(capacity * sizeof(long long));
    if (!arr) {
        free(string_num);
        fprintf(stderr, "内存分配失败！\n");
        return;
    }

    char temp[25];      // 临时缓冲区，最多存 18 位数字 + '\0'
    int temp_len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            // 防止超过 18 位（long long 安全上限）
            if (temp_len < 18) {
                temp[temp_len++] = str[i];
            }

            // 检查是否结束：下一个非数字 或 到末尾 或 已满 18 位
            if (str[i + 1] < '0' || str[i + 1] > '9' || 
                str[i + 1] == '\0' || temp_len == 18) {

                temp[temp_len] = '\0';

                // 如果当前容量不足，扩容（例如翻倍）
                if (count >= capacity) {
                    capacity *= 2;
                    char **new_string_num = realloc(string_num, capacity * sizeof(char *));
                    long long *new_arr = realloc(arr, capacity * sizeof(long long));
                    if (!new_string_num || !new_arr) {
                        // 回收已分配内存
                        for (int j = 0; j < count; j++) {
                            free(string_num[j]);
                        }
                        free(string_num);
                        free(arr);
                        fprintf(stderr, "内存扩容失败！\n");
                        return;
                    }
                    string_num = new_string_num;
                    arr = new_arr;
                }

                // 为当前数字字符串分配内存并复制
                string_num[count] = malloc((temp_len + 1) * sizeof(char));
                if (!string_num[count]) {
                    // 内存分配失败，清理
                    for (int j = 0; j < count; j++) {
                        free(string_num[j]);
                    }
                    free(string_num);
                    free(arr);
                    fprintf(stderr, "内存分配失败！\n");
                    return;
                }
                strcpy(string_num[count], temp);

                count++;
                temp_len = 0; // 重置临时缓冲区
            }
        }
    }

    // 第二阶段：将 string_num 转为 long long
    for (int i = 0; i < count; i++) {
        long long num = 0;
        for (int j = 0; string_num[i][j] != '\0'; j++) {
            num = num * 10 + (string_num[i][j] - '0');
        }
        arr[i] = num;
    }

    // 输出结果
    printf("\n打印整数数组:\n");
    print_arr(arr, count);
    printf("一共有 %d 个数字\n", count);

    // 释放动态内存
    for (int i = 0; i < count; i++) {
        free(string_num[i]);  // 释放每个字符串
    }
    free(string_num);         // 释放指针数组
    free(arr);                // 释放整数数组
}

int main() {
    char string[1024]; // 输入缓冲区仍用固定大小（合理假设）
    printf("请输入一个字符串：");
    if (fgets(string, sizeof(string), stdin) == NULL) {
        printf("输入错误！\n");
        return -1;
    }
    string[strcspn(string, "\n")] = '\0';

    string_search_num(string);
    return 0;
}