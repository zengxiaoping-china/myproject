//练习10：编写一个简单的计算器程序，支持加、减、乘、除四种运算。用户输入两个数字和一个运算符，程序输出计算结果。

#include<stdio.h>

int main(){

    double num1,num2,result;
    char op;
    char continue_choice;

    printf("============== 一个简单的计算器小程序 =================\n\n");
    printf("支持操作：+ (加)  - (减)  * (乘)  / (除)\n\n");
    printf("请输入格式：数字 运算符 数字（例如：3.5 + 2）\n\n");
    printf("=====================================================\n\n");

    do
    {
        printf("请输入表达式：");
        if(scanf("%lf %c %lf",&num1,&op,&num2) != 3){
            printf("❌ 输入格式错误！请按 '数字 运算符 数字' 格式输入。\n\n");
            // 清空输入缓冲区
            int c;
            while ((c=getchar()) !='\n' && c != EOF );
            continue;// 跳过本次循环，重新输入
        }
        
        //计算
        switch (op)
        {
        case '+':
            result = num1 + num2;
            printf("\n结果：%.2f + %.2f = %.2f\n",num1,num2,result);
            break;
        case '-':
            result = num1 - num2;
            printf("\n结果：%.2f - %.2f = %.2f\n",num1,num2,result);
            break;
        case '*':
        case 'x':
        case 'X':
            result = num1 * num2;
            printf("\n结果：%.2f x %.2f = %.2f\n",num1,num2,result);
            break;
        case '/':
            if (num2 == 0)
            {
                printf("❌ 错误：除数不能为零！\n\n");
            }else{
                result = num1 / num2;
                printf("\n结果：%.2f / %.2f = %.2f\n",num1,num2,result);
                }
            break;
        default:
                printf("❌ 不支持的运算符 '%c'！请使用 +、-、*、/。\n\n", op);
            break;
        }
        // 询问是否继续
        printf("\n是否继续计算？(y/n):");
        scanf(" %c",&continue_choice);
        printf("\n");
    } while (continue_choice == 'y' || continue_choice == 'Y');
    printf("👋 感谢使用！再见！\n");
    return 0;
}