//16.输入一个字符串,内有数字和非数字字符，例如:A123x456 17960?302tab5876
//将其中连续的数字作为一个整数,依次存放到一数组a 中。例如,123 放在 a[0],456 放在a[1]....统计共有多少个整数,并输出这些数。

#include <stdio.h>
#include <string.h>

void print_str(char str[][25], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", str[i]);
    }
}

void print_arr(long long arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld\n", arr[i]);
    }
}

void string_search_num(char str[]) {
    char temp[25];                // 临时存储当前数字字符串
    char string_num[256][25];     // 存储所有数字字符串
    long long arr[256];           // 存储转换后的整数
    int k = 0;                    // 数字字符串个数
    int count = 0;                // temp 中字符个数

    // 初始化 temp 为空
    temp[0] = '\0';

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            // 累积数字字符到 temp
            // 防止超过18位（long long 最多安全表示18位十进制数）
            if (count < 18) {
                temp[count] = str[i];
                count++;
            }

            // 如果已满18位，或下一个不是数字，或到结尾，则结束当前数字
            if (str[i + 1] < '0' || str[i + 1] > '9' || str[i + 1] == '\0'|| count == 18) {
                temp[count] = '\0';               // 结束字符串
                strcpy(string_num[k], temp);      // 保存到 string_num
                k++;
                count = 0;                        // 重置计数器
                temp[0] = '\0';                   // 清空 temp
            }
        }
    }

    printf("\n打印数字字符串数据\n\n");
    print_str(string_num, k);
    printf("\n==========================\n\n");

    // 将 string_num 转为整数
    for (int i = 0; i < k; i++) {
        long long num = 0;
        for (int j = 0; string_num[i][j] != '\0'; j++) {
            num = num * 10 + (string_num[i][j] - '0');
        }
        arr[i] = num;
    }

    printf("\n打印整数数组\n\n");
    print_arr(arr, k);
    printf("一共有 %d 个数字", k);
}

int main() {
    char string[256];
    printf("请输入一个字符串：");
    if (fgets(string, sizeof(string), stdin) == NULL) {
        printf("输入的字符串错误！");
        return -1;
    }
    // 移除 fgets 读入的换行符
    string[strcspn(string, "\n")] = '\0';

    string_search_num(string);
    return 0;
}