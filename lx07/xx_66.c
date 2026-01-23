//给出年、月、日,计算该日是该年的第几天。

#include<stdio.h>

int is_valid_date(int year, int month, int day);
int is_leap_year(int year);
int day_of_year(int year, int month, int day);

int main(){
    int y,m,d,day_num;
    printf("\n请输入年、月、日：");
    scanf("%d %d %d",&y,&m,&d);
    if (!is_valid_date(y, m, d)) {
        printf("错误：输入的日期错误!\n");
        return 1;
    } 
    printf("\n您输入的日期是：%d年%d月%d日\n\n",y,m,d);
    day_num = day_of_year(y,m,d);
    printf("%d年%d月%d日是该年的第%d天",y,m,d,day_num);
    return 0;
}

// 日期合法性检查
int is_valid_date(int year, int month, int day) {
    if (year <= 0 || month < 1 || month > 12 || day < 1) return 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(year)) days_in_month[1] = 29;
    return day <= days_in_month[month - 1];
}

//判断是否是闰年的函数
int is_leap_year(int year){
    if (year % 4 == 0 && year % 100 !=0 || year % 400 == 0)
    {
        return 1;
    }
    return 0;
}

//计算该日是当年第几天函数
int day_of_year(int year, int month, int day){
    int i;
    int total = 0;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(is_leap_year(year)) days_in_month[1]=29;
 
    for ( i = 0; i < month-1; i++)
    {
        total = total + days_in_month[i];
    }
    total = total + day;
    return(total);
}