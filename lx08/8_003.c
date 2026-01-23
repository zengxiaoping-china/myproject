#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100 // 最大有效字符数 (不包括 '\0')
#define BUF_SIZE (MAX_LEN + 2) // 缓冲区大小 = MAX_LEN + 换行符 + '\0'

// ========== 排序函数 ==========
// 唯一参数 p: 指向以 NULL 结尾的字符串指针数组
void sort_strings(char **p) {
    if (p == NULL || *p == NULL) {
        // 空数组或无效指针，直接返回
        return;
    }

    // 1. 首先计算数组长度 (通过查找 NULL 哨兵)
    int count = 0;
    while (p[count] != NULL) {
        count++;
    }

    // 2. 使用冒泡排序进行排序
    char *temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(p[j], p[j + 1]) > 0) {
                // 交换指针
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
// ============================

//==========辅助函数：安全读取一行字符串 ==========
char* safe_read_line(const char* prompt) {
    char buffer[BUF_SIZE];
    printf("%s", prompt);

    // 1. 尝试读取一行
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        // 遇到 EOF 或错误
        return NULL;
    }

    // 2. 检查是否读取到了完整的行（即包含了换行符 '\n'）
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        // 情况A: 输入完整，正常去除换行符
        buffer[len - 1] = '\0';
        // 为精确长度分配内存
        return strdup(buffer);
    } else {
        // 情况B: 输入过长，fgets 没有读到 '\n'
        printf("【警告】输入过长！已截取前 %d 个字符。\n", MAX_LEN);
        
        // 手动添加字符串结束符
        buffer[MAX_LEN] = '\0';

        // 3. 清理输入缓冲区中剩余的字符
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            // 一直读取直到遇到换行符或文件结束
        }

        // 为截断后的字符串分配内存
        return strdup(buffer);
    }
}

// ========== 辅助函数：动态读取字符串并以 NULL 结尾 ==========
char **read_strings_with_sentinel() {
    int capacity = 2;
    int count = 0;
    char **str_array = (char **)malloc(capacity * sizeof(char *));
    if (!str_array) return NULL;

    printf("请输入任意数量的字符串（输入 \"Q\" 结束）:\n");
    char buffer[MAX_LEN];

    while (1) {
        printf(">> ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;

        buffer[strcspn(buffer, "\n")] = '\0';

        if (buffer[0] == 'Q') break;

        // 动态扩容
        if (count >= capacity) {
            capacity *= 2;
            char **temp = realloc(str_array, capacity * sizeof(char *));
            if (!temp) {
                // 内存分配失败，清理并退出
                for (int i = 0; i < count; i++) free(str_array[i]);
                free(str_array);
                return NULL;
            }
            str_array = temp;
        }

        // 复制字符串
        str_array[count] = strdup(buffer); // strdup = malloc + strcpy
        if (!str_array[count]) {
            // 内存分配失败，清理并退出
            for (int i = 0; i < count; i++) free(str_array[i]);
            free(str_array);
            return NULL;
        }
        count++;
    }

    // 关键步骤：添加哨兵 NULL
    // 先确保有足够空间存放 NULL
    char **temp = realloc(str_array, (count + 1) * sizeof(char *));
    if (temp) {
        str_array = temp;
    }
    str_array[count] = NULL; // 设置哨兵

    return str_array;
}
// ==========================================================

// ========== 清理函数 ==========
void free_strings(char **p) {
    if (!p) return;
    // 遍历直到遇到 NULL 哨兵
    for (int i = 0; p[i] != NULL; i++) {
        free(p[i]);
    }
    free(p);
}
// ============================

// ========== 打印字符串函数 ==========
void print_string(char **p){
    for (int i = 0; p[i] != NULL; i++)
    {
        printf("%s\n",*(p+i));
    }   
}
// ============================

// ========== 主函数 ==========
int main() {
    // 1. 读取字符串，得到一个以 NULL 结尾的指针数组
    char **p = read_strings_with_sentinel();
    if (!p) {
        fprintf(stderr, "读取字符串失败！\n");
        return 1;
    }

    printf("\n--- 排序前 ---\n");
    print_string(p);

    // 2. 调用排序函数，只传入 p
    sort_strings(p);

    printf("\n--- 排序后 ---\n");
    print_string(p);

    // 3. 清理内存
    free_strings(p);

    return 0;
}