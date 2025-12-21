//练习实现贷款还款月份计算程序

#include <stdio.h>
#include <math.h>

int main() {
    double loan_amount;      // 贷款总额（本金）
    double monthly_payment;  // 每月还款额
    double monthly_rate;     // 月利率（小数，如 0.005 = 0.5%）
    double months;           // 还款月数（保留一位小数）

    printf("\n\t请输入需要的贷款总额（单位：元）：");
    if (scanf("%lf", &loan_amount) != 1 || loan_amount <= 0) {
        printf("\t输入无效！贷款金额必须为正数。\n\n");
        return 1;
    }
    printf("\n\t您输入的贷款本金是：%.2f 元。\n\n", loan_amount);

    printf("\t请输入每月还款金额（单位：元）：");
    if (scanf("%lf", &monthly_payment) != 1 || monthly_payment <= 0) {
        printf("\t输入无效！还款金额必须为正数。\n\n");
        return 1;
    }
    printf("\n\t您输入的每月还款金额是：%.2f 元。\n\n", monthly_payment);

    printf("\t请输入贷款月利率（小数形式，如 0.005 表示 0.5%%）：");
    if (scanf("%lf", &monthly_rate) != 1 || monthly_rate <= 0) {
        printf("\t输入无效！贷款月利率必须为正数。\n\n");
        return 1;
    }
    printf("\n\t您输入的贷款月利率是：%.4f（即 %.2f%%）。\n\n", monthly_rate, monthly_rate * 100);

    // 关键校验：月供必须大于首月利息
    if (monthly_payment <= loan_amount * monthly_rate) {
        printf("\t错误：每月还款金额 %.2f 元 不足以支付首月利息 %.2f 元，贷款无法还清！\n\n",
               monthly_payment, loan_amount * monthly_rate);
        return 1;
    }

    // 计算还款月数
    months = log(monthly_payment / (monthly_payment - loan_amount * monthly_rate)) 
             / log(1 + monthly_rate);

    printf("\n\t您总计需要还款的月份数是：%.1f 个月。\n\n", months);

    return 0;
}