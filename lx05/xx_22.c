/*给出一百分制成绩,要求输出成绩等级'A'.'B'.'C'.'D'、'E'。90分以上为'A',80~89分为'B' ,70~79分为'C ,60~69分为'D' ,60分以下为'E'。*/

#include <stdio.h>

int main() {
    int score;

    char grade,continue_choice;
    
    do  
    {
        printf("\n请输入成绩(0-100): ");
        if (scanf("%d", &score) != 1)
        {
            printf("\n输入无效，请输入一个整数成绩(0-100): ");
            while(getchar() != '\n'); // 清除输入缓冲区
            continue;
        }

        if (score >= 90 && score <= 100) {
            grade = 'A';
        } else if (score >= 80 && score < 90) {
            grade = 'B';
        } else if (score >= 70 && score < 80) {
            grade = 'C';
        } else if (score >= 60 && score < 70) {
            grade = 'D';
        } else if (score >= 0 && score < 60) {
            grade = 'E';
        } else {
            printf("输入的成绩无效！\n");
            return 1;
        }
        printf("成绩等级为: %c\n", grade);

        // 询问是否继续
        printf("\n是否继续计算？(y/n):");
        scanf(" %c",&continue_choice);
        printf("\n");
    } while (continue_choice == 'y' || continue_choice == 'Y');

    printf("👋 感谢使用！再见！\n");

    return 0;
}