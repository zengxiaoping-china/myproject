//写入二进制文件

#include <stdio.h>
#define SIZE 10

struct Student_type {
    char name[10];
    int num;
    int age;
    char add[15];
};

struct Student_type stud[SIZE];

void save() {
    FILE *fp;
    int i;
    if ((fp = fopen("stu.dat", "wb")) == NULL) {
        printf("打开文件错误！\n");
        return;
    }

    for (i = 0; i < SIZE; i++) {
        if (fwrite(&stud[i], sizeof(struct Student_type), 1, fp) != 1) {
            printf("文件写入错误！\n");
            fclose(fp);
            return;
        }
    }
    fclose(fp);
}

int main() {
    int i;
    printf("请输入 %d 个学生数据（姓名 学号 年龄 地址）：\n", SIZE);
    for (i = 0; i < SIZE; i++) {
        printf("学生 %d: ", i + 1);
        // 限制输入长度，防止溢出
        if (scanf("%9s %d %d %14s", stud[i].name, &stud[i].num, &stud[i].age, stud[i].add) != 4) {
            printf("输入格式错误！\n");
            return 1;
        }
    }
    save();
    printf("数据已保存到 stu.dat\n");
    return 0;
}
