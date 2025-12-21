//练习实现银行定期存款利息计算程序

#include <stdio.h>
#include <math.h>

int main() {
    const int YEARS = 5;
    double p, sum;
    int choice;

    // 打印标题和说明
    printf("\n\t======================== 2017年某银行定期存款方案 ========================\n\n");
    printf("\t（1）一次存 5 年期。\n");
    printf("\t（2）先存 2 年期，到期后将本息再存 3 年期。\n");
    printf("\t（3）先存 3 年期，到期后将本息再存 2 年期。\n");
    printf("\t（4）存 1 年期，到期后将本息再存 1 年期，连续存 5 次。\n");
    printf("\t（5）存活期存款。活期利息每一季度结算一次。\n\n");

    printf("\t2017 年的银行存款利率如下：\n\n");
    printf("\t1 年期定期存款利率为 1.5%%；\n");
    printf("\t2 年期定期存款利率为 2.1%%；\n");
    printf("\t3 年期定期存款利率为 2.75%%；\n");
    printf("\t5 年期定期存款利率为 3%%；\n");
    printf("\t活期存款利率为 0.35%%（按季度复利计息）。\n\n");
    printf("\t=========================== 请开始您的选择操作 ===========================\n\n");

    // 输入本金
    printf("\t请输入需要存款的本金（单位：元）：");
    if (scanf("%lf", &p) != 1 || p <= 0) {
        printf("\t输入无效！本金必须为正数。\n\n");
        return 1;
    }
    printf("\n\t您输入的本金是：%.2f 元。\n\n", p);

    // 选择方案
    printf("\t请选择5年期存款方案（输入数字1至5）：");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 5) {
        printf("\n\t输入无效！请选择 1 到 5 之间的数字。\n\n");
        return 1;
    }
    printf("\n");

    // 计算并输出结果
    switch (choice) {
        case 1: {
            printf("\t您选择的是（%d）方案：一次存 5 年期。\n\n", choice);
            sum = p * (1 + 0.03 * YEARS);
            break;
        }
        case 2: {
            printf("\t您选择的是（%d）方案：先存 2 年期，到期后将本息再存 3 年期。\n\n", choice);
            sum = p * (1 + 0.021 * 2) * (1 + 0.0275 * 3);
            break;
        }
        case 3: {
            printf("\t您选择的是（%d）方案：先存 3 年期，到期后将本息再存 2 年期。\n\n", choice);
            sum = p * (1 + 0.0275 * 3) * (1 + 0.021 * 2);
            break;
        }
        case 4: {
            printf("\t您选择的是（%d）方案：存 1 年期，连续转存 5 次。\n\n", choice);
            sum = p * pow(1 + 0.015, YEARS);
            break;
        }
        case 5: {
            printf("\t您选择的是（%d）方案：存活期存款（按季度复利计息）。\n\n", choice);
            sum = p * pow(1 + 0.0035 / 4, 4 * YEARS);
            break;
        }
    }

    printf("\t预计您的存款到期后本息合计：%.2f 元。\n\n", sum);
    printf("\t========================== 操作结束 感谢您的使用 ==========================\n\n");

    return 0;
}