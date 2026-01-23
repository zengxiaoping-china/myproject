#include<stdio.h>
#include<string.h>

// 将职工号字符串转整数（只处理正数）
int my_atoi(char s[]) {
    int num = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

//按职工号排序函数
void sort(char ids[][4], char names[][30]) {
    int i, j, k;
    char temp_id[4];
    char temp_name[30];

    for (i = 0; i < 9; i++) {
        k = i;
        for (j = i + 1; j < 10; j++) {
            // 用 my_atoi 比较数值大小
            if (my_atoi(ids[j]) < my_atoi(ids[k])) {
                k = j;
            }
        }
        // 交换 ids
        strcpy(temp_id, ids[k]);
        strcpy(ids[k], ids[i]);
        strcpy(ids[i], temp_id);

        // 交换 names
        strcpy(temp_name, names[k]);
        strcpy(names[k], names[i]);
        strcpy(names[i], temp_name);
    }
}

// 折半查找（无指针）：返回找到的下标，没找到返回 -1
int binary_search_index(char target_id[], char ids[][4], int n) {
    int target_num = my_atoi(target_id);
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int mid_num = my_atoi(ids[mid]);

        if (mid_num == target_num) {
            return mid;      // 找到了，返回下标
        } else if (mid_num < target_num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;  // 没找到
}

int main(){
    int i,j;
     int n = 10;
    // 10 个无序、不重复的三位工号
    char ids[10][4] = {
        "842", 
        "036",
        "693",
        "308",
        "021",
        "476",
        "234",
        "009",
        "510",
        "645"
    };

    // 对应的英文名，每个不超过 10 个字符
    char names[10][30] = {
        "刘亦菲",
        "陈慧琳",
        "郭富城",
        "苏有朋",
        "邓丽君",
        "陈淑桦",
        "张靓颖",
        "谢霆锋",
        "刘德华",
        "张学友"
    };
    
    /*    
    printf("请输入10个职工的职工号和姓名\n\n");
    for ( i = 0; i < 10; i++)
    {
        printf("\n输入第%d个职工的职工号和姓名：",i+1);
        scanf("%s %s",&ids[i],&names[i]);
    }
    */

    printf("\n未排序的职工表：\n\n");
    for ( i = 0; i < 10; i++)
    {
        printf("%-3s %-12s",ids[i],names[i]);
        if ((i+1) % 5 == 0) printf("\n\n");
    }
    if ((i) % 5 != 0) printf("\n\n");

    printf("===========================================================================\n\n");
    printf("排序后的职工表：\n\n");
    sort(ids,names);
    for ( i = 0; i < 10; i++)
    {
        printf("%-3s %-12s",ids[i],names[i]);
        if ((i+1) % 5 == 0) printf("\n\n");
    }
    if ((i) % 5 != 0) printf("\n\n");

     // 输入要查找的工号
    char input_id[10];
    printf("\n请输入要查找的工号: ");
    scanf("%s", input_id);

    // 查找（返回下标）
    int pos = binary_search_index(input_id, ids, n);

    if (pos != -1) {
        printf("\n职工号 %s 的职工姓名是: %s\n", ids[pos],names[pos]);
    } else {
        printf("\n未找到该工号( %s )的职工。\n",ids[pos]);
    }
}