//定义和使用结构体类型和结构体变量

#include <stdio.h>
#include <string.h>  // 用于 strcpy

int main() {
    struct Date {
        int month;
        int day;
        int year;
    };

    struct Student {
        long int num;
        char name[20];
        char sex;
        struct Date birthday;  // 修正拼写：brithday → birthday
        char add[20];
    };

    // 初始化结构体变量 a
    struct Student a = {
        10101,
        "LiLin",
        'M',
        {1, 13, 1988},         // month=1, day=13, year=1988
        "123 Beijing Road"
    };

    // 修复 printf：参数顺序要和格式串一致！
    printf("NO.:\n");
    printf("num: %ld\n", a.num);
    printf("name: %s\n", a.name);
    printf("sex: %c\n", a.sex);
    printf("birthday: %d-%d-%d\n", a.birthday.year, a.birthday.month, a.birthday.day);
    printf("add: %s\n", a.add);

    // 定义并部分初始化 b（指定初始化器）
    struct Student b = {.name = "ZengXiaoping"};

    b.sex = 'M';
    b.num = 10102;
    
    // ❌ 错误：b.add = "ChangSha"; —— 数组不能直接赋值！
    // ✅ 正确：使用 strcpy
    strcpy(b.add, "ChangSha");

    b.birthday.year = 1988;
    b.birthday.month = 1;
    b.birthday.day = 13;

    // 可选：打印 b 验证
    printf("\nStudent b:\n");
    printf("num: %ld\n", b.num);
    printf("name: %s\n", b.name);
    printf("sex: %c\n", b.sex);
    printf("birthday: %d-%d-%d\n", b.birthday.year, b.birthday.month, b.birthday.day);
    printf("add: %s\n", b.add);

    return 0;
}