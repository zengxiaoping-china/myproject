/*从键盘输人一个小于1000的正数,要求输出它的平方根(如平方根不是整数,则输出其整数部分)。要求在输人数据后先对其进行检查是否为小于1000的正数。若不是,则要求重新输人。*/
#include <stdio.h>
#include <math.h>
int main() {
    double num, sqrt_num;
    while (1) {
        printf("请输入一个小于1000的正数: ");
        scanf("%lf", &num);
        if (num > 0 && num < 1000) {
            break;
        } else {
            printf("输入错误，请重新输入。\n");
        }
    }
    sqrt_num = sqrt(num);
    printf("该数的平方根的整数部分为: %d\n", (int)sqrt_num);
    return 0;
}
