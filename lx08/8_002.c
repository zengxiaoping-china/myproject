#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 100 // 单个字符串的最大长度
#define INITIAL_CAPACITY 2 // 初始容量

/*
 * 动态读取字符串，直到用户输入结束标记
 * 参数:
 *   char ***p_str_array: 用于返回分配好的指针数组
 *   int *p_count: 用于返回实际读取的字符串数量
 * 返回值:
 *   成功返回 0，失败返回 -1
 */
int input_strings_dynamic(char ***p_str_array, int *p_count) {
    if (p_str_array == NULL || p_count == NULL) {
        return -1;
    }

    // 1. 初始化
    int capacity = INITIAL_CAPACITY; // 当前分配的容量
    int count = 0;                   // 当前已存储的字符串数量

    // 2. 为指针数组分配初始内存
    char **str_array = (char **)malloc(capacity * sizeof(char *));
    if (str_array == NULL) {
        fprintf(stderr, "初始内存分配失败!\n");
        return -1;
    }

    printf("请输入任意数量的字符串（输入 \"EOF\" 结束）:\n");

    while (1) {
        char buffer[MAX_STR_LEN]; // 临时缓冲区

        printf(">> ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // 处理 Ctrl+D (Linux/macOS) 或 Ctrl+Z (Windows)
            break;
        }

        // 去除换行符
        buffer[strcspn(buffer, "\n")] = '\0';

        // 检查结束条件
        if (strcmp(buffer, "EOF") == 0) {
            break;
        }

        // --- 动态扩容检查 ---
        if (count >= capacity) {
            // 容量不足，尝试扩容（这里采用翻倍策略）
            capacity *= 2;
            char **temp = (char **)realloc(str_array, capacity * sizeof(char *));
            if (temp == NULL) {
                fprintf(stderr, "内存扩容失败!\n");
                // 清理已分配的内存
                for (int i = 0; i < count; i++) {
                    free(str_array[i]);
                }
                free(str_array);
                return -1;
            }
            str_array = temp; // 更新指针
        }
        // ---------------------

        // 3. 为新字符串分配内存并复制
        str_array[count] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (str_array[count] == NULL) {
            fprintf(stderr, "字符串内存分配失败!\n");
            // 清理已分配的内存
            for (int i = 0; i <= count; i++) {
                free(str_array[i]);
            }
            free(str_array);
            return -1;
        }
        strcpy(str_array[count], buffer);
        count++;
    }

    // 4. （可选）将内存缩小到实际使用的大小
    // 这不是必须的，但可以节省一点内存
    if (count > 0) {
        char **temp = (char **)realloc(str_array, count * sizeof(char *));
        if (temp != NULL) {
            str_array = temp;
        }
        // 即使 realloc 失败，str_array 仍然有效，只是多占了点内存
    } else {
        // 如果一个字符串都没读到，释放初始内存
        free(str_array);
        str_array = NULL;
    }

    // 5. 通过指针参数“返回”结果
    *p_str_array = str_array;
    *p_count = count;

    return 0;
}

// 配套的清理函数
void free_strings(char **str_array, int count) {
    if (str_array == NULL) return;
    for (int i = 0; i < count; i++) {
        free(str_array[i]);
    }
    free(str_array);
}

// 主函数
int main() {
    char **strings = NULL;
    int count = 0;

    if (input_strings_dynamic(&strings, &count) != 0) {
        printf("读取字符串失败！\n");
        return 1;
    }

    printf("\n--- 共读取了 %d 个字符串 ---\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i + 1, strings[i]);
    }

    // 释放所有内存
    free_strings(strings, count);

    return 0;
}