//习题1.定义一个结构体变量(包括年、月、日)。计算该日在本年中是第几天,注意闰年问题。

#include <stdio.h>

struct Date {
    int year;
    int month;
    int day;
};

// 判断是否为闰年
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 检查日期是否合法
int isValidDate(struct Date *d) {
    if (d->year < 1 || d->month < 1 || d->month > 12 || d->day < 1) {
        return 0;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    daysInMonth[1] = isLeapYear(d->year) ? 29 : 28;
    return d->day <= daysInMonth[d->month - 1];
}

// 计算该日是当年第几天（假设输入合法）
int days(struct Date *p) {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    daysInMonth[1] = isLeapYear(p->year) ? 29 : 28;

    int sum = 0;
    for (int i = 0; i < p->month - 1; i++) {
        sum += daysInMonth[i];
    }
    sum += p->day;
    return sum;
}

int main() {
    struct Date day;

    printf("请输入一个日期\n");
    while (1) {
        printf("请输入年份：");
        scanf("%d", &day.year);
        printf("请输入月份：");
        scanf("%d", &day.month);
        printf("请输入日子：");
        scanf("%d", &day.day);

        if (isValidDate(&day)) {
            break;
        }
        printf("输入的日期错误！请重新输入\n");
    }

    printf("输入的日期是：%d-%d-%d\n", day.year, day.month, day.day);
    int result = days(&day);
    printf("输入的日期是这一年中的第 %d 天\n", result);

    return 0;
}


